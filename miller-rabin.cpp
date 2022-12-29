// PROBLEM: https://www.pbinfo.ro/probleme/45/verifprim
// LEARN: https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/

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


bool prime(unsigned n, const int tests = 1)
{
   if (n <= 1)
      return false;
   if (n <= 3)
      return true;

   unsigned m = n-1; // n-1 without the factors of 2
   for (; m % 2 == 0; m >>= 1);
   
   for (int t = 1; t <= tests; ++t)
   {
      unsigned a = 2 + rand() % (n-3);

      unsigned b = ezpow(a, m, n);
      if (b == 1 || b == n-1)
         goto next_test; // probably prime, go to the next test.
      else
      {
         for (unsigned mc = m; mc != n-1; mc <<= 1)
         {
            b = 1ULL*b*b % n;
            if (b == 1)
               return false; // surely not a prime.
            if (b == n-1)
               goto next_test; // probably prime, go to the next test.
         }

         return false; // surely not a prime.
      }

      next_test:;
   }

   return true; // probably prime.
}


int main()
{
   int x;
   cin >> x;
   cout << (prime(x, 10) ? "DA" : "NU");
}