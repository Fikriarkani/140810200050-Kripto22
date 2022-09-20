/* 
Nama : Fikri Arkani Salim
NPM  : 140810200050 
Tugas Shift Cipher
*/
#include <iostream>
#include <fstream>
using namespace std;

int mod_negative(int a,int b){
    int result = (b+(a%b)%b);
    return result;
}

void encrypt()
{   
    int K;
    string text;
    cout << "Masukkan Text  : "; getline(cin, text);
    cout << "Masukkan Kunci : "; cin >> K;
    string result;
    for (int i=0;i<text.length();i++){
        if (isupper(text[i])){
            result += char(int(text[i]+K-65)%26 +65);
        } else if (islower(text[i])){
            result += char(int(text[i]+K-97)%26 +97);
        } else{
            result+=" ";
        }
    }
    cout <<"kalimat enkripsi : "<< result << endl;
    
}

void decrypt()
{   
    int K;
    string text;
    cout << "Masukkan Text  : "; getline(cin, text);
    cout << "Masukkan Kunci : "; cin >> K;
    string result;
    for (int i=0;i<text.length();i++){
        if (isupper(text[i])){
            if(text[i]-K-65 < 0){
                result += char(mod_negative(int(text[i]-K-65),26)+65);
            } else {
                result += char(int(text[i]-K-65)%26 +65);
            }
        } else if (islower(text[i])){
            if(text[i]-K-97 < 0){
                result += char(mod_negative(int(text[i]-K-97),26)+97);
            } else {
                result += char(int(text[i]-K-97)%26 +97);}
        } else {
            result+=" ";
        }
    }
    cout <<"kalimat deskripsi : "<< result << endl;
}

int main() {
    int input;
    
    do{
        cout << "1. Enkripsi\n"
             << "2. Deskripsi\n"
             << "3. Exit\n"
             << "Pilihan = ";
        cin >> input;
        cin.ignore();
        if(input == 1 ){
            encrypt();
        } else if (input == 2){
            decrypt();
        } else if (input == 3){
            cout << "Program Selesai\n";
        } else if (isdigit(input) == 0 || input <= 0 || input >=4 ){
            cout << "Masukkan Angka 1-3 untuk memilih menu!\n";  
        }  
    } while (input != 3);
    
}
