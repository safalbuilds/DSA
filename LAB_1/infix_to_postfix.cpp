#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

std::unordered_map<std::string, int> priority = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}, {"(", 0}, {")", 0}};

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
    std::vector<std::string> splitted = split(expression);
    std::vector<std::string> post_fix;
    std::stack<std::string> s;
    std::string post_fix_exp;
    for (auto &ch : splitted)
    {
        if (ch == "(")
        {
            s.push(ch);
        }
        else if (ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "^")
        {
            if (!s.empty())
            {
                if (priority[s.top()] >= priority[ch])
                {
                    post_fix.push_back(s.top());
                    s.pop();
                    s.push(ch);
                }
                else
                {
                    s.push(ch);
                }
            }
            else
            {
                s.push(ch);
            }
        }
        else if (ch == ")")
        {
            while (s.top() != "(")
            {
                post_fix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else
        {
            post_fix.push_back(ch);
        }
    }
    while (!s.empty())
    {
        auto ch = s.top();
        s.pop();
        post_fix.push_back(ch);
    }
    for (auto &ch : post_fix)
    {
        post_fix_exp += ch + ' ';
    }
    
    return post_fix_exp;
}
int main()
{
    std::string expression;

    std::cout << "Enter the expression:" << std::endl;
    std::getline(std::cin, expression);

    std::string result = convert(expression);

    std::cout << "The posttfix of " << expression << " is " << result << std::endl;
}