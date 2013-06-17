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
	struct Const: public virtual Expr, public virtual Base::Const<BaseEval>
	{
		Const(int value	):Base::Const<BaseEval>(value){}

		virtual int eval() const { return value; }
	};
	virtual Expr* new_Const(int value) const { return new Const<BaseEval>(value); }

	template<typename _Out>
	struct Add: public virtual Expr, public virtual Base::Add<BaseEval>
	{
		Add(Expr* left, Expr* right):Base::Add<BaseEval>(left, right) {}

		virtual int eval() const { return left->eval() + right->eval(); }
	};
	virtual Expr* new_Add(Expr* left, Expr* right) const { return new Add<BaseEval>(left, right); }
};




#endif