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
    if (i != 0 && lb[i-1] < 0)
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

    
    int lrestantes=(int) QR.size()-j;
    for (int x = j; x < (int) QR.size(); x++){
        if(QR[i][x]) lrestantes--;
    }
    
    //corte linhas pretos restantes
    if(lb[i]> lrestantes){
        return;
    }

    int crestantes=(int) QR.size()-i;
    for (int x = i; x < (int) QR.size(); x++){
        if(QR[x][j]) crestantes--;
    }
    
    //corte pretos restantes na coluna
    if(cb[j]> crestantes){
        return;
    }

    //corte pretos restantes na d0
    int d0restantes=(int) QR.size()-i;
    if(i==j){
        
        int contad0=0;
        for (int x = i; x < (int) QR.size(); x++){
            if(QR[x][j+contad0]) d0restantes--;
            contad0++;
        }

        if( db[0] > d0restantes){
            return;
        }
    }
    

    //corte pretos restantes na d1
    int d1restantes=(int) QR.size()-i;
    if(i== (int) QR.size()-j-1){

        int contad1=0;
        for (int x = i; x < (int) QR.size(); x++){
            if(QR[x][j+contad1]) d1restantes--;
            contad1--;
        }

        if( db[1] > d1restantes){
            return;
        }
    }

    //CASO DE PRE PROCESSAMENTO JA COLOCAR CELULAS A 1
    if((int) QR.size() % 2 == 0){
        int qq;
        if(i <= chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));
            
            //cout << "q1\n";
            for (int x = j; x < (int) QR.size(); ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y <= chao; ++y) {
                for (int x = chao+1; x < QR.size(); ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[0]>qq) return;
        } else if (i <= chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));

            //cout <<"q2\n";
            for (int x = j; x <= chao; ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y <= chao; ++y) {
                for (int x = 0; x <= chao; ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[1]>qq) return;    
        } else if (i >  chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));
            //cout <<"q3\n";
            for (int x = j; x <= chao; ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y < (int) QR.size(); ++y) {
                for (int x = 0; x <= chao; ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[2]>qq) return;    
        } else if (i >  chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));

            //cout <<"q4\n";
            for (int x = j; x < (int) QR.size(); ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y < (int) QR.size(); ++y) {
                for (int x = chao+1; x < (int) QR.size(); ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[0]>qq) return;    
        }
    } else {   //----------------------------------ÍMPAR ---------------------------------------
        int qq;
        if(i <= chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2 + 1));
            //cout << "aqui1\n";
            for (int x = j; x < (int) QR.size(); ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y <= chao; ++y) {
                    for (int x = chao+1; x < QR.size(); ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[0]>qq) return;
        } else if (i <= chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));
            //cout << "aqui2\n";
            for (int x = j; x <= chao; ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y <= chao; ++y) {
                    for (int x = 0; x <= chao; ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[1]>qq) return;    
        } else if (i >  chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));
            //cout << "aqui3\n";
            for (int x = j; x <= chao; ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = 0; x <= chao; ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[2]>qq) return;    
        } else if (i >  chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2 + 1));

            //cout << "aqui4\n";
            for (int x = j; x < (int) QR.size(); ++x) {
                if(QR[i][x]) qq--;
            }

            for (int y = i+1; y < (int) QR.size(); ++y) {
                for (int x = chao+1; x < (int) QR.size(); ++x) {
                    if(QR[y][x]) qq--;
                }
            }

            if(qb[0]>qq) return;    
        }
    }
    

    int contatx=0;
    int contatc=0;
    if(j>0){
        
        for (int x = 1; x < j; x++){
            if(QR[i][x] != QR[i][x-1]) contatx++; 
        }
        if(contatx>lt[i]) return;
    }
    if(i>0){
        for (int x = 1; x < i; x++){
            if(QR[x][j] != QR[x-1][j]) contatc++; 
        }
        if(contatc>ct[j]) return;
    }


     //numero de transiçoes restantes maior do que as possiveis para certo espaço -> cortar
    if(i>0 && j>0){
        int taml = (int) QR.size()-j;
        if (taml%2==0) {

            int pretos=lb[i];
            for (int x = j; x < (int) QR.size() ; x++)
            {
                if(QR[i][x]) pretos++;
            }
            

            if(pretos==taml/2 && (lt[i]-contatx)> (2*pretos)) return;
            //--
            else if((pretos<taml/2) ){
                if(QR[i][j-1] && (lt[i]-contatx) > (2*pretos+1)) return;
                if(!QR[i][j-1] && (lt[i]-contatx) > (2*pretos)) return;
            }
            else if(pretos>taml/2 ){
                if(QR[i][j-1] && (lt[i]-contatx) > (2*(taml - pretos))) return;
                if(!QR[i][j-1] && (lt[i]-contatx) > (2*(taml - pretos)+1)) return;
            }
        }
        else{

            int pretos=lb[i];
            for (int x = j; x < (int) QR.size() ; x++)
            {
                if(QR[i][x]) pretos++;
            }

            if(pretos==taml/2 ) {
                if(QR[i][j-1] && (lt[i]-contatx)> (2*pretos)+1) return;
                if(!QR[i][j-1] && (lt[i]-contatx)> (2*pretos)) return;
            }
            else if((pretos==taml/2 +1) ) {
                if(QR[i][j-1] && (lt[i]-contatx)> (2*pretos)) return;
                if(!QR[i][j-1] && (lt[i]-contatx)> (2*pretos)+1) return;
            }
            //--
            else if((pretos<taml/2)){
                if(QR[i][j-1] && (lt[i]-contatx) > (2*pretos+1)) return;
                if(!QR[i][j-1] && (lt[i]-contatx) > (2*pretos)) return;
            }
            else if((pretos>taml/2+1) ){
                if(QR[i][j-1] && (lt[i]-contatx) > (2*(taml - pretos))) return;
                if(!QR[i][j-1] && (lt[i]-contatx) > (2*(taml - pretos)+1)) return;
            }
        }

        int tamc = (int) QR.size()-i;
        if (tamc%2==0) {

            int pretos=cb[j];
            for (int x = i; x < (int) QR.size() ; x++)
            {
                if(QR[x][j]) pretos++;
            }

            if(pretos==tamc/2 && (ct[j]-contatc)> (2*pretos)) return;
            //--
            else if((pretos<tamc/2) ){
                if(QR[i-1][j] && (ct[j]-contatc) > (2*pretos+1)) return;
                if(!QR[i-1][j] && (ct[j]-contatc) > (2*pretos)) return;
            }
            else if(pretos>tamc/2 ){
                if(QR[i-1][j] && (ct[j]-contatc) > (2*(tamc - pretos))) return;
                if(!QR[i-1][j] && (ct[j]-contatc) > (2*(tamc - pretos)+1)) return;
            }
        }
        else{

            int pretos=cb[j];
            for (int x = i; x < (int) QR.size() ; x++)
            {
                if(QR[x][j]) pretos++;
            }

            if(pretos==tamc/2){
                if(QR[i-1][j] && (ct[j]-contatc)> (2*pretos)+1) return;
                if(!QR[i-1][j] && (ct[j]-contatc)> (2*pretos)) return;
            }
            else if((pretos==tamc/2 +1)){
                if(QR[i-1][j] && (ct[j]-contatc)> (2*pretos)) return;
                if(!QR[i-1][j] && (ct[j]-contatc)> (2*pretos)+1) return;
            }
            //--
            else if((pretos<tamc/2)){
                if(QR[i-1][j] && (ct[j]-contatc) > (2*pretos+1)) return;
                if(!QR[i-1][j] && (ct[j]-contatc) > (2*pretos)) return;
            }
            else if((pretos>tamc/2+1) ){
                if(QR[i-1][j] && (ct[j]-contatc) > (2*(tamc - pretos))) return;
                if(!QR[i-1][j] && (ct[j]-contatc) > (2*(tamc - pretos)+1)) return;
            }
        }
    }



    // completar o resto das transiçoes preto branco e branco preto
    // if (((int) QR.size() - j) % 2) {
    //     for (int i = j; i < (int) QR.size(); ++i) {
    //         if(lt[i] == (int) QR.size() - j-1 && lb[i] > 0){
    //             if(lb[i] == (int) QR.size()/2+1) {
    //                 for (int x = 0; x < (int) QR.size(); x+=2) {
    //                     QR[i][x] = 1;
    //                 }
    //             } else if (lb[i] == (int) QR.size()/2 ) {
    //                 for (int x = 1; x < (int) QR.size(); x+=2) {
    //                     QR[i][x] = 1;
    //                 }
    //             }
    //         }
    //     }
    //     for (int i = 0; i < n; ++i) {
    //         if(ct[i] == n-1 && cb[i] > 0){
    //             if(cb[i] == n/2 + 1 ){
    //                 for (int x = 0; x < n; x+=2) {
    //                     QR[x][i] = 1;
    //                 }
    //             } else if (cb[i] == n/2 ) {
    //                 for (int x = 1; x < n; x+=2) {
    //                     QR[x][i] = 1;
    //                 }
    //             }            
    //         }
    //     }
    // }

    
    //backtracking linhas
    if(lb[i]>0 && lb[i] == lrestantes){
        bool v = false;
        for (int x = j; x < (int) QR.size(); x++) {
            if(!cb[x] && !QR[i][x])v = true;
        }
        if(!v){
            vector<vector<int>> auxl = QR;
            for (int x = j; x < (int) QR.size(); x++) {
                if(!QR[i][x]){
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
            }
        
            recursion(QR, i+1, 0);

            for (int x = j; x < (int) QR.size(); x++) {
                if(!auxl[i][x]){
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
        }
        return;
    }

    //backtracking colunas
    if(cb[j]>0 && cb[j] == crestantes){
        bool v = false;
        for (int x = i; x < (int) QR.size(); x++) {
            if(!lb[x] && !QR[x][j])v = true;
        }
        if(!v){
            vector<vector<int>> auxl = QR;
            for (int x = i; x < (int) QR.size(); x++) {
                if(!QR[x][j]){
                    QR[x][j] = 1;
                    lb[x]--;
                    cb[j]--;
                    if (x <= chao && j >  chao) qb[0]--;
                    else if (x <= chao && j <= chao) qb[1]--;
                    else if (x >  chao && j <= chao) qb[2]--;
                    else if (x >  chao && j >  chao) qb[3]--;

                    if(x == j) db[0]--;
                    if(j == (int) QR.size() - 1 - x)  db[1]--;
                }
            }

            recursion(QR, i, j+1);

            for (int x = i; x < (int) QR.size(); x++) {
                if(!auxl[x][j]){
                    QR[x][j] = 0;
                    lb[x]++;
                    cb[j]++;
                    if (x <= chao && j >  chao) qb[0]++;
                    else if (x <= chao && j <= chao) qb[1]++;
                    else if (x >  chao && j <= chao) qb[2]++;
                    else if (x >  chao && j >  chao) qb[3]++;

                    if(x == j) db[0]++;
                    if(j == (int) QR.size() - 1 - x)  db[1]++;
                }
            }
        }
        return;
    }

    //backtracking d0
    if( db[0]>0 && i==j && db[0] == d0restantes){
        int contador=0;
        bool v = false;
        for (int x = i; x < (int) QR.size(); x++) {
            if(!lb[x] && !QR[x][x])v = true;
            if(!cb[x] && !QR[x][x])v = true;
            
        }

        if(!v){
            vector<vector<int>> auxl = QR;
            contador = 0;
            for (int x = i; x < (int) QR.size(); x++) {
                if(!QR[x][j+contador]){
                    QR[x][j+contador] = 1;
                    lb[x]--;
                    cb[j+contador]--;
                    if (x <= chao && j+contador >  chao) qb[0]--;
                    else if (x <= chao && j+contador <= chao) qb[1]--;
                    else if (x >  chao && j+contador <= chao) qb[2]--;
                    else if (x >  chao && j+contador >  chao) qb[3]--;

                    if(x == j+contador) db[0]--;
                    if(j+contador == (int) QR.size() - 1 - x)  db[1]--;
                    
                }
                contador++;
            }

            recursion(QR, i, j+1);

            contador = 0;
            for (int x = i; x < (int) QR.size(); x++) {
                if(!auxl[x][j+contador]){
                    QR[x][j+contador] = 0;
                    lb[x]++;
                    cb[j+contador]++;
                    if (x <= chao && j+contador >  chao) qb[0]++;
                    else if (x <= chao && j+contador <= chao) qb[1]++;
                    else if (x >  chao && j+contador <= chao) qb[2]++;
                    else if (x >  chao && j+contador >  chao) qb[3]++;

                    if(x == j+contador) db[0]++;
                    if(j+contador == (int) QR.size() - 1 - x)  db[1]++;
                }
                contador++;
            }

        }
        return;

    }

    //backtracking d1
    if( db[1]>0 && i== (int) QR.size()-j-1 && db[1] == d1restantes){
        int contador1=0;
        bool v = false;
        for (int x = i; x < (int) QR.size(); x++) {
            if(!lb[x] && !QR[x][j+contador1])v = true;
            if(!cb[j+contador1] && !QR[x][j+contador1])v = true;
            contador1--;
        }

        if(!v){
            vector<vector<int>> auxl = QR;
            contador1 = 0;
            for (int x = i; x < (int) QR.size(); x++) {
                if(!QR[x][j+contador1]){
                    QR[x][j+contador1] = 1;
                    lb[x]--;
                    cb[j+contador1]--;
                    if (x <= chao && j+contador1 >  chao) qb[0]--;
                    else if (x <= chao && j+contador1 <= chao) qb[1]--;
                    else if (x >  chao && j+contador1 <= chao) qb[2]--;
                    else if (x >  chao && j+contador1 >  chao) qb[3]--;

                    if(x == j+contador1) db[0]--;
                    if(j+contador1 == (int) QR.size() - 1 - x)  db[1]--;
                }
                contador1--;
            }

            recursion(QR, i, j+1);

            contador1 = 0;
            for (int x = i; x < (int) QR.size(); x++) {
                if(!auxl[x][j+contador1]){
                    QR[x][j+contador1] = 0;
                    lb[x]++;
                    cb[j+contador1]++;
                    if (x <= chao && j+contador1 >  chao) qb[0]++;
                    else if (x <= chao && j+contador1 <= chao) qb[1]++;
                    else if (x >  chao && j+contador1 <= chao) qb[2]++;
                    else if (x >  chao && j+contador1 >  chao) qb[3]++;

                    if(x == j+contador1) db[0]++;
                    if(j+contador1 == (int) QR.size() - 1 - x)  db[1]++;
                }
                contador1--;
            }

        }
        return;

    }


    //PREENCHER QUADRANTES------------------------------------------------------------------------------------------
    

    if((int) QR.size() % 2 == 0){
        int qq;
        if(i <= chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));
            if (qb[0] == qq) {
                vector<vector<int>> aux = QR;
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == (int) QR.size() - 1 - i)  db[1]--;
                    }
                }
                
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = chao+1; x < QR.size(); ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == (int) QR.size() - 1 - y)  db[1]--;
                        }
                    }
                }
                int qb_number = qb[0];
                qb[0] = 0;
                recursion(QR, i+1, 0);
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == (int) QR.size() - 1 - i)  db[1]++;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = chao+1; x < QR.size(); ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == (int) QR.size() - 1 - y)  db[1]++;
                        }
                    }
                }
                qb[0] = qb_number;
                return;
            }
        } else if (i <= chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));
            if (qb[1] == qq) {
                vector<vector<int>> aux = QR;
                // preenche linha
                for (int x = j; x <= chao; ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == i)  db[0]--;
                    }
                }
                // preenche restante
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == y)  db[0]--;
                        }
                    }
                }
                int qb_number = qb[1];
                qb[1] = 0;

                recursion(QR, i, chao+1);

                for (int x = j; x <= chao; ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == i)  db[0]++;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == y)  db[0]++;
                        }
                    }
                }
                qb[1] = qb_number;
                return;
            }

        } else if (i >  chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));
            if (qb[2] == qq) {
                vector<vector<int>> aux = QR;
                // preenche linha
                for (int x = j; x <= chao; ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == (int) QR.size() - 1 - i)  db[1]--;
                    }
                }
                // preenche restante
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == (int) QR.size() - 1 - i)  db[1]--;
                        }
                    }
                }
                int qb_number = qb[2];
                qb[2] = 0;

                recursion(QR, i, chao+1);

                for (int x = j; x <= chao; ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == (int) QR.size() - 1 - i)  db[1]++;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == (int) QR.size() - 1 - i)  db[1]++;
                        }
                    }
                }
                qb[2] = qb_number;
                return;
            }
        } else if (i >  chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));
            if (qb[3] == qq) {
                vector<vector<int>> aux = QR;
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == i)  db[0]--;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = chao+1; x < (int) QR.size(); ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == y)  db[0]--;
                        }
                    }
                }
                int qb_number = qb[3];
                qb[3] = 0;
                recursion(QR, i+1, 0);
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == i)  db[0]++;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = chao+1; x < (int) QR.size(); ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == y)  db[0]++;
                        }
                    }
                }
                qb[3] = qb_number;
                return;
            }
        }
    } else {
        // ================================== impar =============================================00
        int qq;
        if(i <= chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2 + 1));
            if (qb[0] == qq) {
                //cout << "aqui1\n";
                vector<vector<int>> aux = QR;
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == (int) QR.size() - 1 - i)  db[1]--;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = chao+1; x < QR.size(); ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == (int) QR.size() - 1 - y)  db[1]--;
                        }
                    }
                }
                int qb_number = qb[0];
                qb[0] = 0;
                recursion(QR, i+1, 0);
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == (int) QR.size() - 1 - i)  db[1]++;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = chao+1; x < QR.size(); ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == (int) QR.size() - 1 - y)  db[1]++;
                        }
                    }
                }
                qb[0] = qb_number;
                return;
            }
        } else if (i <= chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size()/2 - i - 1) * ((int) QR.size()/2));
            if (qb[1] == qq) {
                //cout << "aquiq2\n";
                vector<vector<int>> aux = QR;
                for (int x = j; x <= chao; ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == i)  db[0]--;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == y)  db[0]--;
                        }
                    }
                }
                int qb_number = qb[1];
                qb[1] = 0;

                recursion(QR, i, chao+1);

                for (int x = j; x <= chao; ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == i)  db[0]++;
                    }
                }
                for (int y = i+1; y <= chao; ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == y)  db[0]++;
                        }
                    }
                }
                qb[1] = qb_number;
                return;
            }
        } 
        else if (i >  chao && j <= chao) {
            qq = ((int) QR.size()/2 - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2));
            if (qb[2] == qq) {
                //cout << "aqui3\n";
                //printQR(QR);
                //cout << i << " "<< j <<"\n";
                //cout << qb[2] << " " << qq << endl;
                vector<vector<int>> aux = QR;
                // preenche linha
                for (int x = j; x <= chao; ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == (int) QR.size() - 1 - i)  db[1]--;
                    }
                }
                // preenche restante
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == (int) QR.size() - 1 - i)  db[1]--;
                        }
                    }
                }
                int qb_number = qb[2];
                qb[2] = 0;

                recursion(QR, i, chao+1);

                for (int x = j; x <= chao; ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == (int) QR.size() - 1 - i)  db[1]++;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = 0; x <= chao; ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == (int) QR.size() - 1 - i)  db[1]++;
                        }
                    }
                }
                qb[2] = qb_number;
                return;
            }
            
        } else if (i >  chao && j >  chao) {
            qq = ((int) QR.size() - j) + (((int) QR.size() - i - 1) * ((int) QR.size()/2 + 1));
            if (qb[3] == qq) {
                //cout << "aqui4\n";
                vector<vector<int>> aux = QR;
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!QR[i][x]) {
                        QR[i][x] = 1;
                        lb[i]--;
                        cb[x]--;
                        if (x == i)  db[0]--;
                        if (x == (int) QR.size() - 1 - i)  db[1]--;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = chao+1; x < (int) QR.size(); ++x) {
                        if (!QR[y][x]) {
                            lb[y]--;
                            cb[x]--;
                            QR[y][x] = 1;
                            if (x == y)  db[0]--;
                            if (x == (int) QR.size() - 1 - i)  db[1]--;
                        }
                    }
                }
                int qb_number = qb[3];
                qb[3] = 0;
                recursion(QR, i+1, 0);
                for (int x = j; x < (int) QR.size(); ++x) {
                    if (!aux[i][x]) {
                        QR[i][x] = 0;
                        lb[i]++;
                        cb[x]++;
                        if (x == i)  db[0]++;
                        if (x == (int) QR.size() - 1 - i)  db[1]++;
                    }
                }
                for (int y = i+1; y < (int) QR.size(); ++y) {
                    for (int x = chao+1; x < (int) QR.size(); ++x) {
                        if (!aux[y][x]) {
                            lb[y]++;
                            cb[x]++;
                            QR[y][x] = 0;
                            if (x == y)  db[0]++;
                            if (x == (int) QR.size() - 1 - i)  db[1]++;
                        }
                    }
                }
                qb[3] = qb_number;
                return;
            }
        }
    }
    // =================================== end ========================================


    //Q1 E Q2 DONE 
    if (i <= chao && !qb[1] && !qb[0]){
        if(lb[i])
            return;
        recursion(QR, chao+1, 0);
        return;
    }
    //Q2 DONE
    if (i <= chao && j <= chao && !qb[1]){
        recursion(QR, i, chao+1);
        return;
    }

    ////Q1 DONE
    if (i <= chao && j > chao && !qb[0]){
        
        if(lb[i])
            return;
        recursion(QR, i+1, 0);
        return;
    } 

    //Q3 E Q4 DONE
    if (i > chao && !qb[2] && !qb[3]){
        if(lb[i])
            return;
        if(cb[j])
            return;
        recursion(QR, (int) QR.size(), 0);
        return;
    }
    //Q3 DONE
    if (i > chao && j <= chao && !qb[2]){
        recursion(QR, i, chao+1);
        return;
    }

    ////Q4 DONE
    if (i > chao && j > chao && !qb[3]){
        if(lb[i])
            return;
        if(i== (int) QR.size()-1 && cb[j])
            return;
        recursion(QR, i+1, 0);
        return;
    } 

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

    if (n%2) {
        for (int i = 0; i < n; ++i) {
            if (lb[i] < n/2 && lb[i]*2 < lt[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (lb[i] > n/2+1 && (n-lb[i])*2 < lt[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (lt[i] > n-1 ) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            }
            if (cb[i] < n/2 && cb[i]*2 < ct[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (cb[i] > n/2+1 && (n-cb[i])*2 < ct[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (ct[i] > n-1) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (lb[i] < n/2 && lb[i]*2 < lt[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (lb[i] > n/2 && (n-lb[i])*2 < lt[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } if (lt[i] > n-1) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            }
            if (cb[i] < n/2 && cb[i]*2 < ct[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } else if (cb[i] > n/2 && (n-cb[i])*2 < ct[i]) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            } if (ct[i] > n-1) {
                cout << "DEFECT: No QR Code generated!\n"; return;
            }
        }
    }

    int md = n/2;
    int cl = 0, cc = 0;
    for (int i = 0; i < md; ++i) {
        cl += lb[i];
        cc += cb[i];
    }
    if (cl != qb[0] + qb[1]) {
        cout << "DEFECT: No QR Code generated!\n";
        return;
    } else if (cc != qb[1] + qb[2]) {
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }
    cl = 0, cc = 0;
    for (int i = md; i < n; ++i) {
        cl += lb[i];
        cc += cb[i];
    }
    if (cl > qb[2] + qb[3]) {
        cout << "DEFECT: No QR Code generated!\n";
        return;
    } else if (cc != qb[0] + qb[3]) {
        cout << "DEFECT: No QR Code generated!\n";
        return;
    }
    
    
    for (int i = 0; i < n; ++i) {
        if(lb[i] < coln){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
        else if(lb[i] > (n-col0)){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
        else if(cb[i] < linn){
            cout << "DEFECT: No QR Code generated!\n";
            return;
        }
        else if(cb[i] > (n-lin0)){
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


    //DIAGONAIS
    if(n%2==0 ){
        if(db[0]==n && db[1]==n){
            for (int i = 0; i < n; ++i) {
                if(lb[i]<2 || cb[i]<2){
                    cout << "DEFECT: No QR Code generated!\n";
                    return;
                }
            }
        } else if(db[0]==n || db[1] ==n){
            for (int i = 0; i < n; ++i) {
                if(lb[i]<1 || cb[i]<1){
                    cout << "DEFECT: No QR Code generated!\n";
                    return;
                }
            }
        }
    } else{
        if(db[0]==n && db[1]==n){
            for (int i = 0; i < n; ++i) {
                if(i != n/2){
                    if(lb[i]<2 || cb[i]<2){
                        cout << "DEFECT: No QR Code generated!\n";
                        return;
                    }
                }
                else{
                    if(lb[i]<1 || cb[i]<1){
                        cout << "DEFECT: No QR Code generated!\n";
                        return;
                    }
                }
            }
        } else if(db[0]==n || db[1] ==n){
            for (int i = 0; i < n; ++i) {
                if(lb[i]<1 || cb[i]<1){
                    cout << "DEFECT: No QR Code generated!\n";
                    return;
                }
            }
        }
    }
    

    //preto branco ou branco preto sempre
    if(n % 2){
        for (int i = 0; i < n; ++i) {
            if(lt[i] == n-1 && lb[i] > 0){
                if(lb[i] == n/2+1){
                    for (int x = 0; x < n; x+=2) {
                        QR[i][x] = 1;
                    }
                } else if (lb[i] == n/2 ) {
                    for (int x = 1; x < n; x+=2) {
                        QR[i][x] = 1;
                    }
                } else  {
                    cout << "DEFECT: No QR Code generated!\n";
                    return;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if(ct[i] == n-1 && cb[i] > 0){
                if(cb[i] == n/2 + 1 ){
                    for (int x = 0; x < n; x+=2) {
                        QR[x][i] = 1;
                    }
                } else if (cb[i] == n/2 ) {
                    for (int x = 1; x < n; x+=2) {
                        QR[x][i] = 1;
                    }
                } else  {
                    cout << "DEFECT: No QR Code generated!\n";
                    return;
                }
            }
        }
    }

    int q1, q2;
    if (n%2 == 0) {
        q1 = q2 = n/2;
    } else {
        q1 = n/2;
        q2 = n/2 + 1;
    } if (qb[0] == q1*q2) {
        for (int i = 0; i < q1; ++i) {
            for (int j = 0; j < q2; ++j)
                QR[i][q1 + j] = 1;
        }
    } if (qb[1] == q1*q1) {
        for (int i = 0; i < q1; ++i) {
            for (int j = 0; j < q1; ++j)
                QR[i][j] = 1;
        }
    } if (qb[2] == q1*q2) {
        for (int i = 0; i < q2; ++i) {
            for (int j = 0; j < q1; ++j)
                QR[q1 + i][j] = 1;
        }
    } if (qb[3] == q2*q2) {
        for (int i = 0; i < q2; ++i) {
            for (int j = 0; j < q2; ++j)
                QR[q1 + i][q1 + j] = 1;
        }
    }

      
    for (int i = 0; i < n; ++i) {
        if(lt[i]==1){

            int posix=0;
            for (int x = 0; x < lb[i]; x++)
            {
                if(cb[n-1-x]==0){ 
                    posix=1;
                    break;
                }
                if(cb[x]==0){
                    posix=2;
                    break;
                }
            }
             
            if(posix==2){
                for (int j = n-1; j >= (n- lb[i]); j--) {
                    QR[i][j]=1;
                } 
            }
            else if(posix==1){
                for (int j = 0; j < lb[i] ; j++) {
                    QR[i][j]=1;
                } 
            }
        }
        if(ct[i]==1){

            int posic=0;
            for (int x = 0; x < cb[i]; x++)
            {
                if(lb[n-1-x]==0){ 
                    posic=1;
                    break;
                }
                if(lb[x]==0){
                    posic=2;
                    break;
                }
            }

            if(posic==2){
                for (int j = n-1; j >= (n- cb[i]); j--) {
                    QR[j][i]=1;
                } 
            }
            else if(posic==1){
                for (int j = 0; j < cb[i] ; j++) {
                    QR[j][i]=1;
                } 
            }
        }

    }

    //ver caso de 1 transiçao -> tudo no inicio ou no fim

   

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
    
    //auto start = chrono::high_resolution_clock::now();
    while (t--) {
        //auto start = chrono::high_resolution_clock::now();
        //conta=0;
	    solve();
        //cout << conta << endl;
        //auto stop = std::chrono::high_resolution_clock::now();
        //auto all_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "Time: " << all_time.count() << " milliiseconds\n";
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto all_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Time: " << all_time.count() << " milliiseconds\n";

    return 0;
}