
#include "CalculatorProcessor.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <sstream>
#include <queue>

CalculatorProcessor* CalculatorProcessor::instance = nullptr;

CalculatorProcessor* CalculatorProcessor::GetInstance() 
{
    if (instance == nullptr) 
    {
        instance = new CalculatorProcessor();
    }
    return instance;
}

std::vector<std::string> CalculatorProcessor::Tokenize(const std::string& expression) 
{
    std::vector<std::string> tokens;
    std::string token;
    for (size_t i = 0; i < expression.length(); i++)
    {
        char current = expression[i];
        if (isdigit(current) || current == '.') 
        {
            token += current;
        }
        else 
        {
            if (!token.empty()) 
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, current));
        }
    }
    if (!token.empty()) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

double CalculatorProcessor::Calculate(const std::string& expression) 
{
    std::vector<std::string> tokens = Tokenize(expression);
    std::stack<std::string> operators;
    std::stack<double> values;

    for (const std::string& token : tokens) 
    {
        if (isdigit(token[0]))
        {
            values.push(std::stod(token));
        }
        else if (IsOperator(token))
        {
            while (!operators.empty() && GetOperatorPrecedence(operators.top()) >= GetOperatorPrecedence(token)) 
            {
                ApplyOperator(operators, values);
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) 
    {
        ApplyOperator(operators, values);
    }

    if (values.size() != 1) 
    {
        throw std::runtime_error("Invalid expression");
    }

    return values.top();
}

bool CalculatorProcessor::IsOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

void CalculatorProcessor::ApplyOperator(std::stack<std::string>& operators, std::stack<double>& values) 
{
    if (values.size() < 2) 
    {
        throw std::runtime_error("Invalid expression");
    }

    std::string op = operators.top();
    operators.pop();

    double right = values.top();
    values.pop();

    double left = values.top();
    values.pop();

    values.push(ApplyBinaryOperation(op, left, right));
}

double CalculatorProcessor::ApplyBinaryOperation(const std::string& op, double left, double right) 
{
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") 
    {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }
    if (op == "%") return fmod(left, right);
    throw std::runtime_error("Unknown binary operator");
}

int CalculatorProcessor::GetOperatorPrecedence(const std::string& op) 
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}
