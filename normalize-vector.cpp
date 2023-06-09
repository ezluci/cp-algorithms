#include <bits/stdc++.h>
using namespace std;

struct Elem {
   int val, idx, nrm;
};

Elem* normalize(Elem v[], int st, int dr)
{
   for (int i = st; i <= dr; ++i)
      v[i].idx = i;
   
   sort(v + st, v + dr+1, [](const Elem &A, const Elem &B) {
      return (A.val < B.val);
   });

   v[st].nrm = 1;
   for (int i = st+1; i <= dr; ++i)
      v[i].nrm = v[i-1].nrm + (v[i-1].val != v[i].val);
   
   sort(v + st, v + dr+1, [](const Elem &A, const Elem &B) {
      return (A.idx < B.idx);
   });

   return v;
}

vector<Elem>& normalize(vector<Elem> &v, int st, int dr)
{
   for (int i = st; i <= dr; ++i)
      v[i].idx = i;
   
   sort(v.begin() + st, v.begin() + dr+1, [](const Elem &A, const Elem &B) {
      return (A.val < B.val);
   });

   v[st].nrm = 1;
   for (int i = st+1; i <= dr; ++i)
      v[i].nrm = v[i-1].nrm + (v[i-1].val != v[i].val);
   
   sort(v.begin() + st, v.begin() + dr+1, [](const Elem &A, const Elem &B) {
      return (A.idx < B.idx);
   });

   return v;
}

int main()
{
   
}
