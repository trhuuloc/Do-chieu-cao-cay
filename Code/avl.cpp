#include <bits/stdc++.h>
using namespace std;
struct Node
{

    int data;
    Node *left;
    Node *right;
    int height;
};

int getHeight(Node *node)
{
    if(node==NULL)
    {
        //cout<<"**\n";
        return 0;
    }
    return node->height;
}
Node* taonode(int data)
{
    Node* tmp=new Node();
    tmp->left=NULL;
    tmp->right=NULL;
    tmp->data=data;
    tmp->height=1;
    return tmp;
}
int getbalance(Node *node)
{
    return getHeight(node->left)-getHeight(node->right);
}
Node* left(Node *root)
{
    Node *x=root->right;

    root->right=x->left;
    x->left=root;

    root->height=1+max(getHeight(root->left),getHeight(root->right));
    x->height=1+max(getHeight(x->left),getHeight(x->right));

    return x;

}
Node* right(Node *root)
{
    Node *x=root->left;

    root->left=x->right;
    x->right=root;

    root->height=1+max(getHeight(root->left),getHeight(root->right));
    x->height=1+max(getHeight(x->left),getHeight(x->right));

    return x;
}
Node* insert(Node *root,int data)
{
    if(root==NULL)
    {
        return taonode(data);
    }
    if(data==root->data)
    {
        return root;
    }
    if(data<root->data)
    {
        root->left=insert(root->left,data);
    }
    if(data>root->data)
    {
        root->right=insert(root->right,data);
    }
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    int balancefactor=getbalance(root);
    if(balancefactor>1&&data<root->left->data)
    {
        return right(root);
    }
    if(balancefactor>1&&data>root->left->data)
    {
        root->left=left(root->left);
        return right(root);
    }
    if(balancefactor<-1&&data>root->right->data)
    {
        return left(root);
    }
    if(balancefactor<-1&&data<root->right->data)
    {
        root->right=right(root->right);
        return left(root);
    }
    return root;
}
int main()
{
    freopen("test10.inp","r",stdin);
    //freopen("avl.out","w",stdout);
    Node *root=NULL;
    int n,x;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>x;
        root=insert(root,x);
    }
    cout<<root->height;
}
