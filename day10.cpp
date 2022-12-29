#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

enum class Instruction { Noop, AddX };

struct Command {
  Instruction instruction;
  int value;
};

std::queue<Command> g_command_queue;

void ImportInstructions() {
  std::ifstream file{"day10testinput.txt"};
  // std::ifstream file{"day10input.txt"};
  if (file.is_open()) {
    std::string line;
    std::string instr;
    while (std::getline(file, line)) {
      std::istringstream ss{line};
      Command command{};
      ss >> instr;
      if (instr == "noop") {
        command.instruction = Instruction::Noop;
      } else {
        command.instruction = Instruction::AddX;
        ss >> command.value;
      }
      g_command_queue.push(command);
      // std::cout << "COMMAND:" << instr << " : " << command.value <<
      // std::endl;
    }
  }
}

void PrintVec(const std::vector<char>& curr_line) {
  for (const auto& c : curr_line) std::cout << c;
  std::cout << std::endl;
}

void StateMachineRunner() {
  int pixel_scan_position{0};
  int current_cycle{1};
  int registerX{1};

  int instruction_timer{0};

  int sum_interesting_signals{0};

  std::array<int, 6> interesting_cycles{20, 60, 100, 140, 180, 220};
  std::vector<char> current_output_line{};

  while (!g_command_queue.empty()) {
    std::cout << "Cycle<:" << current_cycle << " RegisterX:" << registerX
              << std::endl;

    // PART ONE
    // if (std::find(std::begin(interesting_cycles),
    // std::end(interesting_cycles),
    //              current_cycle) != std::end(interesting_cycles)) {
    //  int signal_strength = current_cycle * registerX;
    //  sum_interesting_signals += signal_strength;
    //  std::cout << "INTERESTING CYCLE!:" << current_cycle
    //            << " RegisterX:" << registerX
    //            << " SStrength:" << signal_strength << std::endl;
    //}

    // PART TWO
    std::cout << "SPRITE POSITION:" << registerX
              << " PIXEL POSITION:" << pixel_scan_position << std::endl;
    if (pixel_scan_position >= registerX - 1 &&
        pixel_scan_position <= registerX + 1) {
      current_output_line.push_back('#');
    } else {
      current_output_line.push_back('.');
    }

    pixel_scan_position++;
    if (pixel_scan_position == 40) {
      PrintVec(current_output_line);
      pixel_scan_position = 0;
      current_output_line.clear();
    }

    if (instruction_timer > 0) {
      instruction_timer--;
      if (instruction_timer == 0) {
        registerX += g_command_queue.front().value;
        g_command_queue.pop();
      }
    } else {
      if (g_command_queue.front().instruction == Instruction::Noop) {
        std::cout << "NOOP\n";
        g_command_queue.pop();
      } else if (g_command_queue.front().instruction == Instruction::AddX) {
        std::cout << "ADDX\n";
        instruction_timer = 1;
      }
    }
    current_cycle++;
  }
}

int main() {
  ImportInstructions();
  StateMachineRunner();
}
