// Satria Arya Mahendra_124250160
// Mahawira Dzakie_124250180
// Project Manajemen Data Film

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// Kredensial login
const string VALID_USERNAME = "algo";
const string VALID_PASSWORD = "123";

struct Node {
    string judul, genre;
    int tahun;
    float rating;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;
Node* current = NULL;

// ===== UI =====
void garis() {
    cout << "==================================================\n";
}

void header(string judul) {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    garis();

    cout << "              " << judul << endl;

    garis();
}

void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.get();
}

// ===== LOWERCASE =====
string toLower(string teks) {

    for (size_t i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);
    }

    return teks;
}

// ===== LOGIN =====
bool login() {

    string username, password;

    int percobaan = 0;

    const int MAX_COBA = 3;

    garis();
    cout << "       SISTEM MANAJEMEN DATA FILM\n";
    garis();

    while (percobaan < MAX_COBA) {

        cout << "\nLogin (" << (MAX_COBA - percobaan)
             << " kesempatan tersisa)\n";

        cout << "Username : ";
        cin >> username;

        cout << "Password : ";
        cin >> password;

        cin.ignore();

        if (username == VALID_USERNAME &&
            password == VALID_PASSWORD) {

            cout << "\nLogin berhasil!\n";

            pause();

            return true;

        } else {

            percobaan++;

            cout << "\n[!] Username atau password salah\n";
        }
    }

    cout << "\nAkses ditolak!\n";

    return false;
}

