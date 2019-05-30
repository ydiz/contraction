#include "defs.h"

bool isQuark(Sym sym) {
  static std::unordered_set<Sym> quarks = {Sym::u, Sym::d, Sym::s, Sym::uBar, Sym::dBar, Sym::sBar};
  if(quarks.find(sym) != quarks.end()) return true;
  else return false;
}

bool isNotQuark(Sym sym) {
  return !isQuark(sym);
}

bool isProp(Sym sym) {
  static std::unordered_set<Sym> props = {Sym::Pu, Sym::Pd, Sym::Ps};
  if(props.find(sym) != props.end()) return true;
  else return false;
}

Sym propToQuark(Sym prop) {
  static std::unordered_map<Sym, Sym> props = { {Sym::Pu, Sym::u}, {Sym::Pd, Sym::d}, {Sym::Ps, Sym::s} };
  return props[prop];
}


Sym bar(Sym q) {
  switch(q) {
    case Sym::u : return Sym::uBar;
    case Sym::d : return Sym::dBar;
    case Sym::s : return Sym::sBar;
    default : assert(0);
  }
}

Sym prop(Sym q) {
  switch(q) {
    case Sym::u : return Sym::Pu;
    case Sym::d : return Sym::Pd;
    case Sym::s : return Sym::Ps;
    default : assert(0);
  }
}


// use these two functions to get color and spin index

static int color_counter = 0;
static int spin_counter = 0;

static std::vector<Sym> color_idx = {Sym::c0, Sym::c1, Sym::c2, Sym::c3, Sym::c4, Sym::c5, Sym::c6, Sym::c7, Sym::c8, Sym::c9};
static std::vector<Sym> spin_idx = {Sym::s0, Sym::s1, Sym::s2, Sym::s3, Sym::s4, Sym::s5, Sym::s6, Sym::s7, Sym::s8, Sym::s9};

Sym get_color() {
  assert(color_counter <= 10);
  return color_idx[color_counter++];
}

Sym get_spin() {
  assert(spin_counter <= 10);
  return spin_idx[spin_counter++];
}


// For displaying variables


static std::unordered_map<Sym, std::string> symStr = { 
  {Sym::u, "u"}, {Sym::uBar, "uBar"}, {Sym::d, "d"}, {Sym::dBar, "dBar"}, {Sym::s, "s"}, {Sym::sBar, "sBar"},
  {Sym::a, "a"}, {Sym::b, "b"}, {Sym::c0, "c0"}, {Sym::c1, "c1"}, {Sym::c2, "c2"}, {Sym::c3, "c3"}, {Sym::c4, "c4"}, {Sym::c5, "c5"}, {Sym::c6, "c6"},{Sym::c7, "c7"}, {Sym::c8, "c8"}, {Sym::c9, "c9"},
  {Sym::alpha, "alpha"}, {Sym::beta, "beta"}, {Sym::s0, "s0"}, {Sym::s1, "s1"}, {Sym::s2, "s2"}, {Sym::s3, "s3"}, {Sym::s4, "s4"}, {Sym::s5, "s5"}, {Sym::s6, "s6"},{Sym::s7, "s7"}, {Sym::s8, "s8"}, {Sym::s9, "s9"},
  {Sym::w, "w"}, {Sym::x, "x"}, {Sym::y, "y"}, {Sym::z, "z"}, {Sym::v, "v"},
  {Sym::g5, "g5"}, {Sym::gmu, "gmu"}, {Sym::gnu, "gnu"}, {Sym::gL, "gL"}, {Sym::gR, "gR"}, 
  {Sym::Pu, "Pu"}, {Sym::Pd, "Pd"}, {Sym::Ps, "Ps"}};


std::ostream& operator<<(std::ostream &out, Sym sym) {
  out << symStr[sym];
  return out;
}

std::string str(Sym sym) {
  return symStr[sym];
}


std::string str(const std::vector<Sym> &syms) {
  std::string ret("");
  if(syms.empty()) return ret;
  else {
    // std::string ret = "{"
    for(int i=0; i<syms.size()-1; ++i) ret += str(syms[i]) + ",";
    ret += str(syms[syms.size()-1]);
  }
  return ret;
}
