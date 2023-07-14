#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

/* Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
private:
    string encodeI(int num) { // make integer into string with ','
        string ans = std::to_string(num); // int to string
        ans.push_back(',');
        return ans;
    }

    /* make node's value into string and if there's a NULL leaf, mark as 'x' */
    void encode_preorder(TreeNode* root, string& encode) {
        if(!root) {
            encode += "x,"; 
            return;
        }
        encode += encodeI(root->val);
        encode_preorder(root->left, encode);
        encode_preorder(root->right, encode);
    }

    /* the initial idea is to split data into string vector and then use preorder way to build BT */
    /* a Optimized Way for memory and speed is that: 
        skipping the string vector and turn it into pointer queue directly */
    void stringToQueue(string data, queue<TreeNode*>& words) {
        string tmp; 
        stringstream ss(data);
        
        while(getline(ss, tmp , ',')) {
            if(tmp == "x") {
                words.push(NULL);
            } else {
                words.push(new TreeNode(std::stoi(tmp)));
            }
        }
    }

    /* build BT by preorder */
    TreeNode* preorder(queue<TreeNode*>& numstringQ) {
        if(numstringQ.empty()) {
            return NULL;
        }
        TreeNode* node = numstringQ.front();
        numstringQ.pop();
        if(node == NULL) {
            return NULL;
        }
        node->left = preorder(numstringQ);
        node->right = preorder(numstringQ);
        return node;
    }
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) {
            return "";
        }
        string res = "";
        encode_preorder(root, res);
        // cout <<"Serialize: ";
        // cout << res << endl;
        return res;
    }

    // // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") {
            return NULL;
        }   
        // cout << "Deserialize: ";
        queue<TreeNode*> numstringQ;
        stringToQueue(data, numstringQ);
        TreeNode* root = preorder(numstringQ);
        return root;
    }
};

void test_ans(TreeNode* root) {
    if(!root) {
        cout << "NULL, ";
        return;
    }
    cout << root->val << ", ";
    test_ans(root->left);
    test_ans(root->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    TreeNode* tmp = root->right;
    tmp->left = new TreeNode(12);
    tmp->right = new TreeNode(5);

    Codec ser, deser;
    TreeNode* ans = deser.deserialize(ser.serialize(root));
    
    // test_ans(ans);

    return 0;
}