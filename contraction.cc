#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "sym.h"
#include "elem.h"
#include "operator.h"
#include "contract.h"

using namespace std;

int main() {


  // Op pi_x = pion(Sym::x, Sym::d);
  // Op pi_y = pion(Sym::y, Sym::d);
  // Term t = pi_x * pi_y;

  Op jmu = Jmu(Sym::x, Sym::d);
  Op jnu = Jnu(Sym::y, Sym::d);
  Op pi = pion(Sym::z, Sym::d);
  Term t = jmu * jnu * pi;
  

  // vector<Term> tt = contract(t, Sym::d);
  vector<Term> tt = contract(t);
  for(const auto &x: tt) cout << x << endl;
 


	return 0;
}
