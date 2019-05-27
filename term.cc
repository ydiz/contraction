#include "defs.h"

// using Term = std::vector<Elem>;

std::ostream& operator<<(std::ostream &out, const Term &term) {
  if(term.empty()) return out;
  if(term.back().sym == Sym::minus) out << "- ";
  for(int i=0; i<term.size(); ++i) out << term[i] << " ";
  return out;
}


std::ostream& operator<<(std::ostream &out, const std::vector<Term> &terms) {
  for(const auto &t: terms) out << t << std::endl;
  return out;
}

Term operator*(const Term &ops1, const Term &ops2) {
  int hasMinus=1;
  Term ops1_cp = ops1;
  Term ops2_cp = ops2;
  if(ops1_cp.back().sym==Sym::minus) {
    hasMinus *= -1;
    ops1_cp.pop_back();
  }
  if(ops2_cp.back().sym==Sym::minus) {
    hasMinus *= -1;
    ops2_cp.pop_back();
  }

  Term ret = ops1_cp;
  ret.insert(ret.end(), ops2_cp.begin(), ops2_cp.end());

  if(hasMinus == -1) ret.push_back(Sym::minus);
  return ret;
}


// positive -> negative; negative -> positive
void changeSign(Term &term) {
      if(term.back().sym != Sym::minus) term.push_back(Elem(Sym::minus)); // minus is at the rear and thus does not affect positions of q and qBar
      else term.pop_back();
}

// if the termm has a minus sign
bool hasMinus(const Term &term) {
  if(term.back().sym == Sym::minus) return true;
  else return false;
}
