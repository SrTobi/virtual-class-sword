#pragma once
#ifndef _VCS_BASENEGEVAL_HPP
#define _VCS_BASENEGEVAL_HPP


#include "base.hpp"
#include "baseEval.hpp"
#include "baseNeg.hpp"

struct BaseNegEval: public virtual BaseNeg, public virtual BaseEval
{
	typedef BaseEval::Expr Expr;

	template<typename _Out>
	struct Neg: public virtual BaseNeg::Neg<_Out>, public virtual BaseEval::Expr
	{
		typedef typename _Out::Expr out_expr;
		
		Neg(out_expr* right): BaseNeg::Neg<_Out>(right) {}

		virtual int eval() const { return -right->eval(); }
	};
	virtual Expr* new_neg(Expr* right) const { return new Neg<BaseNegEval>(right); }
};





#endif
