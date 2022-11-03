// PROBLEM: https://www.geeksforgeeks.org/program-nth-catalan-number/
// https://en.wikipedia.org/wiki/Catalan_number
// https://practice.geeksforgeeks.org/problems/nth-catalan-number0817/1

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;  // https://www.geeksforgeeks.org/factorial-large-number-using-boost-multiprecision-library/
using namespace std;


class Solution
{
   private:
   cpp_int fact(int n)
   {
      cpp_int x = 1;
      for (int i = 2; i <= n; ++i)
         x *= i;
      
      return x;
   }

   cpp_int comb(int n, int k)
   {
      return fact(n) / (fact(n-k) * fact(k));
   }

   public:
   cpp_int findCatalan(int n)
   {
      return fact(2*n) / (fact(n) * fact(n+1));


      /* 2
      return comb(2*n, n) / (n+1);
      */


      /* 3
      cpp_int x1 = 1, x2 = 1;
      for (int i = 2; i <= n; ++i)
      {
         x1 *= n+i;
         x2 *= i;
      }

      return x1 / x2;
      */
   }
};


int main()
{
   // taking count of testcases
	int t;
	cin >> t;

	while (t--)
   {
	   // taking nth number
	   int n;
	   cin >> n;
	   Solution obj;
	   // calling function findCatalan function
	   cout << obj.findCatalan(n) << '\n';
	}

	return 0;
}