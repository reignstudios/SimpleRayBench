#pragma once
#include "LangUtils.h"

#define NUM64
//#define FOG_BASIC
//#define RANDOM_CACHE

#if defined(NUM32)
#define Num float
#define MATH MathF
#elif defined(NUM64)
#define Num double
#define MATH Math
#endif

namespace SimpleRayBench
{
	static class RandomUtil
	{
	public:
		static int nextValue;

		#if RANDOM_CACHE
		static Num[] values = new Num[]
		{
			0.5131366,0.47369808,0.5355348,0.2797321,0.9233443,0.94912815,0.14586163,0.30903548,0.94743615,0.58786625,
			0.9668644,0.5584841,0.025240779,0.6176654,0.5316545,0.8852849,0.12660599,0.35615206,0.9546824,0.02586317,
			0.81509244,0.34394866,0.07938832,0.8642365,0.048390687,0.884387,0.55920166,0.86752623,0.3444876,0.07635695,
			0.68642074,0.8988211,0.58721966,0.6842663,0.32011318,0.71642447,0.15513289,0.83587873,0.37929702,0.11406493,
			0.21583551,0.90324044,0.15580535,0.19788212,0.9759695,0.82100695,0.18947572,0.36430824,0.92472243,0.017311156,
			0.91937256,0.99684864,0.8568594,0.97259927,0.59285814,0.58655363,0.7781577,0.2628913,0.026745737,0.5972613,
			0.809816,0.9051277,0.55815554,0.44243264,0.34004086,0.656188,0.9743796,0.5629352,0.9384745,0.680604,
			0.2547078,0.010892212,0.9825735,0.40277225,0.9277489,0.34304756,0.2644722,0.07906562,0.23258018,0.45819247,
			0.6436251,0.72362727,0.0491243,0.9053614,0.017784,0.6906157,0.63710564,0.06327033,0.8212551,0.6816109,
			0.046097875,0.71246654,0.5903521,0.9587056,0.3274861,0.31728834,0.6412734,0.32748264,0.7084488,0.43491495,
			0.86271584,0.9702974,0.49212074,0.6956525,0.7211632,0.07477033,0.18114424,0.83223575,0.3600428,0.5805837,
			0.93793505,0.35527015,0.72051805,0.92048204,0.089633286,0.8884545,0.8599433,0.32220298,0.7847129,0.89836806,
			0.6645203,0.24697345,0.8602744,0.9965967,0.1467238,0.293316,0.18254852,0.8949484,0.82631147,0.13577425,
			0.79806566,0.07945639,0.35479784,0.3011884,0.25134295,0.05494255,0.8458432,0.36783832,0.07386756,0.23765498,
			0.31452072,0.091495454,0.9797041,0.5821717,0.7067076,0.10672462,0.5993222,0.16339159,0.557504,0.56940585,
			0.51105946,0.72144973,0.79186076,0.38657552,0.5579826,0.05248207,0.88468844,0.8305916,0.038596272,0.9570422,
			0.2534969,0.21159768,0.6917146,0.092182994,0.014812052,0.15601492,0.47773015,0.897941,0.28146082,0.20175934,
			0.7023841,0.77531564,0.7636091,0.4588235,0.90350735,0.34414297,0.18683541,0.50955397,0.19094044,0.23574096,
			0.58244985,0.2165432,0.030815005,0.9202402,0.8731397,0.7973387,0.9560503,0.06517774,0.023783684,0.73838425,
			0.8529261,0.43987584,0.3967008,0.19308954,0.5763217,0.36454993,0.7974134,0.19139373,0.036942482,0.07471973
		};

		static Num NextValue()
		{
			Num result = values[nextValue++];
			if (nextValue == values.Length) nextValue = 0;
			return result;
		}

		#else
		static Num NextValue()
		{
			nextValue = (nextValue * 57 + 43) % 10007;
			//nextValue = fmod((nextValue * 57 + 43), 10007);// very slow
			return nextValue / (Num)10007;
		}
		#endif
	};
	int RandomUtil::nextValue = 0;

