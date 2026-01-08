#include <mutex>
#include <atomic>

#if 0

/**
* 使用std::atomic来解决"DCL失效"问题
*/

class Singleton
{
public:
	static Singleton* getInstance()
	{
		Singleton* tmp = instance.load(std::memory_order_acquire);
		if (tmp == nullptr)
		{
			std::lock_guard<std::mutex> lock(mtx);
			tmp = instance.load(std::memory_order_relaxed);
			if (tmp == nullptr)
			{
				tmp = new Singleton();
				instance.store(tmp, std::memory_order_release);
			}
		}
		return tmp;
	}

private:
	Singleton() { }
	static std::atomic<Singleton*> instance;
	static std::mutex mtx;
};

std::atomic<Singleton*> Singleton::instance(nullptr);
std::mutex Singleton::mtx;

#else

/**
* Meyers' Singleton (C++11标准后单例模式的最佳实践)
* C++11标准: 局部静态变量的初始化是线程安全的。即: 如果多个线程同时尝试初始化同一个局部静态变量, 只有一个线程会执行初始化。
*/

class Singleton
{
public:
	static Singleton& getInstance()
	{
		static Singleton instance;
		return instance;
	}

private:
	Singleton() { }
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

#endif
