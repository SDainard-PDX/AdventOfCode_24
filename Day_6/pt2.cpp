#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define FILE_IN "../data.txt"
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

//4 varients to cover always looking the turn direction of the heading looking for the turn direction
//stop if #
int look(const vector<vector<char>> field, security_guard guard, int width, int height) {
    return 0;
}

int main() {
    //variables
    int verb = 1;
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
            if (x == '^') { flip = true; }
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
        int t_in = total;
        switch (guard.heading) {
            case Up:
                if ( guard.y != 0 && (field[guard.y-1][guard.x]) == '#') {
                    guard.heading = Right;
                    field[guard.y][guard.x] = 'r';
                    ++guard.x;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'd') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Left for an l
                } else {
                    field[guard.y][guard.x] = 'u';
                    --guard.y;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'r') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Down for a d
                }
                break;
            case Right:
                if ( guard.x != width-1 && (field[guard.y][guard.x+1]) == '#') {
                    guard.heading = Down;
                    field[guard.y][guard.x] = 'd';
                    ++guard.y;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'l') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Up for an u
                } else {
                    field[guard.y][guard.x] = 'r';
                    ++guard.x;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'd') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Left for an l
                }
                break;
            case Down:
                if ( guard.y != height-1 && (field[guard.y+1][guard.x]) == '#') {
                    guard.heading = Left;
                    field[guard.y][guard.x] = 'l';
                    --guard.x;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'u') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Right for an r
                } else {
                    field[guard.y][guard.x] = 'd';
                    ++guard.y;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'l') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Up for an u
                }
                break;
            case Left:
                if ( guard.x != 0 && (field[guard.y][guard.x-1]) == '#') {
                    guard.heading = Up;
                    field[guard.y][guard.x] = 'u';
                    --guard.y;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'r') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Down for a d
                } else {
                    field[guard.y][guard.x] = 'l';
                    --guard.x;
                    if (inbounds(guard, width, height) && field[guard.y][guard.x] == 'u') { ++total; }
                    //for each of these add a look() as an OR to above; this would be look Right for an r
                }
                break;
        }
        if (t_in != total) printField(field);
    }



    if(verb) printField(field);
    if(verb) cout << guard.x << '\t' << guard.y << endl;

    cout << "\t Tot = " << total << '\n' << endl;

    return EXIT_SUCCESS;
}
