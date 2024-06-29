#include <iostream>

#include "ExpressionCalculator.cpp"

int main()
{
	BooleanExpressionHandler be("((p)|((q)&(t)))");
	BooleanInterpretation bi;
	bi.set('p', true);
	std::cout << be.evaluate(bi) << std::endl;
	BooleanExpressionHandler be2("((p)|(!(p)))");
	BooleanExpressionHandler be3("((!(a))&(a))");
	std::cout << be3.isContradiction() << std::endl;
}