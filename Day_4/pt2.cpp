#include <iostream>
#include <string>
#include <fstream>
#include <vector>


#define FILE_IN "../t1data.txt"
using namespace std;


int findXMAS(const vector<vector<char>> &field, pair<int,int> dir, pair<int,int> pos ) {
    if (field[pos.second] [pos.first] == 'X') {
        if (field[pos.second + dir.second][pos.first + dir.first] == 'M') {
            if (field[pos.second + dir.second*2][pos.first + dir.first*2] == 'A') {
                if (field[pos.second + dir.second*3][pos.first + dir.first*3] == 'S') {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int findMASX(const vector<vector<char>> &field, bool mupleft, pair<int,int> pos ) {
    if (mupleft) {
        if (
            field[pos.second-1] [pos.first+1] == 'M'
            && field[pos.second+1] [pos.first-1] == 'S'
            && field[pos.second+1] [pos.first+1] == 'S' ) {
            cout << "UU : ";
            return 1; }
        else if (
            field[pos.second+1] [pos.first-1] == 'M'
            && field[pos.second-1] [pos.first+1] == 'S'
            && field[pos.second+1] [pos.first+1] == 'S' ) {
            cout << "LL : ";
            return 1;}
    } else {
        if (
            field[pos.second+1] [pos.first-1] == 'M'
            && field[pos.second-1] [pos.first+1] == 'S'
            && field[pos.second-1] [pos.first-1] == 'S' ) {
            cout << "DD : ";
            return 1; }
        else if (
            field[pos.second-1] [pos.first+1] == 'M'
            && field[pos.second+1] [pos.first-1] == 'S'
            && field[pos.second-1] [pos.first-1] == 'S' ) {
            cout << "RR : ";
            return 1;}
    }
    return 0;
}


int main() {
    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    //variables
    int verb = 0, total = 0;
    char in;
    vector<vector<char>> field = {};
    vector<char> line = {};

// create a field of input using a double vector
    while (in_file.get(in)) {
        if (in == '\n') {
            field.push_back(line);
            line = {};
        }
        else line.push_back(in);
    }
    field.push_back(line);
    in_file.close();

// for printing the field
    if(verb) {
        for (auto x: field) {
            for (auto y: x) cout << y;
            cout << endl;
        }
    }

// find all the x's and check each of the 9 directions
    int row = 0, col = 0;
    int row_max = line.size(), col_max = field.size();

    for (auto y: field) {
        row = 0;
        for (char x: y) {
            bool left = false, up = false, right = false, down = false;
            if (x == 'A') {
                if (row > 0) left = true;
                if (col > 0) up = true;
                if (row < (row_max - 1)) right = true;
                if (col < (col_max - 1)) down = true;

                if (left && up && right && down) {

                    bool  mupleft, mlwright;
                    (field[col-1][row-1] == 'M')?mupleft = true:mupleft = false;
                    (field[col+1][row+1] == 'M')?mlwright = true:mlwright = false;

                    if (mupleft || mlwright) {
                        if (findMASX(field, mupleft, {row, col})) {
                            ++total;
                            cout << "A(" << col + 1 << "," << row + 1 << ") - " << total << endl;
                            cout << "\t" << field[col - 1][row - 1] << " " << field[col - 1][row + 1] << endl;
                            cout << "\t " << field[col][row] << endl;
                            cout << "\t" << field[col + 1][row - 1] << " " << field[col + 1][row + 1] << endl;
                        }
                    }

                    //total += findMASX(field, mupleft, {row, col});
                }
            }

            ++row;
        }
        //end of line here
        ++col;
    }

    cout << "\n\t Tot = " << total << endl;
    return EXIT_SUCCESS;
}
