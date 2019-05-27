#include "defs.h"

using namespace std;

int main() {

  // Op pi_x = Pi0(Sym::x);
  // Op pi_y = Pi0(Sym::y);
  // std::vector<Term> t = pi_x * pi_y;

  Op jmu = Jmu(Sym::x);
  Op jnu = Jnu(Sym::y);
  Op pi = Pi0(Sym::z);
  std::vector<Term> t = jmu * jnu * pi;

  // Op jmu = Jmu(Sym::u);
  // Op jnu = Jnu(Sym::v);
  // Op q1 = Q1(Sym::x);
  // Op k = K0(Sym::y);
  // std::vector<Term> t = jmu * jnu * q1 * k;


  bool verbose = true;
  // bool allowDisconnected = true;
  bool allowDisconnected = false;
  vector<Term> tt = contract(t, allowDisconnected, verbose);
 


	return 0;
}
