#include <iostream>
#include <vector>
using namespace std;
class TrieNode {
public:
  TrieNode *children[26];
  bool isEnd;
  TrieNode() {
    isEnd = false;
    for (int i{0}; i < 26; i++) {
      children[i] = nullptr;
    }
  }
};
class Trie {
private:
  TrieNode *root;
  void clear(TrieNode *node) {
    for (int i{0}; i < 26; i++) {
      if (node->children[i]) {
        clear(node->children[i]);
      }
    }
    delete node;
  }

public:
  Trie() { root = new TrieNode(); }
  ~Trie() { clear(root); }
  void insert(const string &key) {
    TrieNode *cur = root;
    for (char c : key) {
      if (cur->children[c - 'a'] == nullptr) {
        TrieNode *newNode = new TrieNode();
        cur->children[c - 'a'] = newNode;
      }
      cur = cur->children[c - 'a'];
    }
    cur->isEnd = true;
  } // Time: O(n), Space: O(n)
  bool search(const string &key) {
    TrieNode *cur = root;
    for (char c : key) {
      if (cur->children[c - 'a'] == nullptr)
        return false;
      cur = cur->children[c - 'a'];
    }
    return cur->isEnd;
  } // Time: O(n), Space: O(1)
  bool isPrefix(const string &key) {
    TrieNode *cur = root;
    for (char c : key) {
      if (cur->children[c - 'a'] == nullptr)
        return false;
      cur = cur->children[c - 'a'];
    }
    return true;
  }
};
int main() {

  // Create am example Trie
  Trie trie;
  vector<string> arr = {"and", "ant", "do", "dad"};
  for (const string &s : arr) {
    trie.insert(s);
  }

  // One by one search strings
  vector<string> searchKeys = {"do", "gee", "bat"};
  for (string &s : searchKeys) {

    if (trie.search(s))
      cout << "true ";
    else
      cout << "false ";
  }
  cout << "\n";

  // One by one search for prefixes
  vector<string> prefixKeys = {"ge", "ba", "do", "de"};
  for (string &s : prefixKeys) {

    if (trie.isPrefix(s))
      cout << "true ";
    else
      cout << "false ";
  }

  return 0;
}