#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#define FILE_IN "../t1data.txt"
using namespace std;

int main() {
    //variables
    int verb = {0};
    int firtot = 0, sectot = 0, total = 0;
    int i = 1;
    vector<int> left;
    vector<int> right;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    while (!in_file.eof()) {
        int x = 0;
        in_file >> x;
        left.push_back(x);
        in_file >> x;
        right.push_back(x);

        /*
        int fir = 0, sec = 0;
        in_file >> fir;
        firtot += fir;
        in_file >> sec;
        sectot += sec;
        cout << i << ": \t" << fir << " / " << sec;
        cout << " : \t" << firtot << " / " << sectot;
        cout << " : \t" << abs(firtot - sectot) << endl;
        i++;
         */
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    i = 0;
    for (int x : left) {
        total += abs(x - right[i]);
        i++;
    }

    //total = abs(firtot - sectot);
    cout << "\t Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}
