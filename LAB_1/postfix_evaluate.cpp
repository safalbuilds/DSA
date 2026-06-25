#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

using std::string, std::stack, std::cout, std::endl, std::cin, std::vector;

// 5454++_

vector<string> split(string str)
{
    string current;
    vector<string> result;
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

double evaluate(vector<string> expression)
{
    stack<double> s;
    double result;
    // cout << expression;
    for (auto &c : expression)
    {
        if (c != "+" &&
            c != "-" &&
            c != "*" &&
            c != "/" &&
            c != "%" &&
            c != "^")
        {
            s.push(stod(c));
        }
        else
        {
            double val1 = s.top();
            s.pop();
            double val2 = s.top();
            s.pop();

            if (c == "+")
                result = val2 + val1;
            else if (c == "-")
                result = val2 - val1;
            else if (c == "*")
                result = val2 * val1;
            else if (c == "/")
                result = val2 / val1;
            else if (c == "%")
                result = (int) val2 % (int) val1;
            else if (c == "^")
                result = pow(val2, val1);

            s.push(result);
        }
    }
    return s.top();
}

int main()
{
    string expression;

    cout << "Enter the postfix expression:" << endl;
    std::getline(cin, expression);

    vector<string> splitted = split(expression);

    double result = evaluate(splitted);
    cout << "The result of " << expression << " is " << result << endl;
}