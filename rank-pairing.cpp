#include <fstream>
#include<iostream>
#include<vector>
using namespace std;
struct node{ ///heapul este, in esenta, un pointer catre nod, si e de maxim
    int val;
    node* child;
    node* bro;
    node(int x=0, node* son=NULL, node* bro_=NULL): val(x), child(son), bro(bro_) {}
};
class pairingHeap{
private:
    node* root;
    node* getRoot(){
        return root;
    }
    void setRoot(node* point){
        root=point;
    }
    node* mergeNodes(node* h1, node* h2){
        if(h1==NULL){
            h1=h2;
            return h1;
        }
        if(h2==NULL)
            return h1;
        if(h1->val<h2->val)
            swap(h1, h2);
        h2->bro=h1->child;
        h1->child=h2;
        return h1;
    }
    node* mergeSons(node* h){ ///asta, de fapt, scoate maximul
        if(h==NULL||h->bro==NULL)
            return h;///sf. iulia din sziget!
        node* one=h;
        node* two=h->bro;
        node* three=h->bro->bro;
        one->bro=two->bro=NULL;
        return mergeNodes(mergeNodes(one, two), mergeSons(three));
    }
public:
    pairingHeap(int key){
        root=new node(key); ///ca sa il stearga, trb alocare dinamica
    }
    pairingHeap(node* root_=NULL): root(root_) {}
    int findMax(){
        return root->val;
    }
    void mergeHeap(pairingHeap other){
        if(root==NULL){
            root=other.root;
            return;
        }
        else if(other.root==NULL)
            return;
        if(root->val<other.root->val)
            swap(root, other.root);
        other.root->bro=root->child;
        root->child=other.root;
        other.root=NULL;
    }
    void push(int key){
        mergeHeap(pairingHeap(key));
    }
    void pop(){
        node *temp=root;
        root=mergeSons(temp->child);
        delete temp;///la ce foloseste temp, naiba stie
    }
    void mergeSet(pairingHeap &other){
        mergeHeap(other);
        other.root=NULL;///dupa ce o amesteca, o distruge, ca sa nu ocupe memoria degeaba
    }
    void decKey(node* h, int amount){ ///scade fiul lui h cu cat zic eu
       if(amount<0)
          std::cout<<"NU POTI CRESTE CHEIA\n";
       else{
          node* kid=h->child;
          h->child=NULL;
          (kid->val)-=amount;
          mergeHeap(pairingHeap(kid));
       }
    }
};
std::vector<pairingHeap> h; ///nu vom dezaloca un heap interclasat, se mai poate baga in el
int main()
{
    std::ifstream fin("heap.in");
    std::ofstream fout("heap.out");
    int n, opcount, opcode; fin>>n>>opcount;
    for(int i=0; i<n; i++){
       pairingHeap temp;
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
          fout<<h[id].findMax()<<"\n";
          h[id].pop();
       }
       else if(opcode==3){
          int id, otherId; fin>>id>>otherId;
          h[id].mergeHeap(h[otherId]);
       }
    }
    return 0;
}
