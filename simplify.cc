#include "defs.h"


//if current Jmu or Jnu is self-connected, remove that term (SU(3) flavor symmetry)
static bool JmuSelfConnected(const Term &term) { 
  for(int i=0; i<term.size(); ++i) {
    const Elem &e = term[i];
    if(isProp(e.sym) && ((e.pos[0]==Sym::u &&e.pos[1]==Sym::u) || (e.pos[0]==Sym::v &&e.pos[1]==Sym::v))) return true;
  }
  return false;
}

void removeJmuSelfConnected(std::vector<Term> &terms) {
  terms.erase(std::remove_if(terms.begin(), terms.end(), JmuSelfConnected), terms.end()); // remove_if is O(n)
}



////////////////////////////////////////////////////////////////////


// combine terms that are equal if d quark propagators is equal to u quark propagators
static bool symEqual(const Sym &s1, const Sym &s2) {
  return s1==s2 || (s1==Sym::Pu && s2==Sym::Pd) || (s1==Sym::Pd && s2==Sym::Pu);
}

// static bool symEqual(const Sym &s1, const Sym &s2) {
//   return s1==s2 || (s1==Sym::Pu && s2==Sym::Pd) || (s1==Sym::Pd && s2==Sym::Pu)
//    || (s1==Sym::Pu && s2==Sym::Ps) || (s1==Sym::Pd && s2==Sym::Ps)
//   || (s1==Sym::Ps && s2==Sym::Pd) || (s1==Sym::Ps && s2==Sym::Pu);
// }

static bool elemEqual(const Elem &e1, const Elem &e2) {
 return e1.pos==e2.pos && e1.color==e2.color && e1.spin==e2.spin && symEqual(e1.sym, e2.sym);
}

static bool contractionEqual(const Term &t1, const Term &t2) {
  if(t1.size()!=t2.size()) return false;
  for(int i=0; i<t1.size(); ++i) {
    if(!elemEqual(t1[i], t2[i])) return false;
  }
  return true;
}

void combine_u_d_prop(std::vector<Term> &terms) {
  int size = terms.size();
  for(int i=0; i<size; ++i) {

    std::vector<int> repeats;
    for(int j=i+1; j<size; ++j) {
      if(contractionEqual(terms[i], terms[j])) repeats.push_back(j);
    }

    for(int r=repeats.size()-1; r>=0; --r) { // must erase the element in the back before erasing elements in the front!! Indices will change after 'erase'.
      terms[i].coef += terms[repeats[r]].coef;
      terms.erase(terms.begin() + repeats[r]);
      --size;
    }
  }

}
