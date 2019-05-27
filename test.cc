#include "defs.h"

// #include "contract.h"

using namespace std;

int main() {

  // Op pi_x = Pi0(Sym::x);
  // Op pi_y = Pi0(Sym::y);
  // std::vector<Term> t = pi_x * pi_y;
  // std::cout << t << std::endl;

  // Op jmu = Jmu(Sym::x, Sym::u);
  // Op jnu = Jnu(Sym::y, Sym::u);
  // Op pi = Pion(Sym::z, Sym::u);
  // Term t = jmu * jnu * pi;

  Op jmu = Jmu(Sym::u, Sym::u);
  Op jnu = Jnu(Sym::v, Sym::u);
  Op q1 = Q1(Sym::x);
  Op k = K0(Sym::y);
  std::vector<Term> t = jmu * jnu * q1 * k;

  // std::cout << pi_x[1] * pi_y[0] << std::endl;

  bool verbose = true;
  bool allowDisconnected = true;
  vector<Term> tt = contract(t, allowDisconnected, verbose);
  // cout << tt << endl;
 


	return 0;
}
