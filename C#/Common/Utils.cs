using System;
using System.IO;

namespace SimpleRayBench
{
	public static class Utils
	{
		public static byte[] ConvertRawImageSDR(RawImage image)
		{
			var data = new byte[image.width * image.height * 3];
			int i = 0;
			//for (int y = 0; y != image.height; ++y)
			for (int y = image.height - 1; y != -1; --y)// invert Y
			{
				for (int x = 0; x != image.width; ++x)
				{
					var color = image.colors[x, y] * 255;
					data[i] = (byte)Math.Clamp(color.r, 0, 255);
					data[i + 1] = (byte)Math.Clamp(color.g, 0, 255);
					data[i + 2] = (byte)Math.Clamp(color.b, 0, 255);
					i += 3;
				}
			}
			return data;
		}

		public static void SaveImageData(string filename, byte[] imageData)
		{
			using (var stream = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.Read))
			{
				stream.Write(imageData, 0, imageData.Length);
				stream.Flush();
			}
		}

		public static void SeedRandomValues(int[] values)
		{
			var random = new Random();
			for (int i = 0; i != values.Length; ++i)
			{
				values[i] = random.Next();
			}
		}

		public static void PrintRandomValues(int count)
		{
			var random = new Random();
			for (int i = 0; i != count; ++i)
			{
				Console.Write(random.NextSingle().ToString() + ",");
				if (i % 10 == 9) Console.WriteLine();
			}
		}
	}
}