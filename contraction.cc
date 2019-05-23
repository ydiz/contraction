#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "sym.h"
#include "elem.h"
#include "operator.h"

using namespace std;

int main() {

  // Elem u1(u, x, a, alpha);
  // cout << u1.str() << endl;
  //
  // Elem G(g5, {alpha, beta});
  // cout << G.str() << endl;

  // Op pi(3);
  // pi[0] = Elem(uBar, x, a, alpha);
  // pi[1] = Elem(g5, {alpha, beta});
  // pi[2] = Elem(u, x, a, beta);
  //
  // cout << pi << endl;

  cout << pion(Symbol::x) << endl;
  

	return 0;
}
