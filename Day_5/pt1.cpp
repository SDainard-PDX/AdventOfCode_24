#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#define FILE_IN "../t1data.txt"
using namespace std;

int main() {
    int verb = 0;

    ifstream in_file(FILE_IN);
    if (!in_file.is_open()) {
        cout << "failed to open file" << endl;
        return EXIT_FAILURE;
    }

    //variables
    int rnd = {0},total = {0};
//    multimap<int, int> leads = {};   //key is page # & value is pages that must be after
    multimap<int, int> follows = {}; //key is page # & value is pages that must be before it

        //get the rules by reading in numbers for part 1
        while ( in_file.peek() != '\n' ) {
            string line;
            int fir = 0, sec = 0;
            getline(in_file, line, '|');
            fir = stoi(line);
            getline(in_file, line);
            sec = stoi(line);

//            leads.insert({fir, sec});
            follows.insert({sec, fir});
            char x = in_file.peek();
            if (verb > 1) cout << fir << '\t' << sec << endl;
        }
        if (verb) {
//            cout << "Leads rules" << endl;
//            for (auto rule_l : leads) {cout << rule_l.first << " - " << rule_l.second << endl;}
            cout << "Follows rules" << endl;
            for (auto rule_f : follows) {cout << rule_f.first << " - " << rule_f.second << endl;}
        }


        //get & check the print order list
        while ( !in_file.eof() ) {
            //get
            in_file.get();  //clear the new line char
            vector<int> print_order = {};
            while ( in_file.peek() != '\n' && in_file.peek()  != '\377') {
                int y;
                in_file >> y;
                print_order.push_back(y);
                if ( in_file.peek() == ',') in_file.get();
            }
            if (verb) {
                for (auto page : print_order) cout << page << ", ";
            }

            //check
            int n = print_order.size();
            bool good = true;
            for (int page = 0; page < n-1; ++page) {
                auto range_f = follows.equal_range(print_order[page]);   //find iterator to elem 1 if curr page in key
                if (range_f.first != range_f.second) {                                //if it exists go over all elem in value
                    for (int following = page+1; following < n && good; ++following) {   // comparing prior pages
                        for (auto it = range_f.first; it != range_f.second; ++ it) {
                            if (verb > 1) cout << "Page " << print_order[page] <<
                            " follows " << it->second << " compare to " << print_order[following];
                            if ( print_order[following] == it->second ) {
                                if(verb) cout << "\tbad1" << endl;
                                good = false;
                                break;
                            }
                            if(verb > 1) cout << endl;
                        }
                    }
                }
/*
                auto range_l = leads.equal_range(print_order[page]);   //find iterator to elem 1 if curr page in key
                if (range_l.first != range_l.second) {                                //if it exists go over all elem in value
                    for (int leading = page-1; leading >= 0 && good; --leading) {   // comparing prior pages
                        for (auto it = range_l.first; it != range_l.second; ++ it) {
                            if (verb > 1) cout << "Page " << print_order[page] <<
                            " leads " << it->second << " compare to " << print_order[leading];
                            if ( print_order[leading] == it->second ) {
                                if(verb) cout << "\tbad2" << endl;
                                good = false;
                                break;
                            }
                            if(verb > 1) cout << endl;
                        }
                    }
                }
*/
            }
            if (good) {
                total += print_order[n/2];
                if (verb) cout << "\tGood mid is " << print_order[n/2] << " total is " << total << endl;

            }
        }

    cout << "\t Tot = " << total << '\n' << endl;

    in_file.close();
    return EXIT_SUCCESS;
}
