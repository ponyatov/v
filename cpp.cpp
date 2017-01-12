#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return "<"+val+">"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=sel.begin(),e=sel.end();it!=e;it++)
		S += "\n"+pad(depth+1)+it->first+":"+it->second->dump(depth+2);
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Sym* Sym::lookup(string V) { auto X = sel.find(V);
	if (X==sel.end()) return NULL; else return X->second; }

Sym* Sym::eval(Sym*env) { Sym*E = env->lookup(val);
	if (E) return E; else return this; }

Sym* Sym::eq(Sym*o) { glob.sel[val]=o; return o; }

Vector::Vector():Sym("[]"){}
string Vector::head() { return val; }

Op::Op(string V):Sym(V){}
string Op::head() { return val; }
Sym* Op::eval(Sym*env) { Sym::eval(env);
	if (val=="=") return nest[0]->eq(nest[1]);
	return this;
}

Sym glob("glob");
void glob_init() {
//	glob.sel["add"] = new Sym("+++");
}
