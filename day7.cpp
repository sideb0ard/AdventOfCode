#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int kTotalSizeDisk = 70000000;
constexpr int kSpaceNeededForUpdate = 30000000;

struct File {
  File(std::string name, int size) : name{name}, size{size} {}
  std::string name;
  int size;
};

struct Dir {
  Dir(std::string name, Dir* parent) : name{name}, parent{parent} {}

  std::string name;
  Dir* parent{nullptr};

  std::vector<File> files;
  std::vector<Dir> dirs;

  int CalculateSize();
  int CollectSizes(std::vector<int>& dir_sizes, int max_size);
  void AddFile(File file);
  void AddDir(Dir dir);
};

int Dir::CalculateSize() {
  int total_size = 0;
  for (auto& f : files) {
    total_size += f.size;
  }
  for (auto& d : dirs) {
    total_size += d.CalculateSize();
  }
  std::cout << "DIR:" << name << " SIZE:" << total_size << std::endl;
  return total_size;
}

int Dir::CollectSizes(std::vector<int>& dir_sizes, int max_size) {
  int total_size = 0;
  for (auto& f : files) {
    total_size += f.size;
  }
  for (auto& d : dirs) {
    total_size += d.CollectSizes(dir_sizes, max_size);
  }

  std::cout << "DIR:" << name << " SIZE:" << total_size << std::endl;
  if (total_size > max_size) {
    std::cout << "TOT SZ:" << total_size << " IS lESS! ADDING TO DIR SOZES\n";
    dir_sizes.push_back(total_size);
  } else {
    std::cout << total_size << " is not < 100000!" << std::endl;
  }

  return total_size;
}

void Dir::AddFile(File file) { files.push_back(file); };
void Dir::AddDir(Dir dir) { dirs.push_back(dir); };

Dir root{"/", nullptr};

Dir* ChangeDir(Dir* cwd, std::string dir_name) {
  if (dir_name == root.name) {
    return &root;
  }
  if (dir_name == "..") {
    return cwd->parent;
  }
  for (auto& d : cwd->dirs) {
    if (dir_name == d.name) {
      return &d;
    }
  }
  return nullptr;
}

std::vector<std::string> GetTokens(std::string line) {
  std::vector<std::string> tokens;
  std::string delim = " ";
  size_t pos = 0;
  while ((pos = line.find(delim)) != std::string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delim.length());
  }
  tokens.push_back(line);

  return tokens;
}

void ReadCommands() {
  Dir* pwd = &root;
  // std::ifstream file{"day7testinput.txt"};
  std::ifstream file{"day7realinput.txt"};
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // std::cout << "LINE:" << line << std::endl;
      auto tokens = GetTokens(line);
      if (tokens.size() > 1) {
        if (tokens[0] == "$") {
          if (tokens[1] == "cd") {
            if (tokens.size() == 3) {
              // std::cout << "CD TO DIR NAME:" << tokens[2] << std::endl;
              Dir* newdir = ChangeDir(pwd, tokens[2]);
              if (newdir) {
                // std::cout << "CHANGE DIR SUCCEEDED!\n";
                pwd = newdir;
              } else {
                // std::cout << "CHANGE DIR FAAAAAIl!\n";
              }
            }
          } else if (tokens[1] == "ls") {
            // std::cout << "ls COMMAND!\n";
          }
        } else if (tokens[0] == "dir") {
          // std::cout << "DIR!: " << tokens[1] << "\n";
          pwd->AddDir({tokens[1], pwd});
        } else {
          // std::cout << "FILE!: " << tokens[1] << "\n";
          pwd->AddFile({tokens[1], std::stoi(tokens[0])});
        }
      }
    }
  }
}

void PrintDirSizes() {
  int used_total = root.CalculateSize();
  int free_space = kTotalSizeDisk - used_total;
  int need_to_find = kSpaceNeededForUpdate - free_space;
  std::cout << "Used Total:" << used_total << " Free Space:" << free_space
            << " Need to find:" << need_to_find << std::endl;
  std::vector<int> dir_sizes;
  root.CollectSizes(dir_sizes, need_to_find);
  std::cout << "YO, COLLECTED:";
  int total = 0;
  for (const auto& n : dir_sizes) {
    std::cout << n << " ";
    total += n;
  }
  std::cout << std::endl;

  std::vector<int>::iterator result =
      std::min_element(dir_sizes.begin(), dir_sizes.end());
  int dist = std::distance(dir_sizes.begin(), result);
  std::cout << "\nSMALLEST is:" << dir_sizes[dist] << std::endl;
}

int main() {
  ReadCommands();
  PrintDirSizes();
}
