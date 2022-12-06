
#include <functional>
#include <memory>

namespace singleton_util {

void registerImplementation(const std::type_info& typeInfo, std::function<void*()> createFn);
void* createInstance(const std::type_info& typeInfo);

}

template <typename I>
class Singleton
{
public:
	static I& instance();
	static void registerImplementation(std::function<I*()> createFn);

protected:
	Singleton() = default;
	//~Singleton() = default;
    Singleton( const Singleton& ) = delete;
    Singleton& operator=( const Singleton& ) = delete;
};

template <typename I>
I& Singleton<I>::instance()
{
	static std::unique_ptr<I> theInstance(static_cast<I*>(singleton_util::createInstance(typeid(I))));
	return *theInstance;
}

template <typename I>
void Singleton<I>::registerImplementation(std::function<I*()> createFn)
{
	singleton_util::registerImplementation(typeid(I), createFn);
}
