#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "labyrinth.h"

bool labyrinth_t::ReadLabyrinth(std::ifstream &fl) {
  std::string str;
  std::getline(fl, str);
  std::stringstream sstr (str);
  sstr >> width >> height;
  if (width == 0 || height == 0) {
    std::cerr << "No size arguments" << std::endl;
    return false;
  }
  //std::cout << width << ' ' << height << std::endl;
  try {
    map = new cell_t*[height];
  }
  catch (std::bad_alloc){
    return true;
  }

  for (int i = 0; i < height; i++) {
    try {
      map[i] = new cell_t[width];
    }
    catch (std::bad_alloc) {
      for (int j = i - 1; j >= 0; j--) {
        delete[] map[j];
      }
      delete[] map;
      std::cout << "Not enougth memory" << std::endl;
      return true;
    }
  }
  for (int i = 0; i < height && !fl.eof(); i++) {
    std::getline(fl, str);
    if (str.size() != width) {
      for (int j = 0; j < height; j++) {
        delete[] map[j];
      }
      delete[] map;
      std::cout << "Discrepancy between the indicated and actual dimensions" << std::endl;
      return true;
    }
    for (int j = 0; j < width; j++) {
      switch (str[j]) {
      case ' ': 
        map[i][j].type = CORRIDOR;
        break;
      case 'S':
        if (start.x != -1 && start.y != -1) {
          Delete();
          std::cout << "More then one start" << std::endl;
          return true;
        }
        map[i][j].type = START;
        start.x = j;
        start.y = i;
        break;
      case 'F':
        if (finish.x != -1 && finish.y != -1) {
          Delete();
          std::cout << "More then one finish" << std::endl;
          return true;
        }
        map[i][j].type = FINISH;
        finish.x = j;
        finish.y = i;
        break;
      default:
        map[i][j].type = WALL;
        break;
      }
      map[i][j].flag = false;
    }
  }

  if (start.x == -1 || start.y == -1) {
    std::cout << "No start" << std::endl;
    return true;
  }
  if (finish.x == -1 || finish.y == -1) {
    std::cout << "No finish" << std::endl;
    return true;
  }

  return false;
}

void labyrinth_t::DrawLabyrinth(void) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      switch (map[i][j].type) {
      case WALL:
        std::cout << "#";
        break;
      case CORRIDOR:
        std::cout << " ";
        break;
      case START:
        std::cout << "S";
        break;
      case FINISH:
        std::cout << "F";
        break;
      }
    }
    std::cout << std::endl;
  }
}

bool labyrinth_t::Go(point_t curPoint) {
  map[curPoint.y][curPoint.x].flag = true;
  if (curPoint.x == finish.x && curPoint.y == finish.y) {
    std::cout << std::endl;
    return true;
  }
  if (curPoint.y - 1 >= 0 && map[curPoint.y - 1][curPoint.x].type != WALL && map[curPoint.y - 1][curPoint.x].flag == false) {
    std::cout << "UP ";
    if (Go({ curPoint.x, curPoint.y - 1 })) {
      return true;
    }
    std::cout << "DOWN ";
  }
  if (curPoint.x + 1 < width && map[curPoint.y][curPoint.x + 1].type != WALL && map[curPoint.y][curPoint.x + 1].flag == false) {
    std::cout << "RIGHT ";
    if (Go({ curPoint.x + 1, curPoint.y})) {
      return true;
    }
    std::cout << "LEFT ";
  }
  if (curPoint.y + 1 < height && map[curPoint.y + 1][curPoint.x].type != WALL && map[curPoint.y + 1][curPoint.x].flag == false) {
    std::cout << "DOWN ";
    if (Go({ curPoint.x, curPoint.y + 1 })) {
      return true;
    }
    std::cout << "UP ";
  }
  if (curPoint.x - 1 >= 0 && map[curPoint.y][curPoint.x - 1].type != WALL && map[curPoint.y][curPoint.x - 1].flag == false) {
    std::cout << "LEFT ";
    if (Go({ curPoint.x - 1, curPoint.y })) {
      return true;
    }
    std::cout << "RIGHT ";
  }
  return false;
}

void labyrinth_t::SolveLabyrinth(void) {
  if (!Go(start))
    std::cout << "Imposible to solve" << std::endl;
}

void labyrinth_t::Delete(void) {
  for (int j = 0; j < height; j++) {
    delete[] map[j];
  }
  delete[] map;
}