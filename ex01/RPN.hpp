#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN 
{
	private:
	enum
	{
		STACK_MUST_BE_EMPTY,
		STACK_CANT_BE_EMPTY
	};

	static std::stack<float> _stack;

		RPN();
		RPN( RPN const & rhs );
		RPN & operator=( RPN const & rhs );
		~RPN();

		static void IsEmptyString(std::string string);
		static void CheckStack(int condition);
		static bool IsSign(char &i);
		static void HandleSigns(char &sign);
		static float GetTopNumber();
		static void HandleWrongInput();
	public:
		static void calculate(const std::string &string );
};

#endif
