// Anagram Solver (for GamePigeon iMessage Anagram Game)
// By: Benjamin Yee (Yu Anmin / Yeo Anmin)
// Email: yeebenja@umich.edu
// LinkedIn: https://www.linkedin.com/in/yeebenja/
// GitHub: https://github.com/yeebenja

#include <iostream>
#include <getopt.h>
#include <set>
#include <queue>
#include <cassert>
#include <string>
#include <fstream>
#include <cassert>
#include <map>

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
	// --- Private Variables ---
	vector<char> char_vect;
	map<char, int> char_map;
	set<char> char_set;
	vector<string> list_of_words;
	// Use set/subset instead of map
	
	
	struct Solution {
		string word;
		int points;
	};



	class Solution_Compare {
	public:
		// EFFECTS: Returns true if priority(a) < priority(b)
		bool operator()(const Solution& a, const Solution& b) {
			if (a.points < b.points) {
				return true;
			}
			else if (a.points > b.points) {
				return false;
			}
			else {
				return a.word[0] < b.word[0];
			}
		}
	};
	priority_queue<Solution, vector<Solution>, Solution_Compare> Solution_pq;


	// --- Private Functions ---
	
	// EFFECTS: Runs solver
	void solve(void) {
		for (auto current_word : list_of_words) {
			set<char> current_word_set;
			// Create set for current word in word_list
			for (size_t i = 0; i < current_word.size(); ++i) {
				current_word_set.insert(current_word[i]);

			}
			// If current_word_set is a subset of char_set, then current_word
			// is a valid solution


			// Link: https://stdcxx.apache.org/doc/stdlibug/8-2.html#:~:text=The%20function%20std%3A%3Aincludes,to%20which%20it%20compares%20equal.
			// Shows me how to check if set is subset of another set
			if (includes(char_set.begin(), char_set.end(), current_word_set.begin(), current_word_set.end())) {
				// For the Anagram game specifically:
				// If the solution contains more letters than the amount of letters given, then
				// the solution is not valid
				// Make sure that the current_word's letters have the same quantity then the 
				// char_vect's letters, I.E:
				// Make sure if char_vect has 3 A's, that the Solution has 3 A's or less
				// 
				//if (current_word.size() <= char_vect.size()) {
				//	Solution temp_solution{ current_word, (int) current_word.size() };
				//	Solution_pq.push(temp_solution);
				//}
				if (solution_is_valid(current_word)) {
					Solution temp_solution{ current_word, (int) current_word.size() };
					Solution_pq.push(temp_solution);
				}
				
			}

		}
	}

	// EFFECTS: Given current_word, checks to see if solution is valid
	bool solution_is_valid(const string& current_word) {
		map<char, int> current_word_map;
		for (size_t i = 0; i < current_word.size(); ++i) ++current_word_map[current_word[i]];
		// Now compare the two maps: current_word_map and char_map
		for (auto i : current_word_map) {
			char letter = i.first;
			int quantity = i.second;
			if (quantity > char_map[letter]) return false;
		}
		return true;
	}

	// EFFECTS: Prints results
	void print_results(void) {
		while (!Solution_pq.empty()) {
			cout << Solution_pq.top().word << ", " << Solution_pq.top().points << " points\n";
			Solution_pq.pop();
		}
	}
	
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
		// Properly initilaize char_set, list_of_words, and char_map
		char_vect = options.char_vect;
		for (auto i : char_vect) char_set.insert(i);
		
		ifstream file;
		// File can be found here: https://drive.google.com/file/d/1oGDf1wjWp5RF_X9C7HoedhIWMh5uJs8s/view
		file.open("Collins_Scrabble_Words_(2019).txt");
		// Throw exception if file is not open
		if (file.is_open() == false) assert(false);
		string str_temp;
		getline(file, str_temp);
		while (file >> str_temp) {
			list_of_words.push_back(str_temp);
		}
		file.close();
		
		for (auto i : char_vect) ++char_map[i];
	}

	// EFFECTS: Runs Anagram Solver object
	void run(void) {
		solve();
		print_results();
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
			//sort(options.char_vect.begin(), options.char_vect.end());
			// No need to sort!
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