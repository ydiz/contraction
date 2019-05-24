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

  bool allowDisconnected = false; // display disconnected diagram or not
  // bool allowDisconnected = true; // display disconnected diagram or not

  // Op pi_x = Pion(Sym::x, Sym::d);
  // Op pi_y = Pion(Sym::y, Sym::d);
  // Term t = pi_x * pi_y;

  // Op jmu = Jmu(Sym::x, Sym::u);
  // Op jnu = Jnu(Sym::y, Sym::u);
  // Op pi = Pion(Sym::z, Sym::u);
  // Term t = jmu * jnu * pi;

  Op jmu = Jmu(Sym::x, Sym::u);
  Op jnu = Jnu(Sym::y, Sym::u);
  Op q1 = Q1(Sym::w);
  Op k = Kaon(Sym::z);
  Term t = jmu * jnu * q1 * k;

  // vector<Term> tt = contract(t, Sym::d);
  vector<Term> tt = contract(t, allowDisconnected);
  if(tt.empty()) cout << "empty" << endl;
  for(const auto &x: tt) cout << x << endl;
 


	return 0;
}
