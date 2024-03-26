#include <stdio.h>
#include <random>
using namespace std;
int main()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(0, 100);
  for (unsigned int i = 0; i < 1000; i++)
  {
    printf("%d ", distrib(gen));
  }
  scanf("%d");
  return 0;
}