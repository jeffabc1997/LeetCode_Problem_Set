#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    string stringName;
    Node *children[26];
    Node() {
        for(int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        // not empty when it's the end of a word and we don't need to store every character of the words
        stringName = ""; 
    }
};

class Solution {
private:
    void insert(string word) {
        int n = word.size();
        Node* ptr = root;
        
        for(int i = 0, index; i < n; i++) {
            index = word[i] - 'a';
            if(ptr->children[index] == nullptr) {
                ptr->children[index] = new Node();
            }
            ptr = ptr->children[index];
        }
        ptr->stringName = word;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j, Node* ptr) {
        
        char cur = board[i][j];
        int index = cur - 'a';
        /* check if we can move to next node of Trie */
        if(ptr->children[index] == nullptr) {
            return; // can't move to next node because ptr doesn't have that child
        } else {
            ptr = ptr->children[index];
        }
        if(ptr->stringName != "") {
            answer.push_back(ptr->stringName);
            ptr->stringName = ""; /* VERY IMPORTANT Step to remove duplicate words for the answer */
        }
        
        board[i][j] = '#'; // to avoid using another mxn array to remember visited places
        int m = board.size(), n = board[0].size();
        /* move to the next cell of 4 direction */
        if((i+1 < m) && (board[i+1][j] != '#')){            
            dfs(board, (i+1), j, ptr);          
        }
        if((i-1 >= 0) && (board[i-1][j] != '#')) {                 
            dfs(board, (i-1), j, ptr);         
        }
        if((j+1 < n) && (board[i][j+1] != '#')){              
            dfs(board, i, (j+1), ptr);           
        }
        if((j-1 >= 0) && (board[i][j-1] != '#')){             
            dfs(board, i, (j-1), ptr);           
        }
        board[i][j] = cur; // mark as unvisited when we return
    }
public:
    Node* root;
    vector<string> answer;
    Solution() {
        root = new Node;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size(), n = board[0].size();
        
        for(auto w: words) {
            insert(w);
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                Node* ptr = root;
                dfs(board, i, j, ptr); // dfs every cell on the board
            }
        }
        return answer;
    } 
};

int main() {
    // vector<vector<char>> board = {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    // vector<string> words = {"oath","pea","eat","rain"};
    vector<vector<char>> board = {{'o','a','b','n'},{'o','t','a','e'},{'a','h','k','r'},{'a','f','l','v'}};
    vector<string> words = {"oa","oaa"};
    Solution* sol = new Solution;
    
    vector<string> test = sol->findWords(board, words); 
    
    
    for(auto ans: test) {
        cout << ans << endl;
    }
    return 0;
}
