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
    int verb = 2;
    int rnd = {1}, rnd_score = {0}, total = {0};
    string line;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    bool go = true;
    int ln = 1;
    while ( !in_file.eof() ) {

        getline(in_file, line);
        int found = -1, dew = -1, don = -1;
        bool first = true;

        dew = line.find("do()");
        don = line.find("don't()");
        if(verb > 1) cout << "\nLine : " << ln << endl;
        ln++;
        if(verb > 0) cout << "dew/don/first : " << dew << "/" << don << "/ na" << endl;

        while ( found != string::npos || first ) {
            if (!go && first && dew != -1) {
                don = line.find("don't()", dew);
                found = dew;
                go = true;
            }
            first = false;

            if (go) {

                while ((found = line.find("mul(", found + 1)) != string::npos
                       && (don == -1 || (found < don))) {
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
                    if (verb > 1) {
                        cout << "Find " << rnd << " @ " << found << ": "
                             << fir.second << "*" << sec.second << "=" << (fir.second * sec.second)
                             << " \tTotal = " << total << endl;
                    }
                    ++rnd;
                }
                if ( found != -1) go = false;
            }   //end of go

            //find next dew/don block in line if not out of mul()
            if ( found != string::npos ) {
                dew = line.find("do()", don);   //find next dew after current don
                don = line.find("don't()", dew);//find next don after new dew
                found = dew;
                if (dew != string::npos) go = true;
                if(verb > 0) cout << "dew/don/found : " << dew << "/" << don << "/" << found << endl;
            }
        }

            //update go status before getting new line
            int lastdew = dew, lastdon = don;
            while ( (dew = line.find("do()", + dew + 1)) != string::npos ) { lastdew = dew; }
            while ( (don = line.find("don't()", + don + 1)) != string::npos ) { lastdon = don; }
            dew = lastdew, don = lastdon;
            (dew != don)?(dew > don)?go = true:go = false:go = go;

    }

    cout << "\t Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}