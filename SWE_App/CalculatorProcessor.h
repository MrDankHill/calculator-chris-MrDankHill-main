
#ifndef CALCULATOR_PROCESSOR_H
#define CALCULATOR_PROCESSOR_H

#include <string>
#include <stack>
#include <vector>

class CalculatorProcessor 
{
private:
    static CalculatorProcessor* instance;
    CalculatorProcessor() {}

public:
    static CalculatorProcessor* GetInstance();
    double Calculate(const std::string& expression);
    double ApplyBinaryOperation(const std::string& op, double left, double right);
    int GetOperatorPrecedence(const std::string& op);

    // New methods for the Shunting Yard Algorithm
    std::vector<std::string> Tokenize(const std::string& expression);
    bool IsOperator(const std::string& token);
    void ApplyOperator(std::stack<std::string>& operators, std::stack<double>& values);
};

#endif
