#include <future>
  #include <iostream>
  #include <thread>

  int main(int argc, char* argv[]) {
      int count = 10;

    auto future2 = std::async(std::launch::async, [&count] {
        for(int i=0; i<count; ++i) {
            std::cout << 2;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    return 0
}