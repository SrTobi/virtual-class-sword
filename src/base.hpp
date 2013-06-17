#pragma once
#ifndef _VCS_BASE_HPP
#define _VCS_BASE_HPP

#include <string>


struct Base
{
	struct Expr
	{
		virtual std::string show() const = 0;
	};

	template<typename _Out>
	struct Const: public virtual Expr
	{
		int value;
		Const(int value	):value(value){}

		virtual std::string show() const { return std::to_string(value);}
	};
	virtual Expr* new_Const(int value) const { return new Const<Base>(value); }

	template<typename _Out>
	struct Add: public virtual Expr
	{
		typedef typename _Out::Expr out_expr;
		out_expr *left, *right;
		Add(out_expr* left, out_expr* right):left(left),right(right) {}

		virtual std::string show() const { return "(" + left->show() + " + " + right->show() + ")"; }
	};
	virtual Expr* new_Add(Expr* left, Expr* right) const { return new Add<Base>(left, right); }
};




#endif