	struct Color
	{
	public:
		Num r, g, b;

		Color()
		{
			r = 0;
			g = 0;
			b = 0;
		}

		Color(Num r, Num g, Num b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}

		inline
		Color operator+(const Color& p2)
		{
			return Color(r + p2.r, g + p2.g, b + p2.b);
		}

		inline
		Color operator-(const Color& p2)
		{
			return Color(r - p2.r, g - p2.g, b - p2.b);
		}

		inline
		Color operator*(const Color& p2)
		{
			return Color(r * p2.r, g * p2.g, b * p2.b);
		}

		inline
		friend Color operator*(const Color& p1, Num p2)
		{
			return Color(p1.r * p2, p1.g * p2, p1.b * p2);
		}

		inline
		friend Color operator/(const Color& p1, Num p2)
		{
			return Color(p1.r / p2, p1.g / p2, p1.b / p2);
		}

		inline
		static Color Lerp(Color p1, Color p2, Num t)
		{
			return p1 + ((p2 - p1) * t);
		}

		inline
		static Color LerpClamp(Color p1, Color p2, Num t)
		{
			return p1 + ((p2 - p1) * MATH::Clamp(t, 0, 1));
		}
	};

	struct Vec3
	{
	public:
		Num x, y, z;

		Vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vec3(Num x, Num y, Num z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		inline
		Vec3 operator +(const Vec3& p2)
		{
			return Vec3(x + p2.x, y + p2.y, z + p2.z);
		}

		inline
		Vec3 operator -(const Vec3& p2)
		{
			return Vec3(x - p2.x, y - p2.y, z - p2.z);
		}

		inline
		friend Vec3 operator-(const Vec3& p1, Num p2)
		{
			return Vec3(p1.x - p2, p1.y - p2, p1.z - p2);
		}

		inline
		Vec3 operator-()
		{
			return Vec3(-x, -y, -z);
		}

		inline
		Vec3 operator*(const Vec3& p2)
		{
			return Vec3(x * p2.x, y * p2.y, z * p2.z);
		}

		inline
		friend Vec3 operator*(const Vec3& p1, Num p2)
		{
			return Vec3(p1.x * p2, p1.y * p2, p1.z * p2);
		}

		inline
		friend Vec3 operator*(Num p1, const Vec3& p2)
		{
			return Vec3(p1 * p2.x, p1 * p2.y, p1 * p2.z);
		}

		inline
		Vec3 operator/(const Vec3& p2)
		{
			return Vec3(x / p2.x, y / p2.y, z / p2.z);
		}

		inline
		friend Vec3 operator/(const Vec3& p1, Num p2)
		{
			return Vec3(p1.x / p2, p1.y / p2, p1.z / p2);
		}

		inline
		Num Dot()
		{
			return (x * x) + (y * y) + (z * z);
		}

		inline
		Num Dot(Vec3 vec)
		{
			return (x * vec.x) + (y * vec.y) + (z * vec.z);
		}

		inline
		Num Length()
		{
			return MATH::Sqrt((x * x) + (y * y) + (z * z));
		}

		inline
		Vec3 Normalize()
		{
			return (*this) / MATH::Sqrt((x * x) + (y * y) + (z * z));
		}

		inline
		Vec3 Reflect(Vec3 planeNormal)
		{
			return (*this) - (planeNormal * this->Dot(planeNormal) * 2);
		}

		inline
		static Num FresnelSchlickZero(Vec3 rayDirection, Vec3 normal)
		{
			return MATH::Pow(1 - MATH::Max((-rayDirection).Dot(normal), 0), 5);
		}
	};

	struct Ray
	{
	public:
		Vec3 origin, direction;

		Ray()
		{
			origin = Vec3();
			direction = Vec3();
		}

		Ray(Vec3 origin, Vec3 direction)
		{
			this->origin = origin;
			this->direction = direction;
		}
	};

