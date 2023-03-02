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

bool validation(vector<vector<int>> QR){
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



void recursion(vector<vector<int>> QR, int i, int j) {

    if (lb[i] < 0 || cb[i] < 0)
        return;
    if (qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0)
        return;
    if (db[0] < 0 || db[1] < 0)
        return;
    // if (ct[j] < 0 || lt[i] < 0)
    //     return;

    if (i == (int) QR.size()) {
        // if (!accumulate(ct.begin(), ct.end(), 0) && !accumulate(lt.begin(), lt.end(),0) && !db[0] && !db[1]) {
        //     valid_qr++;
        //     cp = QR;
        // }
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
    if (!lb[i] && !cb[j]) {
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
    if((j == (int) QR.size() - 1 - i))  db[1]--;

    // if(j > 0 && !QR[i][j-1]) lt[i]--;
    // if(i > 0 && !QR[i-1][j]) ct[j]--;

    recursion(QR, i, j+1);

    // if(j > 0 && !QR[i][j-1]) lt[i]++;
    // if(i > 0 && !QR[i-1][j]) ct[j]++;

    QR[i][j] = 0;

    // if(j > 0 && QR[i][j-1]) lt[i]--;
    // if(i > 0 && QR[i-1][j]) ct[j]--;

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


    // solve
    vector<vector<int>> QR(n, vector<int>(n, 0));
    chao = n / 2;
    chao--;

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


    while (t--) {
	    solve();
    }

    return 0;
}
