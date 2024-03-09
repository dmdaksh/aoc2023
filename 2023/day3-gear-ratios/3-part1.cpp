#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<int, int> getNumberIdx(string &line, int pos) {
  int first = pos;
  int last = pos;
  while (first-- && isdigit(line[first])) {
  }
  while (last++ && last < line.length() && isdigit(line[last])) {
  }
  return pair<int, int>{first + 1, last - 1};
}

int main() {
  // reading file and storing in vector<string>
  ifstream input("./2023/day3-gear-ratios/input");
  string input_line;

  vector<string> schematic;
  if (input.is_open()) {
    while (getline(input, input_line)) {
      schematic.push_back(input_line);
    }
  } else {
    cerr << "Error reading input!" << endl;
  }

  // declaring variable result
  long res = 0;

  // defining directions
  pair<int, int> offSets[] = {
      {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1},
  };

  int rows = schematic.size();
  int cols = schematic[0].length();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // flag for symbol around
      bool is_symbol_present = false;

      if (isdigit(schematic[i][j])) {
        // check offsets
        for (pair<int, int> offset : offSets) {
          int new_i = (i + offset.first < rows && i + offset.first >= 0)
                          ? i + offset.first
                          : i;
          int new_j = (j + offset.second < cols && j + offset.second >= 0)
                          ? j + offset.second
                          : j;
          if (schematic[new_i][new_j] != '.' &&
              !isdigit(schematic[new_i][new_j])) {
            is_symbol_present = true;
            break;
          }
        }
      }
      // if symbol found
      pair<int, int> num_idx;
      if (is_symbol_present) {
        // get number idx
        num_idx = getNumberIdx(schematic[i], j);
        // change j to last of number idx
        // to avoid counting same number multiple times
        j = num_idx.second + 1;

        // extract number and sum to res
        res += stoi(schematic[i].substr(num_idx.first,
                                        num_idx.second - num_idx.first + 1));
      }
    }
  }

  cout << "Answer: " << res << endl;
}
