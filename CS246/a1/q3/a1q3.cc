import <iostream>;
import <sstream>;
import <string>;

using namespace std;

int main(int argc, char *argv[]) {
	int max_columns[10];
	int columns = 0;

	for (int i = 0; i < 10; i++) {
		max_columns[i] = 0;
	}

	string line;

	while(getline(cin, line)) {
		istringstream iss{line};
		string word;
		int i = 0;

		while (iss >> word) {
			max_columns[i] = max(max_columns[i], int(word.length()));
			i += 1;

			columns = max(columns, i);

			if (argc == 2 && i >= stoi(argv[1])) {
				i = 0;
			}
		}
	}

	int result = max(0, columns - 1);

	for (int i = 0; i < columns; i++) {
		result += max_columns[i];
	}

	cout << result << endl;
}
