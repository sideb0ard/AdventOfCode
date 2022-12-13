#include <fstream>
#include <iostream>
#include <memory>
#include <string>

constexpr int kMaxDepth = 3;

struct Node {
  Node(int idx, int count) : elf_idx{idx}, calorie_count{count} {}
  int elf_idx{0};
  int calorie_count{0};

  Node* left_child{nullptr};
  Node* right_child{nullptr};
};

void Insert(Node*& root, Node* new_node) {
  if (!root) {
    root = new_node;
  } else {
    if (new_node->calorie_count < root->calorie_count) {
      Insert(root->left_child, new_node);
    } else {
      Insert(root->right_child, new_node);
    }
  }
}

void PrintCalories(Node* node) {
  if (!node) return;

  PrintCalories(node->left_child);
  std::cout << "ELF:" << node->elf_idx << " Calories:" << node->calorie_count
            << std::endl;
  PrintCalories(node->right_child);
}

void CountCalories() {
  // std::ifstream file("elftestcals.txt");
  std::ifstream file("elfcals.txt");
  if (file.is_open()) {
    int calorie_count = 0;
    int elf_idx = 0;
    Node* root{nullptr};

    std::string line;
    while (std::getline(file, line)) {
      if (line.length() == 0) {
        std::cout << "YO CREATING A NODE WITH :" << calorie_count << " CALS!"
                  << std::endl;
        Node* new_node = new Node(elf_idx, calorie_count);
        std::cout << "LETS INSERT!\n";
        Insert(root, new_node);
        elf_idx++;
        calorie_count = 0;
      } else {
        std::cout << "LINE:" << line << std::endl;
        std::size_t pos{};
        calorie_count += std::stoi(line, &pos);
      }
    }
    file.close();
    if (calorie_count > 0) {
      // last node
      Node* new_node = new Node(elf_idx, calorie_count);
      Insert(root, new_node);
    }

    PrintCalories(root);
  }
}

int main() { CountCalories(); }
