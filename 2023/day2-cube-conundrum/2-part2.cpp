#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct cubes {
  int red = 0;
  int green = 0;
  int blue = 0;
};

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

long game_power(vector<cubes> &each_game) {
  cubes min_cube;
  /* cout << min_cube.red << " " << min_cube.green << " " << min_cube.blue <<
   * endl; */
  for (cubes game : each_game) {
    if (min_cube.red < game.red) {
      min_cube.red = game.red;
    }
    if (min_cube.green < game.green) {
      min_cube.green = game.green;
    }
    if (min_cube.blue < game.blue) {
      min_cube.blue = game.blue;
    }
  }

  long res = 1;
  if (min_cube.red != 0) {
    res *= min_cube.red;
  }
  if (min_cube.green != 0) {
    res *= min_cube.green;
  }
  if (min_cube.blue != 0) {
    res *= min_cube.blue;
  }
  return res;
}

int main() {
  // answer
  long res = 0;

  vector<cubes> each_game;
  string each_game_line;

  ifstream input("./2023/day2-cube-conundrum/input");
  if (input.is_open()) {
    while (getline(input, each_game_line)) {
      each_game = parse_game_line(each_game_line);
      res += game_power(each_game);
    }
    cout << "Result: " << res << endl;
  } else {
    cerr << "Error reading input" << endl;
  }
}
