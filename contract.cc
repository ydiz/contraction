#include "defs.h"

// Whether the contraction has an overall minus sign

// number of moves to make q followed by qBar -> (u uBar) = Propagator
static int moves(int q_pos, int qBar_pos, const Term &term, const std::unordered_set<int> &contracted) {
  int ret = 0;
  if(qBar_pos < q_pos) {
    for(int i=qBar_pos+1; i<q_pos; ++i) {
      if(isQuark(term[i].sym) && contracted.find(i)==contracted.end()) ret += 1; // if is a quark and has not been contracted
    }
    return ret + 1; // + 1 is because we want q followed by qBar
  }

  else { // qBar_pos > q_pos
    for(int i=qBar_pos-1; i>q_pos; --i) {
      if(isQuark(term[i].sym) && contracted.find(i)==contracted.end()) ret += 1;
    }
    return ret;
  }

}

// check if the contraction will give an extra minus sign
static bool isMinus(const std::vector<std::pair<int, int>> &contractions, const Term &term) {
  using namespace std;
  unordered_set<int> contracted;

  int total_moves = 0;
  for(const auto &x: contractions) {
    total_moves += moves(x.first, x.second, term, contracted);
    contracted.insert(x.first);
    contracted.insert(x.second);
  }

  // cout << total_moves << endl;
  return total_moves % 2 == 1;
}


////////////////////////////////////////////////////////
// whether the diagram is connected
// FIXME: this is wrong. Hw is a four-quark operator and can connect with itself.

static bool isConnected(const std::vector<std::pair<int, int>> &contractions, const Term &term) {
  for(const auto& x: contractions) {
    if(term[x.first].pos[0] == term[x.second].pos[0]) return false; // if two contracted quarks are at the same position
  }
  return true;
}


////////////////////////////////////////////////////////

// find all positions of one type of quark
static std::vector<int> find_all(Sym target, const Term &term) {
  std::vector<int> ret;
  for(int i=0; i<term.size(); ++i) {
    if(term[i].sym == target) ret.push_back(i);
  }

  return ret;
}

// find all possible ways of contractions for one type of quark

static std::vector<std::vector<std::pair<int, int>>> combinations_recursion(const std::vector<int> &qs, const std::vector<int> &qBars){

  using namespace std;
  vector<vector<pair<int, int>>> ret;

  if(qs.size()==1) {
    ret.resize(1);
    ret[0].push_back(make_pair(qs[0], qBars[0]));
    return ret;
  }

  for(int i=0; i<qs.size(); ++i) {
    for(int j=0; j<qs.size(); ++j) {
      pair<int, int> cur_pair = make_pair(qs[i], qBars[j]);

      vector<int> qs2 = qs; qs2.erase(qs2.begin() + i);
      vector<int> qBars2 = qBars; qBars2.erase(qBars2.begin() + j);
      vector<vector<pair<int, int>>> pre_ret = combinations_recursion(qs2, qBars2); // recursion

      for(int k=0; k<pre_ret.size(); ++k) {

        pre_ret[k].push_back(cur_pair);      
        ret.push_back(pre_ret[k]);
      }
    }
  }
  return ret;
}


static std::vector<std::vector<std::pair<int, int>>> combinations(const std::vector<int> &qs, const std::vector<int> &qBars){
  using namespace std;
  assert(qs.size() == qBars.size()); // number of quarks and anti-quarks should be the same
  vector<vector<pair<int, int>>> ret;

  ret = combinations_recursion(qs, qBars);

  // delete duplicate
  for(auto &x: ret) sort(x.begin(), x.end());
  set<vector<pair<int, int>>> s(ret.begin(), ret.end());
  ret.assign(s.begin(), s.end());

  assert(ret.size()==0 || ret.size() == factorial(qs.size())); // number of combinations should be n!
  assert(ret.size()==0 || ret[0].size() == qs.size());

  return ret;
}



static std::vector<Term> contract(const Term &term, Sym q_type, bool allowDisconnected = false) {
  using namespace std;
  vector<Term> ret;

  // find all combinations of q and qBar
  vector<int> qs = find_all(q_type, term);
  if(qs.size()==0) {
    ret.push_back(term);
    return ret;
  } // if there is no this type of quark, no contraction is needed; return the original expression

  vector<int> qBars = find_all(bar(q_type), term);
  vector<vector<pair<int, int>>> combs = combinations(qs, qBars); // combs.size() = factorial(qs.size())

  for(int i=0; i<combs.size(); ++i) { // iterate over all ways of contracting q (q can be u, d, or s)

    if(allowDisconnected == false && !isConnected(combs[i], term)) continue;

    ret.push_back(term);
    Term &ret_i = ret.back(); // current contraction

    // cout << combs[i] << endl;
    // if(isMinus(combs[i], term)) cout << "Minus" << endl;
    if(isMinus(combs[i], term)) changeSign(ret_i);  // minus is at the rear and thus does not affect positions of q and qBar

    for(int j=0; j<qs.size(); ++j) { // iterate over all occurrences of q
      int q_loc = combs[i][j].first; // location of quark
      int qBar_loc = combs[i][j].second; // location of anti-quark
      const Elem &q = term[q_loc];
      const Elem &qBar = term[qBar_loc];

      // insert propagator at the location is q
      Sym prop_type = prop(q_type);
      Elem prop = Elem(prop_type, {q.pos[0], qBar.pos[0]}, {q.color[0], qBar.color[0]}, {q.spin[0], qBar.spin[0]});
      ret_i[q_loc] = prop;
    }
    
    // remove all qBar
    auto isBar = [q_type](const Elem &e) { 
      if(e.sym == bar(q_type)) return true;
      else return false;
    };
    ret_i.erase(remove_if(ret_i.begin(), ret_i.end(), isBar), ret_i.end());
  }

  return ret;
}



std::vector<Term> contract(const Term &term, bool allowDisconnected /* = false */) {
  using namespace std;
  vector<Term> ret_s = contract(term, Sym::s, allowDisconnected);

  vector<Term> ret_d;
  for(int i=0; i<ret_s.size(); ++i) {
    vector<Term> tmp = contract(ret_s[i], Sym::d, allowDisconnected);
    ret_d.insert(ret_d.end(), tmp.begin(), tmp.end()); // concatenate possible contractions
  }
  
  vector<Term> ret_u;
  for(int i=0; i<ret_d.size(); ++i) {
    vector<Term> tmp = contract(ret_d[i], Sym::u, allowDisconnected);
    ret_u.insert(ret_u.end(), tmp.begin(), tmp.end()); // concatenate possible contractions
  }

  return ret_u;
}



std::vector<Term> contract(const std::vector<Term> &terms, bool allowDisconnected/* = false */, bool verbose/* = false */) {
  using namespace std;
  vector<Term> ret;
  for(const auto &term: terms) {

    vector<Term> t = contract(term, allowDisconnected);
    ret.insert(ret.end(), t.begin(), t.end());

    if(verbose) {
      cout << std::string(30, '-') << endl;
      cout << "Term: " << term << endl;
      cout << endl;
      cout << "Contractions: " << endl;
      cout << t << endl;
    }
  }
  return ret;
}
