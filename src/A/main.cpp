/**
    Authors:
    Joao Moreira 2020230563
    Tomas Pinto 2020224069
*/
#include <bits/stdc++.h>

using namespace std;


//int conta;

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
    int Tx, Tc;
    Tx = Tc =  0;

    for (int i = 0; i < (int) QR.size(); ++i) {
        for (int j = 0; j < (int) QR.size(); ++j) {
            
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

    //conta++;

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

    ////Q1 DONE
    //if (i <= chao && j > chao && !qb[0]){
    //    recursion(QR, i+1, 0);
    //    return;
    //} 

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

    ////Q4 DONE
    //if (i > chao && j > chao && !qb[3]){
    //    recursion(QR, i+1, 0);
    //    return;
    //} 

    if(!lb[i]){
        recursion(QR, i+1, 0);
        return;
    }
    if (!cb[j]) {
        recursion(QR, i, j+1);
        return;
    }

    if(QR[i][j]){
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
    int ncol=0, nlin=0, nquad=0;
    int col0=0, lin0=0;
    int coln=0, linn=0;

    cin >> n;
    vector<vector<int>> QR(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        cin >> lb[i];
        nlin+= lb[i];
        if(lb[i]==0) lin0++;
        else if(lb[i]==n) linn++;
    }
    for (int i = 0; i < n; ++i) {
        cin >> cb[i];
        ncol+=cb[i];
        if(cb[i]==0) col0++;
        else if(cb[i]==n) coln++;
    }
    for (int i = 0; i < n; ++i) {
        cin >> lt[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> ct[i];
    }
    cin >> qb[0] >> qb[1] >> qb[2] >> qb[3];
    nquad= qb[0] + qb[1] + qb[2] + qb[3];

    cin >> db[0] >> db[1];

    // tx
    bool v = false;
    for (int i = 0; i < n; ++i) {
        if (lt[i] > 2*lb[i]) v = true;
        if (ct[i] > 2*cb[i]) v = true;

        if((cb[i] != n) && (cb[i] != 0) && (ct[i] == 0)) v=true;
        if((lb[i] != n) && (lb[i] != 0) && (lt[i] == 0)) v=true;

        if((lt[i]==n) || (ct[i]==n)) v=true;

        if(cb[i] == n && ct[i]!= 0) v=true;
        if(cb[i] == 0 && ct[i]!= 0) v=true;
        if(lb[i] == n && lt[i]!= 0) v=true;
        if(cb[i] == 0 && ct[i]!= 0) v=true;

        if(v){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if(lb[i] < coln){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
        else if(cb[i] < linn){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
    }

    if(nlin != ncol){ 
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }
    else if(nlin != nquad){ 
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }
    else if(ncol!= nquad){ 
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }

    else if(lin0 > n - db[0] || lin0 > n - db[1]){ 
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }

    else if(col0 > n - db[0] || col0 > n - db[1]){ 
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }


    chao = n / 2;
    chao--;
    

    for (int i = 0; i < n; ++i) {
        if(lb[i] == n){
            for (int x = 0; x < n; x++) {
                QR[i][x] = 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if(cb[i] == n){
            for (int x = 0; x < n; x++) {
                QR[x][i] = 1;
            }
        }
    }

    if(db[0] == n){
        for (int x = 0; x < n; x++) {
            QR[x][x] = 1;
        }
    }
    if(db[1] == n){
        for (int x = 0; x < n; x++) {
            QR[x][n-1-x] = 1;
        }
    }

    
    //int q1, q2;
    //if (n%2 == 0) {
    //    q1 = q2 = n/2;
    //} else {
    //    q1 = n/2;
    //    q2 = n/2 + 1;
    //} if (qb[0] == q1*q2) {
    //    //cout << "here0\n";
    //    for (int i = 0; i < q1; ++i) {
    //        for (int j = 0; j < q2; ++j)
    //            QR[i][q1 + j] = 1;
    //    }
    //} if (qb[1] == q1*q1) {
    //    //cout << "here1\n";
    //    for (int i = 0; i < q1; ++i) {
    //        for (int j = 0; j < q1; ++j)
    //            QR[i][j] = 1;
    //    }
    //} if (qb[2] == q1*q2) {
    //    //cout << "here2\n";
    //    for (int i = 0; i < q2; ++i) {
    //        for (int j = 0; j < q1; ++j)
    //            QR[q1 + i][j] = 1;
    //    }
    //} if (qb[3] == q2*q2) {
    //    //cout << "here3\n";
    //    for (int i = 0; i < q2; ++i) {
    //        for (int j = 0; j < q2; ++j)
    //            QR[q1 + i][q1 + j] = 1;
    //    }
    //}
    

    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(QR[i][j]){
                lb[i]--;
                cb[j]--;
            }
            if (i <= chao && j >  chao && QR[i][j]) qb[0]--;
            if (i <= chao && j <= chao && QR[i][j]) qb[1]--;
            if (i >  chao && j <= chao && QR[i][j]) qb[2]--;
            if (i >  chao && j >  chao && QR[i][j]) qb[3]--;

            if(i == j && QR[i][j]) db[0]--;
            if((j == (int) QR.size() - 1 - i)  && QR[i][j])  db[1]--;
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
