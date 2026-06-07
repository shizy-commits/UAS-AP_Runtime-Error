#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string buatSoal(string negara) {
    string soal = negara;

    int panjang = negara.length(); 


    int jumlahHilang = max(2, panjang / 2);

    vector<int> indeks;

    for (int i = 0; i < panjang; i++) {
        indeks.push_back(i); 
    }

    random_shuffle(indeks.begin(), indeks.end()); 

    for (int i = 0; i < jumlahHilang; i++) {
        soal[indeks[i]] = '_'; 
     
    }

    return soal;
}

int main() {
    srand(time(0));

    vector<string> negara = {
    "indonesia",
    "malaysia",
    "singapura",
    "thailand",
    "vietnam",
    "filipina",
    "brunei",
    "laos",
    "kamboja",
    "myanmar",
    "china",
    "jepang",
    "korea",
    "india",
    "pakistan",
    "bangladesh",
    "nepal",
    "bhutan",
    "mongolia",
    "srilanka",
    "australia",
    "selandia baru",
    "amerika",
    "kanada",
    "meksiko",
    "kuba",
    "jamaika",
    "panama",
    "guatemala",
    "honduras",
    "brazil",
    "argentina",
    "chile",
    "peru",
    "kolombia",
    "ekuador",
    "bolivia",
    "uruguay",
    "paraguay",
    "venezuela",
    "inggris",
    "irlandia",
    "prancis",
    "jerman",
    "belanda",
    "belgia",
    "spanyol",
    "portugal",
    "italia",
    "swedia",
    "norwegia",
    "finlandia",
    "denmark",
    "polandia",
    "ukraina",
    "rusia",
    "yunani",
    "swiss",
    "austria",
    "hungaria",
    "mesir",
    "maroko",
    "aljazair",
    "tunisia",
    "libya",
    "sudan",
    "ethiopia",
    "kenya",
    "uganda",
    "tanzania",
    "ghana",
    "nigeria",
    "kamerun",
    "angola",
    "afrika",
    "zimbabwe",
    "turki",
    "iran",
    "irak",
    "suriah",
    "yordania",
    "israel",
    "arab saudi",
    "yaman",
    "oman",
    "qatar",
    "kuwait",
    "bahrain",
    "uni emirat arab"
};

    int skor = 0;
    char lagi;

    do {
        int randomNegara = rand() % negara.size();

        string jawabanBenar = negara[randomNegara];
        string soal = buatSoal(jawabanBenar);

        string tebakan;

        cout << "\n==================================" << endl;
        cout << "Tebak negara : " << soal << endl;
        cout << "Negara apa yang dimaksud? ";
        cin.ignore();
        getline(cin, tebakan);


        transform(tebakan.begin(), tebakan.end(),
                  tebakan.begin(), ::tolower);
                 

        if (tebakan == jawabanBenar) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        }
        else {
            cout << "Maaf, Anda salah." << endl;
            cout << "Jawaban yang benar adalah : "
                 << jawabanBenar << endl;
        }

        cout << "Skor Anda : " << skor << endl;

        cout << "Ingin bermain lagi? (y/n) : ";
        cin >> lagi;

    } while (lagi == 'y' || lagi == 'Y');

    cout << "\nGame selesai. Terima kasih telah bermain :D" << endl;

    return 0;
}