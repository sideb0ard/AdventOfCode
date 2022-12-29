#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

//  -87,109
// -87,110
// -87,111
// -87,112
// -87,113
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

std::set<Pos, PosCmp> pos_visited;

void PrintSet() {
  std::cout << "POS VISITED:";
  for (const auto& s : pos_visited) {
    std::cout << s.x << "," << s.y << " ";
  }
  std::cout << std::endl;
}
void RopeBridge() {
  for (int i = 0; i < 3; i++) {
    std::pair<std::set<Pos>::iterator, bool> ret;
    ret = pos_visited.insert({-87, 109});
    if (ret.second == true)
      std::cout << "** INSERTED POS:" << std::endl;
    else
      std::cout << "** FAILED TO INSERT POS:" << std::endl;
    PrintSet();
  }
}

int main() {
  RopeBridge();
  std::cout << "Tail visited this number of places:" << pos_visited.size()
            << std::endl;
}
