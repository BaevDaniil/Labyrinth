#include <fstream>
#include <string>
#include <iostream>
#include "labyrinth.h"

extern cell_t** map;
extern int height;

int main(void) {
  const std::string file = "example.txt";
  std::ifstream fl(file);
  labyrinth_t labyrinth;
  if (!fl.is_open()) {
    std::cerr << "File not open" << std::endl;
    return 0;
  }
  if (labyrinth.ReadLabyrinth(fl)) {
    //std::cerr << "ALARM!" << std::endl;
    return 0;
  }

  labyrinth.DrawLabyrinth();

  labyrinth.SolveLabyrinth();

  labyrinth.Delete();
  return 0;
}