#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

constexpr int num_stacks = 9;
std::array<std::stack<char>, num_stacks> stacks;

void SetupTestInput() {
  stacks[0].push('Z');
  stacks[0].push('N');
  stacks[1].push('M');
  stacks[1].push('C');
  stacks[1].push('D');
  stacks[2].push('P');
}

void SetupInput() {
  std::vector<char> stack1 = {'B', 'Z', 'T'};
  std::vector<char> stack2 = {'V', 'H', 'T', 'D', 'N'};
  std::vector<char> stack3 = {'B', 'F', 'M', 'D'};
  std::vector<char> stack4 = {'T', 'J', 'G', 'W', 'V', 'Q', 'L'};
  std::vector<char> stack5 = {'W', 'D', 'G', 'P', 'V', 'F', 'Q', 'M'};
  std::vector<char> stack6 = {'V', 'Z', 'Q', 'G', 'H', 'F', 'S'};
  std::vector<char> stack7 = {'Z', 'S', 'N', 'R', 'L', 'T', 'C', 'W'};
  std::vector<char> stack8 = {'Z', 'H', 'W', 'D', 'J', 'N', 'R', 'M'};
  std::vector<char> stack9 = {'M', 'Q', 'L', 'F', 'D', 'S'};
  std::vector<std::vector<char>> cstacks{stack1, stack2, stack3, stack4, stack5,
                                         stack6, stack7, stack8, stack9};

  int stack_no = 0;
  for (const auto& stack : cstacks) {
    for (int i = 0; i < stack.size(); i++) {
      stacks[stack_no].push(stack[i]);
    }
    stack_no++;
  }
}

void ReadStackOutput() {
  for (int i = 0; i < num_stacks; i++) {
    std::cout << stacks[i].top();
  }
  std::cout << std::endl;
}

int main() {
  // SetupTestInput();
  // std::ifstream file{"day5testinput.txt"};

  SetupInput();
  std::ifstream file{"day5input.txt"};
  if (file.is_open()) {
    std::string line;
    int num_to_move = 0;
    int stack_num_from = 0;
    int stack_num_to = 0;
    std::stack<char> temp_stack;
    while (std::getline(file, line)) {
      std::cout << "GOT LINE:" << line << std::endl;
      std::stringstream sstr;
      sstr << line;
      sstr >> num_to_move;
      sstr >> stack_num_from;
      sstr >> stack_num_to;
      std::cout << "NUM2MOVE:" << num_to_move << " FROM:" << stack_num_from
                << " TO:" << stack_num_to << std::endl;
      for (int i = 0; i < num_to_move; i++) {
        temp_stack.push(stacks[stack_num_from - 1].top());
        stacks[stack_num_from - 1].pop();
      }
      for (int i = 0; i < num_to_move; i++) {
        stacks[stack_num_to - 1].push(temp_stack.top());
        temp_stack.pop();
      }
    }
    ReadStackOutput();
  }
}
