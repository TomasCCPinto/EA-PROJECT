#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long int lli;
const int mod = 1e9 +7;
lli task, bestprofit, possibilities;
int n, d, k, r;
vector<int> history2;
//int conta;

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

    //int acoes = 0;
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
void task3(vector <vector<long long int>> &DP1,vector<int> &shares, lli profit, int acoes,int day){

    if(profit >= DP1[day][acoes]){
        DP1[day][acoes] = profit;
    }
    else{
        return;
    }


    if(day == d && acoes==0){
        if(profit > bestprofit){
            bestprofit = profit;
            possibilities=1;
        }
        else if(profit == bestprofit) {
            possibilities = (possibilities+1) % mod;
        }


        return;
    }
    else if(day == d) return;

    //conta++;
    
    //vender 
    for (int i = 0; i <= acoes; i++)
    {
        task3(DP1,shares,profit + i*shares[day]  , acoes - i, day+1);
    }
    
    
    //comprar
    for (int i = 1; i <= k-acoes; i++)
    {
        task3(DP1,shares,profit - i*shares[day] - i*r ,acoes + i, day+1);
    }
    
    return;
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
        bestprofit=0;
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
            vector <vector<long long int>> DP1 (d+1,vector<long long int>(k+1, -INT_MAX));
            task3(DP1,shares,0,0,0);
            cout << bestprofit << " " << possibilities << endl;
        }
        /*
        for (int i = 1; i <= d; i++)
        {
            for (int j = 0; j < k; j++)
            {
                cout << DP1[i][j] <<  " ";
            }    
            cout << endl;
        }
        */
    }
    //cout << "recursoes: " << conta << endl;

    return 0;
}