#include <iostream>
#include <vector>
#include <stack>

std::vector<std::string> split(std::string str)
{
    std::string current;
    std::vector<std::string> result;
    int count = 0;
    for (char ch : str)
    {
        if (ch != ' ')
        {
            current += ch;
        }
        else
        {
            if (!current.empty())
            {
                result.push_back(current);
                current = "";
            }
        }
    }
    if (!current.empty())
        result.push_back(current);
    return result;
}

std::string convert(std::string expression)
{
    std::vector<std::string> splited = split(expression);
    std::stack<std::string> s;
    std::string result;

    for (auto &c : splited)
    {
        if (c != "+" &&
            c != "-" &&
            c != "*" &&
            c != "/" &&
            c != "%" &&
            c != "^")
        {
            s.push(c);
        }
        else
        {
            std::string val1 = s.top();
            s.pop();
            std::string val2 = s.top();
            s.pop();

            result = "( " + val2 + " " + c + " " + val1 + " )";
            s.push(result);
        }
    }
    return s.top();
}

int main()
{
    std::string expression;
    std::cout << "Enter postfix expression:" << std::endl;
    std::getline(std::cin, expression);

    std::cout << "The infix of " << expression << " is " << convert(expression) << std::endl;
}