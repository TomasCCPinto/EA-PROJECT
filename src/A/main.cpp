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
    /**
        0 -> white
        1 -> black
    */

    int N = 0;
    int C = 0;
    int Tx = 0;
    int Tc = 0;
    int D1 = 0; 
    int D2 = 0;
    int Q1, Q2, Q3, Q4;
    Q1 = Q2 = Q3 = Q4 = 0;
    int floor = QR.size() / 2;
    floor--;


    for (int i = 0; i < (int) QR.size(); ++i) {
        for (int j = 0; j < (int) QR.size(); ++j) {
            
            if(i==j && QR[i][j]==1) D1++;
            if((j== (int) QR.size() - 1 - i) && QR[i][j])  D2++;
            if (QR[i][j] == 1) {
                N++;
            }
            if (QR[j][i] == 1) {
                C++;
            }
            if((j+1)<(int) QR.size() && QR[i][j] != QR[i][j+1]){
                Tx++;
            }
            if((j+1)<(int) QR.size() && QR[j][i] != QR[j+1][i]){
                Tc++;
            }
            if (i <= floor && j >  floor && QR[i][j]) Q1++;
            if (i <= floor && j <= floor && QR[i][j]) Q2++;
            if (i >  floor && j <= floor && QR[i][j]) Q3++;
            if (i >  floor && j >  floor && QR[i][j]) Q4++;
        }


        if (N != lb[i]) {
            return false;
        } else if (C != cb[i]) {
            return false;
        } else if (Tx != lt[i]) {
            return false;
        } else if (Tc != ct[i]) {
            return false;
        }
        C = 0;
        N = 0;
        Tx = 0;
        Tc = 0;
    }
    if (Q1 != qb[0])
        return false;
    else if (Q2 != qb[1])
        return false;
    else if (Q3 != qb[2])
        return false;
    else if (Q4 != qb[3])
        return false;
    else if (D1 != db[0])
        return false;
    else if (D2 != db[1])
        return false;

    return true;
}

void recursion(vector<vector<int>> QR, int i, int j) {
    /**
        i -> lines
        j -> columns
    */
    if (i == (int) QR.size()) {
        if (validation(QR)) {
            valid_qr++;
            cp = QR;
        }
        return;
    }
    if (j == (int) QR.size()) {
        recursion(QR, i+1, 0);
        return;
    }
    
    recursion(QR, i, j+1);
    QR[i][j] = 1;
    recursion(QR, i, j+1);
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

    recursion(QR, 0, 0);

    if (valid_qr == 1) {
        cout << "VALID: 1 QR Code generated!\n";
        printQR(cp);
    } else if (valid_qr == 0) {
        cout << "DEFECT: No QR Code generated!\n" ;
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
