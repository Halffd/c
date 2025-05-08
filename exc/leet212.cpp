#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    string word = ""; // non-empty if this node ends a word
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = buildTrie(words);
        unordered_set<string> result;
        
        int rows = board.size(), cols = board[0].size();
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dfs(board, r, c, root, result);
            }
        }
        
        return vector<string>(result.begin(), result.end());
    }

private:
    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (const string& word : words) {
            TrieNode* node = root;
            for (char ch : word) {
                if (!node->children.count(ch))
                    node->children[ch] = new TrieNode();
                node = node->children[ch];
            }
            node->word = word;
        }
        return root;
    }
    
    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, unordered_set<string>& result) {
        if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size()) return;
        char ch = board[r][c];
        
        if (ch == '#' || !node->children.count(ch)) return;
        
        node = node->children[ch];
        if (!node->word.empty()) {
            result.insert(node->word);
            node->word.clear(); // avoid duplicates faster
        }
        
        board[r][c] = '#'; // mark visited
        
        dfs(board, r+1, c, node, result);
        dfs(board, r-1, c, node, result);
        dfs(board, r, c+1, node, result);
        dfs(board, r, c-1, node, result);
        
        board[r][c] = ch; // undo mark
    }
};

int main() {
    Solution solver;
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words = {"oath","pea","eat","rain"};
    
    vector<string> found = solver.findWords(board, words);
    
    for (const auto& word : found) {
        cout << word << endl;
    }
    return 0;
}
