#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define FILE_IN "../t1data.txt"
using namespace std;

void printField(const vector<vector<char>> &field) {
    for (auto i : field) {
        for (auto j : i) {
            cout << j;
        }
        cout << endl;
    }
    cout << endl;
}

enum direction {Up, Right, Down, Left};

struct security_guard {
    int x = 0;
    int y = 0;
    direction heading = Up;
};

bool inbounds(security_guard guard, int width, int height) {
    if (guard.x >= 0 && guard.x < width && guard.y >= 0 && guard.y < height) return true;
    return false;
}

int main() {
    //variables
    int verb = 0;
    int total = {0};
    string line;
    vector<vector<char>> field = {};
    security_guard guard;
    bool flip = false;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    //get input to field
    while ( !in_file.eof() ) {
        char x;
        vector<char> ln = {};
        while ( ((x = in_file.get()) != '\n') && !in_file.eof() ) {
            if (x == '^') {
                ++total;
                flip = true;
                x = 'X';
            }
            ln.push_back(x);
            if (!flip) ++guard.x;
        }
        if (!flip) {
            guard.x = 0;
            ++guard.y;
        }
        field.push_back(ln);
    }
    in_file.close();

    //move that shit
    int height = field.size();
    int width = field[0].size();
    while ( inbounds(guard,width,height) ) {
        switch (guard.heading) {
            case Up:
                if ( guard.y != 0 && (field[guard.y-1][guard.x]) == '#') {
                    guard.heading = Right;
                    ++guard.x;
                } else {
                    --guard.y;
                }
                break;
            case Right:
                if ( guard.x != width-1 && (field[guard.y][guard.x+1]) == '#') {
                    guard.heading = Down;
                    ++guard.y;
                } else {
                    ++guard.x;
                }
                break;
            case Down:
                if ( guard.y != height-1 && (field[guard.y+1][guard.x]) == '#') {
                    guard.heading = Left;
                    --guard.x;
                } else {
                    ++guard.y;
                }
                break;
            case Left:
                if ( guard.x != 0 && (field[guard.y][guard.x-1]) == '#') {
                    guard.heading = Up;
                    --guard.y;
                } else {
                    --guard.x;
                }
                break;
        }
        if (inbounds(guard, width, height) && field[guard.y][guard.x] != 'X') {
            field[guard.y][guard.x] = 'X';
            ++total;
        }
    }



    if(verb) printField(field);
    if(verb) cout << guard.x << '\t' << guard.y << endl;

    cout << "\t Tot = " << total << '\n' << endl;

    return EXIT_SUCCESS;
}
