import <iostream>;
import <sstream>;
import rational;
using namespace std;

int main(){
  const int arr_size = 4;
  Rational a[arr_size];

  bool done = false;
  while(!done){
    string command;
    char which;

    cin >> command;
    if (cin.eof()) { 
      break;
    }

    if (command == "quit"){
      done = true;      
    }
    else if (command == "create") { // Create a new rational in slot [a-d]
      cin >> which; // reads a b c or d
      cin >> a[which-'a'];
    }
    else if (command == "print") { // Print the rational in slot [a-d]
      cin >> which; // reads a b c or d
      cout << a[which-'a'] << endl;;
    }
    else if (command == "-") { // Subtract the second from the first
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] - a[which2-'a'] << endl;
    }
    else if (command == "u-") { //unary minus
      cin >> which; // reads a b c or d
      cout << -a[which-'a']  << endl;
    }
    else if (command == "+") { // Add the first and second
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] + a[which2-'a'] << endl;
    }
    else if (command == "*") { // Multiply the first and second
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] * a[which2-'a'] << endl;
    }
    else if (command == "/") { // Divide the first by the second
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] / a[which2-'a'] << endl;
    }
    else if (command == "+=") { // Augment the first by the second
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      a[which-'a'] += a[which2-'a']; 
      cout << a[which-'a']  << endl;
    }
    else if (command == "-="){ // Decrease the first by the second
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      a[which-'a'] -= a[which2-'a'];
      cout << a[which-'a'] << endl;
    }
  }
}
