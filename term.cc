#include "defs.h"


// struct Term : public std::vector<Elem> {
//
//   double coef;
//   Term() : coef(1.0) {}
// };
//



Term operator*(const Term &term1, const Term &term2) {

  Term ret = term1;
  ret.coef *= term2.coef;
  ret.insert(ret.end(), term2.begin(), term2.end());

  return ret;
}

std::ostream& operator<<(std::ostream &out, const Term &term) {
  if(term.empty()) return out;
  
  if(term.coef==1.) ;
  else if(term.coef==-1.) out << "- ";
  else out << term.coef << " ";

  if(!term.spinSingletDelimiter.empty()) out << "[ ";

  for(int i=0; i<term.size(); ++i) {
    if(std::find(term.spinSingletDelimiter.begin(), term.spinSingletDelimiter.end(), i) != term.spinSingletDelimiter.end())
          out << "] [ ";
    out << term[i] << " ";
  }

  if(!term.spinSingletDelimiter.empty()) out << "]";
  return out;
}


std::ostream& operator<<(std::ostream &out, const std::vector<Term> &terms) {
  for(const auto &t: terms) out << t << std::endl;
  return out;
}



