#include "svpng.inc"
#include <algorithm>
#include <cmath>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <sys/stat.h> // struct stat
using namespace std;
#define COLOR 255

void Hide(char in[], char out[] = (char*)"隐藏.png")
{
	struct stat statbuf;
	stat(in, &statbuf);

	unsigned int PHOTOSIZE = sqrt(statbuf.st_size / 3) + 1;

	unsigned char rgb[PHOTOSIZE * PHOTOSIZE * 3], *p = rgb;
	char ch;
	FILE* code = fopen(in, "rt");
	FILE* fp = fopen(out, "wb");
	if (code == NULL)
	{
		printf("路径错误/文件打不开！\n");
		return;
	}
	for (unsigned int y = 0; y < PHOTOSIZE; ++y)
	{
		for (unsigned int x = 0; x < PHOTOSIZE; ++x)
		{
			for (int i = 0; i < 3; ++i)
			{
				if ((ch = fgetc(code)) != -1)
				{
					*p++ = (unsigned char)ch;
				}
				else
				{
					fill(p, rgb + PHOTOSIZE * PHOTOSIZE * 3, COLOR);
					goto gotoSHIT;
				}
			}
		}
	}
gotoSHIT:
	svpng(fp, PHOTOSIZE, PHOTOSIZE, rgb, 0);
	fclose(code);
	fclose(fp);
}
void Unhide(char in[], char out[] = (char*)"读取.txt")
{
	FILE* fp = fopen(out, "wb");
	if (fp == NULL)
	{
		printf("路径错误/文件打不开！\n");
		return;
	}
	int width, heigh, n;
	unsigned char* data = stbi_load(in, &width, &heigh, &n, 0);
	unsigned char* pixelOffset, *pl;
	pl = data + (heigh * width - width - 1) * n;
	for (int y = 0; y < heigh; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			pixelOffset = data + (x + y * width) * n;
			if (pixelOffset[0] == pixelOffset[1] &&
			        pixelOffset[1] == pixelOffset[2] &&
			        pixelOffset[0] == pl[2])
				return;
			fprintf(fp, "%c", pixelOffset[0]);
			fprintf(fp, "%c", pixelOffset[1]);
			fprintf(fp, "%c", pixelOffset[2]);
		}
	}
	fclose(fp);
}
int main()
{
	char path[256] = "隐藏.png";
	Unhide(path);
	return 0;
}
