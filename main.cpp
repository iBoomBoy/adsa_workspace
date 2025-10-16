#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct slot {
    string key;
    char status; 
};

int hashFunc(const string &word) {
    return word.back() - 'a';
}

class hashtable {
private:
    vector<slot> table;

public:
    hashtable() {
        table.resize(26);
        for (int i = 0; i < 26; i++) {
            table[i].status = 'N';
        }
    }

    int search(const string &key) {
        int start = hashFunc(key);
        int index = start;
        while (true) {
            if (table[index].status == 'N') {
                return -1;
            }
            if (table[index].status == 'O' && table[index].key == key) {
                return index;
            }
            index = (index + 1) % 26;
            if (index == start) return -1;
        }
    }

    void insert(const string &key) {
        if (search(key) != -1) return;

        int start = hashFunc(key);
        int index = start;
        while (true) {
            if (table[index].status == 'N' || table[index].status == 'T') {
                table[index].key = key;
                table[index].status = 'O';
                return;
            }
            index = (index + 1) % 26;
        }
    }

    void remove(const string &key) {
        int pos = search(key);
        if (pos != -1) {
            table[pos].status = 'T';
        }
    }

    void print() {
        bool first = true;
        for (int i = 0; i < 26; i++) {
            if (table[i].status == 'O') {
                if (!first) cout << " ";
                cout << table[i].key;
                first = false;
            }
        }
        cout << endl;
    }
};

int main() {
    hashtable ht;
    string inputLine;
    getline(cin, inputLine);

    string move = "";
    for (size_t i = 0; i <= inputLine.size(); i++) {
        if (i == inputLine.size() || inputLine[i] == ' ') {
            if (!move.empty()) {
                char op = move[0];
                string key = move.substr(1);
                if (op == 'A') ht.insert(key);
                else if (op == 'D') ht.remove(key);
                move = "";
            }
        } else {
            move += inputLine[i];
        }
    }

    ht.print();
    return 0;
}
