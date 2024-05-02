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
    pairingHeap(): root(NULL) {}
    pairingHeap(int key){
        root=new node(key); ///aloc dinamic noul nod, ca ii voi da delete mai incolo
    }
    pairingHeap(node* root_): root(root_) {}
    int findMax(){///nu va fi apelat pe vid niciodata
        return root->val;///minimul e mereu in varf
    }
    void mergeHeap(pairingHeap other){
        if(root==NULL){
            root=other.root;
            return;
        }
        if(other.root==NULL)
            return;
        if(root->val<other.root->val)
            swap(root, other.root);
        other.root->bro=root->child;///o facem pe aia cu radacina mica fiica a aleia cu radacina mare, asta e merge-ul in  a nutshell
        root->child=other.root;
        other.root=NULL;
    }
    void push(int key){
        mergeHeap(pairingHeap(key));///push-ul poate fi modelat ca un merge
    }
    void pop(){
        node *temp=root;///scoaterea inseamna sa interclasam tot nivelul pe care se afla
        root=mergeSons(temp->child);
        delete temp;///la ce foloseste temp, naiba stie
    }
    void mergeSet(pairingHeap &other){
        mergeHeap(other);
        other.root=NULL;///dupa ce o amesteca, o distruge, ca sa nu ocupe memoria degeaba
    }
    void incKey(node* h, int amount){ ///creste fiul lui h cu cat zic eu
       if(amount<0)
          std::cout<<"NU POTI CRESTE CHEIA\n";
       else{
          node* kid=h->child;///ia separat fiul lui h
          h->child=NULL;
          (kid->val)+=amount; ///creste cheia, ca nu se strica proprietatea de heap
          mergeHeap(pairingHeap(kid));///si interclaseaza unde s-o potrivi
       }
    }
};
pairingHeap h[2000];
int main()
{
    std::ifstream fin("mergeheap.in");
    std::ofstream fout("mergeheap.out");
    int n, opcount, opcode; fin>>n>>opcount;
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
          h[id].mergeSet(h[otherId]);
       }
    }
    return 0;
}
