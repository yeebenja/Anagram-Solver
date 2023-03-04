// Anagram Solver (for GamePigeon iMessage Anagram Game)
// By: Benjamin Yee (Yu Anmin / Yeo Anmin)
// Email: yeebenja@umich.edu
// LinkedIn: https://www.linkedin.com/in/yeebenja/
// GitHub: https://github.com/yeebenja

#include <iostream>
#include <getopt.h>
#include <map>
#include <queue>
#include <cassert>


using namespace std;

//// Option enumerated classes
enum class Specify_Letters_Mode {kNone = 0, k_Mode_On};	// -s

// Options struct
struct Options {
	Specify_Letters_Mode SLM = Specify_Letters_Mode::kNone;
	vector<char> char_vect;
};


class Anagram_Solver {
private:
	vector<char> char_vect;



public:
	// Custom Constructor
	Anagram_Solver(Options& options) {
		if (options.SLM == Specify_Letters_Mode::kNone) {
			// Default letters will be abcdef if not specified in command line
			char_vect.push_back('A');
			char_vect.push_back('B');
			char_vect.push_back('C');
			char_vect.push_back('D');
			char_vect.push_back('E');
			char_vect.push_back('F');
		}
		else {
			char_vect = options.char_vect;
		}
	}

	// EFFECTS: Runs Anagram Solver object
	void run(void) {

	}
};



// EFFECTS: Given character, returns capitalized 
// version of the character
char capital(const char& c) {
	if (c >= 65 && c <= 90) return c;
	else if (c >= 97 && c <= 122) return c - 32;
	else {
		cout << "Invalid character\n";
		assert(false);
	}
	return 0;
}

void getMode(int argc, char* argv[], Options& options) {
	// These are used with getopt_long()
	opterr = false; // Let us handle all error output for command line options
	int choice;
	int index = 0;
	option long_options[] = {
		{ "specify-letters", required_argument, nullptr, 's'},

	};  // long_options[]

	while ((choice = getopt_long(argc, argv, "s:", long_options, &index)) != -1) {
		switch (choice) {
		case 's': {
			options.SLM = Specify_Letters_Mode::k_Mode_On;
			string arg{ optarg };
			for (size_t i = 0; i < arg.length(); ++i) {
				options.char_vect.push_back(capital(arg[i]));
			}
			sort(options.char_vect.begin(), options.char_vect.end());
			break;
		}
		default: {
			cerr << "error: invalid option" << endl;
			exit(1);
		}
		}
	}
}

// Main function
int main(int argc, char** argv) {
	Options options;
	getMode(argc, argv, options);
	Anagram_Solver solver_1(options);
	solver_1.run();

	return 0;
}