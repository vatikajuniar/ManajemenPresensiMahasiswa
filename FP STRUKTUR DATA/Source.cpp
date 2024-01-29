#include <iostream>
#include <string>       // untuk menggunakan getline

using namespace std;

// variable global
const int MAX_SIZE = 20;

struct Data {
    string nim[MAX_SIZE] = { "22.11.1230", "22.11.1322", "22.11.2298", "22.11.1111",  "22.11.1214" };   // 5 -- >  15
    string nama[MAX_SIZE] = { "JOY","LISA", "JANE", "EVE", "ASA" };
    string absen[MAX_SIZE]; // menampung mahasiswa yanng sudah presensi
    int nimCount = 5;       // jumlah data awal dalam array nim dan nama
    int count = 0;          // jumlah data awal dalam array absen
} D;

void tampilNim();           
void presensi();            
void unPresensi();
void unPresensiNim();
void unPresensiStack();
void tampilan();
void cari();                

int main() {
    int menu;

    // perulangan while (for - while - do whlie)
    while (true) {
        system("cls");

        cout << "\t\tPRESENSI" << endl << endl;
        cout << "[1] Daftar NIM" << endl;
        cout << "[2] Presensi" << endl;
        cout << "[3] Gagalkan Presensi" << endl;
        cout << "[4] Tampilkan" << endl;
        cout << "[5] Cari NIM" << endl;
        cout << "[6] Keluar" << endl << endl;
        cout << "Pilih[1/2/3/4/5/6]: ";
        cin >> menu;

        switch (menu) {
        case 1:
            tampilNim();
            break;
        case 2:
            presensi();
            break;
        case 3:
            unPresensi();
            break;
        case 4:
            tampilan();
            break;
        case 5:
            cari();
            break;
        case 6:
            exit(0);

        }
    }
    return 0;
}

void tampilNim() {
    string tambah;
    int jumlah;
    bool tData = true;
    int size = D.nimCount; // mengambil nilai count sebagai jumlah data

    system("cls");

    cout << "\t\t>>> Daftar NIM <<<" << endl << endl;
    cout << "Jumlah data: " << size << endl << endl;

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << D.nama[i] << "\t [" << D.nim[i] << "]" << endl;
    }
    cout << endl;

    while (tData && size < MAX_SIZE) {
        cout << "Tambah NIM[y/n]: ";
        cin >> tambah;

        if (tambah == "y" || tambah == "Y") {
            cout << "Jumlah data yang ingin ditambahkan (MAX 15) \t: ";
            cin >> jumlah;

            if (size + jumlah > MAX_SIZE) {
                cout << "Jumlah data yang ingin ditambahkan melebihi batas maksimum!" << endl;
                system("pause > nul");
                break;
            }

            cin.ignore(); // Menggunakan cin.ignore() untuk mengabaikan karakter newline (\n) sebelum menggunakan getline()

            for (int i = size; i < size + jumlah; i++) {
                cout << "Masukkan NIM(22.11.xxxx): ";
                getline(cin, D.nim[i]);
                cout << "Masukkan Nama\t\t: ";
                getline(cin, D.nama[i]);
            }

            size += jumlah;
            D.nimCount = size; // memperbarui nilai count dengan jumlah data terbaru
            cout << endl << "\t\t\t->>> Data Berhasil Ditambahkan <<<-";
            tData = false;
            system("pause > nul");
        }
        else {
            tData = false;
        }
    }
}

void presensi() {
    string n;
    int size = D.nimCount;
    bool nimTerdaftar = false;
    system("cls");

    cout << "\t\tMENU PRESENSI" << endl << endl;
    cout << "Masukkan NIM: ";
    cin.ignore();
    getline(cin, n);
    if (n == "0") main();

    for (int i = 0; i < size; i++) {
        if (n == D.nim[i]) {
            nimTerdaftar = true;
            break;
        }
    }

    if (nimTerdaftar) {

        bool nimAbsen = false;
        for (int i = 0; i < D.count; i++) {
            if (n == D.absen[i]) {
                nimAbsen = true;
                break;
            }
        }

        if (nimAbsen) {
            cout << endl << "\t\t\tAnda sudah melakukan presensi sebelumnya";
        }
        else {
            D.absen[D.count] = n;
            D.count++;
            cout << endl << "\t\t\tPresensi Berhasil";
        }
    }
    else {
        cout << endl << "\t\t\tNIM Anda tidak terdaftar" << endl << endl;
    }

    system("pause > nul");
}

