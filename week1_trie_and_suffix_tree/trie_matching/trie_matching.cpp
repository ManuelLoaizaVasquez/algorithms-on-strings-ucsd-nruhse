#include <iostream>
#include <vector>
#include <map>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

vector<int> positions;
map<char, int> char_to_int;

struct Trie {
  int nodes = 1;
  vector<vector<int>> trie;
  vector<bool> terminal;

  void add_node() {
    vector<int> node(4, -1);
    trie.push_back(node);
    terminal.push_back(false);
  }

  Trie() { add_node(); }

  void add_word(string& word) {
    int size = word.size();
    int current = 0;
    for (int pos = 0; pos < size; pos++) {
      int letter = char_to_int[word[pos]];
      if (trie[current][letter] == -1) {
        trie[current][letter] = nodes;
        current = trie[current][letter];
        add_node();
        nodes++;
      } else {
        current = trie[current][letter];
      }
    }
    terminal[current] = true;
  }

  bool check(string& word, int first_pos) {
    int size = word.size();
    int current = 0;
    for (int pos = first_pos; pos < size; pos++) {
      int letter = char_to_int[word[pos]];
      if (trie[current][letter] == -1) return false;
      current = trie[current][letter];
      if (terminal[current]) return true;
    }
    return false;
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
  string text;
  cin >> text;
  int words;
  cin >> words;
  Trie dictionary;
  while (words--) {
    string word;
    cin >> word;
    dictionary.add_word(word);
  }
  vector<int> answer;
  for (int pos = 0; pos < text.size(); pos++) {
    if (dictionary.check(text, pos)) answer.push_back(pos);
  }
  for (int pos = 0; pos < answer.size(); pos++) {
    if (pos > 0) cout << " ";
    cout << answer[pos];
  }
  cout << endl;
  return 0;
}