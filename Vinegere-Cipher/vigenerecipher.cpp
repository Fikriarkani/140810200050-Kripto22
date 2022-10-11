/* 
Nama : Fikri Arkani Salim
NPM  : 140810200050 
Tugas Vinegere Cipher
*/
#include<iostream>

using namespace std;
 
/*  fungsi untuk membuat key yang diberikan 
    menjadi jumlahnya sama apabila string cipher/plainteks 
    lebih panjang */
string generateKey(string teksInput, string key){
    /* proses melengkapi panjang key */
    for (int i = 0; key.size() < teksInput.size(); i++)
    {   
        /* memasukkan huruf tambahan ke akhir string key
        berdasarkan indeks string key */
        key.push_back(key[i]);
    }
    return key;
}
 
/*  fungsi untuk melakukan enkripsi terhadap
    plaintext yang diberikan */
void encrypt(){

    string plainText;
    string keyword;
    cout << "Masukkan ciphertext : "; getline(cin,plainText);
    cout << "Masukkan keyword : "; getline(cin,keyword);
    string key = generateKey(plainText, keyword);

    string cipherText;
 
    for (int i = 0; i < plainText.size(); i++){   
        if(isalpha(plainText[i])&& isupper(plainText[i])){
            //konversikan key menjadi uppercase apabila
            //plaintext uppercase
            if(islower(key[i])){
                char temp = toupper(key[i]);
                key[i] = temp;
            }
            // konversi ke nilai 0-25
            char x = (plainText[i] + key[i]) %26;
    
            // konversi nilai ke huruf menggunakan bilangan ASCII
            x += 'A';

            //masukkan huruf ke cipherText
            cipherText.push_back(x);

        } 
    }
    cout <<"Teks yang telah dienkripsi : "<< cipherText << endl;
}
 
/*  fungsi untuk melakukan deksripsi terhadap cipherteks
    yang diberikan  */
void decrypt(){   
    string cipherText;
    string keyword;
    cout << "Masukkan ciphertext : "; getline(cin,cipherText);
    cout << "Masukkan keyword : "; getline(cin,keyword);
 
    string key = generateKey(cipherText, keyword);
    
    string decryptText;
 
    for (int i = 0 ; i < cipherText.size(); i++){
        if(isalpha(cipherText[i])&&isupper(cipherText[i])){
            //konversikan key menjadi uppercase apabila
            //cipherext uppercase
            if(islower(key[i])){
                char temp = toupper(key[i]);
                key[i] = temp;
            }
            // konversi ke nilai 0-25
            char x = (cipherText[i] - key[i] + 26) %26;
    
            // konversi nilai ke huruf menggunakan bilangan ASCII
            x += 'A';
            //masukkan huruf ke decryptText
            decryptText.push_back(x);
        } 
    }
    cout <<"Teks yang telah didekripsi : "<< decryptText << endl;
}
 
int main(){
    // deklarasi input dan membuat menu tampilan vinegere cipher
    int input;
    do{
        cout << "=Vinegere Cipher=\n"
             << "1.Enkripsi\n"
             << "2.Dekripsi\n"
             << "3.Keluar\n" 
             << "Input = ";
        cin >> input;
        cin.ignore();
        if (input ==  1){
            encrypt();
        } else if (input == 2){
            decrypt();
        } else if(input == 3){
            cout << "Program selesai" << endl;
        }
            
    } while (input != 3);
    
}