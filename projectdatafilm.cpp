// Satria Arya Mahendra_124250160
// Mahawira Dzakie_124250180
// Project Manajemen Data Film


#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    string judul, genre;
    int tahun;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;
Node* current = NULL;

// ===== UI =====
void garis() {
    cout << "========================================\n";
}

void header(string judul) {
    system("cls"); // Windows (kalau Linux/Mac pakai "clear")
    garis();
    cout << "        " << judul << endl;
    garis();
}

void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.get();
}

// ===== TAMBAH =====
void tambahFilm(string judul, string genre, int tahun) {
    Node* newNode = new Node{judul, genre, tahun, NULL, NULL};

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

    while (getline(file, judul)) {
        getline(file, genre);
        file >> tahun;
        file.ignore();

        tambahFilm(judul, genre, tahun);
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
        temp = temp->next;
    }

    file.close();
}

// ===== TAMPIL =====
void tampilRapi() {
    Node* temp = head;

    if (temp == NULL) {
        cout << "[!] Data kosong\n";
        return;
    }

    garis();
    cout << "No | Judul | Genre | Tahun\n";
    garis();

    int no = 1;
    while (temp != NULL) {
        cout << no++ << ".  "
             << temp->judul << " | "
             << temp->genre << " | "
             << temp->tahun << endl;
        temp = temp->next;
    }

    garis();
}

// ===== SUBMENU =====
void menuTampilFilm() {
    int pilih;
    do {
        header("MENU TAMPIL FILM");
        cout << "1. Lihat Semua Film\n";
        cout << "2. Kembali\n";
        garis();
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            header("DAFTAR FILM");
            tampilRapi();
            pause();
        }

    } while (pilih != 2);
}

// ===== SORT =====
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
                swap(ptr->judul, ptr->next->judul);
                swap(ptr->genre, ptr->next->genre);
                swap(ptr->tahun, ptr->next->tahun);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);

    cout << "[✓] Data berhasil diurutkan!\n";
}

// ===== NEXT =====
void nextFilm() {
    if (current == NULL) {
        cout << "[!] Belum ada film\n";
    } else if (current->next == NULL) {
        cout << "[!] Sudah di film terakhir\n";
    } else {
        current = current->next;
        cout << "[>] " << current->judul << endl;
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
        cout << "[<] " << current->judul << endl;
    }
}

// ===== CURRENT =====
void tampilCurrent() {
    if (current == NULL) {
        cout << "[!] Belum ada film\n";
    } else {
        garis();
        cout << "FILM SAAT INI\n";
        garis();
        cout << "Judul : " << current->judul << endl;
        cout << "Genre : " << current->genre << endl;
        cout << "Tahun : " << current->tahun << endl;
    }
}

// ===== SEARCH =====
void searchFilm(string cari) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->judul == cari) {
            cout << "[✓] Ditemukan:\n";
            cout << temp->judul << " | " << temp->genre << " | " << temp->tahun << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "[!] Tidak ditemukan\n";
}

// ===== EDIT =====
void editFilm(string cari) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->judul == cari) {
            cout << "Judul baru: ";
            getline(cin, temp->judul);
            cout << "Genre baru: ";
            getline(cin, temp->genre);
            cout << "Tahun baru: ";
            cin >> temp->tahun;
            cin.ignore();

            cout << "[✓] Berhasil diupdate\n";
            saveFile();
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

            if (temp == head && temp == tail) {
                head = tail = current = NULL;
            } 
            else if (temp == head) {
                head = head->next;
                head->prev = NULL;
            } 
            else if (temp == tail) {
                tail = tail->prev;
                tail->next = NULL;
            } 
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            delete temp;
            cout << "[✓] Film dihapus\n";
            saveFile();
            return;
        }
        temp = temp->next;
    }

    cout << "[!] Tidak ditemukan\n";
}

// ===== MAIN =====
int main() {
    int pilihan;
    string judul, genre;
    int tahun;

    loadFile(); // ← penting!

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
        cout << "9. Sorting Tahun\n";
        cout << "10. Keluar\n";

        garis();
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                header("TAMBAH FILM");
                cout << "Judul: ";
                getline(cin, judul);
                cout << "Genre: ";
                getline(cin, genre);
                cout << "Tahun: ";
                cin >> tahun;
                cin.ignore();
                tambahFilm(judul, genre, tahun);
                saveFile();
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
                cout << "Judul: ";
                getline(cin, judul);
                searchFilm(judul);
                pause();
                break;

            case 7:
                header("EDIT FILM");
                cout << "Judul: ";
                getline(cin, judul);
                editFilm(judul);
                pause();
                break;

            case 8:
                header("HAPUS FILM");
                cout << "Judul: ";
                getline(cin, judul);
                hapusFilm(judul);
                pause();
                break;

            case 9:
                header("SORTING");
                sortTahun();
                saveFile();
                pause();
                break;
        }

    } while (pilihan != 10);

    return 0;
}
