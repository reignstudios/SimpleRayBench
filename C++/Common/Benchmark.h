#pragma once
#include "LangUtils.h"

#define NUM64
//#define FOG_BASIC

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
		inline
		static Num NextValue(Num u, Num v)
		{
			#define randoValueX 12.9898f
			#define randoValueY 78.233f
			#define randoValueZ 43758.543123f

			Num result = (u * randoValueX) + (v * randoValueY);
			result = MATH::Sin(result) * randoValueZ;
			return result - MATH::Floor(result);
		}
	};

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
				Num widthRange = width - 1;
				Num heightRange = height - 1;
				for (int f = 0; f != frames; ++f)
				{
					std::cout << "Frame:" << f << " started rendering" << std::endl;
					auto colors = movie->frames[f]->colors;
					for (int y = 0; y != height; ++y)
					{
						for (int x = 0; x != width; ++x)
						{
							ray.direction = Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();

							// generate shared random vector
							Num randomVal = RandomUtil::NextValue(x / widthRange, y / heightRange);
							auto randomVec = Vec3(randomVal, randomVal, randomVal) - .5f;

							// trace
							int maxBounce = maxBounceCount;
							auto light = Color();
							Trace(ray, &light, &maxBounce, randomVec);

							// write result
							colors[x + (y * width)] = light;
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
						data->waiting = false;
					}

					// wait for all threads to finish
					for (int i = 0; i != threadCount; ++i)
					{
						auto data = threadDatas[i];
						while (!data->done) Sleep(1);
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
			auto colors = data->image->colors;
			Num widthRange = width - 1;
			Num heightRange = height - 1;
			for (int y = data->y; y < data->yEnd; ++y)
			{
				for (int x = data->x; x < data->xEnd; ++x)
				{
					ray.direction = Vec3((x / (Num)(width - 1)) - .5f, (y / (Num)(height - 1)) - .5f, -1).Normalize();
					
					// generate shared random vector
					Num randomVal = RandomUtil::NextValue(x / widthRange, y / heightRange);
					auto randomVec = Vec3(randomVal, randomVal, randomVal) - .5f;

					// trace
					int maxBounce = maxBounceCount;
					auto light = Color();
					Trace(ray, &light, &maxBounce, randomVec);

					// write result
					colors[x + (y * width)] = light;
				}
			}

			// tell main thread we're done
			data->done = true;
		}

		static bool Trace(Ray& ray, Color* light, int* maxBounce, Vec3& randomVec)
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
					reflectedClosestInfo.normal = closestInfo.normal + (randomVec * closestObject->roughness);
					reflectedRay.direction = ray.direction.Reflect(reflectedClosestInfo.normal.Normalize());
					reflectedRay.origin = closestInfo.point - (reflectedRay.direction * .0001f);// move a little off surface to correct for floating point errors

					// gather surface light
					GatherLight(closestObject, &reflectedClosestInfo, &diffuseLight, randomVec);

					// trace from this reflected path
					*maxBounce = maxBounceReset;// reset max bounce here or we lose light average consistancy
					Trace(reflectedRay, &reflectedLight, maxBounce, randomVec);
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
					if (!IsInShadow(fogPos, randomVec)) fogLitDis += volumeFogStep;
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
					if (!IsInShadow(fogPos, randomVec)) fogLitDis += volumeFogStep;
				}
				Color fogColorValue = fogColor * (fogLitDis / (maxVolumeFogSteps * volumeFogStep));
				(*light) = Color::LerpClamp((*light), fogColorValue, MATH::Pow(closestDis, fogFalloff) * fogDensity);
			}
			#endif

			// hit nothing
			return false;
		}

		static void GatherLight(Obj* obj, HitInfo* info, Color* light, Vec3& randomVec)
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
					auto softDir = -l->direction + (randomVec * l->softness);
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

		static bool IsInShadow(Vec3& point, Vec3& randomVec)
		{
			for (int i = 0; i != directionalLightCount; ++i)
			{
				auto l = directionalLights[i];

				for (int i2 = 0; i2 != objectCount; ++i2)
				{
					auto o = objects[i2];

					auto softDir = -l->direction + (randomVec * l->softness);
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