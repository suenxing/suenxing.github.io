#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int divMod(char* ch, int num)
{
	int s = 0;
	for (int i = 0; ch[i] != '\0'; i++)
		s = (s * 10 + ch[i] - '0') % num;
	return s;
}
int main()
{
	for (size_t i = 1; i < 100; ++i)
	{
		printf("%d => %llu \n", i, );
	}
}
