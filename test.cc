#include "defs.h"


using namespace std;

int main() {

  // Op pi_x = Pi0(Sym::x);
  // Op pi_y = Pi0(Sym::y);
  // std::vector<Term> t = pi_x * pi_y;

  // Op jmu = Jmu(Sym::u);
  // Op jnu = Jnu(Sym::v);
  // Op pi = Pi0(Sym::x);
  // std::vector<Term> t = jmu * jnu * pi;

  Op jmu = Jmu(Sym::u);
  Op jnu = Jnu(Sym::v);
  // Op q1 = Q1(Sym::x);
  // Op q1bar = Q1bar(Sym::x);
  // Op q2 = Q2(Sym::x);
  Op q2bar = Q2bar(Sym::x);
  // Op q3 = Q3(Sym::x);

  // Op k = K0(Sym::y);
  Op kbar = K0bar(Sym::y);
  // std::vector<Term> t = jmu * jnu * q1 * k;
  // std::vector<Term> t = jmu * jnu * q1bar * kbar;
  // std::vector<Term> t = jmu * jnu * q2 * k;
  std::vector<Term> t = jmu * jnu * q2bar * kbar;
  // std::vector<Term> t = jmu * jnu * q3 * k;

  // bool verbose = true;
  bool verbose = false;
  bool allowDisconnected = true; // cannot be false; disconnected diagrams are also important
  // bool allowDisconnected = false;
  vector<Term> tt = contract(t, allowDisconnected, verbose);

  removeJmuSelfConnected(tt);  // uncomment me to remove JmuSelfConnected diagrams
  combine_u_d_prop(tt);

  generateLatex(tt, "./tmp/tmp.tex");
  // generateLatex(tt, "./tmp/tmp.tex", false);

	return 0;
}
