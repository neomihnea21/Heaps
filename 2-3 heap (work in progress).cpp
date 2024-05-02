#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<unordered_set>
using namespace std;


struct node{

node* parent;
vector<node*> children;
vector<int> values;
};


unordered_set<node*> free_leafs;
unordered_set<node*> full_leafs;

node* root=NULL;

const int INF=2147483647;

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
    upscale(dad);
}

node* fix_over_flow(node* nod)
{
    if(nod->values.size()<=2)
    {
        return nod;
    }
    if(nod==root)
    {
        if(nod->children.size()==0)
        {
            node* child1=new node;
            node* child2=new node;
            child1->parent=nod;
            child2->parent=nod;
            free_leafs.insert(child1);
            free_leafs.insert(child2);
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
            nod->children.push_back(child1);
            nod->children.push_back(child2);
            return child1;
        }
        else
        {
            node* child1=new node;
            node* child2=new node;
            child1->parent=nod;
            child2->parent=nod;
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
            nod->children.push_back(child1);
            nod->children.push_back(child2);
            return child1;
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
            free_leafs.insert(child1);
            free_leafs.insert(child2);
            child1->values.push_back(nod->values.back());
            nod->values.pop_back();
            child2->values.push_back(nod->values.back());
            nod->values.pop_back();
            vector<node*> aux;
            for(auto w:dad->children)
            {
                if(w!=nod)
                {
                    aux.push_back(w);
                }
            }
            dad->children=aux;
            dad->children.push_back(child1);
            dad->children.push_back(child2);
            dad->values.push_back(nod->values.back());
            sort(dad->values.begin(),dad->values.end());
            delete nod;
            node* lol=fix_over_flow(dad);
            return child1;
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
            vector<node*> aux;
            for(auto w:dad->children)
            {
                if(w!=nod)
                {
                    aux.push_back(w);
                }
            }
            dad->children=aux;
            dad->children.push_back(child1);
            dad->children.push_back(child2);
            dad->values.push_back(nod->values.back());
            sort(dad->values.begin(),dad->values.end());
            delete nod;
            node* lol=fix_over_flow(dad);
            return child1;
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
        free_leafs.insert(root);
        return;
    }
    if(!free_leafs.empty())
    {
        node* cnod=*free_leafs.begin();
        free_leafs.erase(free_leafs.begin());
        cnod->values.push_back(value);
        sort(cnod->values.begin(),cnod->values.end());
        full_leafs.insert(cnod);
        upscale(cnod);
        return;
    }
    node* cnod=*full_leafs.begin();
    full_leafs.erase(full_leafs.begin());
    cnod->values.push_back(value);
    sort(cnod->values.begin(),cnod->values.end());
    upscale(fix_over_flow(cnod));
    return;
}

node* bring_down(node* nod)
{
    if(nod->children.size()==0)
    {
        return nod;
    }
    int minn=INF;
    node* min_nod;
    for(auto w:nod->children)
    {
        if(w->values[0]<minn)
        {
            minn=w->values[0];
            min_nod=w;
        }
    }
    swap(min_nod->values[0],nod->values[0]);
    sort(nod->values.begin(),nod->values.end());
    return bring_down(min_nod);
}

void adjust(node* nod)
{
    if(nod->children.size()==0)
    {
        sort(nod->values.begin(),nod->values.end());
        return;
    }
    int minn=INF;
    node* min_nod;
    for(auto w:nod->children)
    {
        if(w->values[0]<minn)
        {
            minn=w->values[0];
            min_nod=w;
        }
    }
    if(minn<nod->values[0])
    {
        swap(min_nod->values[0],nod->values[0]);
        sort(nod->values.begin(),nod->values.end());
        adjust(min_nod);
    }
    else
    {
        sort(nod->values.begin(),nod->values.end());
        return;
    }
}


void fix_under_flow(node* nod)
{   //stim garantat ca nod nu este frunza
    if(nod==root)
    {
        node* old_root=root;
        root=root->children[0];
        root->parent=NULL;
        delete old_root;
        return;
    }
    for(auto w:nod->parent->children)
    {  ///we try to borrow a value from a sibling
        if(w->values.size()==2)
        {
            nod->values.push_back(w->values.back());
            w->values.pop_back();
            nod->children.push_back(w->children.back());
            w->children.pop_back();
            nod->children.back()->parent=nod;
            adjust(nod);
            return;
        }
    }
    if(nod->parent->values.size()==2)
    {
        node* dad=nod->parent;
        vector<node*> aux;
        for(auto w:dad->children)
        {
            if(w!=nod)
            {
                aux.push_back(w);
            }
        }
        dad->children=aux;
        node* best_kid=dad->children[0];
        best_kid->values.push_back(dad->values.back());
        dad->values.pop_back();
        best_kid->children.push_back(nod->children[0]);
        nod->children[0]->parent=best_kid;
        delete nod;
        adjust(best_kid);
        return;
    }
    else if(nod->parent->values.size()==1)
    {
        node* dad=nod->parent;
        vector<node*> aux;
        for(auto w:dad->children)
        {
            if(w!=nod)
            {
                aux.push_back(w);
            }
        }
        dad->children=aux;
        node* best_kid;
        best_kid=dad->children[0];
        best_kid->values.push_back(dad->values.back());
        dad->values.pop_back();
        best_kid->children.push_back(nod->children[0]);
        nod->children[0]->parent=best_kid;
        delete nod;
        adjust(best_kid);
        fix_under_flow(dad);
    }
}

void rem()   /// fix free_leafs and full_leafs
{
    node* bad_nod=bring_down(root);
    if(bad_nod==root)
    {
        reverse(root->values.begin(),root->values.end());
        root->values.pop_back();
        if(root->values.size()==1)
        {
            free_leafs.insert(root);
            full_leafs.erase(full_leafs.find(root));
            return;
        }
        free_leafs.erase(free_leafs.find(root));
        root=NULL;
        return;
    }
    reverse(bad_nod->values.begin(),bad_nod->values.end());
    bad_nod->values.pop_back();
    if(bad_nod->values.size()==1)
    {
        free_leafs.insert(bad_nod);
        full_leafs.erase(full_leafs.find(bad_nod));
        return;
    }
    else
    {
        /// we try to borrow a value from a sibling
        for(auto w:bad_nod->parent->children)
        {
            if(w->values.size()==2)
            {
                bad_nod->values.push_back(w->values.back());
                w->values.pop_back();
                free_leafs.insert(w);
                full_leafs.erase(full_leafs.find(w));
                return;
            }
        }
        if(bad_nod->parent->values.size()==2)
        {
            node* dad=bad_nod->parent;
            vector<node*> aux;
            for(auto w:dad->children)
            {
                if(w!=bad_nod)
                {
                    aux.push_back(w);
                }
            }
            dad->children=aux;
            free_leafs.erase(free_leafs.find(bad_nod));
            delete bad_nod;
            full_leafs.insert(dad->children[0]);
            free_leafs.erase(free_leafs.find(dad->children[0]));
            dad->children[0]->values.push_back(dad->values.back());
            dad->values.pop_back();
            sort(dad->children[0]->values.begin(),dad->children[0]->values.end());
            return;
        }
        else if(bad_nod->parent->values.size()==1)
        {
            node* dad=bad_nod->parent;
            vector<node*> aux;
            for(auto w:dad->children)
            {
                if(w!=bad_nod)
                {
                    aux.push_back(w);
                }
            }
            dad->children=aux;
            free_leafs.erase(free_leafs.find(bad_nod));
            delete bad_nod;
            full_leafs.insert(dad->children[0]);
            free_leafs.erase(free_leafs.find(dad->children[0]));
            dad->children[0]->values.push_back(dad->values.back());
            dad->values.pop_back();
            sort(dad->children[0]->values.begin(),dad->children[0]->values.end());
            fix_under_flow(dad);
        }
    }
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a,op;
        cin>>op;
        if(op==1)
        {
            cin>>a;
            add(a);
        }
        if(op==2)
        {
            cout<<root->values[0]<<"\n";
        }
        if(op==3)
        {
            rem();
        }
    }
}
