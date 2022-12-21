#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> tree_map;
// std::vector<std::vector<int>> tree_map = {{3, 0, 3, 7, 3},
//                                           {2, 5, 5, 1, 2},
//                                           {6, 5, 3, 3, 2},
//                                           {3, 3, 5, 4, 9},
//                                           {3, 5, 3, 9, 0}};
bool TreeIsVisible(int x, int y) {
  if (x == 0 || x == tree_map[0].size() - 1 || y == 0 ||
      y == tree_map.size() - 1)
    return true;

  bool is_clear_path = true;
  // left
  for (int i = x - 1; i >= 0; i--) {
    if (tree_map[y][i] >= tree_map[y][x]) {
      is_clear_path = false;
      break;
    }
  }
  if (is_clear_path) return true;

  is_clear_path = true;
  // right
  for (int i = x + 1; i < tree_map[0].size(); i++) {
    if (tree_map[y][i] >= tree_map[y][x]) {
      is_clear_path = false;
      break;
    }
  }
  if (is_clear_path) return true;

  is_clear_path = true;
  // up
  for (int i = y - 1; i >= 0; i--) {
    if (tree_map[i][x] >= tree_map[y][x]) {
      is_clear_path = false;
      break;
    }
  }
  if (is_clear_path) return true;

  is_clear_path = true;
  // down
  for (int i = y + 1; i < tree_map.size(); i++) {
    if (tree_map[i][x] >= tree_map[y][x]) {
      is_clear_path = false;
      break;
    }
  }

  return is_clear_path;
}

int CalculateScenicScore(int x, int y) {
  if (x == 0 || x == tree_map[0].size() - 1 || y == 0 ||
      y == tree_map.size() - 1)
    return 0;

  // left
  int left_trees_seen = 0;
  for (int i = x - 1; i >= 0; i--) {
    left_trees_seen++;
    if (tree_map[y][i] >= tree_map[y][x]) {
      break;
    }
  }

  int right_trees_seen = 0;
  for (int i = x + 1; i < tree_map[0].size(); i++) {
    right_trees_seen++;
    if (tree_map[y][i] >= tree_map[y][x]) {
      break;
    }
  }

  int up_trees_seen = 0;
  // up
  for (int i = y - 1; i >= 0; i--) {
    up_trees_seen++;
    if (tree_map[i][x] >= tree_map[y][x]) {
      break;
    }
  }

  int down_trees_seen = 0;
  // down
  for (int i = y + 1; i < tree_map.size(); i++) {
    down_trees_seen++;
    if (tree_map[i][x] >= tree_map[y][x]) {
      break;
    }
  }

  return left_trees_seen * right_trees_seen * up_trees_seen * down_trees_seen;
}

void CalculateTreeHeights() {
  assert(tree_map.size() > 0);
  int highest_tree_score = 0;
  for (int y = 0; y < tree_map.size(); y++) {
    for (int x = 0; x < tree_map[y].size(); x++) {
      // bool is_visible = TreeIsVisible(x, y);
      // if (is_visible) visible_trees++;
      // std::cout << tree_map[x][y] << " has clear path?"
      //           << (is_visible ? "true" : "false") << std::endl;
      int scenic_score = CalculateScenicScore(x, y);
      if (scenic_score > highest_tree_score) highest_tree_score = scenic_score;
      std::cout << tree_map[y][x] << " Has score:" << scenic_score << std::endl;
    }
  }
  std::cout << "HIGHEST SCORE FOUND:" << highest_tree_score << std::endl;
}

void ImportTreeMap() {
  std::ifstream file{"day8input.txt"};
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << "LINE:" << line << std::endl;
      std::vector<int> row;
      for (auto& c : line) {
        int v = int(c) - 48;
        std::cout << "Char is " << c << " as INT:" << v << std::endl;
        row.push_back(v);
      }
      tree_map.push_back(row);
    }
  }
}

int main() {
  ImportTreeMap();
  CalculateTreeHeights();
}
