#pragma once
#ifndef _VCS_BASE_HPP
#define _VCS_BASE_HPP

#include <string>


struct Base
{
	class Expr
	{
	public:
		virtual std::string show() const = 0;
	};

	class Const: public virtual Expr
	{
		int value;
	public:
		Const(int value	):value(value){}

		virtual std::string show() const { return std::to_string(value);}
	};
	virtual Const* new_Const(int value) const { return new Const(value); }

	class Add: public virtual Expr
	{
		Expr *left, *right;
	public:
		Add(Expr* left, Expr* right):left(left),right(right) {}

		virtual std::string show() const { return "(" + left->show() + " + " + right->show() + ")"; }
	};
	virtual Add* new_Add(Expr* left, Expr* right) const { return new Add(left, right); }
};




#endif