#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

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

      // storing new row as well as unique cols range
      set<pair<int, pair<int, int>>> num_indices;

      if (schematic[i][j] == '*') {
        // check offsets
        for (pair<int, int> offset : offSets) {
          int new_i = (i + offset.first < rows && i + offset.first >= 0)
                          ? i + offset.first
                          : i;
          int new_j = (j + offset.second < cols && j + offset.second >= 0)
                          ? j + offset.second
                          : j;
          if (isdigit(schematic[new_i][new_j])) {
            num_indices.insert(pair<int, pair<int, int>>(
                new_i, getNumberIdx(schematic[new_i], new_j)));
          }
        }
      }

      // check length of num_indices set
      // if length is 2, that means it has exactly
      // two part numbers
      if (num_indices.size() == 2) {
        long tmp_num = 1;
        for (pair<int, pair<int, int>> x : num_indices) {
          tmp_num *= stoi(schematic[x.first].substr(
              x.second.first, x.second.second - x.second.first + 1));
        }
        res += tmp_num;
      }
    }
  }

  cout << "Answer: " << res << endl;
}
