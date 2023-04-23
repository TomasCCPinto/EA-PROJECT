#include <iostream>
#include <vector>
#include <stack>
#include <climits>

typedef long long int lli;
using namespace std;

lli maxvalue ;
lli t;


void tarjan(vector<lli> entitlement,stack<lli> &pilha,vector<bool> &visited,vector<lli> &low, vector<lli> &dfs, vector<vector<lli>> &adj, lli v) {
  low[v] = t;
  dfs[v] = t;
  t += 1;
  pilha.push(v);
  visited[v] = true;
  for (int x = 0; x < (int)adj[v].size(); x++) {
    if (dfs[adj[v][x]] == 0) {
      tarjan(entitlement,pilha,visited,low,dfs,adj, adj[v][x]);
      low[v] = min(low[v], low[adj[v][x]]);
    } else if (visited[adj[v][x]] == true) {
      low[v] = min(low[v], dfs[adj[v][x]]);
    }
  }

  if (low[v] == dfs[v]) {
    lli cont=0;
    lli value=0;
    while (1) {
        lli w = pilha.top();
        cont++;
        value+= entitlement[w];
        pilha.pop();
        visited[w] = false;
        if (w == v)
            break;
    }
    if(cont>1){
        if(value > maxvalue) maxvalue = value;
    }
  }
}

int main(){

    lli n;
    while(cin >> n){
        vector<vector<lli>> adj(n + 2, vector<lli>());
        vector<lli> entitlement (n+2, 0);
        stack<lli> pilha;
        vector<lli> low(n+2, 0);
        vector<lli> dfs(n+2, 0);
        vector<bool> visited(n+2, false);
        maxvalue = -INT_MAX;
        t=1;
        lli b,input,d;

        for (int i = 0; i < n; i++) {
            cin >> b;
            while(cin >> input && input != 0){
                cin >> d;
                adj[b].push_back(d);
                entitlement[b]-=input;
                entitlement[d]+=input;
            }
            
        }
           
        for (int x = 1; x <= n; x++) {
            if (dfs[x] == 0) {
                tarjan(entitlement,pilha,visited,low,dfs,adj, x);
            }
        }

        if(maxvalue== -INT_MAX) cout << "No cluster\n" ; 
        else cout << maxvalue << endl;


    }

    return 0;
}