#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define FILE_IN "../t1data.txt"
using namespace std;

int main() {
    //variables
    int verb = {0};
    int total = 0;
    int i = 1;
    unordered_map<int, int> left;
    unordered_map<int, int> right;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    //build a left & right hashtable
    while (!in_file.eof()) {
        int x = 0;
        in_file >> x;
        left[x]++;
        in_file >> x;
        right[x]++;
    }

    //multiply left table entries by occurrences in right table & then left table occurrences
    for (auto x : left) {
        if ( right[x.first] ) {
            total += right[x.first] * x.first * x.second;
        }
    }

    cout << "\t Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}
