#include <iostream>
#include <string>
#include <fstream>

#define FILE_IN "../t1data.txt"
using namespace std;

pair<int, int> getNum(string input) {
    pair<int, int> ret = {0,0};
    char y;
    for(auto x = 0; x < 3; ++x) {
        y = input[x];
        if (isdigit(y)) {
            ret.first++;
            ret.second = 10 * ret.second + (y - '0');
        } else {
            break;
        }
    }
    return ret;
}

int main() {
    //variables
    int verb = 0;
    int rnd = {0}, rnd_score = {0}, total = {0};
    string line;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    while ( !in_file.eof() ) {
        getline(in_file, line);
        size_t found = -1;

        while ((found = line.find("mul(", found + 1)) != string::npos) {
            //find first and second number while ensuring format, else continue
            pair<int, int> fir = {0, 0}, sec = {0, 0};
            fir = getNum(line.substr(found + 4, 3));
            if (fir.first == 0) continue;
            if (line[found + 4 + fir.first] != ',') continue;
            sec = getNum(line.substr(found + 5 + fir.first, 3));
            if (sec.first == 0) continue;
            if (line[found + 5 + fir.first + sec.first] != ')') continue;

            //determine result and add to total
            total += (fir.second * sec.second);
            cout << "Find " << rnd << " @ " << found << ": "
                 << fir.second << "*" << sec.second << "=" << (fir.second * sec.second)
                 << " \tTotal = " << total << endl;
            ++rnd;
        }
    }

    cout << "\t Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}
