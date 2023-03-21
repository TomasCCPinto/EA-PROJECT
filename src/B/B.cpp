#include <iostream>
#include <vector>

using namespace std;

int task, bestprofit, possibilities;
int n, d, k, r;
vector<int> history2;


void recursive(vector<int> shares,vector<int> history, int profit, int acoes,int day){

    

    if(day == d && acoes==0){
        if(profit > bestprofit){
            bestprofit = profit;
            possibilities=1;
            history2 = history;
        }
        else if(profit == bestprofit) {
            possibilities++;
            history2 = history;
        }


        return;
    }
    else if(day == d) return;
    
    for (int i = 0; i <= acoes; i++)
    {
        history[day]=i;
        recursive(shares,history,profit + i*shares[day] - i*r ,acoes - i, day+1);
    }
    

    for (int i = 1; i <= k-acoes; i++)
    {
        history[day]=-i;
        recursive(shares,history,profit - i*shares[day],acoes + i, day+1);
    }
    
    return;
}


int main(){

    
    cin >> task;

    cin >> n >> d >> k >> r;

    for (int i = 0; i < n; i++){
        vector<int> shares;
        vector<int> history(d+1,0);
        int s;
        for (int j = 0; j < d; j++)
        {
            cin >> s;
            shares.push_back(s);
                   
        }
        bestprofit=0;
        possibilities=0;
        recursive(shares,history,0,0,0);
        
        if(task==1)cout << bestprofit << endl;
        else if (task==2){
            cout << bestprofit << endl;
            for (int x=0; x < d ; x++)
            {
                cout << history2[x] << " ";
            }
            cout << endl;
        }
        else if(task==3) cout << bestprofit << " " << possibilities << endl;

        for (int x=0; x < d ; x++){
            history[x]=0;
        }
    }

    return 0;
}