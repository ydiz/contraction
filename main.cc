#include "defs.h"


using namespace std;

int main() {

  // Op pi_x = Pi0(Sym::x);
  // Op pi_y = Pi0(Sym::y);
  // std::vector<Term> t = pi_x * pi_y;

  // Op eta_x = Eta(Sym::x);
  // Op eta_y = Eta(Sym::y);
  // std::vector<Term> t = eta_x * eta_y;

  // Op jmu = Jmu_no_s(Sym::u);
  // Op jnu = Jnu_no_s(Sym::v);
  // // Op pi = Pi0(Sym::x);
  // Op uBar_g5_u = UBar_g5_u(Sym::x);
  // // std::vector<Term> t = jmu * jnu * pi;
  // std::vector<Term> t = jmu * jnu * uBar_g5_u;

  // Op jmu = Jmu(Sym::u);
  // Op jnu = Jnu(Sym::v);


  // Op uBar_g5_u = UBar_g5_u(Sym::u);
  Op dBar_g5_d = DBar_g5_d(Sym::u);

  // Op q1 = Q1(Sym::x);
  // Op q1bar = Q1bar(Sym::x);
  // Op q2 = Q2_mixed(Sym::x);
  // Op q2 = Q2_unmixed(Sym::x);
  // Op q2bar = Q2bar_mixed(Sym::x);
  // Op q2bar = Q2bar_unmixed(Sym::x);
  // Op q3 = Q3(Sym::x);
  Op s_bar_d = sBar_d(Sym::x);
  // Op d_bar_s = dBar_s(Sym::x);

  Op k = K0(Sym::y);
  // Op kbar = K0bar(Sym::y);

  // std::vector<Term> t = jmu * jnu * q1 * k;
  // std::vector<Term> t = jmu * jnu * q1bar * kbar;
  // std::vector<Term> t = jmu * jnu * q2 * k;
  // std::vector<Term> t = jmu * jnu * q2bar * kbar;
  // std::vector<Term> t = jmu * jnu * q3 * k;

  // Op pi = Pi0(Sym::u);
  // std::vector<Term> t = pi * q1 * k;
  // std::vector<Term> t = pi * q1bar * kbar;
  // std::vector<Term> t = pi * q2 * k;
  // std::vector<Term> t = pi * q2bar * kbar;
  // std::vector<Term> t = pi * s_bar_d * k;

  // Op eta = Eta(Sym::u);
  // std::vector<Term> t = eta * q1 * k;
  // std::vector<Term> t = eta * q1bar * kbar;
  // std::vector<Term> t = eta * q2 * k;
  // std::vector<Term> t = eta * q2bar * kbar;
  // std::vector<Term> t = eta * s_bar_d * k;
  // std::vector<Term> t = eta * d_bar_s * kbar;

  // std::vector<Term> t = jmu * jnu * s_bar_d * k;
  // std::vector<Term> t = jmu * jnu * d_bar_s * kbar;

  // std::vector<Term> t = uBar_g5_u * q1 * k;
  // std::vector<Term> t = uBar_g5_u * q2 * k;
  // std::vector<Term> t = uBar_g5_u * s_bar_d * k;
  // std::vector<Term> t = dBar_g5_d * q1 * k;
  // std::vector<Term> t = dBar_g5_d * q2 * k;
  std::vector<Term> t = dBar_g5_d * s_bar_d * k;

  // bool verbose = true;
  bool verbose = false;
  bool allowDisconnected = true; // cannot be false; disconnected diagrams are also important
  // bool allowDisconnected = false;
  vector<Term> tt = contract(t, allowDisconnected, verbose);

  // IMPORTANT!!!: must not remove self loop at u/v if operator at u/v is not  Jmu or Jnu
  // removeJmuSelfConnected(tt);  // uncomment me to remove JmuSelfConnected diagrams
  combine_u_d_prop(tt);

  generateLatex(tt, "./tmp/tmp.tex");
  // generateLatex(tt, "./tmp/tmp.tex", false);

	return 0;
}
