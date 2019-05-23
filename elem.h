#pragma once

#include "sym.h"

struct Elem {
  Symbol sym;
  std::vector<Symbol> pos;
  std::vector<Symbol> color;
  std::vector<Symbol> spin;

  Elem();
  Elem(Symbol _sym, Symbol _pos, Symbol _color, Symbol _spin); // for quark
  Elem(Symbol _sym, std::vector<Symbol> _spin); // for gamma matrix
  std::string str() const; // string representation
};

Elem::Elem() {}

Elem::Elem(Symbol _sym, Symbol _pos, Symbol _color, Symbol _spin) : sym(_sym), pos({_pos}), color({_color}), spin({_spin}) {}

Elem::Elem(Symbol _sym, std::vector<Symbol> _spin) : sym(_sym), spin(_spin) {}

std::string Elem::str() const {
  std::string ret = ::str(sym);
  if(!pos.empty()) ret += "(" + ::str(pos) + ")";
  ret += "_{";
  if(!color.empty()) ret += ::str(color) + ", ";
  ret += ::str(spin) + "}"; // every element has spin index
  return ret;
}


std::ostream& operator<<(std::ostream &out, const Elem &e) {
  out << e.str(); 
  return out;
}


std::ostream& operator<<(std::ostream &out, const std::vector<Elem> &vec) {
  for(int i=0; i<vec.size()-1; ++i) out << vec[i] << " ";
  out << vec[vec.size()-1];
  return out;
}

std::vector<Elem> operator*(const std::vector<Elem> &ops1, const std::vector<Elem> &ops2) {
  std::vector<Elem> ret = ops1;
  ret.insert(ret.end(), ops2.begin(), ops2.end());
  return ret;
}

using Op = std::vector<Elem>;


