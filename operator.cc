#include "defs.h"

// struct Op : public std::vector<Term> {};

std::ostream& operator<<(std::ostream &out, const Op &op) {
  for(int i=0; i<op.size(); ++i) out << op[i] << " ";
  return out;
}


std::vector<Term> operator*(const Op &op1, const Op &op2) {
  std::vector<Term> ret;
  for(int i=0; i<op1.size(); ++i)
    for(int j=0; j<op2.size(); ++j)
    {
      Term t = op1[i] * op2[j];
      ret.push_back(t);
    }
  return ret;
}


std::vector<Term> operator*(const std::vector<Term> &terms, const Op &op) {
  std::vector<Term> ret;
  for(int i=0; i<terms.size(); ++i)
    for(int j=0; j<op.size(); ++j)
    {
      Term t = terms[i] * op[j];
      ret.push_back(t);
    }
  return ret;
}

std::vector<Term> operator*(const Op &op, const std::vector<Term> &terms) {
  std::vector<Term> ret;
  for(int i=0; i<terms.size(); ++i)
    for(int j=0; j<op.size(); ++j)
    {
      Term t = terms[i] * op[j];
      ret.push_back(t);
    }
  return ret;
}



Op Pi0(Sym pos) {
  Op pi;
  pi.resize(2); // Pi0 has two terms

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = pi[0];
  term1.coef = 0.7071;
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);

  Term &term2 = pi[1];
  term2.coef = -0.7071;
  term2.resize(3);
  term2[0] = Elem(Sym::dBar, pos, c, s1);
  term2[1] = Elem(Sym::g5, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c, s2);
  term2.push_back(Sym::minus); // second term is negative

  return pi;
}


Op K0(Sym pos) {
  Op K;
  K.resize(1);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = K[0];
  term1.resize(3);
  term1[0] = Elem(Sym::dBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::s, pos, c, s2);
  return K;
}

Op Jmu(Sym pos, Sym q) {
  Op J;
  J.resize(1);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = J[0];
  term1.resize(3);
  term1[0] = Elem(bar(q), pos, c, s1);
  term1[1] = Elem(Sym::gmu, {s1, s2});
  term1[2] = Elem(q, pos, c, s2);
  return J;
}



Op Jnu(Sym pos, Sym q) {
  Op J;
  J.resize(1);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = J[0];
  term1.resize(3);
  term1[0] = Elem(bar(q), pos, c, s1);
  term1[1] = Elem(Sym::gnu, {s1, s2});
  term1[2] = Elem(q, pos, c, s2);
  return J;
}


//
// Op Jnu(Sym pos, Sym q) {
//   Op pi(3);
//
//   Sym c = get_color(), s1 = get_spin(), s2 = get_spin();
//   pi[0] = Elem(bar(q), pos, c, s1);
//   pi[1] = Elem(Sym::gnu, {s1, s2});
//   pi[2] = Elem(q, pos, c, s2);
//   return pi;
// }


Op Q1(Sym pos) {
  Op q1;
  q1.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q1[0];
  term1.resize(6);
  term1[0] = Elem(Sym::sBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c2, s4);
  return q1;
}


