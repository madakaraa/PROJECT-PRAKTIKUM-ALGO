// Satria Arya Mahendra_124250160
// Mahawira Dzakie_124250180
// Project Manajemen Data Film

#include <iostream>
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

// Tambah film di akhir
void tambahFilm(string judul, string genre, int tahun) {
    Node* newNode = new Node{judul, genre, tahun, NULL, NULL};

    if (head == NULL) {
        head = tail = current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    cout << "Film berhasil ditambahkan!\n";
}

// SUBMENU tampil film
void menuTampilFilm() {
    int pilih;

    do {
        cout << "\n=== MENU TAMPIL FILM ===\n";
        cout << "1. Lihat Semua Film\n";
        cout << "2. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            Node* temp = head;

            if (temp == NULL) {
                cout << "Data film kosong.\n";
            } else {
                cout << "\nDaftar Film:\n";
                while (temp != NULL) {
                    cout << "Judul : " << temp->judul << endl;
                    cout << "Genre : " << temp->genre << endl;
                    cout << "Tahun : " << temp->tahun << endl;
                    cout << "----------------------\n";
                    temp = temp->next;
                }
            }

        } else if (pilih == 2) {
            cout << "Kembali ke menu utama...\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 2);
}

// Navigasi next
void nextFilm() {
    if (current == NULL) {
        cout << "Belum ada film.\n";
    } else if (current->next == NULL) {
        cout << "Sudah di film terakhir.\n";
    } else {
        current = current->next;
        cout << "Sekarang di film:\n";
        cout << current->judul << endl;
    }
}

// Navigasi prev
void prevFilm() {
    if (current == NULL) {
        cout << "Belum ada film.\n";
    } else if (current->prev == NULL) {
        cout << "Sudah di film pertama.\n";
    } else {
        current = current->prev;
        cout << "Sekarang di film:\n";
        cout << current->judul << endl;
    }
}

// Tampilkan film saat ini
void tampilCurrent() {
    if (current == NULL) {
        cout << "Belum ada film.\n";
    } else {
        cout << "\nFilm saat ini:\n";
        cout << "Judul : " << current->judul << endl;
        cout << "Genre : " << current->genre << endl;
        cout << "Tahun : " << current->tahun << endl;
    }
}

int main() {
    int pilihan;
    string judul, genre;
    int tahun;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Semua Film\n";
        cout << "3. Next Film\n";
        cout << "4. Prev Film\n";
        cout << "5. Tampilkan Film Saat Ini\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Judul: ";
                getline(cin, judul);
                cout << "Genre: ";
                getline(cin, genre);
                cout << "Tahun: ";
                cin >> tahun;
                tambahFilm(judul, genre, tahun);
                break;

            case 2:
                menuTampilFilm(); // ← sudah diganti ke submenu
                break;

            case 3:
                nextFilm();
                break;

            case 4:
                prevFilm();
                break;

            case 5:
                tampilCurrent();
                break;
        }

    } while (pilihan != 6);

    return 0;
}
