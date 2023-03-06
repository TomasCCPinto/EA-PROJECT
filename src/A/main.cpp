/**
    Authors:
    Joao Moreira 2020230563
    Tomas Pinto 2020224069
*/
#include <bits/stdc++.h>

using namespace std;


vector<vector<int>> cp;

vector<int> lb(31);    // black line cells
vector<int> cb(31);    // black column cells
vector<int> lt(31);    // line transitions
vector<int> ct(31);    // col transitions
vector<int> qb(4);     // quadrant black cells
vector<int> db(2);     // diagonal black cells 

int valid_qr;
int chao;


void printQR(vector<vector<int>> &QR) {
    cout << "+";
    for (int i = 0; i < (int) QR.size(); ++i) {
        cout << "-";
    }
    cout << "+\n";
    for (auto v:QR) {
        cout << "|";
        for (auto vv:v)
            if (vv == 1)
                cout << "#";
            else
                cout << " ";
        cout << "|\n";
    }
    cout << "+";
    for (int i = 0; i < (int) QR.size(); ++i) {
        cout << "-";
    }
    cout << "+\n";
}


bool validation(vector<vector<int>> &QR){
    int N, C, Tx, Tc, D1, D2;
    N = C = Tx = Tc = D1 = D2 = 0;

    int Q1, Q2, Q3, Q4;
    Q1 = Q2 = Q3 = Q4 = 0;

    for (int i = 0; i < (int) QR.size(); ++i) {
        for (int j = 0; j < (int) QR.size(); ++j) {
            
            if(i==j && QR[i][j]==1) D1++;
            if((j== (int) QR.size() - 1 - i) && QR[i][j])  D2++;
            if((j+1)<(int) QR.size() && QR[i][j] != QR[i][j+1]){
                Tx++;
            }
            if((j+1)<(int) QR.size() && QR[j][i] != QR[j+1][i]){
                Tc++;
            }
        }
        if (Tx != lt[i]) {
            return false;
        } else if (Tc != ct[i]) {
            return false;
        }
        Tx = 0;
        Tc = 0;
    }

    return true;
}


void recursion(vector<vector<int>> &QR, int i, int j) {
    if (lb[i] < 0 || cb[j] < 0)
        return;
    if (qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0)
        return;
    if (db[0] < 0 || db[1] < 0)
        return;
    if (j != 0 && cb[j-1] < 0)
        return;

    if (i == (int) QR.size()) {
        if (validation(QR) && !db[0] && !db[1]) {
            valid_qr++;
            cp = QR;
        }
        return;
    }

    if (j == (int) QR.size()) {
        if (lb[i] != 0)
            return;
        recursion(QR, i+1, 0);
        return;
    }

    if(j>0){
        int contatx=0;
        for (int x = 1; x < j; x++){
            if(QR[i][x] != QR[i][x-1]) contatx++; 
        }
        if(contatx>lt[i]) return;
    }
    if(i>0){
        int contatc=0;
        for (int x = 1; x < i; x++){
            if(QR[x][j] != QR[x-1][j]) contatc++; 
        }
        if(contatc>ct[j]) return;
    }
    
    if(lb[i] == (int) QR.size() - j){
        bool v = false;
        for (int x = j; x < (int) QR.size(); x++) {
            if(!cb[x])v = true;
        }
        if(!v){
            for (int x = j; x < (int) QR.size(); x++) {
                QR[i][x] = 1;
                lb[i]--;
                cb[x]--;
                if (i <= chao && x >  chao) qb[0]--;
                else if (i <= chao && x <= chao) qb[1]--;
                else if (i >  chao && x <= chao) qb[2]--;
                else if (i >  chao && x >  chao) qb[3]--;

                if(i == x) db[0]--;
                if(x == (int) QR.size() - 1 - i)  db[1]--;
            }

            recursion(QR, i+1, 0);

            for (int x = j; x < (int) QR.size(); x++) {
                QR[i][x] = 0;
                lb[i]++;
                cb[x]++;
                if (i <= chao && x >  chao) qb[0]++;
                else if (i <= chao && x <= chao) qb[1]++;
                else if (i >  chao && x <= chao) qb[2]++;
                else if (i >  chao && x >  chao) qb[3]++;

                if(i == x) db[0]++;
                if(x == (int) QR.size() - 1 - i)  db[1]++;
            }
        }
        return;
    }

    //Q1 E Q2 DONE 
    if (i <= chao && !qb[1] && !qb[0]){
        recursion(QR, chao+1, 0);
        return;
    }
    //Q2 DONE
    if (i <= chao && j <= chao && !qb[1]){
        recursion(QR, i, chao+1);
        return;
    } 
    //Q3 E Q4 DONE
    if (i > chao && !qb[2] && !qb[3]){
        recursion(QR, (int) QR.size(), 0);
        return;
    }
    //Q3 DONE
    if (i > chao && j <= chao && !qb[2]){
        recursion(QR, i, chao+1);
        return;
    } 

    if(!lb[i]){
        recursion(QR, i+1, 0);
        return;
    }
    else if (!cb[j]) {
        recursion(QR, i, j+1);
        return;
    }

    recursion(QR, i, j+1);
    lb[i]--;
    cb[j]--;
    QR[i][j] = 1;
    if (i <= chao && j >  chao) qb[0]--;
    else if (i <= chao && j <= chao) qb[1]--;
    else if (i >  chao && j <= chao) qb[2]--;
    else if (i >  chao && j >  chao) qb[3]--;

    if(i == j) db[0]--;
    if(j == (int) QR.size() - 1 - i)  db[1]--;

    recursion(QR, i, j+1);

    QR[i][j] = 0;

    lb[i]++;
    cb[j]++;
    if (i <= chao && j >  chao) qb[0]++;
    else if (i <= chao && j <= chao) qb[1]++;
    else if (i >  chao && j <= chao) qb[2]++;
    else if (i >  chao && j >  chao) qb[3]++;
    
    if(i == j ) db[0]++;
    if(j == (int) QR.size() - 1 - i)  db[1]++;

}


