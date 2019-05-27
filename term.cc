#include "defs.h"

// using Term = std::vector<Elem>;

std::ostream& operator<<(std::ostream &out, const Term &vec) {
  if(vec.empty()) return out;
  if(vec.back().sym == Sym::minus) out << "- ";
  for(int i=0; i<vec.size(); ++i) out << vec[i] << " ";
  // out << vec[vec.size()-1];
  return out;
}

Term operator*(const Term &ops1, const Term &ops2) {
  Term ret = ops1;
  ret.insert(ret.end(), ops2.begin(), ops2.end());
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
