#include "defs.h"

Op Pion(Sym pos, Sym q) {
  Op pi(3);

  Sym cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  pi[0] = Elem(bar(q), pos, cc, ss1);
  pi[1] = Elem(Sym::g5, {ss1, ss2});
  pi[2] = Elem(q, pos, cc, ss2);
  return pi;
}


Op Kaon(Sym pos) {
  Op K(3);

  Sym cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  K[0] = Elem(Sym::dBar, pos, cc, ss1);
  K[1] = Elem(Sym::g5, {ss1, ss2});
  K[2] = Elem(Sym::s, pos, cc, ss2);
  return K;
}

Op Jmu(Sym pos, Sym q) {
  Op pi(3);

  Sym cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  pi[0] = Elem(bar(q), pos, cc, ss1);
  pi[1] = Elem(Sym::gmu, {ss1, ss2});
  pi[2] = Elem(q, pos, cc, ss2);
  return pi;
}

Op Jnu(Sym pos, Sym q) {
  Op pi(3);

  Sym cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  pi[0] = Elem(bar(q), pos, cc, ss1);
  pi[1] = Elem(Sym::gnu, {ss1, ss2});
  pi[2] = Elem(q, pos, cc, ss2);
  return pi;
}


Op Q1(Sym pos) {
  Op q1(6);

  Sym c1 = get_color(), c2 = get_color();
  Sym s1 = get_spin(), s2 = get_spin(), s3 = get_spin(), s4 = get_spin();

  q1[0] = Elem(Sym::sBar, pos, c1, s1);
  q1[1] = Elem(Sym::gL, {s1, s2});
  q1[2] = Elem(Sym::d, pos, c1, s2);

  q1[3] = Elem(Sym::uBar, pos, c2, s3);
  q1[4] = Elem(Sym::gL, {s3, s4});
  q1[5] = Elem(Sym::u, pos, c2, s4);
  return q1;
}

