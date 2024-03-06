# include<iostream>
# include<queue>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr){};
};

void test1(TreeNode* node){
    node->val = 100;
}

void test2(TreeNode& node){
    node.val = 100;
}

int main(){
    TreeNode* a = new TreeNode(1);
    TreeNode b(1);
    test1(a);
    test2(b);
    cout<<a->val<<endl;
    cout<<b.val<<endl;
}
