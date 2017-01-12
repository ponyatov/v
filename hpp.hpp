#ifndef _H_HPP
#define _H_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Sym {
	string val;
	Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual string head(); string pad(int); virtual string dump(int=0);
};

struct Vector: Sym { Vector(); string head(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) {yylval.o = new C(yytext); return X;}
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
