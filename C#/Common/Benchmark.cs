#define NUM64
//#define FOG_BASIC

using System;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Runtime.InteropServices;

#if NUM32
using Num = System.Single;
using MATH = System.MathF;
#elif NUM64
using Num = System.Double;
using MATH = System.Math;
#endif

namespace SimpleRayBench
{
	static class RandomUtil
	{
		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Num NextValue(Num u, Num v)
		{
			const Num randoValueX = 12.9898f;
			const Num randoValueY = 78.233f;
			const Num randoValueZ = 43758.543123f;

			Num result = (u * randoValueX) + (v * randoValueY);
			result = MATH.Sin(result) * randoValueZ;
			return result - MATH.Floor(result);
		}
	}

	public struct Color
	{
		public Num r, g, b;

		public Color(Num r, Num g, Num b)
		{
			this.r = r;
			this.g = g;
			this.b = b;
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color operator+(in Color p1, in Color p2)
		{
			return new Color(p1.r + p2.r, p1.g + p2.g, p1.b + p2.b);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color operator-(in Color p1, in Color p2)
		{
			return new Color(p1.r - p2.r, p1.g - p2.g, p1.b - p2.b);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color operator*(in Color p1, in Color p2)
		{
			return new Color(p1.r * p2.r, p1.g * p2.g, p1.b * p2.b);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color operator*(in Color p1, Num p2)
		{
			return new Color(p1.r * p2, p1.g * p2, p1.b * p2);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color operator/(in Color p1, Num p2)
		{
			return new Color(p1.r / p2, p1.g / p2, p1.b / p2);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color Lerp(Color p1, Color p2, Num t)
		{
			return p1 + ((p2 - p1) * t);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Color LerpClamp(Color p1, Color p2, Num t)
		{
			return p1 + ((p2 - p1) * MATH.Clamp(t, 0, 1));
		}
	}

	struct Vec3
	{
		public Num x, y, z;

		public Vec3(Num x, Num y, Num z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator +(in Vec3 p1, in Vec3 p2)
		{
			return new Vec3(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator -(in Vec3 p1, in Vec3 p2)
		{
			return new Vec3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator-(in Vec3 p1, Num p2)
		{
			return new Vec3(p1.x - p2, p1.y - p2, p1.z - p2);
		}
		
		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator-(in Vec3 p1)
		{
			return new Vec3(-p1.x, -p1.y, -p1.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator*(in Vec3 p1, in Vec3 p2)
		{
			return new Vec3(p1.x * p2.x, p1.y * p2.y, p1.z * p2.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator*(in Vec3 p1, Num p2)
		{
			return new Vec3(p1.x * p2, p1.y * p2, p1.z * p2);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator*(Num p1, in Vec3 p2)
		{
			return new Vec3(p1 * p2.x, p1 * p2.y, p1 * p2.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator/(in Vec3 p1, in Vec3 p2)
		{
			return new Vec3(p1.x / p2.x, p1.y / p2.y, p1.z / p2.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Vec3 operator/(in Vec3 p1, Num p2)
		{
			return new Vec3(p1.x / p2, p1.y / p2, p1.z / p2);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public Num Dot()
		{
			return (x*x) + (y*y) + (z*z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public Num Dot(in Vec3 vec)
		{
			return (x*vec.x) + (y*vec.y) + (z*vec.z);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public Num Length()
		{
			return MATH.Sqrt((x*x) + (y*y) + (z*z));
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public Vec3 Normalize()
		{
			return this / MATH.Sqrt((x*x) + (y*y) + (z*z));
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public Vec3 Reflect(Vec3 planeNormal)
		{
			return this - (planeNormal * this.Dot(planeNormal) * 2);
		}

		[MethodImpl(MethodImplOptions.AggressiveInlining)]
		public static Num FresnelSchlickZero(Vec3 rayDirection, Vec3 normal)
		{
			return MATH.Pow(1 - MATH.Max((-rayDirection).Dot(normal), 0), 5);
		}
	}

	struct Ray
	{
		public Vec3 origin, direction;

		public Ray(Vec3 origin, Vec3 direction)
		{
			this.origin = origin;
			this.direction = direction;
		}
	}

	struct HitInfo
	{
		public Vec3 point, normal;
	}

	abstract class Obj
	{
		public Color color;
		public Num roughness;
		public Num reflectiveness, metalic;

		public Obj(Color color, Num roughness, Num reflectiveness, Num metalic)
		{
			this.color = color;
			this.roughness = roughness;
			this.reflectiveness = reflectiveness;
			this.metalic = metalic;
		}

		public abstract bool Hit(in Ray ray, out HitInfo info);
	}

	sealed class Sphere : Obj
	{
		public Vec3 center;
		public float radius;

		public Sphere(Vec3 center, float radius, Color color, Num roughness, Num reflectiveness, Num metalic)
		: base(color, roughness, reflectiveness, metalic)
		{
			this.center = center;
			this.radius = radius;
		}

		public override bool Hit(in Ray ray, out HitInfo info)
		{
			// if ray pointing wrong direction ignore
			if (ray.direction.Dot(ray.origin - center) >= 0)
			{
				info = new HitInfo();
				return false;
			}

			// compute
			Vec3 d = ray.origin - center;
			Num a = ray.direction.Dot(ray.direction);
			Num b = d.Dot(ray.direction);
			Num c = d.Dot() - radius * radius;

			// if ray not pointing at object ignore
			Num disc = b * b - a * c;
			if (disc < 0)
			{
				info = new HitInfo();
				return false;
			}

			// compute
			Num sqrtDisc = MATH.Sqrt(disc);
			Num invA = 1 / a;
			Num t1 = (-b - sqrtDisc) * invA;
			//Num t2 = (-b + sqrtDisc) * invA;
			
			info.point = ray.origin + t1 * ray.direction;
			//info.point = ray.origin + t2 * ray.direction;
			info.normal = (info.point - center).Normalize();

			return true;
		}
	}

	sealed class Plane : Obj
	{
		public Vec3 center, normal;

		public Plane(Vec3 center, Vec3 normal, Color color, Num roughness, Num reflectiveness, Num metalic)
		: base(color, roughness, reflectiveness, metalic)
		{
			this.center = center;
			this.normal = normal.Normalize();
		}

		public override bool Hit(in Ray ray, out HitInfo info)
		{
			// if ray pointing wrong direction ignore
			if (ray.direction.Dot(normal) >= 0)
			{
				info = new HitInfo();
				return false;
			}

			Num denom = normal.Dot(ray.direction);
			if (MATH.Abs(denom) > 0.0001f)
			{
				Num t = (center - ray.origin).Dot(normal) / denom;
				if (t >= 0)
				{
					info.point = ray.origin + (ray.direction * t);
					info.normal = normal;
					return true;
				}
			}

			info = new HitInfo();
			return false;
		}
	}

	public class RawImage
	{
		public int width, height;
		public Color[,] colors;

		public RawImage(int width, int height)
		{
			this.width = width;
			this.height = height;
			colors = new Color[width, height];
		}
	}

	public class RawMovie
	{
		public int width, height;
		public RawImage[] frames;

		public RawMovie(int width, int height, int frameCount)
		{
			this.width = width;
			this.height = height;
			frames = new RawImage[frameCount];
			for (int i = 0; i != frames.Length; ++i)
			{
				frames[i] = new RawImage(width, height);
			}
		}
	}

	class Camera
	{
		public Vec3 position, forward, up;

		public Camera(Vec3 position, Vec3 forward, Vec3 up)
		{
			this.position = position;
			this.forward = forward.Normalize();
			this.up = up.Normalize();
		}
	}

	sealed class DirectionalLight
	{
		public Vec3 direction;
		public Color color;
		public Num softness;

		public DirectionalLight(Vec3 direction, Color color, Num softness)
		{
			this.direction = direction.Normalize();
			this.color = color;
			this.softness = softness;
		}
	}

	class RenderThreadData
	{
		public int index, randomIndex;
		public bool waiting, done;
		public int x, y, xEnd, yEnd;
		public RawImage image;
	}

	public static class Benchmark
	{
		const int diffusePasses = 1;// use to set multi-pass diffuse blending
		const int maxBounceCount = 10;// how many ray-bounces are allowed
		const Num roughnessMul = 1;// force tween material value
		const Num shadowSoftnessMul = 0;// force tween shadow value

		const int maxVolumeFogSteps = 500;// how far can we test the shadow volume for
		const Num volumeFogStep = .01f;// how little the shadow volume testing step is
		const Num fogDensity = .4f;// how dense the fog is
		const Num fogFalloff = 1;
		static Color fogColor = new Color(.25f, .25f, .25f);

		static int width, height, frames;
		static RawMovie movie;
		static Camera camera;
		static Obj[] objects;
		static Color ambientLight;
		static DirectionalLight[] directionalLights;

		static RenderThreadData[] threadDatas;
		static Thread[] threads;

		public static void Init(int width, int height)
		{
			// init movie
			Benchmark.width = width;
			Benchmark.height = height;
			frames = 1;
			movie = new RawMovie(width, height, frames);

			// init camera
			camera = new Camera(new Vec3(0, 0, 0), new Vec3(0, 0, -1), new Vec3(0, 1, 0));

			// init scene objects
			objects = new Obj[]
			{
				new Plane(new Vec3(0, -.4f, 0), new Vec3(0, 1, 0), new Color(.3f, .3f, .3f), 0.03f * roughnessMul, 1, 0),
				new Sphere(new Vec3(0, 0, -2), .33f, new Color(1, 0, 0), 0 * roughnessMul, .25f, 0),
				new Sphere(new Vec3(-.25f, .5f, -1.5f), .25f, new Color(0, 1, 0), 0 * roughnessMul, 1, 1),
				new Sphere(new Vec3(1, -.75f, -2), 1, new Color(0, 0, 1), 0 * roughnessMul, 1, 1),
				new Sphere(new Vec3(.2f, .25f, -1.5f), .1f, new Color(1, 1, 0), 0 * roughnessMul, 1, .5f)
			};

			// init scene lights
			ambientLight = new Color(.05f, .05f, .05f);
			directionalLights = new DirectionalLight[]
			{
				new	DirectionalLight(new Vec3(.25f, -1, -.25f), new Color(1, 1, 1), .025f * shadowSoftnessMul)
			};

			// start threads
			int threadCount = Environment.ProcessorCount;
			threadDatas = new RenderThreadData[threadCount];
			threads = new Thread[threadCount];
			for (int i = 0; i != threadCount; ++i)
			{
				threads[i] = new Thread(RenderThread);
				int sectionHeight = height / threadCount;
				threadDatas[i] = new RenderThreadData()
				{
					index = i,
					randomIndex = i % threadCount,
					waiting = true,
					done = false,
					x = 0,
					y = i * sectionHeight,
					xEnd = width,
					yEnd = (i * sectionHeight) + sectionHeight
				};
				if (i == threadCount - 1) threadDatas[i].yEnd = height;
				threads[i].Start(threadDatas[i]);
			}
		}

		public static void Dispose()
		{
			// tell threads to stop waiting
			foreach (var data in threadDatas)
			{
				data.done = true;
				data.waiting = false;
			}
		}

		public static RawMovie Render(bool singleThreaded)
		{
			if (singleThreaded)
			{
				// setup ray
				Ray ray;
				ray.origin = camera.position;

				// render frames
				Num widthRange = width - 1;
				Num heightRange = height - 1;
				for (int f = 0; f != frames; ++f)
				{
					Console.WriteLine($"Frame:{f} started rendering");
					var colors = movie.frames[f].colors;
					for (int y = 0; y != height; ++y)
					{
						for (int x = 0; x != width; ++x)
						{
							ray.direction = new Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();

							// generate shared random vector
							Num randomVal = RandomUtil.NextValue(x / widthRange, y / heightRange);
							var randomVec = new Vec3(randomVal, randomVal, randomVal) - .5f;

							// trace
							int maxBounce = maxBounceCount;
							var light = new Color();
							Trace(ray, ref light, ref maxBounce, randomVec);

							// write result
							colors[x, y] = light;
						}
					}
					Console.WriteLine($"Frame:{f} finished rendering");
				}
			}
			else
			{
				// render frames
				for (int f = 0; f != frames; ++f)
				{
					Console.WriteLine($"Frame:{f} started rendering");
					var frame = movie.frames[f];

					// tell threads to start processing task
					foreach (var data in threadDatas)
					{
						data.image = frame;
						data.waiting = false;
					}

					// wait for all threads to finish
					foreach (var data in threadDatas)
					{
						while (!data.done) Thread.Sleep(1);
					}

					Console.WriteLine($"Frame:{f} finished rendering");
				}
			}

			return movie;
		}

		private static void RenderThread(object dataObj)
		{
			var data = (RenderThreadData)dataObj;

			// wait for main thread to trigger
			while (data.waiting) Thread.Sleep(1);
			if (data.done) return;

			// setup ray
			Ray ray;
			ray.origin = camera.position;

			// render image section
			var colors = data.image.colors;
			Num widthRange = width - 1;
			Num heightRange = height - 1;
			for (int y = data.y; y < data.yEnd; ++y)
			{
				for (int x = data.x; x < data.xEnd; ++x)
				{
					ray.direction = new Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();

					// generate shared random vector
					Num randomVal = RandomUtil.NextValue(x / widthRange, y / heightRange);
					var randomVec = new Vec3(randomVal, randomVal, randomVal) - .5f;

					// trace
					int maxBounce = maxBounceCount;
					var light = new Color();
					Trace(ray, ref light, ref maxBounce, randomVec);

					// write result
					colors[x, y] = light;
				}
			}

			// tell main thread we're done
			data.done = true;
		}

		static bool Trace(Ray ray, ref Color light, ref int maxBounce, in Vec3 randomVec)
		{
			// find closes object
			Obj closestObject = null;
			Num closestDis = Num.MaxValue;
			var closestInfo = new HitInfo();
			for (int o = 0; o != objects.Length; ++o)
			{
				var obj = objects[o];
				if (obj.Hit(ray, out var info))
				{
					Num dis = (ray.origin - info.point).Length();
					if (dis < closestDis)
					{
						closestDis = dis;
						closestObject = obj;
						closestInfo = info;
					}
				}
			}

			// process lighting
			if (closestObject != null)
			{
				if (maxBounce <= 0) return false;
				maxBounce--;
				int maxBounceReset = maxBounce;

				// buffer diffuse pass state objects
				var reflectedClosestInfo = closestInfo;
				var reflectedRay = ray;

				// diffuse light
				var diffuseLight = new Color();
				var reflectedLight = new Color();
				for (int i = 0; i != diffusePasses; ++i)
				{
					// diffuse surface normal
					reflectedClosestInfo.normal = closestInfo.normal + (randomVec * closestObject.roughness);
					reflectedRay.direction = ray.direction.Reflect(reflectedClosestInfo.normal.Normalize());
					reflectedRay.origin = closestInfo.point - (reflectedRay.direction * .0001f);// move a little off surface to correct for floating point errors

					// gather surface light
					GatherLight(closestObject, reflectedClosestInfo, ref diffuseLight, randomVec);

					// trace from this reflected path
					maxBounce = maxBounceReset;// reset max bounce here or we lose light average consistancy
					Trace(reflectedRay, ref reflectedLight, ref maxBounce, randomVec);
				}

				// material (diffuse)
				light = diffuseLight / diffusePasses;

				// material (reflection)
				reflectedLight /= diffusePasses;
				Num fresnel = 1 - Vec3.FresnelSchlickZero(ray.direction, closestInfo.normal);
				light += Color.Lerp(reflectedLight, reflectedLight * closestObject.color, closestObject.metalic * fresnel) * closestObject.reflectiveness;

				// fog
				#if FOG_BASIC
				// basic fog just uses fog color directly
				light = Color.LerpClamp(light, fogColor, MATH.Pow(closestDis, fogFalloff) * fogDensity);
				#else
				// volume fog tracing taking into account shadows
				var fogPos = ray.origin;
				var fogStep = ray.direction * volumeFogStep;
				Num fogDis = 0;
				Num fogLitDis = 0;
				Num closestFogDis = closestDis;
				for (int i = 0; i != maxVolumeFogSteps; ++i)
				{
					fogPos += fogStep;
					fogDis += volumeFogStep;
					if (!IsInShadow(fogPos, randomVec)) fogLitDis += volumeFogStep;
					if (i == maxVolumeFogSteps - 1) closestFogDis = (maxVolumeFogSteps * volumeFogStep);
					if (fogDis > closestDis) break;
				}
				Color fogColorValue = fogColor * (fogLitDis / closestFogDis);
				light = Color.LerpClamp(light, fogColorValue, MATH.Pow(closestDis, fogFalloff) * fogDensity);
				#endif
				
				return true;
			}
			#if FOG_BASIC
			light += fogColor;
			#else
			else
			{
				// volume fog tracing taking into account shadows (optimized for when nothing is hit)
				var fogPos = ray.origin;
				var fogStep = ray.direction * volumeFogStep;
				Num fogLitDis = 0;
				for (int i = 0; i != maxVolumeFogSteps; ++i)
				{
					fogPos += fogStep;
					if (!IsInShadow(fogPos, randomVec)) fogLitDis += volumeFogStep;
				}
				Color fogColorValue = fogColor * (fogLitDis / (maxVolumeFogSteps * volumeFogStep));
				light = Color.LerpClamp(light, fogColorValue, MATH.Pow(closestDis, fogFalloff) * fogDensity);
			}
			#endif

			// hit nothing
			return false;
		}

		static void GatherLight(Obj obj, in HitInfo info, ref Color light, in Vec3 randomVec)
		{
			var objColor = obj.color;

			// ambient
			light += objColor * ambientLight;

			// directional
			bool inShadow = false;
			foreach (var l in directionalLights)
			{
				// in object shadow
				foreach (var o in objects)
				{
					if (o == obj) continue;
					var softDir = -l.direction + (randomVec * l.softness);
					var shadowRay = new Ray(info.point, softDir.Normalize());
					if (o.Hit(shadowRay, out var shadowInfo))
					{
						inShadow = true;
						break;
					}
				}

				// diffuse
				if (!inShadow)
				{
					Num d = MATH.Max(info.normal.Dot(-l.direction), 0);
					light += objColor * l.color * d;
				}
			}
		}

		static bool IsInShadow(Vec3 point, in Vec3 randomVec)
		{
			foreach (var l in directionalLights)
			{
				foreach (var o in objects)
				{
					var softDir = -l.direction + (randomVec * l.softness);
					var shadowRay = new Ray(point, softDir.Normalize());
					if (o.Hit(shadowRay, out var shadowInfo))
					{
						return true;
					}
				}
			}
			return false;
		}
	}
}