#include <iostream>
#include "../../Common/Benchmark.h"
#include "../../Common/Utils.h"

#include <ctime>

using namespace SimpleRayBench;

int main()
{
	const int size = 512;//1024 * 8;
	Benchmark::Init(size, size);

	unsigned int start = clock();
	auto movie = Benchmark::Render(false);
	double sec = ((clock() - start) / (double)CLOCKS_PER_SEC);
	std::cout << "Render Time: " << sec << "s" << std::endl;

	int imageDataLength;
	auto imageData = Utils::ConvertRawImageSDR(movie->frames[0], &imageDataLength);
	Utils::SaveImageData(L"image.rgb", imageData, imageDataLength);
	Benchmark::Dispose();
}