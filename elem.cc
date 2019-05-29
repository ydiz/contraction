#include "defs.h"

Elem::Elem() {}

Elem::Elem(Sym _sym) : sym(_sym) {}

Elem::Elem(Sym _sym, Sym _pos, Sym _color, Sym _spin) : sym(_sym), pos({_pos}), color({_color}), spin({_spin}) {}

Elem::Elem(Sym _sym, std::vector<Sym> _spin) : sym(_sym), spin(_spin) {}

Elem::Elem(Sym _sym, std::vector<Sym> _pos, std::vector<Sym> _color, std::vector<Sym> _spin) : sym(_sym), pos(_pos), color(_color), spin(_spin) {}

std::string Elem::str() const {
  if(sym==Sym::minus) return "xxx"; // Sym::minus is used at the end of a term or Op to mark that this term should have a minus sign

  std::string ret = ::str(sym);
  if(!pos.empty()) ret += "(" + ::str(pos) + ")";
  ret += "_{";
  if(!color.empty()) ret += ::str(color) + ", ";
  ret += ::str(spin) + "}"; // every element has spin index
  return ret;
}

/////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &out, const Elem &e) {
  out << e.str(); 
  return out;
}


