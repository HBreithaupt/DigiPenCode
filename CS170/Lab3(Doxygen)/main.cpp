#include <iostream> // cout
#include <cstdlib>  // atoi

void fibonacci(int max);

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << "You must specify the"
              << " fibonacci numbers to generate.\n";
    return 1;
  }

  int size = std::atoi(argv[1]);
  fibonacci(size);

  return 0;
}
