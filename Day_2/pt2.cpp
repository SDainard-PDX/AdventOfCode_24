#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define FILE_IN "../t1data.txt"
using namespace std;

bool descending(vector<int> data) {
    int y = 0;
    for (int x = 1; x < data.size(); x++) {
        if(data[x-1] < data[x]) y++;
        else y--;
        if ( abs(y) == 2 ) break;
    }
    if (y == 2) return false;
    return true;
}

bool isSafe(vector<int> data, bool descent) {
    for (int x = 0; x < data.size()-1; ++x) {
        if (abs(data[x] - data[x+1]) > 3 ||
            data[x] == data[x+1] ||
            (descent && data[x] < data[x+1]) ||
            (!descent && data[x] > data[x+1])) return false;
    }
    return true;
}

bool safeCheck(int a, int b, bool descent) {
    if (abs(a - b) > 3 ||
        a == b ||
        (descent && a < b) ||
        (!descent && a > b)) return false;
    return true;
}

int badPlace(vector<int> data, int x, bool descent) {
    if ( x == data.size()-2 ) return 5;

    int ret = 0;
    if ( x != 0 && safeCheck(data[x-1],data[x+1],descent) ) ret += 1;
    if ( x != data.size()-2 && safeCheck(data[x],data[x+2],descent)) ret +=2;
    if ( x == 0 && safeCheck(data[x+1],data[x+2],descent)) ret += 4;
    return ret;
}

bool isSafe2(vector<int> data, bool descent) {
    bool buffer = false;
    for (int x = 0; x < data.size()-1; ++x) {

        if (!safeCheck(data[x],data[x+1], descent)) {
            if (buffer) return false;

            int route = badPlace(data, x, descent);
            switch (route) {
                case 0:
                    return false; //no path fwd fail
                case 4:
                    data.erase(data.begin());
                    if (!isSafe(data, descent)) return false;
                    break;
                case 5:
                    return true; //end of vector pass
                case 2:
                    ++x;    //move fwd 2 skipping x+1 @ right; falls into case 1 w/ intent
                case 1:
                    buffer = true;
                    //do nothing let it move fwd skipping current x @ left
                    break;
                case 3:
                case 6: // both work determine if either pass test 1
                    vector<int> left;
                    vector<int> right;
                    copy(data.begin()+x+1,data.end(), back_inserter(left));
                    copy(data.begin()+x+2,data.end(), back_inserter(right));
                    if (!isSafe(left, descent) && !isSafe(right, descent)) return false;
                    break;
            }
        }

    }

    return true;
}

int main() {
    //variables
    bool verb = 0;
    int rnd = 1, total = {0};
    string line;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    while (!in_file.eof()) {
        getline(in_file, line);
        stringstream ln;
        ln << line;

        bool descent = false;
        vector<int> reports;

        //put single line in a vector
        while (ln.peek() != -1) {
            int x = 0;
            ln >> x;
            reports.push_back(x);
        }

        //determine direction
        descent = descending(reports);

        //check if baseline safe
        if(isSafe(reports,descent)) {
            if(verb) cout << rnd << "\tSafe1" << endl;
            ++total;
        }
        else {
            if(isSafe2(reports, descent)) {
                if(verb) cout << rnd << "\tSafe2" << endl;
                ++total;
            }
        }

        ++rnd;
    }

    cout << "\nTot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}