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

// search film
void searchFilm(string cari) {
    Node* temp = head;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->judul == cari) {
            cout << "\nFilm ditemukan:\n";
            cout << "Judul : " << temp->judul << endl;
            cout << "Genre : " << temp->genre << endl;
            cout << "Tahun : " << temp->tahun << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Film tidak ditemukan.\n";
    }
}

//edit film
void editFilm(string cari) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->judul == cari) {
            cout << "Edit data film:\n";

            cout << "Judul baru: ";
            getline(cin, temp->judul);

            cout << "Genre baru: ";
            getline(cin, temp->genre);

            cout << "Tahun baru: ";
            cin >> temp->tahun;
            cin.ignore();

            cout << "Film berhasil diupdate!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Film tidak ditemukan.\n";
}

//hapus film
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

            if (current == temp) current = head;

            delete temp;
            cout << "Film berhasil dihapus!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Film tidak ditemukan.\n";
}

// Tampilkan film berdasarkan rating tertinggi (bubble sort swap data)
void tampilRatingTertinggi() {
    if (head == NULL) {
        cout << "Data film kosong.\n";
        return;
    }
 
    // Hitung jumlah node
    int n = 0;
    Node* temp = head;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }
 
    // Bubble sort - swap data (bukan pointer), descending
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        Node* cur = head;
        for (int j = 0; j < n - i - 1; j++) {
            if (cur->rating < cur->next->rating) {
                // Swap semua field data
                swap(cur->judul, cur->next->judul);
                swap(cur->genre, cur->next->genre);
                swap(cur->tahun, cur->next->tahun);
                swap(cur->rating, cur->next->rating);
                swapped = true;
            }
            cur = cur->next;
        }
        if (!swapped) break;
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
        cout << "6. Search Film\n";
        cout << "7. Edit Film\n";
        cout << "8. Hapus Film\n";
        cout << "9. Tampilkan Film Rating Tertinggi\n";
        cout << "10. Keluar\n";
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

            case 6:
                cout << "Masukkan judul yang dicari: ";
                getline(cin, judul);
                searchFilm(judul);
                break;

            case 7:
                cout << "Masukkan judul yang ingin diedit: ";
                getline(cin, judul);
                editFilm(judul);
                break;

            case 8:
                cout << "Masukkan judul yang ingin dihapus: ";
                getline(cin, judul);
                hapusFilm(judul);
                break;
            case 9:
                tampilRatingTertinggi();
                break;
 
            case 10:
                cout << "Keluar dari program.\n";
                break;
 
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 9);

    return 0;
}

