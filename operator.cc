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

// // not okay. We want different terms in an Op to share the same set of indicies
// Term singlet(Sym pos, Sym qBar, Sym gamma, Sym q) {
//   Term term(3);
//   Sym c = get_color(), s1 = get_spin(), s2 = get_spin();
//   term[0] = Elem(qBar, pos, c, s1);
//   term[1] = Elem(gamma, {s1, s2});
//   term[2] = Elem(q, pos, c, s2);
//   return term;
// }


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

Op K0bar(Sym pos) {
  Op K;
  K.resize(1);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = K[0];
  term1.resize(3);
  term1[0] = Elem(Sym::sBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c, s2);
  return K;
}



Op Jmu(Sym pos) {
  Op J;
  J.resize(3);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = J[0];
  term1.coef = 2./3.;
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::gmu, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);

  Term &term2 = J[1];
  term2.coef = -1./3.;
  term2.resize(3);
  term2[0] = Elem(Sym::dBar, pos, c, s1);
  term2[1] = Elem(Sym::gmu, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c, s2);

  Term &term3 = J[2];
  term3.coef = -1./3.;
  term3.resize(3);
  term3[0] = Elem(Sym::sBar, pos, c, s1);
  term3[1] = Elem(Sym::gmu, {s1, s2});
  term3[2] = Elem(Sym::s, pos, c, s2);
  return J;
}

Op Jnu(Sym pos) {
  Op J;
  J.resize(3);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = J[0];
  term1.coef = 2./3.;
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::gnu, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);

  Term &term2 = J[1];
  term2.coef = -1./3.;
  term2.resize(3);
  term2[0] = Elem(Sym::dBar, pos, c, s1);
  term2[1] = Elem(Sym::gnu, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c, s2);

  Term &term3 = J[2];
  term3.coef = -1./3.;
  term3.resize(3);
  term3[0] = Elem(Sym::sBar, pos, c, s1);
  term3[1] = Elem(Sym::gnu, {s1, s2});
  term3[2] = Elem(Sym::s, pos, c, s2);
  return J;
}


Op Q1(Sym pos) {
  Op q1;
  q1.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q1[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::sBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c2, s4);
  return q1;
}

Op Q1bar(Sym pos) {
  Op q1;
  q1.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q1[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::dBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::s, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c2, s4);
  return q1;
}




Op Q2(Sym pos) {
  Op q2;
  q2.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q2[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::sBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c2, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c1, s4);
  return q2;
}


Op Q2bar(Sym pos) {
  Op q2;
  q2.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q2[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::dBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::s, pos, c2, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c1, s4);
  return q2;
}




Op Q3(Sym pos) {
  Op q3;
  q3.resize(3);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q3[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::sBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::u, pos, c2, s4);

  Term &term2 = q3[1];
  term2.coef = 1.;
  term2.resize(6);
  term2[0] = Elem(Sym::sBar, pos, c1, s1);
  term2[1] = Elem(Sym::gL, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c1, s2);

  term2[3] = Elem(Sym::dBar, pos, c2, s3);
  term2[4] = Elem(Sym::gL, {s3, s4});
  term2[5] = Elem(Sym::d, pos, c2, s4);

  Term &term3 = q3[2];
  term3.coef = 1.;
  term3.resize(6);
  term3[0] = Elem(Sym::sBar, pos, c1, s1);
  term3[1] = Elem(Sym::gL, {s1, s2});
  term3[2] = Elem(Sym::d, pos, c1, s2);

  term3[3] = Elem(Sym::sBar, pos, c2, s3);
  term3[4] = Elem(Sym::gL, {s3, s4});
  term3[5] = Elem(Sym::s, pos, c2, s4);

  return q3;
}