// ===== TAMBAH FILM =====
void tambahFilm(string judul,
                string genre,
                int tahun,
                float rating) {

    Node* newNode = new Node{
        judul,
        genre,
        tahun,
        rating,
        NULL,
        NULL
    };

    if (head == NULL) {

        head = tail = current = newNode;

    } else {

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// ===== LOAD FILE =====
void loadFile() {

    ifstream file("film.txt");

    if (!file.is_open()) return;

    string judul, genre;
    int tahun;
    float rating;

    while (getline(file, judul)) {

        getline(file, genre);

        file >> tahun;
        file >> rating;

        file.ignore();

        tambahFilm(judul, genre, tahun, rating);
    }

    file.close();
}

// ===== SAVE FILE =====
void saveFile() {

    ofstream file("film.txt");

    Node* temp = head;

    while (temp != NULL) {

        file << temp->judul << endl;
        file << temp->genre << endl;
        file << temp->tahun << endl;
        file << temp->rating << endl;

        temp = temp->next;
    }

    file.close();
}

// ===== TAMPIL FILM =====
void tampilRapi() {

    Node* temp = head;

    if (temp == NULL) {

        cout << "[!] Data film kosong\n";

        return;
    }

    int no = 1;

    while (temp != NULL) {

        garis();

        cout << no++ << ". " << temp->judul << endl;

        cout << "   Genre  : " << temp->genre << endl;

        cout << "   Tahun  : " << temp->tahun << endl;

        cout << "   Rating : "
             << temp->rating
             << "/10\n";

        temp = temp->next;
    }

    garis();
}

// ===== MENU TAMPIL =====
void menuTampilFilm() {

    int pilih;

    do {

        header("MENU TAMPIL FILM");

        cout << "1. Lihat Semua Film\n";
        cout << "2. Kembali\n";

        garis();

        cout << "Pilih : ";

        cin >> pilih;

        cin.ignore();

        if (pilih == 1) {

            header("DAFTAR FILM");

            tampilRapi();

            pause();
        }

    } while (pilih != 2);
}

// ===== SORT TAHUN =====
void sortTahun() {

    if (head == NULL) {

        cout << "[!] Data kosong\n";

        return;
    }

    bool swapped;

    Node* ptr;

    Node* last = NULL;

    do {

        swapped = false;

        ptr = head;

        while (ptr->next != last) {

            if (ptr->tahun > ptr->next->tahun) {

                swap(ptr->judul,
                     ptr->next->judul);

                swap(ptr->genre,
                     ptr->next->genre);

                swap(ptr->tahun,
                     ptr->next->tahun);

                swap(ptr->rating,
                     ptr->next->rating);

                swapped = true;
            }

            ptr = ptr->next;
        }

        last = ptr;

    } while (swapped);

    cout << "[✓] Sorting tahun berhasil\n";
}

// ===== SORT JUDUL =====
void sortJudul() {

    if (head == NULL) {

        cout << "[!] Data kosong\n";

        return;
    }

    bool swapped;

    Node* ptr;

    Node* last = NULL;

    do {

        swapped = false;

        ptr = head;

        while (ptr->next != last) {

            if (ptr->judul >
                ptr->next->judul) {

                swap(ptr->judul,
                     ptr->next->judul);

                swap(ptr->genre,
                     ptr->next->genre);

                swap(ptr->tahun,
                     ptr->next->tahun);

                swap(ptr->rating,
                     ptr->next->rating);

                swapped = true;
            }

            ptr = ptr->next;
        }

        last = ptr;

    } while (swapped);

    cout << "[✓] Sorting judul berhasil\n";
}

// ===== MENU SORTING =====
void menuSorting() {

    int pilih;

    do {

        header("MENU SORTING");

        cout << "1. Sorting Tahun\n";
        cout << "2. Sorting Judul A-Z\n";
        cout << "3. Kembali\n";

        garis();

        cout << "Pilih : ";

        cin >> pilih;

        cin.ignore();

        switch (pilih) {

            case 1:

                header("SORTING TAHUN");

                sortTahun();

                saveFile();

                pause();

                break;

            case 2:

                header("SORTING JUDUL");

                sortJudul();

                saveFile();

                pause();

                break;
        }

    } while (pilih != 3);
}

// ===== STATISTIK =====
void statistikFilm() {

    if (head == NULL) {

        cout << "[!] Data kosong\n";

        return;
    }

    int jumlah = 0;

    Node* temp = head;

    Node* terbaru = head;

    Node* terlama = head;

    while (temp != NULL) {

        jumlah++;

        if (temp->tahun > terbaru->tahun) {
            terbaru = temp;
        }

        if (temp->tahun < terlama->tahun) {
            terlama = temp;
        }

        temp = temp->next;
    }

    garis();

    cout << "STATISTIK FILM\n";

    garis();

    cout << "Total Film   : "
         << jumlah << endl;

    cout << "Film Terbaru : "
         << terbaru->judul
         << " (" << terbaru->tahun << ")\n";

    cout << "Film Terlama : "
         << terlama->judul
         << " (" << terlama->tahun << ")\n";

    garis();
}

// ===== NEXT =====
void nextFilm() {

    if (current == NULL) {

        cout << "[!] Belum ada film\n";

    } else if (current->next == NULL) {

        cout << "[!] Sudah di film terakhir\n";

    } else {

        current = current->next;

        cout << "[>] "
             << current->judul
             << endl;
    }
}

// ===== PREV =====
void prevFilm() {

    if (current == NULL) {

        cout << "[!] Belum ada film\n";

    } else if (current->prev == NULL) {

        cout << "[!] Sudah di film pertama\n";

    } else {

        current = current->prev;

        cout << "[<] "
             << current->judul
             << endl;
    }
}

// ===== FILM SAAT INI =====
void tampilCurrent() {

    if (current == NULL) {

        cout << "[!] Belum ada film\n";

    } else {

        garis();

        cout << "FILM SAAT INI\n";

        garis();

        cout << "Judul : "
             << current->judul << endl;

        cout << "Genre : "
             << current->genre << endl;

        cout << "Tahun : "
             << current->tahun << endl;

        cout << "Rating : "
             << current->rating
             << "/10\n";
    }
}

// ===== SEARCH =====
void searchFilm(string cari) {

    Node* temp = head;

    cari = toLower(cari);

    while (temp != NULL) {

        if (toLower(temp->judul) == cari) {

            cout << "[✓] Film ditemukan\n";

            garis();

            cout << "Judul : "
                 << temp->judul << endl;

            cout << "Genre : "
                 << temp->genre << endl;

            cout << "Tahun : "
                 << temp->tahun << endl;

            cout << "Rating : "
                 << temp->rating
                 << "/10\n";

            garis();

            return;
        }

        temp = temp->next;
    }

    cout << "[!] Film tidak ditemukan\n";
}

// ===== EDIT =====
void editFilm(string cari) {

    Node* temp = head;

    while (temp != NULL) {

        if (temp->judul == cari) {

            cout << "Judul baru : ";
            getline(cin, temp->judul);

            cout << "Genre baru : ";
            getline(cin, temp->genre);

            cout << "Tahun baru : ";
            cin >> temp->tahun;

            cout << "Rating baru : ";
            cin >> temp->rating;

            cin.ignore();

            saveFile();

            cout << "[✓] Film berhasil diupdate\n";

            return;
        }

        temp = temp->next;
    }

    cout << "[!] Film tidak ditemukan\n";
}

// ===== HAPUS =====
void hapusFilm(string cari) {

    Node* temp = head;

    while (temp != NULL) {

        if (temp->judul == cari) {

            if (temp == head &&
                temp == tail) {

                head = tail = current = NULL;

            } else if (temp == head) {

                head = head->next;

                head->prev = NULL;

            } else if (temp == tail) {

                tail = tail->prev;

                tail->next = NULL;

            } else {

                temp->prev->next = temp->next;

                temp->next->prev = temp->prev;
            }

            if (current == temp) {
                current = head;
            }

            delete temp;

            saveFile();

            cout << "[✓] Film berhasil dihapus\n";

            return;
        }

        temp = temp->next;
    }

    cout << "[!] Film tidak ditemukan\n";
}

// ===== RATING TERTINGGI =====
void tampilRatingTertinggi() {

    if (head == NULL) {

        cout << "[!] Data kosong\n";

        return;
    }

    bool swapped;

    Node* ptr;

    Node* last = NULL;

    do {

        swapped = false;

        ptr = head;

        while (ptr->next != last) {

            if (ptr->rating <
                ptr->next->rating) {

                swap(ptr->judul,
                     ptr->next->judul);

                swap(ptr->genre,
                     ptr->next->genre);

                swap(ptr->tahun,
                     ptr->next->tahun);

                swap(ptr->rating,
                     ptr->next->rating);

                swapped = true;
            }

            ptr = ptr->next;
        }

        last = ptr;

    } while (swapped);

    Node* temp = head;

    int rank = 1;

    garis();

    cout << "RATING FILM TERTINGGI\n";

    garis();

    while (temp != NULL) {

        cout << rank++ << ". "
             << temp->judul << endl;

        cout << "   Genre  : "
             << temp->genre << endl;

        cout << "   Tahun  : "
             << temp->tahun << endl;

        cout << "   Rating : "
             << temp->rating
             << "/10\n";

        garis();

        temp = temp->next;
    }
}

// ===== MAIN =====
int main() {

    if (!login()) {
        return 0;
    }

    loadFile();

    int pilihan;

    string judul, genre;

    int tahun;

    float rating;

    do {

        header("MENU UTAMA");

        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Film\n";
        cout << "3. Next Film\n";
        cout << "4. Prev Film\n";
        cout << "5. Film Saat Ini\n";
        cout << "6. Search Film\n";
        cout << "7. Edit Film\n";
        cout << "8. Hapus Film\n";
        cout << "9. Sorting\n";
        cout << "10. Statistik Film\n";
        cout << "11. Rating Tertinggi\n";
        cout << "12. Keluar\n";

        garis();

        cout << "Pilih : ";

        cin >> pilihan;

        cin.ignore();

        switch (pilihan) {

            case 1:

                header("TAMBAH FILM");

                cout << "Judul : ";
                getline(cin, judul);

                cout << "Genre : ";
                getline(cin, genre);

                cout << "Tahun : ";
                cin >> tahun;

                cout << "Rating : ";
                cin >> rating;

                cin.ignore();

                tambahFilm(judul,
                            genre,
                            tahun,
                            rating);

                saveFile();

                cout << "[✓] Film berhasil ditambahkan\n";

                pause();

                break;

            case 2:

                menuTampilFilm();

                break;

            case 3:

                header("NEXT FILM");

                nextFilm();

                pause();

                break;

            case 4:

                header("PREV FILM");

                prevFilm();

                pause();

                break;

            case 5:

                header("FILM SAAT INI");

                tampilCurrent();

                pause();

                break;

            case 6:

                header("SEARCH FILM");

                cout << "Masukkan judul : ";

                getline(cin, judul);

                searchFilm(judul);

                pause();

                break;

            case 7:

                header("EDIT FILM");

                cout << "Masukkan judul : ";

                getline(cin, judul);

                editFilm(judul);

                pause();

                break;

            case 8:

                header("HAPUS FILM");

                cout << "Masukkan judul : ";

                getline(cin, judul);

                hapusFilm(judul);

                pause();

                break;

            case 9:

                menuSorting();

                break;

            case 10:

                header("STATISTIK FILM");

                statistikFilm();

                pause();

                break;

            case 11:

                header("RATING TERTINGGI");

                tampilRatingTertinggi();

                pause();

                break;

            case 12:

                header("PROGRAM SELESAI");

                cout << "Terima kasih telah menggunakan program.\n";

                garis();

                break;
        }

    } while (pilihan != 12);

    return 0;
}
