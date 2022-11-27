// PROBLEM: https://www.pbinfo.ro/probleme/4093/apa
// LEARN:
//   1) https://www.youtube.com/watch?v=M6cm8UeeziI
//   2) https://www.youtube.com/watch?v=_SdF4KK_dyM

#ifdef EZ
   #include "./ez/ez.h"
#else
   #include <bits/stdc++.h>
#endif
#define mp make_pair
#define mt make_tuple
#define ll long long
#define pb push_back
#define fi first
#define se second
using namespace std;
const string FILE_NAME = "apa";
ifstream fin (FILE_NAME + ".in");
ofstream fout (FILE_NAME + ".out");

const int nMAX = 280;
struct Edge {
   int nex, c, r;
   Edge *rev;
};

int n;
vector<Edge*> gf[nMAX + 1];
int niv[nMAX + 1];
int Next[nMAX + 1];

bool bfs()
{
   queue<int> q;
   q.push(1);
   fill(niv + 1, niv + n+1, 0);
   niv[1] = 1;

   while (!q.empty())
   {
      int nod = q.front();
      q.pop();

      for (Edge *edge : gf[nod])
      {
         if (edge->r > 0 && niv[edge->nex] == 0)
         {
            niv[edge->nex] = niv[nod] + 1;
            q.push(edge->nex);
         }
      }
   }

   return (niv[n]);
}


int dfs(int nod, int flow = INT_MAX)
{
   if (nod == n)
      return flow;
   
   for (; Next[nod] < gf[nod].size(); ++Next[nod])
   {
      Edge *edge = gf[nod][Next[nod]];
      if (edge->r > 0 && niv[nod] + 1 == niv[edge->nex])
      {
         int mini = dfs(edge->nex, min(flow, edge->r));
         if (mini > 0)
         {
            edge->r -= mini;
            edge->rev->r += mini;
            return mini;
         }
      }
   }

   return 0;
}


int main()
{
   fin >> n;
   int a, b, c;
   while (fin >> a >> b >> c)
   {
      Edge *e1, *e2;
      e1 = new Edge{b, c, c-0, nullptr};
      e2 = new Edge{a, 0, 0-0, e1};
      e1->rev = e2;
      gf[a].pb(e1);
      gf[b].pb(e2);
   }
   
   while (bfs())
   {
      fill(Next + 1, Next + n+1, 0);
      while (dfs(1));
   }

   int flow = 0;
   for (Edge *edge : gf[1])
      flow += edge->c - edge->r;
   
   if (flow == 0)
      fout << "Apa nu ajunge!";
   else
      fout << flow;
}