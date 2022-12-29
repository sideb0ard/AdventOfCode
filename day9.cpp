#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Pos {
  int x{0};
  int y{0};
};

struct PosCmp {
  bool operator()(const Pos& lhs, const Pos& rhs) const {
    std::cout << "POS CMP: lhs:" << lhs.x << "," << lhs.y
              << " and rhs:" << rhs.x << "," << rhs.y << std::endl;
    return (lhs.x < rhs.x) || (lhs.y < rhs.y);
  }
};

std::array<Pos, 10> rope{};
std::set<Pos, PosCmp> pos_visited;

bool NeedsUpdate(const Pos& head, const Pos& tail) {
  if (std::abs(head.x - tail.x) > 1) return true;
  if (std::abs(head.y - tail.y) > 1) return true;
  return false;
}

void PrintSet() {
  std::cout << "POS VISITED:";
  for (const auto& s : pos_visited) {
    std::cout << s.x << "," << s.y << " ";
  }
  std::cout << std::endl;
}

void UpdatePos(const Pos& head, Pos& tail, bool track) {
  if (!NeedsUpdate(head, tail)) return;
  bool is_same_row = head.y == tail.y;
  if (!is_same_row) {
    if (head.y > tail.y) {
      tail.y++;
    } else {
      tail.y--;
    }
  }

  bool is_same_column = head.x == tail.x;
  if (!is_same_column) {
    if (head.x > tail.x) {
      tail.x++;
    } else {
      tail.x--;
    }
  }
  if (track) {
    std::pair<std::set<Pos>::iterator, bool> ret;
    ret = pos_visited.insert({tail.x, tail.y});
    if (ret.second == true)
      std::cout << "** INSERTED POS:" << tail.x << "," << tail.y << std::endl;
    else
      std::cout << "** FAILED TO INSERT POS:" << tail.x << "," << tail.y
                << std::endl;
    std::cout << "Tail: " << tail.x << "," << tail.y
              << " visited this number of places:" << pos_visited.size()
              << std::endl;
    PrintSet();
  }
}

void MovePos(const std::string& dir, int num_steps) {
  for (int i = 0; i < num_steps; i++) {
    if (dir == "U")
      rope[0].y += 1;
    else if (dir == "D")
      rope[0].y -= 1;
    else if (dir == "L")
      rope[0].x -= 1;
    else if (dir == "R")
      rope[0].x += 1;

    std::cout << "HEAD MOVED TO " << rope[0].x << "," << rope[0].y << std::endl;
    for (int i = 0; i < 9; i++) {
      bool track = false;
      if (i == 8) track = true;
      UpdatePos(rope[i], rope[i + 1], track);
    }
  }
}

void RopeBridge() {
  // std::ifstream file{"day9testinput.txt"};
  std::ifstream file{"day9input.txt"};
  if (file.is_open()) {
    pos_visited.insert({0, 0});
    std::string line;
    std::string dir;
    int num_steps;
    while (std::getline(file, line)) {
      std::istringstream ss{line};
      ss >> dir;
      ss >> num_steps;
      std::cout << "DIR:" << dir << " FOR " << num_steps << std::endl;
      MovePos(dir, num_steps);
    }
  }
}

int main() {
  for (int i = 0; i < 10; i++) {
    rope[i] = {0, 0};
  }
  RopeBridge();
  std::cout << "Tail visited this number of places:" << pos_visited.size()
            << std::endl;
}
