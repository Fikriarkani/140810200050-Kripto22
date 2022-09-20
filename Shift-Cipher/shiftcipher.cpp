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
            //result += char(int(text[i]-K-65)%26 +65);
        } else if (islower(text[i])){
            if(text[i]-K-97 < 0){
                result += char(mod_negative(int(text[i]-K-97),26)+97);
            } else {
                result += char(int(text[i]-K-97)%26 +97);}
            //result += char(int(text[i]-K-97)%26 +97);
        } else {
            result+=" ";
        }
    }
    cout <<"kalimat deskripsi : "<< result << endl;
}

void encryptFile(){
    int maxParagraph,K;
    string namaFileInput,namaFileOutput;

    cout << "Masukkan nama file input  (dengan ekstensi) : ";
    cin >> namaFileInput;
    cout << "Masukkan kunci enkripsi                     : "; 
    cin >> K;
    cout << "Masukkan nama file output (dengan ekstensi) : ";
    cin >> namaFileOutput;


    ifstream File(namaFileInput);

    string line;
    int indicatorParagraph=0;

    while (!File.eof()){
        getline(File, line);
        indicatorParagraph++;
    }

    maxParagraph=indicatorParagraph;
    indicatorParagraph=0;

    File.close();

    ifstream File2(namaFileInput);

    string *dataContainer;
    dataContainer = new string[maxParagraph];

    while(!File2.eof()){
        getline(File2, line);
        dataContainer[indicatorParagraph] = line;
        indicatorParagraph++;
    }

    string encryptParagraph;
    string *resultContainer;
    resultContainer = new string[maxParagraph];

    for(int i = 0; i<indicatorParagraph ; i++){
        encryptParagraph = dataContainer[i];
        for(int l = 0; l < encryptParagraph.length(); l++){
            if (isupper(encryptParagraph[l])){
                resultContainer[i] += char(int(encryptParagraph[l]+K-65)%26 +65);
            } else if (islower(encryptParagraph[l])){
                resultContainer[i] += char(int(encryptParagraph[l]+K-97)%26 +97);
            } else{
                resultContainer[i]+=encryptParagraph[l];
            }
        }
    }
    File2.close();
    ofstream Writer(namaFileOutput);

    for(int i = 0; i<indicatorParagraph;i++){
        Writer << resultContainer[i] << endl;
    }

    Writer.close();    



}

void decryptFile(){
    int maxParagraph,K;
    string namaFileInput,namaFileOutput;

    cout << "Masukkan nama file input  (dengan ekstensi) : ";
    cin >> namaFileInput;
    cout << "Masukkan kunci deskripsi                    : "; 
    cin >> K;
    cout << "Masukkan nama file output (dengan ekstensi) : ";
    cin >> namaFileOutput;


    ifstream File(namaFileInput);

    string line;
    int indicatorParagraph=0;

    while (!File.eof()){
        getline(File, line);
        indicatorParagraph++;
    }

    maxParagraph=indicatorParagraph;
    indicatorParagraph=0;

    File.close();

    ifstream File2(namaFileInput);

    string *dataContainer;
    dataContainer = new string[maxParagraph];

    while(!File2.eof()){
        getline(File2, line);
        dataContainer[indicatorParagraph] = line;
        indicatorParagraph++;
    }

    string decryptParagraph;
    string *resultContainer;
    resultContainer = new string[maxParagraph];

    for(int i = 0; i<indicatorParagraph ; i++){
        decryptParagraph = dataContainer[i];
        for(int l = 0; l < decryptParagraph.length(); l++){
            if (isupper(decryptParagraph[l])){
                if(decryptParagraph[l]-K-65 < 0){
                    resultContainer[i] += char(mod_negative(int(decryptParagraph[l]-K-65),26)+65);
                } else {
                    resultContainer[i] += char(int(decryptParagraph[l]-K-65)%26 +65);
                }
                //result += char(int(text[i]-K-65)%26 +65);
            } else if (islower(decryptParagraph[l])){
                if(decryptParagraph[l]-K-97 < 0){
                    resultContainer[i] += char(mod_negative(int(decryptParagraph[l]-K-97),26)+97);
                } else {
                    resultContainer[i] += char(int(decryptParagraph[l]-K-97)%26 +97);}
                //result += char(int(text[i]-K-97)%26 +97);
            } else {
                resultContainer[i] += decryptParagraph[l];
            }
        }
    }
    File2.close();
    ofstream Writer(namaFileOutput);

    for(int i = 0; i<indicatorParagraph;i++){
        Writer << resultContainer[i] << endl;
    }

    Writer.close();
}

int main() {
    int input;
    
    do{
        cout << "1. Enkripsi\n"
             << "2. Deskripsi\n"
             << "3. Enkripsi File\n"
             << "4. Deskripsi File\n"
             << "5. Exit\n"
             << "Pilihan = ";
        cin >> input;
        cin.ignore();
        if(input == 1 ){
            encrypt();
        } else if (input == 2){
            decrypt();
        } else if (input == 3 ){
            encryptFile();
        } else if (input == 4 ){
            decryptFile();
        } else if (input == 5){
            cout << "Program Selesai\n";
        } else if (isdigit(input) == 0 || input <= 0 || input >=6 ){
            cout << "Masukkan Angka 1-5 untuk memilih menu!\n";  
        }  
    } while (input != 5);
    
}
