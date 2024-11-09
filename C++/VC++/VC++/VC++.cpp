#include <iostream>

#define WINDOWS
#include "../../Common/Benchmark.h"
#include "../../Common/Utils.h"

#include <ctime>
#include <chrono>

using namespace SimpleRayBench;

int main()
{
	const int size = 1024 * 2;// image size
	Benchmark::Init(size, size);

	auto start = std::chrono::high_resolution_clock::now();
	auto movie = Benchmark::Render(false);// run benchmark
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> sec = end - start;
	std::cout << "Render Time: " << sec.count() << "s" << std::endl;

	// NOTE: enable this to save raw RGB image data
	/*int imageDataLength;
	auto imageData = Utils::ConvertRawImageSDR(movie->frames[0], &imageDataLength);
	Utils::SaveImageData("image.rgb", imageData, imageDataLength);*/

	Benchmark::Dispose();
}