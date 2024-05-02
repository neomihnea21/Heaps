#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<unordered_set>
using namespace std;

ifstream in("mergeheap.in");
ofstream out("mergeheap.out");

struct node{

node* parent;
vector<node*> children;
vector<int> values;
};

const int NMAX=1000007;

const int INF=2147483647;

node* roots[NMAX];

unordered_set<node*> free_leafs[NMAX];
unordered_set<node*> full_leafs[NMAX];

void upscale(node* nod,int nr)
{
    if(nod==roots[nr])
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
    upscale(dad,nr);
}

node* fix_over_flow(node* nod,int nr)
{
    if(nod->values.size()<=2)
    {
        return nod;
    }
    if(nod==roots[nr])
    {
        if(nod->children.size()==0)
        {
            node* child1=new node;
            node* child2=new node;
            child1->parent=nod;
            child2->parent=nod;
            free_leafs[nr].insert(child1);
            free_leafs[nr].insert(child2);
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
            free_leafs[nr].insert(child1);
            free_leafs[nr].insert(child2);
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
            node* lol=fix_over_flow(dad,nr);
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
            node* lol=fix_over_flow(dad,nr);
            return child1;
        }
    }
}

void add(int value,int nr)
{
    if(roots[nr]==NULL)
    {
        roots[nr]=new node;
        roots[nr]->parent=NULL;
        roots[nr]->values.push_back(value);
        free_leafs[nr].insert(roots[nr]);
        return;
    }
    if(!free_leafs[nr].empty())
    {
        node* cnod=*free_leafs[nr].begin();
        free_leafs[nr].erase(free_leafs[nr].begin());
        cnod->values.push_back(value);
        sort(cnod->values.begin(),cnod->values.end());
        full_leafs[nr].insert(cnod);
        upscale(cnod,nr);
        return;
    }
    node* cnod=*full_leafs[nr].begin();
    full_leafs[nr].erase(full_leafs[nr].begin());
    cnod->values.push_back(value);
    sort(cnod->values.begin(),cnod->values.end());
    upscale(fix_over_flow(cnod,nr),nr);
    return;
}

node* bring_down(node* nod,int nr)
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
    return bring_down(min_nod,nr);
}

void adjust(node* nod,int nr)
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
        adjust(min_nod,nr);
    }
    else
    {
        sort(nod->values.begin(),nod->values.end());
        return;
    }
}


void fix_under_flow(node* nod,int nr)
{   //stim garantat ca nod nu este frunza
    if(nod==roots[nr])
    {
        node* old_root=roots[nr];
        roots[nr]=roots[nr]->children[0];
        roots[nr]->parent=NULL;
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
            adjust(nod,nr);
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
        adjust(best_kid,nr);
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
        adjust(best_kid,nr);
        fix_under_flow(dad,nr);
    }
}

void rem(int nr)   /// fix free_leafs and full_leafs
{
    node* bad_nod=bring_down(roots[nr],nr);
    if(bad_nod==roots[nr])
    {
        reverse(roots[nr]->values.begin(),roots[nr]->values.end());
        roots[nr]->values.pop_back();
        if(roots[nr]->values.size()==1)
        {
            free_leafs[nr].insert(roots[nr]);
            full_leafs[nr].erase(full_leafs[nr].find(roots[nr]));
            return;
        }
        free_leafs[nr].erase(free_leafs[nr].find(roots[nr]));
        roots[nr]=NULL;
        return;
    }
    reverse(bad_nod->values.begin(),bad_nod->values.end());
    bad_nod->values.pop_back();
    if(bad_nod->values.size()==1)
    {
        free_leafs[nr].insert(bad_nod);
        full_leafs[nr].erase(full_leafs[nr].find(bad_nod));
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
                free_leafs[nr].insert(w);
                full_leafs[nr].erase(full_leafs[nr].find(w));
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
            free_leafs[nr].erase(free_leafs[nr].find(bad_nod));
            delete bad_nod;
            full_leafs[nr].insert(dad->children[0]);
            free_leafs[nr].erase(free_leafs[nr].find(dad->children[0]));
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
            free_leafs[nr].erase(free_leafs[nr].find(bad_nod));
            delete bad_nod;
            full_leafs[nr].insert(dad->children[0]);
            free_leafs[nr].erase(free_leafs[nr].find(dad->children[0]));
            dad->children[0]->values.push_back(dad->values.back());
            dad->values.pop_back();
            sort(dad->children[0]->values.begin(),dad->children[0]->values.end());
            fix_under_flow(dad,nr);
        }
    }
}

void mergeheaps(int a,int b)
{
    while(roots[b]!=NULL)
    {
        add(roots[b]->values[0],a);
        rem(b);
    }
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
    int n,q,op,a,b;
    in>>n>>q;
    for(int i=1;i<=q;i++)
    {
        in>>op;
        if(op==1)
        {
            in>>a>>b;
            add(-b,a);
        }
        if(op==2)
        {
            in>>a;
            out<<-roots[a]->values[0]<<"\n";
            rem(a);
        }
        if(op==3)
        {
            in>>a>>b;
            mergeheaps(a,b);
        }
    }
}