void unPresensi() {
    int pilih;

    system("cls");
    cout << "\t\tGAGALKAN PRESENSI" << endl << endl;

    cout << "[1] Batalkan Presensi dengan NIM" << endl;
    cout << "[2] Batalkan Presensi Terbaru" << endl;
    cout << "[3] Kembali" << endl;
    cout << "pilih[1/2/3]: ";
    cin >> pilih;

    switch (pilih) {
    case 1:
        unPresensiNim();
        break;
    case 2:
        unPresensiStack();
        break;
    case 3:
        main();
    }


}

void unPresensiNim() {
    string n;
    bool nimTerdaftar = false;
    system("cls");

    cout << "\t\tGAGALKAN PRESENSI" << endl << endl;
    cin.ignore();

    cout << "Masukan NIM:";
    getline(cin, n);
    if (n == "0") main();

    for (int i = 0; i < D.nimCount; i++) {
        if (n == D.nim[i]) {
            nimTerdaftar = true;
            break;
        }
    }

    if (nimTerdaftar) {
        bool nimAbsen = false;
        for (int i = 0; i < D.count; i++) {
            if (n == D.absen[i]) {
                nimAbsen = true;
                D.absen[i] = "";  // Menghapus data NIM dari array absen dengan mengosongkannya
                D.count--;
                cout << endl << "\t\t\tPresensi Berhasil Dibatalkan" << endl;
                break;  // Menghentikan loop setelah NIM dihapus
            }
        }

        if (!nimAbsen) {
            cout << endl << "\t\t\tAnda belum melakukan presensi" << endl;
        }
    }
    else {
        cout << endl << "\t\t\tNIM Anda tidak terdaftar" << endl;
    }
    system("pause > nul");
}

// menghapus data terbaru
void unPresensiStack() {
    bool nimTerdaftar = false;
    int size = D.count;

    system("cls");
    cout << "\t\tGAGALKAN PRESENSI" << endl << endl;

    // Cek apakah ada data pengguna yang tersedia untuk dihapus
    if (size != 0) {
        // Hapus data pengguna dari paling belakang
        //stack
        int pos = size - 1;

        D.absen[pos] = "";

        cout << "\tPresensi Berhasil Dibatalkan";

        D.count--;

    }
    else {
        cout << "Tidak ada data pengguna yang tersedia" << endl;
        system("pause > null");
        main();
        return;
    }
    system("pause > null");
    main();

}

void tampilan() {
    system("cls");
    cout << "\t\t\tDAFTAR PRESENSI" << endl << endl;

    // Bubble sort - Sortir data secara menaik (ascending)
    for (int i = 0; i < D.nimCount - 1; i++) {
        for (int j = 0; j < D.nimCount - i - 1; j++) {
            if (D.nim[j] > D.nim[j + 1]) {
                // Tukar posisi
                string tempNIM = D.nim[j];
                string tempNama = D.nama[j];

                D.nim[j] = D.nim[j + 1];
                D.nama[j] = D.nama[j + 1];

                D.nim[j + 1] = tempNIM;
                D.nama[j + 1] = tempNama;
            }
        }
    }

    // Menampilkan data setelah diurutkan secara menaik
    for (int i = 0; i < D.nimCount; i++) {
        bool sudahPresensi = false;
        for (int j = 0; j < D.count; j++) {
            if (D.nim[i] == D.absen[j]) {
                sudahPresensi = true;
                break;
            }
        }

        if (sudahPresensi) {
            cout << i + 1 << ". " << D.nama[i] << "\t [" << D.nim[i] << "] - Sudah presensi" << endl;
        }
        else {
            cout << i + 1 << ". " << D.nama[i] << "\t [" << D.nim[i] << "] - Belum presensi" << endl;
        }
    }
    system("pause > nul");
}

void cari() {
    string nimCari;
    bool nimDitemukan = false;
    system("cls");

    cout << "\t\t\tCARI NIM" << endl << endl;
    cout << "Masukkan NIM: ";
    cin.ignore();
    getline(cin, nimCari);
    if (nimCari == "0") main();

    for (int i = 0; i < D.nimCount; i++) {
        if (nimCari == D.nim[i]) {
            nimDitemukan = true;
            cout << endl << "Data ditemukan:" << endl;
            cout << "Nama: " << D.nama[i] << endl;
            cout << "NIM: " << D.nim[i] << endl;

            bool sudahPresensi = false;
            for (int j = 0; j < D.count; j++) {
                if (D.nim[i] == D.absen[j]) {
                    sudahPresensi = true;
                    break;
                }
            }

            if (sudahPresensi) {
                cout << "Status Presensi: Sudah presensi" << endl;
            }
            else {
                cout << "Status Presensi: Belum presensi" << endl;
            }
            break;
        }
    }

    if (!nimDitemukan) {
        cout << endl << "Data tidak ditemukan." << endl;
    }

    system("pause > nul");
}