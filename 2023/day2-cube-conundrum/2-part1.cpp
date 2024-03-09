#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct cubes {
  int red = 0;
  int green = 0;
  int blue = 0;
};

cubes bag = {12, 13, 14};

vector<cubes> parse_game_line(string &line) {
  // Removing everything after :
  line = line.substr(line.find(':') + 1);

  vector<cubes> draws;

  stringstream game_ss(line);
  string each_draw;
  // each game
  while (getline(game_ss, each_draw, ';')) {
    stringstream draw_ss(each_draw);
    string each_cube;
    // each draw
    cubes new_cube;
    while (getline(draw_ss, each_cube, ',')) {
      // removing leading and trailing whitespace
      each_cube.erase(each_cube.find_last_not_of(' ') + 1);
      each_cube.erase(0, each_cube.find_first_not_of(' '));

      // each cube
      stringstream cube_ss(each_cube);
      int count;
      string color;

      if (cube_ss >> count >> color) {

        if (color == "red") {
          new_cube.red = count;
        } else if (color == "green") {
          new_cube.green = count;
        } else if (color == "blue") {
          new_cube.blue = count;
        } else {
          cerr << "Error: Unkown color" << color << endl;
        }
      }
    }
    draws.push_back(new_cube);
  }
  return draws;
}

bool is_game_possible(vector<cubes> &each_game) {
  for (cubes game : each_game) {
    if (game.red > bag.red)
      return false;
    else if (game.green > bag.green)
      return false;
    else if (game.blue > bag.blue)
      return false;
    else
      continue;
  }
  return true;
}

int main() {
  // answer
  long res = 0;

  vector<cubes> each_game;
  long game_num = 0;
  string each_game_line;

  ifstream input("./2023/day2-cube-conundrum/input");
  if (input.is_open()) {
    while (getline(input, each_game_line)) {
      // 5 because of 'G', 'a', 'm', 'e', ' '
      game_num = stoi(each_game_line.substr(5, each_game_line.find(":") - 5));
      each_game = parse_game_line(each_game_line);
      if (is_game_possible(each_game)) {
        res += game_num;
      }
    }
    cout << "Result: " << res << endl;
  } else {
    cerr << "Error reading input" << endl;
  }
}
