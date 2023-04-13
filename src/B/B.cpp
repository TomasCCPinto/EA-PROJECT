#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long int lli;
const int mod = 1e9 +7;
lli task, bestprofit, possibilities;
int n, d, k, r;
vector<int> history2;


//task 1 
lli task1(vector<int> &shares){

   vector <vector<lli>> dp (d+1,vector<lli>(2, -1));

   dp[0][0]=0;
   dp[0][1]= (-k * shares[0] - k*r);

   for (int i = 1; i < d; i++)
   {
    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + shares[i]*k);
    dp[i][1] = max(dp[i-1][1], dp[i-1][0] - shares[i]*k - k*r);
   }
   
   return dp[d-1][0];
}


//task 2
lli task2(vector<int> &shares){
    vector <vector<lli>> dp (d+1,vector<lli>(2, -1));
    vector<int> history(d+1,0);

    dp[0][0]=0;
    dp[0][1]= (-k * shares[0] - k*r);

  
    for (int i = 1; i < d; i++)
    {

        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + shares[i]*k);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] - shares[i]*k - k*r);
    } 

    
    int side=0;
    for (int i = d-1; i >=0; i--)
    {
        if(i==0){
            if(side){
                history[i] = k;
                side=0;
            }
            continue;
        }
        if (!side)
        {
            if(dp[i][0]!=dp[i-1][0]){
                history[i] = -k;
                side=1;
            }
        }
        else{
            if(dp[i][1]!=dp[i-1][1]){
                history[i] = k;
                side=0;
            }
        }
        
    }
 
    history2 = history;
    return dp[d-1][0];
   
}


//task 3
lli task3(vector<int> &shares){
    vector <vector<lli>> dp (d+1,vector<lli>(k+2, -1));
    vector <vector<lli>> paths (d+1,vector<lli>(k+2, -1));

    dp[0][0]=0;
    paths[0][0]=1;
    for (int i = 1; i <= k; i++)
    {
        dp[0][i]= (-i * shares[0] - i*r);
        paths[0][i]=1;
    }
    

    for (int i = 1; i < d; i++){

        for (int j = 0; j <= k; j++)
        {
            lli maximo=-INT_MAX;
        
            for(int z=0; z<=k; z++){
                 if(z==j){
                    if(maximo < dp[i-1][z]){
                        maximo = dp[i-1][z];
                        paths[i][j] = paths[i-1][z] % mod; 
                    }
                    else if(maximo == dp[i-1][z]){
                        paths[i][j] = (paths[i][j] + paths[i-1][z]) % mod ;
                    }
                   
                }
                else if(z<j){
                    if(maximo < (dp[i-1][z] - shares[i]*(j-z) - (j-z)*r)){
                        maximo = (dp[i-1][z] - shares[i]*(j-z) - (j-z)*r);
                        paths[i][j] = paths[i-1][z] % mod;
                    }
                    else if(maximo == (dp[i-1][z] - shares[i]*(j-z) - (j-z)*r)){
                        paths[i][j] = (paths[i][j] + paths[i-1][z]) % mod;
                    }
                   
                }
                else{
                    if(maximo < (dp[i-1][z] + shares[i]*(z-j))){
                        maximo = (dp[i-1][z] + shares[i]*(z-j));
                        paths[i][j] = paths[i-1][z] % mod;
                    }
                    else if(maximo == (dp[i-1][z] + shares[i]*(z-j))){
                        paths[i][j] = (paths[i][j] + paths[i-1][z]) % mod;
                    }
                 
                }         
            }
            dp[i][j] = maximo;
        }
    }

        
    possibilities = paths[d-1][0];
    return dp[d-1][0];
}



int main(){

    
    cin >> task;

    cin >> n >> d >> k >> r;

    //conta=0;
    for (int i = 0; i < n; i++){
        vector<int> shares;
        
        int s;
        for (int j = 0; j < d; j++)
        {
            cin >> s;
            shares.push_back(s);
                   
        }
        possibilities=0;
        
     
        if(task==1){   
            cout << task1(shares) << endl;
        }
        else if (task==2){
            cout << task2(shares) << endl;
            for (int x=0; x < d ; x++)
            {
                cout << history2[x] << " ";
            }
            cout << endl;
        }
        else if(task==3){
            
            cout << task3(shares) << " " << possibilities << endl;
        }
       
    }
    

    return 0;
}