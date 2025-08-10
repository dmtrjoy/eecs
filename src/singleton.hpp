#ifndef ENGINE_SINGLETON_H
#define ENGINE_SINGLETON_H

namespace engine {

template <typename T>
class Singleton {
public:
    Singleton(Singleton&&) = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};

}

#endif // !ENGINE_SINGLETON_H
