#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parents;
    char color;
};
Node* taonode(int data)
{
    Node* tmp= new Node();
    tmp->data=data;
    tmp->left=NULL;
    tmp->right=NULL;
    tmp->parents=NULL;
    tmp->color='R';
    return tmp;
}
Node* left(Node* root)
{
    Node* x=root->right;
    Node* y=x->left;

    x->left=root;
    root->right=y;
    root->parents=x;
    if(y!=NULL)
    {
        y->parents=root;
    }
    return x;
}
Node* right(Node* root)
{
    Node* x=root->left;
    Node* y=x->right;

    x->right=root;
    root->left=y;
    root->parents=x;
    if(y!=NULL)
    {
        y->parents=root;
    }
    return x;
}
class caydoden
{
public:
    Node* goc;
    bool ll=false;
    bool lr=false;
    bool rr=false;
    bool rl=false;
    caydoden()
    {
        goc=NULL;
    }
    Node* insert(Node* root,int data)
    {
        //cout<<data<<"\n";
        bool xungdot=false;
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
            root->left->parents=root;
            if(root!=goc)
            {
                if(root->color=='R'&&root->left->color=='R')
                {
                    xungdot=true;
                }
            }
        }
        else
        {
            root->right=insert(root->right,data);
            root->right->parents=root;
            if(root!=goc)
            {
                if(root->color=='R'&&root->right->color=='R')
                {
                    xungdot=true;
                }
            }
        }
        if(ll)
        {
            //cout<<"**\n";
            root=left(root);
            //cout<<"**\n";
            root->color='B';
            root->left->color='R';
            //cout<<"**\n";
            ll=false;
        }
        else
        {
            if(rr)
            {
                root=right(root);
                root->color='B';
                root->right->color='R';
                rr=false;
            }
            else
            {
                if(lr)
                {
                    root->left=left(root->left);
                    root->left->parents=root;
                    root=right(root);
                    root->color='B';
                    root->right->color='R';
                    lr=false;
                }
                else
                {
                    if(rl)
                    {
                        root->right=right(root->right);
                        root->right->parents=root;
                        root=left(root);
                        root->color='B';
                        root->left->color='R';
                        rl=false;
                    }
                }
            }
        }
        if(xungdot)
        {
            if(root->parents->left==root)
            {
                if(root->parents->right==NULL||root->parents->right->color=='B')
                {
                    if(root->right!=NULL&&root->right->color=='R')
                    {
                        lr=true;
                    }
                    if(root->left!=NULL&&root->left->color=='R')
                    {
                        rr=true;
                    }
                }
                else
                {
                    root->color='B';
                    root->parents->right->color='B';
                    if(root->parents!=goc)
                    {
                        root->parents->color='R';
                    }
                }
            }
            else
            {
                if(root->parents->left==NULL||root->parents->left->color=='B')
                {
                    if(root->left!=NULL&&root->left->color=='R')
                    {
                        rl=true;
                    }
                    if(root->right!=NULL&&root->right->color=='R')
                    {
                        ll=true;
                    }
                }
                else
                {
                    root->color='B';
                    root->parents->left->color='B';
                    if(root->parents!=goc)
                    {
                        root->parents->color='R';
                    }
                }
            }
            xungdot=false;
        }
        return root;
    }
    void them(int data)
    {
        //cout<<data<<"\n";
        if(goc==NULL)
        {
            goc=taonode(data);
            goc->color='B';
        }
        else
        {
            goc=insert(goc,data);
        }
    }
};
int xuat(Node* root)
{
    int height=0;
    if(root!=NULL)
    {
        height=1;
        int h1=xuat(root->left);
        int h2=xuat(root->right);
        height=1+max(h1,h2);
    }
    return height;
}
int main()
{
    freopen("test10.inp","r",stdin);
    //freopen("doden.out","w",stdout);
    caydoden c;
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        c.them(x);
    }
    cout<<xuat(c.goc);
}
