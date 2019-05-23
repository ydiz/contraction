#pragma once

#include <string>
#include <vector>
#include <unordered_map>

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &vec) {
  out << "{";
  for(int i=0; i<vec.size()-1; ++i) out << vec[i] << ",";
  out << vec[vec.size()-1] << "}";
  return out;
}


enum class Symbol {u, uBar, d, dBar, s, sBar, 
  a, b, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9,
  alpha, beta, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9,
  w, x, y, z, g5, gmu, gnu, null};

std::vector<Symbol> color_idx = {Symbol::c0, Symbol::c1, Symbol::c2, Symbol::c3, Symbol::c4, Symbol::c5, Symbol::c6, Symbol::c7, Symbol::c8, Symbol::c9};
std::vector<Symbol> spin_idx = {Symbol::s0, Symbol::s1, Symbol::s2, Symbol::s3, Symbol::s4, Symbol::s5, Symbol::s6, Symbol::s7, Symbol::s8, Symbol::s9};

std::unordered_map<Symbol, std::string> symStr = { {Symbol::u, "u"}, {Symbol::uBar, "uBar"},  
  {Symbol::a, "a"}, {Symbol::b, "b"}, {Symbol::c0, "c0"}, {Symbol::c1, "c1"}, {Symbol::c2, "c2"}, {Symbol::c3, "c3"}, {Symbol::c4, "c4"}, {Symbol::c5, "c5"}, {Symbol::c6, "c6"},{Symbol::c7, "c7"}, {Symbol::c8, "c8"}, {Symbol::c9, "c9"},
  {Symbol::alpha, "alpha"}, {Symbol::beta, "beta"}, {Symbol::s0, "s0"}, {Symbol::s1, "s1"}, {Symbol::s2, "s2"}, {Symbol::s3, "s3"}, {Symbol::s4, "s4"}, {Symbol::s5, "s5"}, {Symbol::s6, "s6"},{Symbol::s7, "s7"}, {Symbol::s8, "s8"}, {Symbol::s9, "s9"},
  {Symbol::w, "w"}, {Symbol::x, "x"}, {Symbol::y, "y"}, {Symbol::z, "z"}, 
  {Symbol::g5, "g5"}, {Symbol::gmu, "gmu"}, {Symbol::gnu, "gnu"} };

std::ostream& operator<<(std::ostream &out, Symbol sym) {
  out << symStr[sym];
  return out;
}

std::string str(Symbol sym) {
  return symStr[sym];
}


std::string str(const std::vector<Symbol> &syms) {
  std::string ret("");
  if(syms.empty()) return ret;
  else {
    // std::string ret = "{"
    for(int i=0; i<syms.size()-1; ++i) ret += str(syms[i]) + ",";
    ret += str(syms[syms.size()-1]);
  }
  return ret;
}