	struct HitInfo
	{
	public:
		Vec3 point, normal;

		HitInfo()
		{
			point = Vec3();
			normal = Vec3();
		}
	};

	class Obj
	{
	public:
		Color color;
		Num roughness;
		Num reflectiveness, metalic;

		Obj(Color color, Num roughness, Num reflectiveness, Num metalic)
		{
			this->color = color;
			this->roughness = roughness;
			this->reflectiveness = reflectiveness;
			this->metalic = metalic;
		}

		virtual bool Hit(Ray& ray, HitInfo* info)
		{
			return false;
		}
	};

	class Sphere : public Obj
	{
	public:
		Vec3 center;
		float radius;

		Sphere(Vec3 center, float radius, Color color, Num roughness, Num reflectiveness, Num metalic)
		: Obj(color, roughness, reflectiveness, metalic)
		{
			this->center = center;
			this->radius = radius;
		}

		virtual bool Hit(Ray& ray, HitInfo* info)
		{
			// if ray pointing wrong direction ignore
			if (ray.direction.Dot(ray.origin - center) >= 0)
			{
				*info = HitInfo();
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
				*info = HitInfo();
				return false;
			}

			// compute
			Num sqrtDisc = MATH::Sqrt(disc);
			Num invA = 1 / a;
			Num t1 = (-b - sqrtDisc) * invA;
			//Num t2 = (-b + sqrtDisc) * invA;

			info->point = ray.origin + t1 * ray.direction;
			//info.point = ray.origin + t2 * ray.direction;
			info->normal = (info->point - center).Normalize();

			return true;
		}
	};

	class Plane : public Obj
	{
	public:
		Vec3 center, normal;

		Plane(Vec3 center, Vec3 normal, Color color, Num roughness, Num reflectiveness, Num metalic)
		: Obj(color, roughness, reflectiveness, metalic)
		{
			this->center = center;
			this->normal = normal.Normalize();
		}

		virtual bool Hit(Ray& ray, HitInfo* info)
		{
			// if ray pointing wrong direction ignore
			if (ray.direction.Dot(normal) >= 0)
			{
				*info = HitInfo();
				return false;
			}

			Num denom = normal.Dot(ray.direction);
			if (MATH::Abs(denom) > 0.0001f)
			{
				Num t = (center - ray.origin).Dot(normal) / denom;
				if (t >= 0)
				{
					info->point = ray.origin + (ray.direction * t);
					info->normal = normal;
					return true;
				}
			}

			*info = HitInfo();
			return false;
		}
	};

	class RawImage
	{
	public:
		int width, height;
		Color* colors;

		RawImage(int width, int height)
		{
			this->width = width;
			this->height = height;
			colors = new Color[width * height];
		}
	};

	class RawMovie
	{
	public:
		int width, height;
		RawImage** frames;

		RawMovie(int width, int height, int frameCount)
		{
			this->width = width;
			this->height = height;
			frames = new RawImage*[frameCount];
			for (int i = 0; i != frameCount; ++i)
			{
				frames[i] = new RawImage(width, height);
			}
		}
	};

	class Camera
	{
	public:
		Vec3 position, forward, up;

		Camera(Vec3 position, Vec3 forward, Vec3 up)
		{
			this->position = position;
			this->forward = forward.Normalize();
			this->up = up.Normalize();
		}
	};

	class DirectionalLight
	{
	public:
		Vec3 direction;
		Color color;
		Num softness;

		DirectionalLight(Vec3 direction, Color color, Num softness)
		{
			this->direction = direction.Normalize();
			this->color = color;
			this->softness = softness;
		}
	};

	class RenderThreadData
	{
	public:
		int index;
		bool waiting, done;
		int x, y, xEnd, yEnd;
		RawImage* image;
	};

	static class Benchmark
	{
	public:
		#define diffusePasses 1// use to set multi-pass diffuse blending
		#define maxBounceCount 10// how many ray-bounces are allowed
		#define roughnessMul 1// force tween material value
		#define shadowSoftnessMul 0// force tween shadow value

