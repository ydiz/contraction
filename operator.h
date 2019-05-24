#pragma once


using Op = std::vector<Elem>;
using Term = std::vector<Elem>;

Op pion(Sym pos, Sym q) {
  Op pi(3);

  Sym cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  pi[0] = Elem(bar(q), pos, cc, ss1);
  pi[1] = Elem(Sym::g5, {ss1, ss2});
  pi[2] = Elem(q, pos, cc, ss2);
  return pi;
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

/////////////////////////

std::ostream& operator<<(std::ostream &out, const std::vector<Elem> &vec) {
  if(vec.empty()) return out;
  if(vec.back().sym == Sym::minus) out << "- ";
  for(int i=0; i<vec.size(); ++i) out << vec[i] << " ";
  // out << vec[vec.size()-1];
  return out;
}

std::vector<Elem> operator*(const std::vector<Elem> &ops1, const std::vector<Elem> &ops2) {
  std::vector<Elem> ret = ops1;
  ret.insert(ret.end(), ops2.begin(), ops2.end());
  return ret;
}
