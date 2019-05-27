#include "defs.h"

// struct Op : public std::vector<Term> {};

std::ostream& operator<<(std::ostream &out, const Op &op) {
  for(int i=0; i<op.size(); ++i) out << op[i] << " ";
  return out;
}


Op Pi0(Sym pos) {
  Op pi;
  pi.resize(2); // Pi0 has two terms

  Sym c = get_color(), s1 = get_spin(), s2 = get_spin();

  Term &term1 = pi[0];
  term1.resize(3);
  term1[0] = Elem(Sym::uBar, pos, c, s1);
  term1[1] = Elem(Sym::g5, {s1, s2});
  term1[2] = Elem(Sym::u, pos, c, s2);

  Term &term2 = pi[1];
  term2.resize(3);
  term2[0] = Elem(Sym::dBar, pos, c, s1);
  term2[1] = Elem(Sym::g5, {s1, s2});
  term2[2] = Elem(Sym::d, pos, c, s2);
  term2.push_back(Sym::minus); // second term is negative

  return pi;
}


// Op Kaon(Sym pos) {
//   Op K(3);
//
//   Sym c = get_color(), s1 = get_spin(), s2 = get_spin();
//   K[0] = Elem(Sym::dBar, pos, c, s1);
//   K[1] = Elem(Sym::g5, {s1, s2});
//   K[2] = Elem(Sym::s, pos, c, s2);
//   return K;
// }
//
// Op Jmu(Sym pos, Sym q) {
//   Op pi(3);
//
//   Sym c = get_color(), s1 = get_spin(), s2 = get_spin();
//   pi[0] = Elem(bar(q), pos, c, s1);
//   pi[1] = Elem(Sym::gmu, {s1, s2});
//   pi[2] = Elem(q, pos, c, s2);
//   return pi;
// }
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
//
//
// Op Q1(Sym pos) {
//   Op q1(6);
//
//   Sym c1 = get_color(), c2 = get_color();
//   Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();
//
//   q1[0] = Elem(Sym::sBar, pos, c1, s1);
//   q1[1] = Elem(Sym::gL, {s1, s2});
//   q1[2] = Elem(Sym::d, pos, c1, s2);
//
//   q1[3] = Elem(Sym::uBar, pos, c2, s3);
//   q1[4] = Elem(Sym::gL, {s3, s4});
//   q1[5] = Elem(Sym::u, pos, c2, s4);
//   return q1;
// }
//

// void printOp(const Op &op) {
//   for(int i=0; i<op.size(); ++i) std::cout << op[i] << " " << std::endl;
// }

