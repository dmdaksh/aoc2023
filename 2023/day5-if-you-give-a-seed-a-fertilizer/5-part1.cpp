#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

void parse_inputs(vector<string> &string_vec, unordered_set<long> &curr_nums) {
  // Here I am parsing inputs strings.
  // I don't need to store all the mapping.
  // I just need to ensure that I modify the
  // source in curr_nums with destination and
  // carry forward my operation.
  // I am also taking care of case when there
  // is no source-to-destination mapping.
  // In the end, I should be left with only locations.

  string big_str = "";
  for (string s : string_vec) {
    big_str = big_str + s + " ";
  }

  if ((curr_nums.empty()) &&
      (big_str.substr(0, big_str.find(":")) == "seeds")) {
    big_str.erase(0, big_str.find(':') + 2);

    stringstream ss(big_str);
    long tmp;

    while (ss >> tmp) {
      curr_nums.insert(tmp);
    }
    return;
  }

  long tmp1, tmp2, tmp3;

  /* cout << big_str << endl; */
  big_str.erase(0, big_str.find(':') + 1);
  stringstream ss(big_str);

  vector<pair<long, long>> insert_erase_vec;

  while (ss >> tmp1 >> tmp2 >> tmp3) {
    for (auto x = curr_nums.begin(); x != curr_nums.end(); x++) {
      if ((*x >= tmp2) && (*x <= (tmp2 + tmp3 - 1))) {
        // modifying existing curr_nums
        // because if there are no source mapping exists
        // then keep the same num for destination
        insert_erase_vec.push_back({(*x - tmp2 + tmp1), (*x)});
      }
    }
  }
  // erasing first, then inserting
  // this is because source for some seed might be
  // the destination of the other seed. That might
  // lead to overwrite if we insert and erase together.
  // It might insert for source of some seed first
  // and then erase destination of another seed
  for (pair<long, long> x : insert_erase_vec) {
    curr_nums.erase(x.second);
  }
  for (pair<long, long> x : insert_erase_vec) {
    curr_nums.insert(x.first);
  }

  /* for (auto x = curr_nums.begin(); x != curr_nums.end(); x++) { */
  /*   cout << *x << " "; */
  /* } */
  /* cout << "\n\n"; */
}

int main(int argc, char *argv[]) {
  ifstream input("./2023/day5-if-you-give-a-seed-a-fertilizer/input");

  unordered_set<long> curr_nums;

  string input_line;
  if (input.is_open()) {
    while (getline(input, input_line)) {
      if (input_line.find(':') != input_line.npos) {
        vector<string> input_strings;
        input_strings.push_back(input_line);
        while (getline(input, input_line) && input_line != "") {
          input_strings.push_back(input_line);
        }
        parse_inputs(input_strings, curr_nums);
      }
    }
  } else {
    cout << "Error opening file" << endl;
  }

  cout << "Answer: "
       << *min_element(curr_nums.begin(), curr_nums.end(),
                       [](long a, long b) { return a < b; })
       << endl;

  return 0;
}
