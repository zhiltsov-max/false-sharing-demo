#include <omp.h>
#include <cstdio>
#include <thread>
#include <cstddef>

void calc(int& var, const size_t iterations) {
  for (size_t i = 0; i < iterations; ++i) {
    var += i % 100;
  }
}

void test_shared(const size_t iterations) {
  int value0 = 0;
  int value1 = 0;

  std::thread t1(calc, std::ref(value0), iterations);
  std::thread t2(calc, std::ref(value1), iterations);

  t1.join();
  t2.join();

  printf("Values: %d, %d\n", value0, value1);
}

void test_not_shared(const size_t iterations) {
  alignas(64) int value0 = 0;
  alignas(64) int value1 = 0;

  std::thread t1(calc, std::ref(value0), iterations);
  std::thread t2(calc, std::ref(value1), iterations);

  t1.join();
  t2.join();

  printf("Values: %d, %d\n", value0, value1);
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("\n"
           "Usage: test <share> <iterations>\n"
           "    share - share variables or not. 0 or 1\n"
           "    iterations - positive number\n"
           "\n");
    exit(0);
  }

  const bool share = (std::atoi(argv[1]) == 1) ? true : false;
  const size_t iterations = std::atol(argv[2]);

  const double time_start = omp_get_wtime();

  if (share) {
    test_shared(iterations);
  } else {
    test_not_shared(iterations);
  }

  const double time_end = omp_get_wtime();

  printf("Time: %.4fs\n", (time_end - time_start));


  return 0;
}