		#define maxVolumeFogSteps 500// how far can we test the shadow volume for
		#define volumeFogStep .01f// how little the shadow volume testing step is
		#define fogDensity .4f// how dense the fog is
		#define fogFalloff 1
		static Color fogColor;

		static int width, height, frames;
		static RawMovie* movie;
		static Camera* camera;
		static int objectCount;
		static Obj** objects;
		static Color ambientLight;
		static int directionalLightCount;
		static DirectionalLight** directionalLights;

		static int threadCount;
		static RenderThreadData** threadDatas;
		static std::thread** threads;
		static bool threadsAlive;

		static void Init(int width, int height)
		{
			// init movie
			Benchmark::width = width;
			Benchmark::height = height;
			frames = 1;
			movie = new RawMovie(width, height, frames);

			// init camera
			camera = new Camera(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));

			// init scene objects
			objectCount = 5;
			objects = new Obj*[objectCount];
			objects[0] = new Plane(Vec3(0, -.4f, 0), Vec3(0, 1, 0), Color(.3f, .3f, .3f), 0.03f * roughnessMul, 1, 0);
			objects[1] = new Sphere(Vec3(0, 0, -2), .33f, Color(1, 0, 0), 0 * roughnessMul, .25f, 0);
			objects[2] = new Sphere(Vec3(-.25f, .5f, -1.5f), .25f, Color(0, 1, 0), 0 * roughnessMul, 1, 1);
			objects[3] = new Sphere(Vec3(1, -.75f, -2), 1, Color(0, 0, 1), 0 * roughnessMul, 1, 1);
			objects[4] = new Sphere(Vec3(.2f, .25f, -1.5f), .1f, Color(1, 1, 0), 0 * roughnessMul, 1, .5f);

			// init scene lights
			ambientLight = Color(.05f, .05f, .05f);
			directionalLightCount = 1;
			directionalLights = new DirectionalLight*[directionalLightCount];
			directionalLights[0] = new DirectionalLight(Vec3(.25f, -1, -.25f), Color(1, 1, 1), .025f * shadowSoftnessMul);

			// start threads
			threadsAlive = true;
			threadCount = Environment::ProcessorCount();
			threadDatas = new RenderThreadData*[threadCount];
			threads = new std::thread*[threadCount];
			for (int i = 0; i != threadCount; ++i)
			{
				int sectionHeight = height / threadCount;
				threadDatas[i] = new RenderThreadData();
				threadDatas[i]->waiting = true;
				threadDatas[i]->done = false;
				threadDatas[i]->index = i,
				threadDatas[i]->x = 0,
				threadDatas[i]->y = i * sectionHeight,
				threadDatas[i]->xEnd = width,
				threadDatas[i]->yEnd = (i * sectionHeight) + sectionHeight;
				if (i == threadCount - 1) threadDatas[i]->yEnd = height;
				threads[i] = new std::thread(RenderThread, threadDatas[i]);
			}
		}

		static void Dispose()
		{
			for (int i = 0; i != threadCount; ++i)
			{
				auto data = threadDatas[i];
				data->done = true;
				data->waiting = false;
			}
		}

