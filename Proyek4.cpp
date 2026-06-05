
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int ukuran;
    int jumlahBom;

    char papan[10][10];
    bool terbuka[10][10];
    bool ditandai[10][10];

    time_t waktuMulai;

public:

    void initGame(int n, int bom) {
        ukuran = n;
        jumlahBom = bom;

        for(int i = 0; i < ukuran; i++) {
            for(int j = 0; j < ukuran; j++) {
                papan[i][j] = '0';
                terbuka[i][j] = false;
                ditandai[i][j] = false;
            }
        }

        tanamBom();
        hitungAngka();

        waktuMulai = time(0);
    }

    void tanamBom() {
        int terpasang = 0;

        while(terpasang < jumlahBom) {

            int r = rand() % ukuran;
            int c = rand() % ukuran;

            if(papan[r][c] != 'B') {
                papan[r][c] = 'B';
                terpasang++;
            }
        }
    }

    void hitungAngka() {

        for(int i = 0; i < ukuran; i++) {

            for(int j = 0; j < ukuran; j++) {

                if(papan[i][j] == 'B')
                    continue;

                int jumlah = 0;

                for(int dr = -1; dr <= 1; dr++) {
                    for(int dc = -1; dc <= 1; dc++) {

                        int nr = i + dr;
                        int nc = j + dc;

                        if(nr >= 0 && nr < ukuran &&
                           nc >= 0 && nc < ukuran &&
                           papan[nr][nc] == 'B') {

                            jumlah++;
                        }
                    }
                }

                papan[i][j] = jumlah + '0';
            }
        }
    }

    void tampilkan() {

        int flag = 0;

        for(int i = 0; i < ukuran; i++) {
            for(int j = 0; j < ukuran; j++) {
                if(ditandai[i][j])
                    flag++;
            }
        }

        cout << "\nBom belum ditandai : "
             << jumlahBom - flag << endl;

        cout << "Waktu berjalan : "
             << (int)(time(0)-waktuMulai)
             << " detik\n\n";

        cout << "   ";

        for(int i = 1; i <= ukuran; i++)
            cout << i << " ";

        cout << endl;

        for(int i = 0; i < ukuran; i++) {

            cout << i+1 << "  ";

            for(int j = 0; j < ukuran; j++) {

                if(ditandai[i][j]) {

                    cout << "F ";

                } else if(!terbuka[i][j]) {

                    cout << "# ";

                } else {

                    cout << papan[i][j] << " ";
                }
            }

            cout << endl;
        }
    }

    void floodFill(int r, int c) {

        if(r < 0 || r >= ukuran ||
           c < 0 || c >= ukuran)
            return;

        if(terbuka[r][c])
            return;

        if(ditandai[r][c])
            return;

        if(papan[r][c] == 'B')
            return;

        terbuka[r][c] = true;

        if(papan[r][c] != '0')
            return;

        for(int dr = -1; dr <= 1; dr++) {
            for(int dc = -1; dc <= 1; dc++) {

                if(dr != 0 || dc != 0) {

                    floodFill(r+dr, c+dc);
                }
            }
        }
    }

    bool bukaKotak(int r, int c) {

        if(ditandai[r][c]) {
            cout << "Kotak ditandai!\n";
            return true;
        }

        if(papan[r][c] == 'B')
            return false;

        floodFill(r,c);

        return true;
    }

    void toggleFlag(int r, int c) {

        if(terbuka[r][c])
            return;

        ditandai[r][c] = !ditandai[r][c];
    }

    bool cekMenang() {

        for(int i = 0; i < ukuran; i++) {

            for(int j = 0; j < ukuran; j++) {

                if(papan[i][j] == 'B' &&
                   !ditandai[i][j])
                    return false;

                if(papan[i][j] != 'B' &&
                   ditandai[i][j])
                    return false;
            }
        }

        return true;
    }

    void tampilSemuaBom() {

        cout << "\n";

        for(int i = 0; i < ukuran; i++) {

            for(int j = 0; j < ukuran; j++) {

                if(papan[i][j] == 'B')
                    cout << "* ";
                else
                    cout << papan[i][j] << " ";
            }

            cout << endl;
        }
    }

    int getWaktu() {
        return (int)(time(0)-waktuMulai);
    }
};

int main() {

    srand(time(0));

    int menu;

    do {

        cout << "\n===== MINESWEEPER++ =====\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilih : ";
        cin >> menu;

        if(menu == 1) {

            int ukuran;
            int bom;

            do {

                cout << "Ukuran papan (4-10): ";
                cin >> ukuran;

            } while(ukuran < 4 || ukuran > 10);

            do {

                cout << "Jumlah bom : ";
                cin >> bom;

            } while(bom <= 0 ||
                    bom >= ukuran*ukuran);

            Minesweeper game;

            game.initGame(ukuran,bom);

            bool hidup = true;

            while(hidup) {

                game.tampilkan();

                int aksi;

                cout << "\n1. Buka Kotak\n";
                cout << "2. Tandai/Hapus Tanda\n";
                cout << "Pilih aksi : ";
                cin >> aksi;

                int r,c;

                cout << "Baris : ";
                cin >> r;

                cout << "Kolom : ";
                cin >> c;

                r--;
                c--;

                if(r < 0 || r >= ukuran ||
                   c < 0 || c >= ukuran) {

                    cout << "Koordinat tidak valid!\n";
                    continue;
                }

                if(aksi == 1) {

                    hidup = game.bukaKotak(r,c);

                    if(!hidup) {

                        cout << "\nBOOM! Anda kalah!\n";

                        game.tampilSemuaBom();

                        cout << "\nWaktu bermain : "
                             << game.getWaktu()
                             << " detik\n";
                    }

                } else if(aksi == 2) {

                    game.toggleFlag(r,c);
                }

                if(game.cekMenang()) {

                    cout << "\nSELAMAT! ANDA MENANG!\n";

                    cout << "Waktu bermain : "
                         << game.getWaktu()
                         << " detik\n";

                    break;
                }
            }
        }

    } while(menu != 2);

    cout << "\nTerima kasih telah bermain!\n";

    return 0;
}

