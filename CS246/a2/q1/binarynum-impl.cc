module binarynum;
import <iostream>;
import <sstream>;
import <string>;
using namespace std;

const int INT_MAX = 2147483647;

BinaryNum readBinaryNum() {
	BinaryNum new_binary;
	int old_size;
	bool* new_content;
	char bit;
	
		while (cin >> bit) {
			if (bit == ' ' || bit == '\n') continue; // ignore whitespaces and newline characters
			old_size = new_binary.size;

			if (bit == '0' || bit == '1') {
				new_binary.size++;
				
				if (new_binary.size > new_binary.capacity) { // increase array length in heap
					if (new_binary.capacity == 0) {
						new_binary.capacity = 4;
					} else {
						new_binary.capacity *= 2;
					}

					new_content = new bool[new_binary.capacity];

					for (int i = 0; i < old_size; i++) {
						new_content[i] = new_binary.contents[i];
					}

					delete[] new_binary.contents;
					new_binary.contents = new_content;
				}

				new_binary.contents[new_binary.size-1] = (bit == '1');
			} else { // otherwise, it is not a bit
				break;
			}
		}

	return new_binary;
}

void binaryConcat(BinaryNum &binNum) {
	bool* new_content;
	int old_size;
	char bit;

	while (cin >> bit) {
		if (bit == ' ' || bit == '\n') continue; // ignore whitespace and newline characters

		old_size = binNum.size;

		if (bit == '0' || bit == '1') {
			binNum.size++;

			if (binNum.size > binNum.capacity) { // increase array length in heap
				if (binNum.capacity == 0) {
						binNum.capacity = 4;
				} else {
						binNum.capacity *= 2; 
				}

				new_content = new bool[binNum.capacity];

				for (int i = 0; i < old_size; i++) {
						new_content[i] = binNum.contents[i];
				}

				delete[] binNum.contents;
				binNum.contents = new_content;
			}

			binNum.contents[binNum.size-1] = (bit == '1');
		} else { // otherwise, it is not a bit
			return;
		}
	}
}

int binaryToDecimal(const BinaryNum &binNum) {
	int result = 0;
	int multiplier = 1;

	for (int i = binNum.size-1; i >= 0; i--) {
		if (result + (multiplier * binNum.contents[i]) <= INT_MAX) {
			result += (multiplier * binNum.contents[i]);
			multiplier *= 2;
		} else {
			return -1; // invalid integer
		}
	}

	return result;
}

void printBinaryNum(std::ostream &out, const BinaryNum &binNum, char sep) {
	for (int i = 0; i < binNum.size; i++) {
		out << binNum.contents[i];

		if (i != binNum.size-1) { // should not end with a separator
			out << sep;
		}
	}
	out << endl;
}
