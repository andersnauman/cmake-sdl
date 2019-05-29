#ifndef CORE_UNIQUE_H_
#define CORE_UNIQUE_H_

namespace Core {
template <class T>
class Unique {
    public:
        static T& GetInstance() {
            static T instance_;
            return instance_;
        };
        Unique(const Unique& arg) = delete; // Copy constructor
        Unique(const Unique&& arg) = delete;  // Move constructor
        Unique& operator=(const Unique& arg) = delete; // Assignment operator
        Unique& operator=(const Unique&& arg) = delete; // Move operator
    private:
        // Must have these two for thread-safety?
        Unique() = default;
        ~Unique() = default;
};
};
#endif // CORE_UNIQUE_H_