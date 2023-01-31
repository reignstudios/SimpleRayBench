#pragma once
#include "Benchmark.h"
#include <fstream>

namespace SimpleRayBench
{
	class Utils
	{
	public:
		static char* ConvertRawImageSDR(RawImage* image, int* imageDataLength)
		{
			*imageDataLength = image->width * image->height * 3;
			auto data = new char[*imageDataLength];
			int i = 0;
			//for (int y = 0; y != image.height; ++y)
			for (int y = image->height - 1; y != -1; --y)// invert Y
			{
				for (int x = 0; x != image->width; ++x)
				{
					auto color = image->colors[x + (y * image->width)] * 255;
					data[i] = (char)Math::Clamp(color.r, 0, 255);
					data[i + 1] = (char)Math::Clamp(color.g, 0, 255);
					data[i + 2] = (char)Math::Clamp(color.b, 0, 255);
					i += 3;
				}
			}
			return data;
		}

		static void SaveImageData(const wchar_t* filename, char* imageData, int imageDataLength)
		{
			std::ofstream fout;
			fout.open(filename, std::ios::binary | std::ios::out);
			fout.write(imageData, imageDataLength);
			fout.flush();
			fout.close();
		}
	};
}