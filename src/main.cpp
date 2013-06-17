#include <iostream>


#include "base.hpp"

void test_base()
{
	Base b;

	Base::Expr* expr = b.new_Add(b.new_Const(4), b.new_Const(10));

	std::cout << "Base[Expr::show]= " << expr->show() << std::endl;
}




#include "baseNeg.hpp"

void test_baseneg()
{
	BaseNeg b;

	Base::Expr* expr = b.new_neg(b.new_Add(b.new_Const(4), b.new_Const(10)));
	std::cout << "BaseNeg[Expr::show]= " << expr->show() << std::endl;
}




int main()
{
	test_base();
	test_baseneg();

#ifdef WIN32
	std::cin.get();
#endif

	return 0;
}