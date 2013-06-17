#pragma once
#ifndef _VCS_BASEEVAL_HPP
#define _VCS_BASEEVAL_HPP


#include "base.hpp"


struct BaseEval: public virtual Base
{
	struct Expr: public virtual Base::Expr
	{
		virtual int eval() const = 0;
	};

	template<typename _Out>
	struct Const: public virtual Expr, public virtual Base::Const<_Out>
	{
		typedef typename _Out::Expr out_expr;
		Const(int value	):Base::Const<_Out>(value){}

		virtual int eval() const { return this->value; }
	};
	virtual Expr* new_Const(int value) const { return new Const<BaseEval>(value); }

	template<typename _Out>
	struct Add: public virtual Expr, public virtual Base::Add<_Out>
	{
		typedef typename _Out::Expr out_expr;
		Add(out_expr* left, out_expr* right):Base::Add<_Out>(left, right) {}

		virtual int eval() const { return this->left->eval() + this->right->eval(); }
	};
	virtual Expr* new_Add(Expr* left, Expr* right) const { return new Add<BaseEval>(left, right); }
};




#endif
