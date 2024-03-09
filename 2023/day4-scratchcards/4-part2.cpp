#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
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
  unordered_map<int, int> cards_map;
  long result = 0;
  // checking if file can be opened successfully
  if (input.is_open()) {
    while (getline(input, input_line)) {
      // fetching card num
      int card_num = stoi(input_line.substr(5, 3));

      // getting number of matches
      int matches_count = num_matches(input_line);

      cout << "Card " << card_num << ": Matches " << matches_count << endl;

      // one original card
      cards_map[card_num]++;
      for (int i = 1; i <= matches_count; i++) {
        // if card x has n number of matches
        // and if we have m number of card x copies
        // then card x+1..n has (m+1) copies of itself
        cards_map[card_num + i] += cards_map[card_num];
      }
    }
  } else {
    cerr << "Error opening file" << endl;
  }
  for (pair<int, int> i : cards_map) {
    cout << i.first << " " << i.second << endl;
  }
  for (pair<int, int> i : cards_map) {
    result += i.second;
  }
  cout << "Answer: " << result << endl;
  return 0;
}
