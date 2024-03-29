#include "defs.h"
#include "cmath"

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

Op UBar_g5_u(Sym pos) {
  Op ubar_u;
  ubar_u.resize(1); // (ubar g5 u) has one terms

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = ubar_u[0];
  term1.coef = 1.;
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);
  return ubar_u;
}

Op DBar_g5_d(Sym pos) {
  Op dbar_d;
  dbar_d.resize(1); // (dbar g5 d) has one terms

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = dbar_d[0];
  term1.coef = 1.;
  term1.resize(3);
  term1[0] = Elem(Sym::dBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c, s2);
  return dbar_d;
}








Op Eta(Sym pos) {
  Op eta;
  eta.resize(3); // Pi0 has two terms

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = eta[0];
  term1.coef = 1. / std::sqrt(6);
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);

  Term &term2 = eta[1];
  term2.coef = 1. / std::sqrt(6);
  term2.resize(3);
  term2[0] = Elem(Sym::dBar, pos, c, s1);
  term2[1] = Elem(Sym::g5, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c, s2);

  Term &term3 = eta[2];
  term3.coef = - 2. / std::sqrt(6);
  term3.resize(3);
  term3[0] = Elem(Sym::sBar, pos, c, s1);
  term3[1] = Elem(Sym::g5, {s1, s2});
  term3[2] = Elem(Sym::s, pos, c, s2);
  return eta;
}




Op K0(Sym pos) { // dBar gamma5 s
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

Op K0bar(Sym pos) { // sBar gamma5 d
  Op K;
  K.resize(1);

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = K[0];
  // term1.coef = -1.; // Note: Fixed 03.16.2021. K0bar does not have minus sign
  term1.coef = 1.; 
  term1.resize(3);
  term1[0] = Elem(Sym::sBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::d, pos, c, s2);
  return K;
}


Op sBar_d(Sym pos) {
  Op sd;
  sd.resize(1);

  Sym c = get_color(), s1 = get_spin();

  Term &term1 = sd[0];
  term1.resize(2);
  term1[0] = Elem(Sym::sBar, pos, c, s1);
  term1[1] = Elem(Sym::d, pos, c, s1);
  return sd;
}

Op dBar_s(Sym pos) {
  Op ds;
  ds.resize(1);

  Sym c = get_color(), s1 = get_spin();

  Term &term1 = ds[0];
  term1.resize(2);
  term1[0] = Elem(Sym::dBar, pos, c, s1);
  term1[1] = Elem(Sym::s, pos, c, s1);
  return ds;
}

Op Jmu_no_s(Sym pos) {
  Op J;
  J.resize(2);

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

  return J;
}

Op Jnu_no_s(Sym pos) {
  Op J;
  J.resize(2);

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

  return J;
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

Op Q2_unmixed(Sym pos) { // after using Fierz symmetry  (bar{s} gamma_L u) (bar{u} gamma_L d)
  Op q2;
  q2.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q2[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::sBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::d, pos, c2, s4);
  return q2;
}


Op Q2_mixed(Sym pos) {  // without using Fierz symmetry // (bar{s} gamma_L d)_{c1,c2} (bar{u} gamma_L u)_{c2,c1}
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

Op Q2bar_unmixed(Sym pos) {
  Op q2;
  q2.resize(1);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  Term &term1 = q2[0];
  term1.coef = 1.;
  term1.resize(6);
  term1[0] = Elem(Sym::dBar, pos, c1, s1);
  term1[1] = Elem(Sym::gL, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c1, s2);

  term1[3] = Elem(Sym::uBar, pos, c2, s3);
  term1[4] = Elem(Sym::gL, {s3, s4});
  term1[5] = Elem(Sym::s, pos, c2, s4);
  return q2;
}



Op Q2bar_mixed(Sym pos) {
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

