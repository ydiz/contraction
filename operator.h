#pragma once

int color_counter = 0;
int spin_counter = 0;

Symbol get_color() {
  return color_idx[color_counter++];
}

Symbol get_spin() {
  return spin_idx[spin_counter++];
}



using Op = std::vector<Elem>;

// FIXME: add d quark
Op pion(Symbol pos) {
  Op pi(3);

  Symbol cc = get_color(), ss1 = get_spin(), ss2 = get_spin();
  pi[0] = Elem(Symbol::uBar, pos, cc, ss1);
  pi[1] = Elem(Symbol::g5, {ss1, ss2});
  pi[2] = Elem(Symbol::u, pos, cc, ss2);
  return pi;
}
