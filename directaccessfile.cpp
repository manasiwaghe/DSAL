#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class DirectFile {
    int ht[10];
    public:

    DirectFile() {
        for (int i = 0; i < 10; i++) {
            ht[i] = -1;
        }
    }

    void insert(string name, int id, int salary) {
        ofstream fout("Record.txt", ios::app);
        int index = id % 10;
        int loc = fout.tellp();
        ht[index] = loc;
        fout << id << " " << name << " " << salary << endl;
        fout.close();
    }

    void display() {
        ifstream fin("Record.txt");
        string info;
        while (!fin.eof()) {
            getline(fin, info);
            cout << info << endl;
        }
        
        fin.close();
    }

    void search(int id) {
        ifstream fin("Record.txt");
        int index = id % 10;
        int loc = ht[index];
        if (loc != -1) {
            fin.seekg(loc, ios::beg);
            string info;
            getline(fin, info);
            cout << info << endl;
            
        }
        fin.close();
    }

    void removeR(int id) {
        ifstream fin("Record.txt");
        int index = id % 10;
        int loc = ht[index];
        string req;
        if (loc != -1) {
            fin.seekg(loc, ios::beg);
            getline(fin, req);
            
        }
        fin.close();
        ifstream fin_temp("Record.txt");
        ofstream fout("temp.txt");
        string info;
        while (!fin_temp.eof()) {
            getline(fin_temp, info);
            if (req != info) {
                fout << info << endl;
            }   
        }
        fout.close();
        fin_temp.close();
        remove("Record.txt"); // Remove original file
        rename("temp.txt", "Record.txt"); // Rename temporary file to original name
        
    }
};


int main() {
    DirectFile df;

    // Inserting records
    df.insert("John", 101, 5000);
    df.insert("Alice", 102, 6000);
    df.insert("Bob", 103, 7000);

    // Displaying records
    cout << "Displaying all records:" << endl;
    df.display();

    // Searching for a record
    cout << "\nSearching for record with ID 102:" << endl;
    df.search(102);

    // Removing a record
    cout << "\nRemoving record with ID 101:" << endl;
    df.removeR(102);

    // Displaying records after removal
    cout << "\nDisplaying all records after removal:" << endl;
    df.display();

    return 0;
}