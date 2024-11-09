#include <iostream>
#include "../Common/Benchmark.h"
#include "../Common/Utils.h"

#include <ctime>

using namespace SimpleRayBench;

int main()
{
	const int size = 1024 * 8;// image size
	Benchmark::Init(size, size);

	unsigned int start = clock();
	auto movie = Benchmark::Render(false);
	double sec = ((clock() - start) / (double)CLOCKS_PER_SEC);
	std::cout << "Render Time: " << sec << "s" << std::endl;

	// NOTE: enable this to save raw RGB image data
	/*int imageDataLength;
	auto imageData = Utils::ConvertRawImageSDR(movie->frames[0], &imageDataLength);
	Utils::SaveImageData("image.rgb", imageData, imageDataLength);*/

	Benchmark::Dispose();
}