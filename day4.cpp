#include <fstream>
#include <iostream>
#include <string>

struct ranger {
  int starting_pos{0};
  int ending_pos{0};
  int length{0};
};

ranger ExtractRangeFromString(std::string strange) {
  std::size_t dash_pos = strange.find('-');
  std::string start_no = strange.substr(0, dash_pos);
  std::string end_no = strange.substr(dash_pos + 1, strange.size());
  int start_num = std::stoi(start_no);
  int end_num = std::stoi(end_no);

  return ranger{start_num, end_num, end_num - start_num};
}

bool RangeOverlaps(const std::string& rone, const std::string& rtwo) {
  auto r1 = ExtractRangeFromString(rone);
  auto r2 = ExtractRangeFromString(rtwo);

  if (r1.starting_pos >= r2.starting_pos && r1.starting_pos <= r2.ending_pos) {
    // if (r1.ending_pos <= r2.ending_pos) {
    std::cout << "RANGE OVERLAPS! " << r1.starting_pos << " " << r1.ending_pos
              << " " << r2.starting_pos << " " << r2.ending_pos << std::endl;
    return true;
    //}
  }

  if (r2.starting_pos >= r1.starting_pos && r2.starting_pos <= r1.ending_pos) {
    // if (r2.ending_pos <= r1.ending_pos) {
    std::cout << "RANGE OVERLAPS! " << r1.starting_pos << " " << r1.ending_pos
              << " " << r2.starting_pos << " " << r2.ending_pos << std::endl;
    return true;
    //}
  }

  return false;
}

void CampCleanup() {
  // std::ifstream file{"camptestdata.txt"};
  std::ifstream file{"campdata.txt"};
  if (file.is_open()) {
    int overlap_count = 0;

    std::string line;
    while (std::getline(file, line)) {
      std::size_t pos = line.find(',');
      std::string first_range = line.substr(0, pos);
      std::string sec_range = line.substr(pos + 1, line.size());
      std::cout << "FIRST:" << first_range << " SEC:" << sec_range << std::endl;

      if (RangeOverlaps(first_range, sec_range)) {
        overlap_count++;
      }
    }

    std::cout << "Overlapping ranges:" << overlap_count << std::endl;
  }
}

int main() { CampCleanup(); }