		static RawMovie* Render(bool singleThreaded)
		{
			if (singleThreaded)
			{
				// setup ray
				Ray ray;
				ray.origin = camera->position;

				// render frames
				for (int f = 0; f != frames; ++f)
				{
					std::cout << "Frame:" << f << " started rendering" << std::endl;
					auto frame = movie->frames[f];
					for (int y = 0; y != height; ++y)
					{
						for (int x = 0; x != width; ++x)
						{
							ray.direction = Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();
							int maxBounce = maxBounceCount;
							auto light = Color();
							Trace(ray, &light, &maxBounce);
							frame->colors[x + (y * width)] = light;
						}
					}
					std::cout << "Frame:" << f << " finished rendering" << std::endl;
				}
			}
			else
			{
				// render frames
				for (int f = 0; f != frames; ++f)
				{
					std::cout << "Frame:" << f << " started rendering" << std::endl;
					auto frame = movie->frames[f];

					// tell threads to start processing task
					for (int i = 0; i != threadCount; ++i)
					{
						auto data = threadDatas[i];
						data->image = frame;
						std::cout << "Telling thread to start: " << data->index << std::endl;
						data->waiting = false;
					}

					// wait for all threads to finish
					for (int i = 0; i != threadCount; ++i)
					{
						auto data = threadDatas[i];
						std::cout << "Waiting on thread: " << data->index << std::endl;
						while (!data->done) Sleep(1);
						std::cout << "Thread finish reported: " << data->index << std::endl;
					}

					std::cout << "Frame:" << f << " finished rendering" << std::endl;
				}
			}

			return movie;
		}

		static void RenderThread(void* dataObj)
		{
			auto data = (RenderThreadData*)dataObj;

			// wait for main thread to trigger
			while (data->waiting) Sleep(1);
			if (data->done) return;

			// setup ray
			Ray ray;
			ray.origin = camera->position;

			// render image section
			auto image = data->image;
			for (int y = data->y; y < data->yEnd; ++y)
			{
				for (int x = data->x; x < data->xEnd; ++x)
				{
					ray.direction = Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();
					int maxBounce = maxBounceCount;
					auto light = Color();
					Trace(ray, &light, &maxBounce);
					image->colors[x + (y * width)] = light;
				}
			}

			// tell main thread we're done
			data->done = true;
		}

