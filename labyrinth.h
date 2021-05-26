#ifndef LABYRINTH
#define LABYRINTH
#pragma once

#include <fstream>

using cell_type_t = enum{
  START,
  WALL,
  CORRIDOR,
  FINISH
};

using cell_t = struct {
  cell_type_t type;
  bool flag;
};

using point_t = struct {
  int x;
  int y;
};

class labyrinth_t {
  private:
    cell_t** map;
    int width = 0;
    int height = 0;
    point_t start = { -1, -1 };
    point_t finish = { -1, -1 };
    bool Go(point_t curPoint);
  public:
    bool ReadLabyrinth(std::ifstream& fl);
    void DrawLabyrinth(void);
    void SolveLabyrinth(void);
    void Delete(void);
};

#endif