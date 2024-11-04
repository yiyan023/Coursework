import <iostream>;
import <string>;
import stringBag;

using namespace std;

StringBag genTempBag();

const int MAX_BAGS = 4;

// TEST HARNESS FILE: Do not modify this file. Make sure you read the comments AND code
//                  : below to understand what the test harness does, so that you can
//                  : create appropriate tests.
// Do not test the test harness or test with invalid inputs.
int main() {
    // You will have 4 StringBags to work with, accessed by indices 0, 1, 2, and 3.
    StringBag bags[MAX_BAGS];
    string cmd;
    while (cin >> cmd) {
        // print idx         : prints the bag at index idx using the << operator.
        if (cmd == "print") {
            int idx; cin >> idx;
            cout << "BAG " << idx << ": " << bags[idx] << endl;
        }

        // debugPrint idx    : debug prints the bag at index idx by calling the
        //                   : debugPrint method.
        else if (cmd == "debugPrint") {
            int idx; cin >> idx;
            cout << "BAG " << idx << ": ";
            bags[idx].debugPrint(cout);
        }

        // arity idx ele     : prints the int returned by calling the arity method
        //                   : with argument ele on the bag at index idx.
        else if (cmd == "arity") {
            int idx; cin >> idx;
            string ele; cin >> ele;
            cout << bags[idx].arity(ele) << endl;
        }

        // getNumElements idx: prints the int returned by calling the getNumElements
        //                   : method on the bag at index idx.
        else if (cmd == "getNumElements") {
            int idx; cin >> idx;
            cout << bags[idx].getNumElements() << endl;
        }

        // getNumValues idx  : prints the int returned by calling the getNumValues
        //                   : method on the bag at index idx.
        else if (cmd == "getNumValues") {
            int idx; cin >> idx;
            cout << bags[idx].getNumValues() << endl;
        }

        // add idx ele       : calls the add method with argument ele on the bag
        //                   : at index idx.
        else if (cmd == "add") {
            int idx; cin >> idx;
            string ele; cin >> ele;
            bags[idx].add(ele);
        }

        // remove idx ele    : calls the remove method with argument ele on the bag
        //                   : at index idx.
        else if (cmd == "remove") {
            int idx; cin >> idx;
            string ele; cin >> ele;
            bags[idx].remove(ele);
        }

        // removeAll idx ele : calls the removeAll method with argument ele on the bag
        //                   : at index idx.
        else if (cmd == "removeAll") {
            int idx; cin >> idx;
            string ele; cin >> ele;
            bags[idx].removeAll(ele);
        }

        // + idx1 idx2       : prints using << the result of using the + operator method
        //                   : of the bag at index idx1 on the bag at index idx2.
        else if (cmd == "+") {
            int idx1, idx2; cin >> idx1 >> idx2;
            cout << bags[idx1]+bags[idx2] << endl;
        }

        // - idx1 idx2       : prints using << the result of using the - operator method
        //                   : of the bag at index idx1 on the bag at index idx2.
        else if (cmd == "-") {
            int idx1, idx2; cin >> idx1 >> idx2;
            cout << bags[idx1]-bags[idx2] << endl;
        }

        // += idx1 idx2      : calls the += operator method of the bag at index idx1 on
        //                   : the bag at index idx2.
        else if (cmd == "+=") {
            int idx1, idx2; cin >> idx1 >> idx2;
            bags[idx1] += bags[idx2];
        }

        // -= idx1 idx2      : calls the -= operator method of the bag at index idx1 on
        //                   : the bag at index idx2.
        else if (cmd == "-=") {
            int idx1, idx2; cin >> idx1 >> idx2;
            bags[idx1] -= bags[idx2];
        }

        // == idx1 idx2      : prints the result of using the == operator method
        //                   : of the bag at index idx1 on the bag at index idx2.
        else if (cmd == "==") {
            int idx1, idx2; cin >> idx1 >> idx2;
            cout << (bags[idx1] == bags[idx2] ? "true" : "false") << endl;
        }

        // dezombify idx     : calls the dezombify method on the bag at index idx.
        else if (cmd == "dezombify") {
            int idx; cin >> idx;
            bags[idx].dezombify();
        }

        // copyconstruct idx : uses the copy constructor to create tmp from the bag at
        //                   : index idx, then prints tmp using <<.
        else if (cmd == "copyconstruct") {
            int idx; cin >> idx;
            StringBag tmp{bags[idx]};
            cout << "COPY OF BAG " << idx << ": " << tmp << endl;
        }

        // moveconstruct     : uses the move constructor to create tmp from the bag returned
        //                   : by genTempBag, then prints tmp using <<.
        else if (cmd == "moveconstruct") {
            StringBag tmp{genTempBag()};
            cout << "MOVE CONSTRUCTED BAG: " << tmp << endl;
        }

        // copy= idx1 idx2   : copies the bag at index idx2 to the bag at index idx1 using
        //                   : copy assignment.
        else if (cmd == "copy=") {
            int idx1, idx2; cin >> idx1 >> idx2;
            bags[idx1] = bags[idx2];
        }

        // move= idx         : moves the bag returned by genTempBag to the bag at index
        //                   : idx using move assignment.
        else if (cmd == "move=") {
            int idx; cin >> idx;
            bags[idx] = genTempBag();
        }

        else {
            cerr << "UNRECOGNIZED COMMAND: " << cmd << endl;
        }
    }
}

// Returns a StringBag containing:
// { ("one", 1), ("two", 2), ("three", 3), } 
// For use to create an r-value to test move operations.
StringBag genTempBag() {
    StringBag result_sb;
    string names[3] = {"one", "two", "three"};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < i+1; ++j) {
            result_sb.add(names[i]);
        }
    }
    return result_sb;
}

