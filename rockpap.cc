#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//       A Rock X == 0
//      /              \
//  B Paper Y == 1      C Scissors Z == 2
//
//  A B C    0 1 2
//  Y Z X    1 2 0
//  players gets point for shape - 1 for Rock, 2 for Paper, 3 for Scissors
//  and score for outcome - 0 if lost, 3 if draw and 6 to winner

constexpr int kTips{3};
constexpr int kShift{1};

bool RightWins(int left, int right) {
  if ((left + kShift) % kTips == right) return true;
  return false;
}
bool Draw(int left, int right) {
  if (left == right) return true;
  return false;
}

int PointForShape(int shape_enum) {
  if (shape_enum < 0 || shape_enum > 2) return -1;
  return shape_enum + 1;
}

std::vector<std::string> kNames{"ROCK", "PAPER", "SCISSORS", "UNKNOWN"};
std::string& NameFromType(int type) {
  if (type < kNames.size()) {
    return kNames[type];
  }
  return kNames[kNames.size() - 1];
}

void CalcComp(const std::vector<std::pair<int, int>>& list) {
  std::vector<std::pair<int, int>> player_scores;
  for (const auto [left, right] : list) {
    int left_score = PointForShape(left);
    int right_score = PointForShape(right);

    std::cout << "LEFT plays " << NameFromType(left) << " and RIGHT "
              << NameFromType(right) << std::endl;

    if (RightWins(left, right)) {
      right_score += 6;
    } else if (Draw(left, right)) {
      left_score += 3;
      right_score += 3;
    } else {
      left_score += 6;
    }

    player_scores.push_back(std::make_pair(left_score, right_score));
  }

  int total_right_score{0};
  for (const auto [left, right] : player_scores) {
    std::cout << "SCORES: Left:" << left << " Right:" << right << std::endl;
    total_right_score += right;
  }
  std::cout << "TOTAL RIGHT SCORE:" << total_right_score << std::endl;
}
int SelectCorrectInstrument(int instr, int strategy) {
  if (strategy == 2)  // WIN
    return (instr + 1) % 3;
  else if (strategy == 1)  // DRAW
    return instr;
  int winner = instr - 1;
  if (winner == -1) winner = 2;
  return winner;
}
int main() {
  std::vector<std::pair<int, int>> num_list;
  // for (int i = 0; i < kTips; i++) {
  //   num_list.push_back(std::make_pair(i, (i + kShift) % kTips));
  // }
  //  num_list.push_back(std::make_pair(0, 1));
  //  num_list.push_back(std::make_pair(1, 0));
  //  num_list.push_back(std::make_pair(2, 2));
  // num_list.push_back(std::make_pair(0, SelectCorrectInstrument(0, 1)));
  // num_list.push_back(std::make_pair(1, SelectCorrectInstrument(1, 0)));
  // num_list.push_back(std::make_pair(2, SelectCorrectInstrument(2, 2)));

  std::ifstream file("paperinput.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream sstr(line);
      std::vector<int> noms;
      int n;
      while (sstr >> n) noms.push_back(n);
      if (noms.size() == 2) {
        int shape = noms[0];
        int strategy = noms[1];
        num_list.push_back(
            std::make_pair(shape, SelectCorrectInstrument(shape, strategy)));
      }
    }
    file.close();
  }
  CalcComp(num_list);
}
