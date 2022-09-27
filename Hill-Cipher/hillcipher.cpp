/* 
Nama : Fikri Arkani Salim
NPM  : 140810200050 
Tugas Hill Cipher
*/
#include<iostream>
#include<vector>
using namespace std;
int mod26(int x){
    return x >= 0 ? (x%26) : 26-(abs(x)%26) ; 
}
int findDetInverse(int R , int D = 26){
    int i = 0 ;
    int p[100] = {0,1};
    int q[100] = {0} ;
    
 
    while(R!=0)
    {
        q[i] = D/R ;
        int oldD = D ;
        D = R ;
        R = oldD%R ;
        if(i>1)
        {
            p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
        }
        i++ ;
    }
    if (i == 1) return 1;
    else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}
int gcd(int m, int n){
    if (n > m)
        swap(m,n);
    
    do{
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}
 
int modInverse(int a, int m){ 
    a=a%m; 
    for(int x=-m;x<m;x++) {
        if((a*x)%m==1) {
            return x; 
        } 
    }
    return 0;
       
} 
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}
int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
} 
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    int det = determinant(a, N, N); 
    if(det == 0){ 
        cout << "Inverse does not exist"; 
        return false; 
    } 
    int invDet = modInverse(det,26);
    cout<<det%26<<' '<<invDet<<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++) 
            inv[i][j] = (adj[i][j]*invDet)%26; 
    return true; 
} 
void encrypt(){
    int x,y,i,j,k,n;
    cout<<"Masukkan Ordo Matriks (harus 2x2) : ";
    cin>>n;
    cout<<"Masukkan kunci matriks : \n";
    int a[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    cout<<"Masukkan Pesan Enkripsi : ";
    string s;
    cin>>s;
    int temp = (n-s.size()%n)%n;
    for(i=0;i<temp;i++){
        s+='x';
    }
    k=0;
    string ans="";
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;
                sum = sum%26;
            }
            ans+=(sum+'a');
        }
        k+=n;
    }
    cout<<"Hasil Enkripsi : "<<ans<<'\n';
}

void decrypt(){
        int x,y,i,j,k,n;
    cout<<"Masukkan ordo matriks (Harus 2x2) : \n";
    cin>>n;
    cout<<"Masukkan nilai martriks\n";
    vector<vector<int> > a(n, vector<int>(n));
    vector<vector<int> > adj(n, vector<int>(n));
    vector<vector<int> > inv(n, vector<int>(n));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    if(inverse(a,inv,n)){
        cout<<"Inverse exist\n";
        cout<<"Masukkan Pesan Deskripsi : ";
        string s;
        cin>>s;
        k=0;
        string ans;
        while(k<s.size()){
            for(i=0;i<n;i++){
                int sum = 0;
                int temp = k;
                for(j=0;j<n;j++){
                    sum += ((inv[i][j] + 26)%26*(s[temp++]-'a')%26)%26;
                    sum = sum%26;
                }
                ans+=(sum+'a');
            }
            k+=n;
        }
        //ans+='\0';
        int f=ans.size()-1;
        while(ans[f]=='x'){
            f--;
        }
        cout << "\nHasil Enkripsi : " ;
        for(i=0;i<=f;i++){
            cout<<ans[i];
        }
        cout<<'\n';
    }
    
}
void findKey(){
    string plainteks,cipherteks;
    int key[2][2],det,detInv,adj[2][2],plainteksInv[2][2],plainMatrix[2][2],cipMatrix[2][2],counter;
    int p,c;
    int transpose[2][2];
    
    cout << "Masukkan Plainteks : ";
    cin.ignore();
    getline(cin,plainteks);
    
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }
    
    cout << "Masukkan Cipherteks : ";
    getline(cin,cipherteks);
    
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }
    
    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if(gcd(det,26)==1){
        detInv = findDetInverse(det, 26);
        
        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1)*plainMatrix[0][1];
        adj[1][0] = (-1)*plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];
        
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                plainteksInv[i][j] = detInv * adj[i][j];
                if(plainteksInv[i][j] < 0){
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
                }else{
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            } 
        }
        
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                key [i][j] = 0;
                for(int k = 0; k < 2; k++){
                    key [i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key [i][j] %= 26;
            }
        }
        
 
        for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            transpose[j][i] = key[i][j];
            }
        }
    
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                cout << (transpose[i][j]) << "\t";
            }
            cout <<endl;
        }       
    }else{
        cout << "Determinan tidak relatif " <<endl;
        cout << "Kunci tidak ditemukan\n\n" ;
    }
}

int main(){
    int input;
    do
    {
        cout << "Hill Cipher\n"
             << "1.Enkripsi\n"
             << "2.Deskripsi\n"
             << "3.Cari Kunci\n"
             << "4.Keluar\n"
             << "Pilihan Menu : ";
        cin >> input;
        cin.ignore();
        if(input == 1){
            encrypt();
        } else if (input == 2){
            decrypt();
        } else if (input == 3){
            findKey();
        } else if (input == 4){
            cout << "Program selesai";
        }
    } while (input!=4);
    return 0;    
}