#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include "TebakKata.h"

using namespace std;

int main(){
    srand(time(0));

    char mainLagi = 'Y';

    while(mainLagi == 'Y' || mainLagi == 'y'){
        KataGame game;

        pilihKesulitan(&game);
        inisialisasiGame(&game);

        char tebakanSalah[26] = {'\0'};
        int jumlahSalah = 0;

        while(game.nyawa > 0 && !menang(game)){
            tampilkan(game, tebakanSalah, jumlahSalah);

            string input;

            cout << "Masukkan Huruf (? untuk hint) : ";
            cin >> input;

            // HINT
            if(input == "?"){
                if(game.nyawa > 1){
                    game.statusTebakan[0] = game.kataAsli[0];
                    game.nyawa--;

                    cout << "Hint digunakan! Huruf pertama dibuka.\n";
                }
                else
                {
                    cout << "Nyawa tidak cukup untuk menggunakan hint!\n";
                }

                cin.ignore(1000, '\n');
                cin.get();
                continue;
            }

            if(input.length() != 1){
                cout << "Masukkan tepat 1 huruf!\n";

                cin.ignore(1000, '\n');
                cin.get();

                continue;
            }

            char huruf = tolower(input[0]);

            if(!isalpha(huruf)){
                cout << "Masukkan huruf A-Z saja!\n";

                cin.ignore(1000, '\n');
                cin.get();

                continue;
            }

            if(sudahDitebak(huruf,
                            game.statusTebakan,
                            tebakanSalah,
                            jumlahSalah))
            {
                cout << "Huruf sudah pernah ditebak!\n";

                cin.ignore(1000, '\n');
                cin.get();

                continue;
            }

            if(cekBenar(&game, huruf)){
                cout << "Tebakan benar!\n";
            }
            else
            {
                cout << "Tebakan salah!\n";

                tebakanSalah[jumlahSalah] = huruf;
                jumlahSalah++;

                game.nyawa--;
            }

            cin.ignore(1000, '\n');
            cin.get();
        }

        tampilkan(game,
                  tebakanSalah,
                  jumlahSalah);

        int skor = 0;

        if(menang(game)){
            if(game.level == 1)
                skor = game.nyawa * 10;
            else if(game.level == 2)
                skor = game.nyawa * 20;
            else
                skor = game.nyawa * 30;

            cout << "SELAMAT ANDA MENANG!\n";
            cout << "Skor Anda : " << skor << endl;

            string nama;

            cout << "Masukkan Nama : ";
            cin >> nama;

            if(jumlahPemain < 5){
                top5[jumlahPemain].nama = nama;
                top5[jumlahPemain].skor = skor;
                jumlahPemain++;
            }
        }
        else{
            cout << "ANDA KALAH!\n";
            cout << "Kata rahasianya adalah : "
                 << game.kataAsli << endl;
        }

        // SORT LEADERBOARD
        for(int i = 0; i < jumlahPemain - 1; i++){
            for(int j = i + 1; j < jumlahPemain; j++)
            {
                if(top5[j].skor > top5[i].skor)
                {
                    Leaderboard temp = top5[i];
                    top5[i] = top5[j];
                    top5[j] = temp;
                }
            }
        }

        // TAMPILKAN LEADERBOARD 
        cout << "\n===== TOP 5 LEADERBOARD =====\n";

        for(int i = 0; i < jumlahPemain; i++){
            cout
            << i + 1
            << ". "
            << top5[i].nama
            << " - "
            << top5[i].skor
            << endl;
        }

        cout << "\nMain lagi? (Y/N) : ";
        cin >> mainLagi;
    }

    cout << "\nTerima kasih sudah bermain!\n";

    return 0;
}
