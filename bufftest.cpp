#include <array>
#include <iostream>

int main() {
  std::array<char, 4> buffer;

  std::cout << "buffer size:" << buffer.size() << std::endl;

  buffer[0] = 'C';
  std::cout << "NOWbuffer size:" << buffer.size() << std::endl;
}
