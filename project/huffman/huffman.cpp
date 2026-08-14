#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Node
{
    unsigned char ch;
    int freq;
    Node *left, *right;

    Node(unsigned char c, int f): ch(c), freq(f)
    {left = right = nullptr;}

    Node(Node *l, Node *r): ch(0), left(l), right(r)
    {freq = l->freq + r->freq;}
};

struct compareFreq
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void buildCodes(Node *node, string path, string codes[256])
{
    if (!node)
        return;

    if (!node->left && !node->right)
    {
        codes[node->ch] = path;
        return;
    }

    buildCodes(node->left, path + "0", codes);
    buildCodes(node->right, path + "1", codes);
}

Node *buildTree(int freq[256])
{
    priority_queue<Node *, vector<Node *>, compareFreq> pq;

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
            pq.push(new Node((unsigned char)i, freq[i]));
    }

    if (pq.empty())
        return nullptr;

    while (pq.size() > 1)
    {
        Node *a = pq.top();
        pq.pop();
        Node *b = pq.top();
        pq.pop();
        pq.push(new Node(a, b));
    }

    return pq.top();
}

void compress(string src, string dst)
{
    ifstream in(src, ios::binary);
    vector<unsigned char> bytes;
    char c;
    while (in.get(c))
    {
        bytes.push_back((unsigned char)c);
    }
    int freq[256] = {0};
    for (unsigned char b : bytes)
    {
        freq[b]++;
    }

    Node *root = buildTree(freq);

    if (!root)
    {
        cout << "Empty file\n";
        return;
    }

    ofstream out(dst, ios::binary);
    string codes[256];
    buildCodes(root, "", codes);
    out.write((char *)freq, sizeof(freq));
    for (unsigned char b : bytes)
    {
        out.write(codes[b].c_str(), codes[b].length());
    }
    cout << "Compressed "<< bytes.size()<< " bytes\n";
}

void decompress(string src, string dst)
{
    ifstream in(src, ios::binary);
    if (!in)
    {
        cout << "Can't open " << src << "\n";
        return;
    }

    int freq[256];
    in.read((char *)freq, sizeof(freq));
    Node *root = buildTree(freq);
    if (!root)
    {
        ofstream out(dst, ios::binary);
        cout << "Decompressed empty file\n";
        return;
    }

    ofstream out(dst, ios::binary);
    if (!root->left && !root->right)
    {
        for (int i = 0; i < freq[root->ch]; i++)
        {
            out.put((char)root->ch);
        }

        cout << "Decompressed " << freq[root->ch] << " bytes\n";
        return;
    }

    Node *cur = root;
    char bit;
    int written = 0;

    while (in.get(bit))
    {
        if (bit == '0')
            cur = cur->left;
        else if (bit == '1')
            cur = cur->right;
        else
            continue;

        if (!cur->left && !cur->right)
        {
            out.put((char)cur->ch);
            written++;
            cur = root;
        }
    }

    cout << "Decompressed " << written << " bytes\n";
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Usage: ./huffman <-c/-d> <src> <dst>\n";
        return 1;
    }

    string mode = argv[1];
    string src = argv[2];
    string dst = argv[3];

    if (mode == "-c" || mode == "-C")
        compress(src, dst);
    else if (mode == "-d" || mode == "-D")
        decompress(src, dst);
    else
        cout << "Unknown mode. Use -c or -d\n";
    return 0;
}