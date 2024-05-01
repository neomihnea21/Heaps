#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;


struct node{

node* parent;
vector<node*> children;
vector<int> values;
};

stack<node*> free_leafs;
stack<node*> full_leafs;

node* root=NULL;


void upscale(node* nod)
{
    if(nod==root)
    {
        return;
    }
    node* dad=nod->parent;
    int nod_size=nod->values.size();
    int dad_size=dad->values.size();
    vector<int> aux;
    for(auto x:nod->values)
    {
        aux.push_back(x);
    }
    for(auto x:dad->values)
    {
        aux.push_back(x);
    }
    sort(aux.begin(),aux.end());
    dad->values.clear();
    nod->values.clear();
    for(int i=0;i<dad_size;i++)
    {
        dad->values.push_back(aux[i]);
    }
    for(int i=dad_size;i<nod_size+dad_size;i++)
    {
        nod->values.push_back(aux[i]);
    }
}

void fix_over_flow(node* nod)
{
    if(nod->values.size()<=2)
    {
        return;
    }
    if(nod==root)
    {
        if(nod->children.size()==0)
        {
            node* child1=new node;
            node* child2=new node;
            child1->parent=nod;
            child2->parent=nod;
            free_leafs.push(child1);
            free_leafs.push(child2);
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
            nod->children.push_back(child1);
            nod->children.push_back(child2);
        }
        else
        {
            node* child1=new node;
            node* child2=new node;
            child1->parent=nod;
            child2->parent=nod;
            nod->children.push_back(child1);
            nod->children.push_back(child2);
            nod->children.back()->parent=child1;
            child1->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child1;
            child1->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child2;
            child2->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child2;
            child2->children.push_back(nod->children.back());
            nod->children.pop_back();
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
        }
    }
    else
    {
        if(nod->children.size()==0)
        {
            node* child1=new node;
            node* child2=new node;
            node* dad=nod->parent;
            child1->parent=dad;
            child2->parent=dad;
            free_leafs.push(child1);
            free_leafs.push(child2);
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
            dad->children.push_back(child1);
            dad->children.push_back(child2);
            dad->values.push_back(nod->values.back());
            sort(dad->values.begin(),dad->values.end());
            delete nod;
            fix_over_flow(dad);
        }
        else
        {
            node* child1=new node;
            node* child2=new node;
            node* dad;
            dad=nod->parent;
            child1->parent=dad;
            child2->parent=dad;
            dad->children.push_back(child1);
            dad->children.push_back(child2);
            nod->children.back()->parent=child1;
            child1->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child1;
            child1->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child2;
            child2->children.push_back(nod->children.back());
            nod->children.pop_back();
            nod->children.back()->parent=child2;
            child2->children.push_back(nod->children.back());
            nod->children.pop_back();
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
            dad->children.push_back(child1);
            dad->children.push_back(child2);
            dad->values.push_back(nod->values.back());
            sort(dad->values.begin(),dad->values.end());
            delete nod;
            fix_over_flow(dad);
        }
    }
}

void add(int value)
{
    if(root==NULL)
    {
        root=new node;
        root->parent=NULL;
        root->values.push_back(value);
        free_leafs.push(root);
        return;
    }
    if(!free_leafs.empty())
    {
        node* cnod=free_leafs.top();
        free_leafs.pop();
        cnod->values.push_back(value);
        sort(cnod->values.begin(),cnod->values.end());
        full_leafs.push(cnod);
        upscale(cnod);
        return;
    }
    node* cnod=full_leafs.top();
    full_leafs.pop();
    cnod->values.push_back(value);
    sort(cnod->values.begin(),cnod->values.end());
    fix_over_flow(cnod);
    upscale(cnod);
    return;
}


void print_tree(node* nod)
{
    for(auto w:nod->values)
    {
        cout<<w<<" ";
    }
    cout<<"\n";
    for(auto w:nod->children)
    {
        print_tree(w);
    }
    for(auto w:nod->values)
    {
        cout<<w<<" ";
    }
    cout<<"\n";
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        add(a);
        cout<<root->values[0]<<"\n";
    }
}

