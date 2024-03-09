#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

int num_matches(string &card) {
  // Sample input:
  // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
  int start_idx = card.find(':');
  int pipe_idx = card.find('|');

  // creating two different strings
  // for winning numbers
  // & numbers we have
  string win_str = card.substr(start_idx + 1, pipe_idx - start_idx - 1);
  string num_str = card.substr(pipe_idx + 1);

  // set to have winning nums
  unordered_set<int> win_nums;

  stringstream ss(win_str);
  int tmp;

  while (ss >> tmp) {
    win_nums.insert(tmp);
  }

  int matches_count = 0;

  ss.clear();
  ss.str(num_str);

  // looking up winning numbers
  // from the numebers we have
  while (ss >> tmp) {
    if (win_nums.find(tmp) != win_nums.end()) {
      matches_count++;
    }
  }

  return matches_count;
}

int main(int argc, char *argv[]) {

  ifstream input("./2023/day4-scratchcards/input");
  string input_line;
  long result = 0;
  // checking if file can be opened successfully
  if (input.is_open()) {
    while (getline(input, input_line)) {
      // getting number of matches
      int matches_count = num_matches(input_line);
      // if matches are found
      if (matches_count != 0) {
        // adding 2^(matches-1) to the result
        result += (1 << (matches_count - 1));
      }
    }
  } else {
    cerr << "Error opening file" << endl;
  }
  cout << (1 << 2) << endl;
  cout << "Answer: " << result << endl;
  return 0;
}