		static bool Trace(Ray& ray, Color* light, int* maxBounce)
		{
			// find closes object
			Obj* closestObject = nullptr;
			Num closestDis = Math::MaxValue();
			auto closestInfo = HitInfo();
			for (int o = 0; o != objectCount; ++o)
			{
				auto obj = objects[o];
				HitInfo info;
				if (obj->Hit(ray, &info))
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
			if (closestObject != nullptr)
			{
				if (*maxBounce <= 0) return false;
				(*maxBounce)--;
				int maxBounceReset = *maxBounce;

				// buffer diffuse pass state objects
				auto reflectedClosestInfo = closestInfo;
				auto reflectedRay = ray;

				// diffuse light
				auto diffuseLight = Color();
				auto reflectedLight = Color();
				for (int i = 0; i != diffusePasses; ++i)
				{
					// diffuse surface normal
					reflectedClosestInfo.normal = closestInfo.normal + ((Vec3(RandomUtil::NextValue(), RandomUtil::NextValue(), RandomUtil::NextValue()) - .5f) * closestObject->roughness);
					reflectedRay.direction = ray.direction.Reflect(reflectedClosestInfo.normal.Normalize());
					reflectedRay.origin = closestInfo.point - (reflectedRay.direction * .0001f);// move a little off surface to correct for floating point errors

					// gather surface light
					GatherLight(closestObject, &reflectedClosestInfo, &diffuseLight);

					// trace from this reflected path
					*maxBounce = maxBounceReset;// reset max bounce here or we lose light average consistancy
					Trace(reflectedRay, &reflectedLight, maxBounce);
				}

				// material (diffuse)
				(*light) = diffuseLight / diffusePasses;

				// material (reflection)
				reflectedLight = reflectedLight / diffusePasses;
				Num fresnel = 1 - Vec3::FresnelSchlickZero(ray.direction, closestInfo.normal);
				(*light) = (*light) + Color::Lerp(reflectedLight, reflectedLight * closestObject->color, closestObject->metalic * fresnel) * closestObject->reflectiveness;

				// fog
				#if defined(FOG_BASIC)
				// basic fog just uses fog color directly
				(*light) = Color::LerpClamp((*light), fogColor, MATH::Pow(closestDis, fogFalloff) * fogDensity);
				#else
				// volume fog tracing taking into account shadows
				auto fogPos = ray.origin;
				auto fogStep = ray.direction * volumeFogStep;
				Num fogDis = 0;
				Num fogLitDis = 0;
				Num closestFogDis = closestDis;
				for (int i = 0; i != maxVolumeFogSteps; ++i)
				{
					fogPos = fogPos + fogStep;
					fogDis += volumeFogStep;
					if (!IsInShadow(fogPos)) fogLitDis += volumeFogStep;
					if (i == maxVolumeFogSteps - 1) closestFogDis = (maxVolumeFogSteps * volumeFogStep);
					if (fogDis > closestDis) break;
				}
				Color fogColorValue = fogColor * (fogLitDis / closestFogDis);
				(*light) = Color::LerpClamp((*light), fogColorValue, MATH::Pow(closestDis, fogFalloff) * fogDensity);
				#endif
				
				return true;
			}
			#if defined(FOG_BASIC)
			(*light) = (*light) + fogColor;
			#else
			else
			{
				// volume fog tracing taking into account shadows (optimized for when nothing is hit)
				auto fogPos = ray.origin;
				auto fogStep = ray.direction * volumeFogStep;
				Num fogLitDis = 0;
				for (int i = 0; i != maxVolumeFogSteps; ++i)
				{
					fogPos = fogPos + fogStep;
					if (!IsInShadow(fogPos)) fogLitDis += volumeFogStep;
				}
				Color fogColorValue = fogColor * (fogLitDis / (maxVolumeFogSteps * volumeFogStep));
				(*light) = Color::LerpClamp((*light), fogColorValue, MATH::Pow(closestDis, fogFalloff) * fogDensity);
			}
			#endif

			// hit nothing
			return false;
		}

		static void GatherLight(Obj* obj, HitInfo* info, Color* light)
		{
			auto objColor = obj->color;

			// ambient
			(*light) = (*light) + objColor * ambientLight;

			// directional
			bool inShadow = false;
			for (int i = 0; i != directionalLightCount; ++i)
			{
				auto l = directionalLights[i];

				// in object shadow
				for (int i2 = 0; i2 != objectCount; ++i2)
				{
					auto o = objects[i2];

					if (o == obj) continue;
					auto softDir = -l->direction + ((Vec3(RandomUtil::NextValue(), RandomUtil::NextValue(), RandomUtil::NextValue()) - .5f) * l->softness);
					auto shadowRay = Ray(info->point, softDir.Normalize());
					HitInfo shadowInfo;
					if (o->Hit(shadowRay, &shadowInfo))
					{
						inShadow = true;
						break;
					}
				}

				// diffuse
				if (!inShadow)
				{
					Num d = MATH::Max(info->normal.Dot(-l->direction), 0);
					(*light) = (*light) + objColor * l->color * d;
				}
			}
		}

		static bool IsInShadow(Vec3& point)
		{
			for (int i = 0; i != directionalLightCount; ++i)
			{
				auto l = directionalLights[i];

				for (int i2 = 0; i2 != objectCount; ++i2)
				{
					auto o = objects[i2];

					auto softDir = -l->direction + ((Vec3(RandomUtil::NextValue(), RandomUtil::NextValue(), RandomUtil::NextValue()) - .5f) * l->softness);
					auto shadowRay = Ray(point, softDir.Normalize());
					HitInfo shadowInfo;
					if (o->Hit(shadowRay, &shadowInfo))
					{
						return true;
					}
				}
			}
			return false;
		}
	};

	Color Benchmark::fogColor = Color(.25f, .25f, .25f);

	int Benchmark::width;
	int Benchmark::height;
	int Benchmark::frames;
	RawMovie* Benchmark::movie;
	Camera* Benchmark::camera;
	int Benchmark::objectCount;
	Obj** Benchmark::objects;
	Color Benchmark::ambientLight;
	int Benchmark::directionalLightCount;
	DirectionalLight** Benchmark::directionalLights;

	int Benchmark::threadCount;
	RenderThreadData** Benchmark::threadDatas;
	std::thread** Benchmark::threads;
	bool Benchmark::threadsAlive;
}