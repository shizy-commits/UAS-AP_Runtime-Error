#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int MAX_MOBIL = 20;
const int TARIF_PER_JAM = 2000;

struct Petugas {
    string nama;
    string id;
};

class Mobil {
public:
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

vector<Mobil> daftarMobil;

void garis() {
    cout << "========================================================================================================================================================================\n";
}

void tampilHeader() {
    garis();
    cout << "---------------------------------------------------------- S E L A M A T   D A T A N G ---------------------------------------------------------------------------------" << endl;
    cout << "                                                          DI PORTAL PARKIR KHUSUS MOBIL" << endl;
    cout << "                                                                    MALL PRIENAL" << endl;
    garis();
    cout << endl;
}

void inputPetugas(Petugas *p) {
    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n\n";

    cout << "Masukkan nama : ";
    getline(cin, (*p).nama);

    cout << "Masukkan ID   : ";
    getline(cin, (*p).id);

    cout << endl;
}

void tampilInfoPetugas(Petugas (*p)) {
    garis();
    cout << "Nama Petugas : " << (*p).nama << endl;
    cout << "ID Petugas   : " << (*p).id << endl;

    cout << "                                                       TERIMA KASIH ATAS KERJASAMANYA !" << endl;
    cout << "------------------------------------------------------- S E L A M A T  B E R T U G A S -------------------------------------------------------------------------------" << endl;
    garis();
    cout << endl;
}

void tambahKendaraan() {

    int jumlah;

    cout << "Masukan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlah;
    cin.ignore();

    if ((int)daftarMobil.size() + jumlah > MAX_MOBIL) {
        cout << "\nMaaf, parkiran hanya dapat memuat "
             << MAX_MOBIL << " mobil.\n\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {

        Mobil m;

        cout << "\nMobil ke " << i + 1 << endl;

        cout << "Masukkan plat mobil  : ";
        getline(cin, m.plat);

        cout << "Masukkan merk mobil  : ";
        getline(cin, m.merk);

        cout << "Masukkan warna mobil : ";
        getline(cin, m.warna);

        m.waktuMasuk = time(0);

        daftarMobil.push_back(m);
    }

    cout << "\nData kendaraan berhasil ditambahkan.\n";
}

void tampilDaftarMobil() {

    if (daftarMobil.empty()) {
        cout << "\nBelum ada kendaraan yang parkir." << endl;
        return;
    }

    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR : " << endl;
    garis();

    time_t sekarang = time(0);

    for (int i = 0; i < daftarMobil.size(); i++) {

        long selisih = sekarang - daftarMobil[i].waktuMasuk;

        int jam = selisih / 3600;
        int menit = (selisih % 3600) / 60;
        int detik = selisih % 60;

        cout << "\nMobil ke-" << i + 1 << endl;
        cout << "Plat mobil  : " << daftarMobil[i].plat << endl;
        cout << "Merk mobil  : " << daftarMobil[i].merk << endl;
        cout << "Warna mobil : " << daftarMobil[i].warna << endl;
        cout << "Waktu parkir : "
             << jam << " jam "
             << menit << " menit "
             << detik << " detik\n";

        garis();
    }
}

void pembayaran() {

    if (daftarMobil.empty()) {
        cout << "\nBelum ada kendaraan.\n\n";
        return;
    }

    tampilDaftarMobil();

    string cariPlat;
    bool ditemukan = false;

    while (!ditemukan) {
        cout << "\nMasukkan plat mobil yang ingin dibayar : ";
        getline(cin, cariPlat);

        for (int i = 0; i < daftarMobil.size(); i++) {

            if (daftarMobil[i].plat == cariPlat) {

                ditemukan = true;

                time_t keluar = time(0);

                long detik = keluar - daftarMobil[i].waktuMasuk;

                int jam = detik / 3600;

                if (detik % 3600 != 0)
                    jam++;

                if (jam == 0)
                    jam = 1;

                int biaya = jam * TARIF_PER_JAM;

                cout << "\nB I A Y A   P A R K I R : Rp" << biaya << endl;
                garis();

                daftarMobil.erase(daftarMobil.begin() + i);

                break;
            }
        }

        if (!ditemukan) {
            cout << "PLAT TIDAK DITEMUKAN !" << endl;
        }
    }
}


void menu() {

    cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
    cout << "1. Tambahkan Daftar Kendaraan" << endl;
    cout << "2. Tampilkan Daftar Kendaraan" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "Masukkan opsi : ";
}

int main() {

    Petugas petugas;

    tampilHeader();

    inputPetugas(&petugas);

    tampilInfoPetugas(&petugas);

    int pilihan;

    do {

        menu();

        cin >> pilihan;
        cin.ignore();

        cout << endl;

        switch (pilihan) {

        case 1:
            tambahKendaraan();
            break;

        case 2:
            tampilDaftarMobil();
            cout << endl;
            break;

        case 3:
            pembayaran();
            break;

        case 4:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 4);

    return 0;
}