void solve() {

    valid_qr = 0;
    // input 
    int n;
    cin >> n;
    vector<vector<int>> QR(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        cin >> lb[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> cb[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> lt[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> ct[i];
    }
    cin >> qb[0] >> qb[1] >> qb[2] >> qb[3];
    cin >> db[0] >> db[1];

    // tx
    bool v = false;
    for (int i = 0; i < n; ++i) {
        if (lt[i] > 2*lb[i]) v = true;
        if (ct[i] > 2*cb[i]) v = true;

        if((cb[i] != n) && (cb[i] != 0) && (ct[i] == 0)) v=true;
        if((lb[i] != n) && (lb[i] != 0) && (lt[i] == 0)) v=true;

        if((lt[i]==n) || (ct[i]==n)) v=true;

        if(v){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
    }


    chao = n / 2;
    chao--;

    // int q1, q2, q3, q4;
    // if (n%2 == 0) {
    //   q1 = q2 = q3 = q4 = n/2;
    // } else {
    //   q1 = pow(n/2 + 1, 2);
    //   q2 = pow(n/2, 2);
    //   q3 = pow(n/2 + 1, 2);
    //   q4 = pow(n/2, 2);
    // }
    // if (qb[0] > q1) {
    //     cout << "DEFECT: No QR Code generated!\n";
    //     return;
    // } else if (qb[1] > q2) {
    //     cout << "DEFECT: No QR Code generated!\n";
    //     return;
    // } else if (qb[2] > q3) {
    //     cout << "DEFECT: No QR Code generated!\n";
    //     return;
    // } else if (qb[3] > q4) {
    //     cout << "DEFECT: No QR Code generated!\n";
    //     return;
    // }
      

    for (int i = 0; i < n; ++i) {
        if(lb[i] == n){
            for (int x = 0; x < n; x++) {
                QR[i][x] = 1;
                cb[x]--;
            }
            lb[i] = 0;
            db[0]--;
            db[1]--;
        }
    }
    for (int i = 0; i < n; ++i) {
        if(cb[i] == n){
            int t = 0;
            for (int x = 0; x < n; x++) {
                QR[x][i] = 1;
                lb[x]--;
            }
            cb[i] = 0;
            db[0]--;
            db[1]--;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i <= chao && j >  chao && QR[i][j]) qb[0]--;
            if (i <= chao && j <= chao && QR[i][j]) qb[1]--;
            if (i >  chao && j <= chao && QR[i][j]) qb[2]--;
            if (i >  chao && j >  chao && QR[i][j]) qb[3]--;
        }
    }

    recursion(QR, 0, 0);
    if (valid_qr == 1) {
        cout << "VALID: 1 QR Code generated!\n";
        printQR(cp);
    } else if (valid_qr == 0) {
        cout << "DEFECT: No QR Code generated!\n";
    } else {
        cout << "INVALID: " << valid_qr << " QR Codes generated!\n";
    }
}


int main() {
    int t;
    cin >> t;
    
    //conta=0;
    while (t--) {
	    solve();
    }
    //cout << conta << endl;

    return 0;
}
