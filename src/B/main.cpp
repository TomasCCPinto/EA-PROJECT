#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 +7;
int task, bestprofit, possibilities;
int n, d, k, r;

int conta;


struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};


int task1_without_dp(const vector<int> &shares, int day, int profit, bool can_buy) {
    conta++;
    for (int i = 0; i < day; ++i) 
        cout << " ";
    cout << day << " . " << profit << endl;

    if(day == d) {
        if(profit > bestprofit){
            bestprofit = profit;
        }
        return profit;
    }
    
    int recursive_calc;
    if(!can_buy) {
        // sell
        int a = task1_without_dp(shares, day+1, profit, can_buy);
        int b = task1_without_dp(shares, day+1, profit + k*shares[day], true);
        recursive_calc = max(a, b);
    } else {
        // buy
        int a = task1_without_dp(shares, day+1, profit, can_buy);
        int b = task1_without_dp(shares, day+1, profit - k*shares[day] - k*r, false);
        recursive_calc = max(a, b);
    }

    return recursive_calc;
}


int task1_with_dp(const vector<int> &shares, unordered_map<pair<int, int>, int, hash_pair> &dp, int day, int profit, bool can_buy) {
    conta++;
    for (int i = 0; i < day; ++i) 
        cout << " ";
    cout << day << " . " << profit << endl;

    if (dp.count({day, profit})) {
        return dp[{day, profit}];
    }

    if(day == d) {
        if(profit > bestprofit){
            bestprofit = profit;
            dp[{day, profit}] = bestprofit;
        }
        return profit;
    }
    
    if(!can_buy) {
        // sell
        dp[{day, profit}] = max(task1_with_dp(shares, dp, day+1, profit, can_buy), task1_with_dp(shares, dp, day+1, profit + k*shares[day], true));
    } else {
        // buy
        dp[{day, profit}] = max(task1_with_dp(shares, dp, day+1, profit, can_buy), task1_with_dp(shares, dp, day+1, profit - k*shares[day] - k*r, false));
    }

    return dp[{day, profit}];
}


int main(){

    cin >> task;
    cin >> n >> d >> k >> r;

    for (int i = 0; i < n; i++){
        vector<int> shares(d);
        
        for (int j = 0; j < d; j++) {
            cin >> shares[j];
        }

        bestprofit = 0;
        possibilities = 0;
        
        if(task == 1) {
            cout << "\n============= day === profit ================\n\n";
            conta = 0;

            unordered_map<pair<int, int>, int, hash_pair> dp;
            // task1_without_dp(shares, 0, 0, true);
            task1_with_dp(shares, dp, 0, 0, true);

            cout << "solve: " << bestprofit << endl;
            cout << "recursions: " << conta << endl;
        } 
    }

    return 0;
}

