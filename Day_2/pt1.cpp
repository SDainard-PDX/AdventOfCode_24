#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define FILE_IN "../t1data.txt"
using namespace std;

int main() {
    //variables
    bool verb = false;
    int rnd = {0}, rnd_score = {0}, total = {0};
    string line;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    while (!in_file.eof()) {
        getline(in_file, line);

        int i = 0, prev = 0, sec = 0;
        bool direction = false, decent = false, safe = true;
        istringstream ln(line);

        ln >> prev;
        while ( ln.peek() != -1 ) {
            ln >> sec;
            if (!direction) {
                if (prev > sec) decent = true;
                direction = true;
            }
            if (verb) cout << prev << " : " << sec << "\t";

            if ( abs(prev - sec) > 3 || prev == sec || (decent && prev < sec) || (!decent && prev > sec) ) {
                safe = false;
                break;
            }
            if (verb) cout << "'" << ln.peek() << "'";
            prev = sec;
        }
        if (safe) total++;
        if (verb) cout << endl;
    }

    cout << "Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}
