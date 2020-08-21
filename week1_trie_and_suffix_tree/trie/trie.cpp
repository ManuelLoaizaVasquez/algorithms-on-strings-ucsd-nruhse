#include <iostream>
#include <vector>
#include <map>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

const int ALPH = 4; // A, C, G, T

struct Edge {
  char letter;
  int from;
  int to;
  Edge() {}
  Edge(char _letter, int _from, int _to) {
    letter = _letter;
    from = _from;
    to = _to;
  }
};
vector<Edge> edges;
map<char, int> char_to_int;

struct Trie {
  int nodes = 1;
  vector<vector<int>> trie;

  void add_node() {
    vector<int> node(4, -1);
    trie.push_back(node);
  }
  
  Trie() { add_node(); }
  
  void add_word(string& word) {
    int size = word.size();
    int current = 0;
    for (int pos = 0; pos < size; pos++) {
      int letter = char_to_int[word[pos]];
      if (trie[current][letter] == -1) {
        // Aniado la nueva arista
        Edge new_edge(word[pos], current, nodes);
        edges.push_back(new_edge);
        // Modifico el trie
        trie[current][letter] = nodes;
        current = trie[current][letter];
        nodes++;
        add_node();
      } else {
        current = trie[current][letter];
      }
    }
  }
};

void initialize() {
  char_to_int['A'] = 0;
  char_to_int['C'] = 1;
  char_to_int['G'] = 2;
  char_to_int['T'] = 3;
}

int main() {
  fastio;
  initialize();
  int words;
  cin >> words;
  Trie dictionary;
  while (words--) {
    string word;
    cin >> word;
    dictionary.add_word(word);
  }
  for (Edge edge : edges) {
    int from = edge.from;
    int to = edge.to;
    char letter = edge.letter;
    cout << from << "->" << to << ":" << letter << endl;
  }
  return 0;
}