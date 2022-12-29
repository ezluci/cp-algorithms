// PROBLEM: https://www.pbinfo.ro/probleme/45/verifprim
// LEARN: https://en.wikipedia.org/wiki/Fermat_primality_test

#include <bits/stdc++.h>
using namespace std;


unsigned ezpow(unsigned a, unsigned b, unsigned mod)
{
   unsigned ans = 1;
   for (; b; b >>= 1)
   {
      if (b & 1)
         ans = 1ULL*ans*a % mod;
      a = 1ULL*a*a % mod;
   }

   return ans;
}


bool prim(unsigned x, const int tests = 1)
{
   if (x <= 1)
      return 0;
   if (x <= 3)
      return 1;
   
   for (int t = 1; t <= tests; ++t)
   {
      unsigned a = 2 + rand() % (x-3);
      if (ezpow(a, x-1, x) != 1)
         return 0; // not prime for sure.
   }
   
   return 1; // probably prime.
}


int main()
{
   int x;
   cin >> x;
   cout << (prim(x, 10) ? "DA" : "NU");
}