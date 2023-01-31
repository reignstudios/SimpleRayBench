using System;
using System.Diagnostics;

namespace SimpleRayBench
{
	internal class Program
	{
		static void Main(string[] args)
		{
			//Utils.PrintRandomValues(200); return;

			const int size = 512;//1024 * 8;
			Benchmark.Init(size, size);

			var watch = new Stopwatch();
			watch.Start();
			var movie = Benchmark.Render(false);
			watch.Stop();
			Console.WriteLine($"Render Time: {Math.Round(watch.Elapsed.TotalSeconds, 2)}s");

			var imageData = Utils.ConvertRawImageSDR(movie.frames[0]);
			Utils.SaveImageData("image.rgb", imageData);
			Benchmark.Dispose();
		}
	}
}