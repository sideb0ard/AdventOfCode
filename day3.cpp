#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// 65 - 90 // 97 - 122

int GetMappingForChar(char c) {
  if (c > 64 && c < 91) {
    return c - 38;
  }
  if (c > 96 && c < 123) {
    return c - 96;
  }
  return -1;
}

int FindCommonCharacterPriority(std::string& first, std::string& second) {
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());

  // std::cout << first << " " << first.size() << " " << second << " "
  //           << second.size() << std::endl;

  for (int i = 0; i < first.size(); i++) {
    for (int j = 0; j < first.size(); j++) {
      if (first[i] == second[j]) {
        int val = GetMappingForChar(first[i]);
        std::cout << "FOUND COMMON CHAR:" << first[i] << " " << second[j]
                  << " with VAL:" << val << std::endl;
        return val;
      }
    }
  }
  return 0;
}

int GetPartOnePriorities() {
  int sum = 0;
  std::ifstream file("rucksacktestdata.txt");
  // std::ifstream file("rucksackdata.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // std::cout << line << std::endl;
      int halfsize = line.size() / 2;
      std::string first_half = line.substr(0, halfsize);
      std::string second_half = line.substr(halfsize, line.size());

      sum += FindCommonCharacterPriority(first_half, second_half);
    }
  }
  return sum;
}

int FindCharacterFromGroup(std::vector<std::string>& bags) {
  if (bags.size() == 3) {
    for (int i = 0; i < bags.size(); i++) {
      std::sort(bags[i].begin(), bags[i].end());
    }

    for (int i = 0; i < bags[0].size(); i++) {
      for (int j = 0; j < bags[1].size(); j++) {
        for (int k = 0; k < bags[2].size(); k++) {
          if (bags[0][i] == bags[1][j] && bags[0][i] == bags[2][k]) {
            int val = GetMappingForChar(bags[0][i]);
            std::cout << "FOUND 3 COMMON CHAR:" << bags[0][i] << " "
                      << bags[1][j] << " " << bags[2][k] << " with VAL:" << val
                      << std::endl;
            return val;
          }
        }
      }
    }
  }
  return 0;
}

int GetPartTwoPriorities() {
  int sum = 0;
  // std::ifstream file("rucksacktestdata.txt");
  std::ifstream file("rucksackdata.txt");
  std::vector<std::string> group;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      group.push_back(line);
      if (group.size() == 3) {
        sum += FindCharacterFromGroup(group);
        group.clear();
      }
    }
  }
  return sum;
}

int main() {
  // int sum = GetPartOnePriorities();
  int sum = GetPartTwoPriorities();
  std::cout << "Sum of priorities is:" << sum << std::endl;
}
