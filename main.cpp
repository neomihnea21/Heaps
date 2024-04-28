#include <iostream>
#include<vector>
using namespace std; ///nu mai fac nicio clasa, e pierdere TOTALA de vreme
struct pairingHeap{
    int val, isEmpty=0;
    vector<pairingHeap*> v;
    pairingHeap(int val_=0, vector<pairingHeap*>v_={}): val(val_), v(v_) {}
};
int findMin(pairingHeap x){
    return x.val;
}
pairingHeap meld(pairingHeap h1, pairingHeap h2){
    if(h1.v.size()==0)
        return h2;
    if(h2.v.size()==0)
        return h1;
    if(h1.val<h2.val){
        h1.v.push_back(&h2);
        return h2;
    }
    else{
        h2.v.push_back(&h1);
        return h2;
    }
}
pairingHeap add(pairingHeap h, int x){
    pairingHeap newP(x);
    return meld(h, newP);
}
pairingHeap removeMin(pairingHeap h){
    if(h.v.size()==0){
        h.val=0;
        return h;
    }
    else{
        pairingHeap ans;
        for(int i=0; i<h.v.size(); i++){
            ans=meld(ans, *(h.v[i]));
        }
        return ans;
    }
}
int main()
{
    pairingHeap h;
    h=add(h, 1);
    cout<<findMin(h);
    return 0;
}
