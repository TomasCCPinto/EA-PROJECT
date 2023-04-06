#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int mod = 1e9 +7;
int task, bestprofit, possibilities;
int n, d, k, r;
vector<int> history2;
//int conta;

//task 1 e 2
void recursive(vector <vector<long long int>> &DP1,vector<int> &shares,vector<int> &history, int profit, int acoes,int day){

    //cout << profit << endl;

    if(profit > DP1[day][acoes]){
        DP1[day][acoes] = profit;
    }
    else{
        return;
    }

    //cout << DP1[day][acoes] << endl;

    if(day == d && acoes==0){
        if(profit > bestprofit){
            bestprofit = profit;
            possibilities=1;
            history2 = history;
        }
        else if(profit == bestprofit) {
            possibilities = (possibilities+1) % mod;
            history2 = history;
        }


        return;
    }
    else if(day == d) return;

    //cout << day << " " << acoes << " " << profit << endl;
    //conta++;
    

    history[day] = 0;
    recursive(DP1,shares,history,profit , acoes , day+1);
    if(acoes!=0){
        history[day] = -k;
        recursive(DP1,shares,history,profit + k*shares[day]  , acoes - k, day+1);
    }
    else{
        history[day] = k;
        recursive(DP1,shares,history,profit - k*shares[day] - k*r ,acoes + k, day+1);
    }


    return;
}

//task 3
void recursive2(vector <vector<long long int>> &DP1,vector<int> &shares, int profit, int acoes,int day){

    //cout << profit << endl;

    if(profit >= DP1[day][acoes]){
        DP1[day][acoes] = profit;
    }
    else{
        return;
    }

    //cout << DP1[day][acoes] << endl;

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

    //cout << day << " " << acoes << " " << profit << endl;
    //conta++;
    
    //vender 
    for (int i = 0; i <= acoes; i++)
    {
        recursive2(DP1,shares,profit + i*shares[day]  , acoes - i, day+1);
    }
    
    
    //comprar
    for (int i = 1; i <= k-acoes; i++)
    {
        recursive2(DP1,shares,profit - i*shares[day] - i*r ,acoes + i, day+1);
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
        

        vector <vector<long long int>> DP1 (d+1,vector<long long int>(k+1, -INT_MAX));

     
        if(task==1){   
            vector<int> history(d+1,0);
            recursive(DP1,shares,history,0,0,0);
            cout << bestprofit << endl;
        }
        else if (task==2){
            vector<int> history(d+1,0);
            recursive(DP1,shares,history,0,0,0);
            cout << bestprofit << endl;
            for (int x=0; x < d ; x++)
            {
                cout << history2[x] << " ";
            }
            cout << endl;
        }
        else if(task==3){
            recursive2(DP1,shares,0,0,0);
            cout << bestprofit << " " << possibilities << endl;
        }


        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j <k; j++)
            {
                DP1[i][j]=-INT_MAX;
            }    
        }

    

    }
    //cout << "recursoes: " << conta << endl;

    return 0;
}
