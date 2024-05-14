#include <chrono>
#include <iostream>
#include <thread>

volatile char global_volatile_reader;

int main() {
  long long kill_memory;
  std::cout << "enter memory top kill in gb: \n";
  std::cin >> kill_memory;
  char *killer;
  if (kill_memory > 0) {
    killer = new char[kill_memory * 1024 * 1024 * 1024];
  } else {
    std::cout << "entered incorrect data";
    return 0;
  }

  char work_mode;
  std::cout << "enter work mode: \n";

  std::cin >> work_mode;

  int step;
  std::cout << "enter step in pages:\n";
  std::cin >> step;
  if (work_mode == 'w' && step > 0) {
    for (int i = 0; i < (kill_memory * 1024 * 1024 / 4); i++) {
      killer[i * 4096 + 1] = 'g';
      if (i != 0 && i % step == 0) {
        std::cout << i << "/" << kill_memory * 1024 * 1024 / 4 << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
    }
  } else if (work_mode == 'r' && step > 0) {
    for (int i = 0; i < (kill_memory * 1024 * 1024 / 4); i++) {
      global_volatile_reader = killer[i * 4096 + 1];
      if (i != 0 && i % step == 0) {
        std::cout << i << "/" << kill_memory * 1024 * 1024 / 4 << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
    }
  } else {
    std::cout << "entered incorrect data\n";
  }
  return 0;
}