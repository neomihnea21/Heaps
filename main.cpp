#include <fstream>
#include<list>
#include<vector>
using namespace std;
struct node{ ///astia vor fi niste arbori skew-binomiali
    int val, deg;
    node *child, *bro, *dad;
    node(int val_=0, node* child_=NULL, node* bro_=NULL, node* dad_=NULL):
        val(val_), child(child_), bro(bro_), dad(dad_) {}
};
class skewBinomialHeap{///ca la binomiala, dar tine alte ordine de arbore
private:
    list<node*> v;
    void addTree(node* x){///nota: pe asta o chem, de regula, cu arbori singleton
        v.push_front(x);
    }
    list<node*>::iterator findMaxNode(){
        list<node*>::iterator maxit=v.begin();
        for(list<node*>::iterator it=v.begin(); it!=v.end(); it++){
            if((*it)->val>((*maxit)->val))
                maxit=it;
        }
        return maxit;
    }
    void deleteRoot(node* tree, skewBinomialHeap &h){
        if(tree->deg==0){
            delete tree;
        }
        else{
            node* temp=tree; ///va fi sters, asa ca trb sa stim unde era
            tree->child->dad=NULL;///daca i-am dezalocat tatal, ii face bine sa-l uite
            temp=temp->child;
            h.addTree(tree->child);
            while(temp->bro!=NULL){
                temp->bro->dad=NULL;///si fratii lui patesc la fel
                h.addTree(temp->bro);
                temp=temp->bro;
            }
        }
        delete tree;
        v=h.v;
    }
    node* simpleMerge(node* tree1, node* tree2){
        if(tree1->val<tree2->val)
            swap(tree1, tree2);///legatura simpla: cel cu varful mai mare devine tata tuturor
        tree2->bro=tree1->child;
        tree2->dad=tree1;
        tree1->child=tree2;
        tree1->deg++;
        return tree1;
    }
     void resizeTrees(){
        if(v.size()<=1) return;
        list <node*> :: iterator prev, curr, next, temp;
        prev=curr=v.begin();
        curr++;
        next = curr;
        next++;
        while(curr!=v.end()){
            while ((next==v.end()||(*next)->deg>(*curr)->deg) &&
                   curr!=v.end()&&(*prev)->deg==(*curr)->deg){
                *curr=simpleMerge(*curr, *prev);
                temp = prev;
                if(prev==v.begin()){
                    prev++;
                    curr++;
                    if( next != v.end() )
                        next++;
                }
                else prev--;
                v.erase( temp );
            }
            prev++;
            if(curr!=v.end()) curr++;
            if(next!=v.end()) next++;
        }
     }
public:
    int top(){
        list<node*>::iterator it=findMaxNode();
        return (*it)->val;
    }
    void mergeHeaps(skewBinomialHeap &other){///TODO refa cu iteratori istoria
        skewBinomialHeap newHeap;
        list<node*>::iterator i(v.begin()), j(other.v.begin());///sunt sortate dupa grad, asa ca e doar o banala interclasare
        while(i!=v.end()&&j!=other.v.end()){ ///pe POINTERI
            if((*i)->deg<(*j)->deg){
                newHeap.addTree(*i);
                i++;
            }
            else{
                newHeap.addTree(*j);
                j++;
            }
        }
        while(i!=v.end()){
            newHeap.addTree((*i));
            i++;
        }
        while(j!=v.end()){
            newHeap.addTree(*j);
            j++;
        }
        other.v.clear();
        newHeap.resizeTrees();///avem kilotone de coliziuni, care trebuie drese
        v=newHeap.v;
    }
    void push(int x){
        node* n=new node(x);
        list<node*>::iterator it=v.begin(), it2=(++it);
        it=v.begin();
        if((*it)->deg!=(*it2)->deg)
           v.push_front(n);
        else{
            int k1=(*it)->val, k2=(*it2)->val;
            if(x>k1&&x>k2){
                (*it)->bro=(*it2);
                n->child=(*it);
                (*it)->dad=n;
                v.push_front(n);
            }
            else{
                node *n1=(*it), *n2=(*it2);
                if(k1<k2)
                    swap(n1, n2);///n1 e cel de chei maxima
                n1->child=n;
                n->bro=n2;
                n->dad=n1;
                v.push_front(n1);
            }
        }
    }
    void pop(){
        list<node*>::iterator x=findMaxNode();
        skewBinomialHeap newHeap;
        deleteRoot((*x), newHeap);
        v.erase(x);///stergem nodul din vector
        mergeHeaps(newHeap);
    }
};
std::vector<skewBinomialHeap> h;
int main()
{
    std::ifstream fin("heap.in");
    std::ofstream fout("heap.out");
    int n, opcount, opcode; fin>>n>>opcount;
    for(int i=0; i<n; i++){
       skewBinomialHeap temp;
       h.push_back(temp);
    }
    for(int i=0; i<opcount; i++){
       fin>>opcode;
       if(opcode==1){
          int id, val; fin>>id>>val;
          h[id].push(val);
       }
       else if(opcode==2){
          int id; fin>>id;
          fout<<h[id].top()<<"\n";
          h[id].pop();
       }
       else if(opcode==3){
          int id, otherId; fin>>id>>otherId;
          h[id].mergeHeaps(h[otherId]);
       }
    }
    return 0;
}
