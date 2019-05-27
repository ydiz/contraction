#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <assert.h>
#include <utility>

int factorial(int n);


// sym.cc

enum class Sym {u, uBar, d, dBar, s, sBar, 
  a, b, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9,
  alpha, beta, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9,
  w, x, y, z, v, g5, gmu, gnu, gL, gR,
  Pu, Pd, Ps, 
  minus, null};

bool isQuark(Sym sym);
bool isNotQuark(Sym sym);
Sym bar(Sym q);
Sym prop(Sym q);
Sym get_color(); // get the next available color index
Sym get_spin(); // get the next available spin index
std::ostream& operator<<(std::ostream &out, Sym sym);
std::string str(Sym sym);
std::string str(const std::vector<Sym> &syms);

// elem.cc

struct Elem {
  Sym sym;
  std::vector<Sym> pos;
  std::vector<Sym> color;
  std::vector<Sym> spin;

  Elem();
  Elem(Sym _sym);
  Elem(Sym _sym, Sym _pos, Sym _color, Sym _spin); // for quark
  Elem(Sym _sym, std::vector<Sym> _spin); // for gamma matrix
  Elem(Sym _sym, std::vector<Sym> _pos, std::vector<Sym> _color, std::vector<Sym> _spin); // for propagator
  std::string str() const; // string representation
};

std::ostream& operator<<(std::ostream &out, const Elem &e);

// terms.cc
// using Term = std::vector<Elem>;
struct Term : public std::vector<Elem> {

  double coef;
  Term() : coef(1.0) {}
};

// bool hasMinus(const Term &term);
// void changeSign(Term &term);

Term operator*(const Term &ops1, const Term &ops2);
std::ostream& operator<<(std::ostream &out, const Term &term);
std::ostream& operator<<(std::ostream &out, const std::vector<Term> &terms);

// operator.cc
struct Op : public std::vector<Term> {}; // to distinguish between Op and vector<Term>

std::vector<Term> operator*(const Op &op1, const Op &op2);
std::vector<Term> operator*(const std::vector<Term> &terms, const Op &op);
std::vector<Term> operator*(const Op &op, const std::vector<Term> &terms);
std::ostream& operator<<(std::ostream &out, const Op &op);

Op Pi0(Sym pos);
Op K0(Sym pos);
Op Jmu(Sym pos, Sym q);
Op Jnu(Sym pos, Sym q);
Op Q1(Sym pos);


// contract.cc
std::vector<Term> contract(const Term &term, bool allowDisconnected = false);
std::vector<Term> contract(const std::vector<Term> &terms, bool allowDisconnected = false, bool verbose = false);


/////////////////////////////////////////////////
// misc

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &vec) {
  if(vec.empty()) { 
    out << "{}";
    return out;
  }
  out << "{";
  for(int i=0; i<vec.size()-1; ++i) out << vec[i] << ",";
  out << vec[vec.size()-1] << "}";
  return out;
}


template <class T, class U>
std::ostream& operator<<(std::ostream &out, const std::pair<T, U> &p) {
  out << "(" << p.first << ", " << p.second << ")";
  return out;
}
