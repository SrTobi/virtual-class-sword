#pragma once
#ifndef _VCS_BASENEG_HPP
#define _VCS_BASENEG_HPP


#include "base.hpp"



struct BaseNeg: public Base
{
	template<typename _Out>
	struct Neg: public virtual Expr
	{
		typedef typename _Out::Expr out_expr;
		out_expr* right;
		Neg(out_expr* right): right(right) {}

		virtual std::string show() const { return "-" + right->show(); }
	};
	virtual Expr* new_neg(Expr* right) const { return new Neg<BaseNeg>(right); }
};








#endif