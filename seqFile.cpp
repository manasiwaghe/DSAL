#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SeqFile {


    public:

    void insert(string name, string id, string salary) {
        ofstream fout("Record.txt", ios::app);
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

    string search(string id) {
        ifstream fin("Record.txt");
        string info;
        while (!fin.eof()) {
            getline(fin, info);
            if (info.length() && info.substr(0, 3) == id) {
                cout << info << endl;
                fin.close();
                return info;
            }   
        }
        info = "Not found";
        fin.close();
        return info;
    }

    void removeR(string id) {
        
        string req = search(id);
        if (id == "Not found") {
            cout << "Entry doesn't exist" << endl;
            return;
        }
        ifstream fin("Record.txt");
        ofstream fout("temp.txt");
        string info;
        while (!fin.eof()) {
            getline(fin, info);
            if (req != info) {
                fout << info << endl;
            }
        }
        fout.close();
        fin.close();
        remove("Record.txt"); // Remove original file
        rename("temp.txt", "Record.txt"); // Rename temporary file to original name
        
    }
};


int main() {
    SeqFile sf;

    // Inserting recordss
    sf.insert("John", "101", "5000");
    sf.insert("Alice", "102", "6000");
    sf.insert("Bob", "103", "7000");

    // Displaying records
    cout << "Displaying all records:" << endl;
    sf.display();

    // Searching for a record
    cout << "\nSearching for record with ID 102:" << endl;
    string result = sf.search("102");
    if (result == "Not found") {
        cout << "Record not found." << endl;
    }

    // Removing a record
    cout << "\nRemoving record with ID 101:" << endl;
    sf.removeR("101");

    // Displaying records after removal
    cout << "\nDisplaying all records after removal:" << endl;
    sf.display();

    return 0;
}