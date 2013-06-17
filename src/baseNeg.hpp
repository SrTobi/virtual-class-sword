#pragma once
#ifndef _VCS_BASENEG_HPP
#define _VCS_BASENEG_HPP


#include "base.hpp"



struct BaseNeg: public Base
{
	class Neg: public virtual Expr
	{
		Expr* right;
	public:
		Neg(Expr* right): right(right) {}
		virtual std::string show() const { return "-" + right->show(); }
	};
	virtual Neg* new_neg(Expr* right) const { return new Neg(right); }
};








#endif