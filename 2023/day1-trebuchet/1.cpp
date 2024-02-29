#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace std::filesystem;

long sum_digit(string &line) {
  long start, end;
  start = 0;
  end = line.length();

  long first, second;
  first = 0;
  for (long i = 0; i < end; i++) {
    if (isdigit(line[i])) {
      first = line[i] - '0';
      break;
    }
  }
  for (long i = end - 1; i >= start; i--) {
    if (isdigit(line[i])) {
      second = line[i] - '0';
      break;
    }
  }
  return first * 10 + second;
}

int main() {
  path filepath = "./2023/day1-trebuchet/input";

  ifstream file(filepath);

  long long summed_num = 0;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      summed_num += sum_digit(line);
    }
    file.close();

    cout << summed_num << endl;
  } else {
    std::cerr << "Error opening file" << endl;
  }
}
