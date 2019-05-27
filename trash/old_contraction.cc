#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "sym.h"


struct Elem {
  Symbol sym;
  std::vector<Symbol> pos;
  std::vector<Symbol> color;
  std::vector<Symbol> spin;

  Elem(Symbol _sym);
  virtual std::string type() const = 0;
  virtual std::string str() const = 0; // string representation
};

Elem::Elem(Symbol _sym) : sym(_sym) {};


struct Quark : public Elem {
  // Symbol pos;
  // Symbol color;
  // Symbol spin;

  Quark(Symbol _sym, Symbol _pos, Symbol _color, Symbol _spin);
  std::string type() const override;
  std::string str() const override;
};


Quark::Quark(Symbol _sym, Symbol _pos, Symbol _color, Symbol _spin) : Elem(_sym), pos({_pos}), color({_color}), spin({_spin}) {};

std::string Quark::type() const {
  return "quark";
}
std::string Quark::str() const {
  return ::str(sym) + "(" + ::str(pos[0]) + ")_{" + ::str(color[0]) + ", "  + ::str(spin[0]) + "}";
}







struct Operator {
  Symbol sym;
  Symbol pos; // position: w, x, y, z
  std::vector<Symbol> sub; // subscript
  Operator(Symbol _sym, Symbol _pos, const std::vector<Symbol> &_sub);
  Operator(Symbol _sym, const std::vector<Symbol> &_sub);
};

Operator::Operator(Symbol _sym, Symbol _pos, const std::vector<Symbol> &_sub) : sym(_sym), pos(_pos), sub(_sub) {};

// no position, like gammas
Operator::Operator(Symbol _sym, const std::vector<Symbol> &_sub) : sym(_sym), pos(null), sub(_sub) {};

std::ostream& operator<<(std::ostream &out, const Operator &op) {
  out << op.sym; 
  if(op.pos!=null) out << "(" << op.pos << ")";
  out << "_" << op.sub;
  return out;
}


using Term = std::vector<Operator>;

std::ostream& operator<<(std::ostream &out, const std::vector<Operator> &vec) {
  for(int i=0; i<vec.size()-1; ++i) out << vec[i] << " ";
  out << vec[vec.size()-1];
  return out;
}

std::vector<Operator> operator*(const std::vector<Operator> &ops1, const std::vector<Operator> &ops2) {
  std::vector<Operator> ret = ops1;
  ret.insert(ret.end(), ops2.begin(), ops2.end());
  return ret;
}

using namespace std;

int main() {

  // Operator u1(u, x, {alpha, a});
  // Operator g1(g5, {alpha, beta});
  // Operator u2(u, x, {beta, a});
  //
  // Operator u3(u, y, {gamma, b});
  // Operator g2(g5, {gamma, delta});
  // Operator u4(u, y, {delta, b});
  //
  // Term pi1 {u1, g1, u2};
  // Term pi2 {u3, g2, u4};

  // cout << pi1 * pi2 << endl;
  //
  //
  Elem *u1 = new Quark(u, x, a, alpha);
  cout << u1->str() << endl;
  cout << u1->color << endl;

	return 0;
}
