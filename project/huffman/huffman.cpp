#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

class Node
{
public:
    unsigned char data;
    int frequency;
    Node *left, *right;

    Node(unsigned char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    Node(Node *left, Node *right) : data(0), frequency(left->frequency + right->frequency), left(left), right(right) {}
};

class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->frequency > b->frequency;
    }
};

void generateCode(Node *root, std::string code, std::string codes[256])
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        codes[root->data] = code;
        return;
    }

    generateCode(root->left, code + "0", codes);
    generateCode(root->right, code + "1", codes);
}

std::vector<unsigned char> packBits(const std::string& encoded, unsigned char& padding )
{
    std::vector<unsigned char> result;

    unsigned char buffer = 0;
    int bitCount = 0;

    for (char bit : encoded)
    {
        buffer <<= 1;

        if (bit == '1')
        {
            buffer |= 1;
        }

        bitCount++;

        if (bitCount == 8)
        {
            result.push_back(buffer);

            buffer = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0)
    {
        padding = 8 - bitCount;

        buffer <<= padding;

        result.push_back(buffer);
    }
    else
    {
        padding = 0;
    }

    return result;
}

void compress(std::string src, std::string dst)
{
    std::ifstream file(src, std::ios::binary);
    std::vector<unsigned char> data;
    char byte;

    while (file.get(byte))
    {
        data.push_back(static_cast<unsigned char>(byte));
    }
    int frequency[256] = {0};

    for (auto i : data)
    {
        frequency[i]++;
    }

    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] != 0)
        {
            Node *node = new Node(i, frequency[i]);
            pq.push(node);
        }
    }
    if (pq.empty())
    {
        std::cout << "File is empty";
        return;
    }
    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *Parent = new Node(left, right);
        pq.push(Parent);
    }

    Node *root = pq.top();
    std::string codes[256];
    generateCode(root, "", codes);
    std::string encoded;

    for (unsigned char byte : data)
    {
        encoded += codes[byte];
    }

    unsigned char padding;
    std::vector<unsigned char> compressed = packBits(encoded, padding);
    std::ofstream output(dst, std::ios::binary);
    output.write("HUF1", 4);
    output.write( reinterpret_cast<char*>(&padding), sizeof(padding));
    output.write( reinterpret_cast<char*>(frequency), sizeof(frequency));
    output.write( reinterpret_cast<char*>(compressed.data()), compressed.size());

    output.close();


    std::cout << "Compression successful!\n";
    std::cout << "Original size: " << data.size() << " bytes\n";
    std::cout << "Compressed size: " << compressed.size() << " bytes\n";
}

void decompress(std::string src, std::string dst)
{
    std::ifstream file(src, std::ios::binary);
    char magic[4];

    file.read(magic, 4);

    if (std::string(magic, 4) != "HUF1")
    {
        std::cerr << "Invalid Huffman file\n";
        return;
    }

    unsigned char padding;
    file.read(reinterpret_cast<char*>(&padding),sizeof(padding));

    int frequency[256];
    file.read(reinterpret_cast<char*>(frequency), sizeof(frequency));

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            Node* node = new Node(
                static_cast<unsigned char>(i),
                frequency[i]
            );

            pq.push(node);
        }
    }
    while (pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(left, right);

        pq.push(parent);
    }

    Node* root = pq.top();

    std::vector<unsigned char> compressed;
    char byte;
    while (file.get(byte))
    {
        compressed.push_back(
            static_cast<unsigned char>(byte)
        );
    }

    file.close();
    std::ofstream output(dst, std::ios::binary);

    if (root->left == nullptr &&
        root->right == nullptr)
    {
        for (int i = 0; i < frequency[root->data]; i++)
        {
            output.put(
                static_cast<char>(root->data)
            );
        }

        output.close();

        std::cout << "Decompression successful!\n";

        return;
    }
    Node* current = root;

    int totalBytes = 0;

    for (unsigned char byte : compressed)
    {
        for (int bit = 7; bit >= 0; bit--)
        {
            // Ignore padding bits at the end
            if (
                &byte == &compressed.back() &&
                bit < padding
            )
            {
                break;
            }

            int value = (byte >> bit) & 1;

            if (value == 0)
                current = current->left;
            else
                current = current->right;


            // Reached a character
            if (current->left == nullptr &&
                current->right == nullptr)
            {
                output.put(
                    static_cast<char>(current->data)
                );

                totalBytes++;

                current = root;
            }
        }
    }

    output.close();

    std::cout << "Decompression successful!\n";
    std::cout << "Original size: " << totalBytes << " bytes\n";
}


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "./huffman <-c|-d> <src> <dst>" << std::endl;
        return 1;
    }

    std::string op = argv[1];
    std::string src = argv[2];
    std::string dst = argv[3];

    if (op == "-c" || op == "-C")
        compress(src, dst);

    else if (op == "-d" || op == "-D")
        decompress(src, dst);

    else
    {
        std::cout << "Invalid Operation";
        return 1;
    }
}