#include "defs.h"
#include <regex>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>

// Math expression

static std::unordered_map<Sym, std::string> symLatex = { 
  {Sym::u, "u"}, {Sym::uBar, "\\bar{u}"}, {Sym::d, "d"}, {Sym::dBar, "\\bar{d}"}, {Sym::s, "s"}, {Sym::sBar, "\\bar{s}"},
  {Sym::a, "a"}, {Sym::b, "b"}, {Sym::c0, "c_0"}, {Sym::c1, "c_1"}, {Sym::c2, "c_2"}, {Sym::c3, "c_3"}, {Sym::c4, "c_4"}, {Sym::c5, "c_5"}, {Sym::c6, "c_6"},{Sym::c7, "c_7"}, {Sym::c8, "c_8"}, {Sym::c9, "c_9"},
  {Sym::alpha, "\\alpha"}, {Sym::beta, "\\beta"}, {Sym::s0, "s_0"}, {Sym::s1, "s_1"}, {Sym::s2, "s_2"}, {Sym::s3, "s_3"}, {Sym::s4, "s_4"}, {Sym::s5, "s_5"}, {Sym::s6, "s_6"},{Sym::s7, "s_7"}, {Sym::s8, "s_8"}, {Sym::s9, "s_9"},
  {Sym::w, "w"}, {Sym::x, "x"}, {Sym::y, "y"}, {Sym::z, "z"}, {Sym::v, "v"},
  {Sym::g5, "\\gamma_5"}, {Sym::gmu, "\\gamma_\\mu"}, {Sym::gnu, "\\gamma_\\nu"}, {Sym::gL, "\\gamma_L"}, {Sym::gR, "\\gamma_R"}, 
  {Sym::Pu, "L"}, {Sym::Pd, "L"}, {Sym::Ps, "H"}};

static std::string toTex(Sym sym) {
  return symLatex[sym];
}

static std::pair<Sym, Sym> firstLastColor(const Term& term, int start, int end) { // search in [start, end)
  Sym start_sym, end_sym;
  for(int i=start; i<end; ++i) {
    if(!term[i].color.empty()) {
      start_sym = term[i].color[0];
      break;
    }
  }
  for(int i=end-1; i>=start; --i) {
    if(!term[i].color.empty()) {
      end_sym = term[i].color.back();
      break;
    }
  }
  return std::make_pair(start_sym, end_sym);
}


static std::string generateLatexMath(const Term &term, int start, int end) {
  using namespace std;
  string ret;
  for(int i=start; i<end; ++i) {
    ret += toTex(term[i].sym);
    if(isProp(term[i].sym)) ret += "(" + toTex(term[i].pos[0]) + ", " + toTex(term[i].pos[1]) + ")";
    ret += " ";
  }
  return ret;
}

std::string generateLatexMath(const Term &term) {
  using namespace std;
  const vector<int> &delim = term.spinSingletDelimiter;
  string ret;

	std::stringstream ss;
	ss << fixed << setprecision(4) << term.coef;
	ret = ss.str() + "\\ ";

  if(delim.empty()) ret += generateLatexMath(term, 0, term.size());
  else {
    for(int i=0; i<delim.size()+1; ++i) {
      int start = (i==0 ? 0 : delim[i-1]); // start of this spin singlet
      int end = (i==delim.size() ? term.size() : delim[i]); // start of next spin singlet

      auto [first, last] = firstLastColor(term, start, end);
      if(first==last) ret += "Tr[ " + generateLatexMath(term, start, end) + "] "; 
      else ret += "Tr_s[ " + generateLatexMath(term, start, end) + "]_{" + toTex(first) + ", " + toTex(last) + "} "; 
    }
  }

  return ret;
}


// plotting graphs

static const std::string latex_preamble = 
"\\documentclass[10pt,a4paper]{article}\n"
"\\usepackage{tikz-feynman}\n"
"\\tikzfeynmanset{compat=1.0.0}\n"
"\\begin{document}\n\n";

static std::string toLatex(Sym q_pos, Sym qBar_pos, Sym q_type) {
  return "(" + str(qBar_pos) + ") --[edge label=" + str(q_type) + "] (" + str(q_pos) + ")";
}

static std::string toLatexBubble(Sym q_pos, Sym q_type) {
  return "(" + str(q_pos) + ") -- [out=135, in=180, edge label=" + str(q_type)+ "] (" + str(q_pos) + str(q_pos) + ") --[out=0, in=45] (" + str(q_pos) + ")";
}

static std::string read(const std::string &filename) {

  std::ifstream f(filename);
  std::stringstream ss;
  ss << f.rdbuf();
  
  return ss.str();
}

static void toLatex(const Term& term, std::string &nonBubbles, std::string &bubbles) {
  Sym q_pos, qBar_pos, q_type;
  for(const auto& elem: term) {
    if(isProp(elem.sym)) {
        q_pos = elem.pos[0];
        qBar_pos = elem.pos[1];
        q_type = propToQuark(elem.sym);
      if(q_pos != qBar_pos) {
        nonBubbles += toLatex(q_pos, qBar_pos, q_type);
        nonBubbles += ",\n";
      }
      else {
        bubbles += toLatexBubble(q_pos, q_type);
        bubbles += ",\n";
      }
    }
  }
}


static std::string toTikz(const Term &term) {
  std::string nonBubbles, bubbles;
  toLatex(term, nonBubbles, bubbles);

  std::string inFile = read("./latex/template.tex");
  std::regex reg("@Non-bubbles@");
  std::string tikz = std::regex_replace(inFile, reg, nonBubbles);

  std::regex reg2("@bubbles@");
  tikz = std::regex_replace(tikz, reg2, bubbles);

  std::regex reg3("@formula@");
  tikz = std::regex_replace(tikz, reg3, generateLatexMath(term));
  return tikz;
}

static std::string toTikz(const std::vector<Term> &terms) {
  std::string ret;
  for(const auto& term: terms) ret += toTikz(term) + "\n\n";
  return ret;
}

static void generateLatex(const std::string &tikz, const std::string &outFile) {
	std::string ret;
	ret = latex_preamble + tikz + "\n\n\\end{document}";

  std::ofstream f(outFile);
  f << ret;
  f.close();
}

void generateLatex(const std::vector<Term> &terms, const std::string &outFile, bool showPDF /*= true */) {
  generateLatex(toTikz(terms), outFile);

  if(showPDF) {
    system("cd tmp && latexmk -pdf -silent -pv ./tmp.tex");
  }
}
