#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct KataGame{
    string kataAsli;
    string statusTebakan;
    int nyawa;
    int level;
};

struct Leaderboard{
    string nama;
    int skor;
};

Leaderboard top5[5];
int jumlahPemain = 0;

const int JUMLAH_KATA = 20;

const string bankKata[JUMLAH_KATA] ={
    "kucing",
    "anjing",
    "rusa",
    "kelinci",
    "capybara",
    "ikan",
    "merpati",
    "tupai",
    "hamster",
    "monyet",
    "tikus",
    "harimau",
    "singa",
    "bebek",
    "buaya",
    "jerapah",
    "domba",
    "katak",
    "sapi",
    "unta"
};

void pilihKesulitan(KataGame *game){
    int pilih;

    cout << "=== PILIH KESULITAN ===\n";
    cout << "1. Easy (8 nyawa)\n";
    cout << "2. Medium (6 nyawa)\n";
    cout << "3. Hard (4 nyawa)\n";
    cout << "Pilihan : ";
    cin >> pilih;

    if(pilih == 1){
        game->nyawa = 8;
        game->level = 1;
    }
    else if(pilih == 2){
        game->nyawa = 6;
        game->level = 2;
    }
    else if(pilih == 3){
        game->nyawa = 4;
        game->level = 3;
    }
    else{
        cout << "Pilihan tidak valid, otomatis Easy.\n";
        game->nyawa = 8;
        game->level = 1;
    }
}

void inisialisasiGame(KataGame *game){
    int index = rand() % JUMLAH_KATA;

    game->kataAsli = bankKata[index];
    game->statusTebakan = "";

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        game->statusTebakan += "_";
    }
}

bool sudahDitebak(char huruf,
                  const string& status,
                  char salah[],
                  int jumlahSalah)
{
    for(int i = 0; i < status.length(); i++)
    {
        if(status[i] == huruf)
            return true;
    }

    for(int i = 0; i < jumlahSalah; i++)
    {
        if(salah[i] == huruf)
            return true;
    }

    return false;
}

bool cekBenar(KataGame *game, char huruf){
    bool ditemukan = false;

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        if(game->kataAsli[i] == huruf)
        {
            game->statusTebakan[i] = huruf;
            ditemukan = true;
        }
    }

    return ditemukan;
}

bool menang(KataGame game){
    return game.kataAsli == game.statusTebakan;
}

void tampilkan(KataGame game,
               char salah[],
               int jumlahSalah)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "===== GAME TEBAK HEWAN =====\n\n";

    cout << "Kata : ";

    for(int i = 0; i < game.statusTebakan.length(); i++){
        cout << game.statusTebakan[i] << " ";
    }

    cout << "\n\n";

    cout << "Nyawa : " << game.nyawa << endl;

    cout << "Huruf Salah : ";

    for(int i = 0; i < jumlahSalah; i++){
        cout << salah[i] << " ";
    }

    cout << "\n\n";
}

#endif