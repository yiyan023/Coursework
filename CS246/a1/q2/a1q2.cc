import <iostream>;
import <sstream>;
import <string>;
import <fstream>;

using namespace std;

int calcCharDiff(string word1, string word2) {
	int diff_count = 0;

	for (int i = 0; i < int(word1.length()); i++) {
		if (word1[i] != word2[i]) {
			diff_count += 1;
		}
	}

	return diff_count;
}

bool checkWordList(string word_list, string word) {
	string dict_word;
	ifstream f(word_list);

	while (f >> dict_word) {
		if (dict_word == word) {
			return true;
		} 
	}
	
	return false;
}

bool canOptimizePlay(string prev_words[], int arr_len, string word) {
	for (int i = 0; i < arr_len-1; i++) {
		if (calcCharDiff(prev_words[i], word) == 1) {
			return true;
		}
	}

	return false;
}

int main(int argc, char *argv[]) {
	string start_word = argv[1];
	string end_word = argv[2];
	bool start_bool = checkWordList(argv[3], start_word);
	bool end_bool = checkWordList(argv[3], end_word);

	string dict_word;
	string cur_word;

	string prev_words[9];
	prev_words[0] = start_word;
	int index = 0; // also represents the number of turns

	int word_len = int(start_word.length());
	int best_score = 0;

	if (!start_bool || !end_bool) {
		cerr << "Error: Starting or ending word not found in words file" << endl;
		return 1;

	} else {
		cout << "Starting Word: " << start_word << endl;

		while (cin >> cur_word) {
			int diff_count;
			bool cur_bool = checkWordList(argv[3], cur_word);

			if (int(cur_word.length()) != word_len) {
				diff_count = 0;
			} else {
				diff_count = calcCharDiff(cur_word, prev_words[index]);
			}

			if (diff_count != 1) {
				cerr << "Error: " << cur_word << " does not differ from " << prev_words[index] << " by exactly one character " << endl;
			} else if (!cur_bool) {
				cerr << "Error: " << cur_word << " does not belong to word file" << endl;
			} else {
				bool optimize_bool = canOptimizePlay(prev_words, index+1, cur_word);

				if (optimize_bool) {
					cout << "This word could have been played earlier" << endl;
				}

				index += 1;
				prev_words[index] = cur_word;

				if (index == 8) {
					cout << "You lose" << endl;
					break;

				} else if (cur_word == end_word) {
					int score = 9 - index;
					best_score = max(best_score, score);
					index = 0;

					cout << "Congratulations! Your score: " << score << ", Best Score: " << best_score << endl;
					cout << "Starting Word: " << start_word << endl;
				}
			}
		}

		return 0;
	}
}
