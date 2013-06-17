#pragma once
#ifndef _VCS_BASENEG_HPP
#define _VCS_BASENEG_HPP


#include "base.hpp"



struct BaseNeg: public Base
{
	template<typename _Out>
	struct Neg: public virtual Expr
	{
		typename _Out::Expr* right;
		Neg(Expr* right): right(right) {}

		virtual std::string show() const { return "-" + right->show(); }
	};
	virtual Expr* new_neg(Expr* right) const { return new Neg<BaseNeg>(right); }
};








#endif