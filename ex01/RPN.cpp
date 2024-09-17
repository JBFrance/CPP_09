#include <sstream>
#include "RPN.hpp"

std::stack<float> RPN::_stack;

void RPN::calculate(const std::string &input_string) 
{
    std::stringstream ss;
    ss << input_string;

    std::string string;
    
    while (ss >> string) 
	{
        IsEmptyString(string);
        if(IsSign(string[0]))
            HandleSigns(string[0]);
        else if (isdigit(string[0]))
            _stack.push(std::atof(string.c_str()));
        else
            HandleWrongInput();
    }
    CheckStack(STACK_CANT_BE_EMPTY);
    float res = _stack.top();
    _stack.pop();
    CheckStack(STACK_MUST_BE_EMPTY);
    std::cout << res << std::endl;
    return ;
}

void RPN::IsEmptyString(std::string string) 
{
    if (string.size() != 1) 
	{
        std::cout << "wrong input" << std::endl;
        exit(1);
    }
}

RPN::RPN() 
{

}

RPN::~RPN() 
{

}

void RPN::CheckStack(int condition) 
{
    switch (condition) 
	{
        case STACK_CANT_BE_EMPTY:
            if (_stack.empty()) 
			{
                std::cout << "wrong input" << std::endl;
                exit(1);
            }
            break;
        case STACK_MUST_BE_EMPTY:
            if (!_stack.empty()) 
			{
                std::cout << "wrong input" << std::endl;
                exit(1);
            }
            break;
        default:
            break;
    }
}

bool RPN::IsSign(char &i) 
{
    if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%')
        return true;
    return false;
}

void RPN::HandleSigns(char &sign) 
{

    switch (sign) 
	{
        case '+': 
		{
            float num2 = GetTopNumber();
            float num1 = GetTopNumber();
            _stack.push(num1 + num2);
            }
            break;
        case '-': 
		{
            float num2 = GetTopNumber();
            float num1 = GetTopNumber();
            _stack.push(num1 - num2);
            }
            break;
        case '*': 
		{
            float num2 = GetTopNumber();
            float num1 = GetTopNumber();
            _stack.push(num1 * num2);
            }
            break;
        case '/': 
		{
            float num2 = GetTopNumber();
            float num1 = GetTopNumber();
            if (num2 == 0) 
			{
                std::cout << "divide by 0, dummy" << std::endl;
                exit(1);
            }
            _stack.push(num1 / num2);
            }
            break;
    }
}

float RPN::GetTopNumber() 
{
    CheckStack(STACK_CANT_BE_EMPTY);
    float number = _stack.top();
    _stack.pop();
    return number;
}

void RPN::HandleWrongInput() 
{
    std::cout << "wrong input" << std::endl;
    exit(1);
}
