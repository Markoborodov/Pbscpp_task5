#include <string>
#include <memory>
#include <iostream>

class Any {
    class IHolder {
    public:
        IHolder() = default;
        virtual ~IHolder() = default;
    };
    template <typename T>
    class THolder : public IHolder {
        T obj;
    public:
        explicit THolder(const T& t): obj(t) {}
        T& get() {
            return obj;
        }
    };

    std::shared_ptr<IHolder> holder;
public:
    template <typename T>
    explicit Any(const T& t): holder(new THolder<T>(t)) {}
    template <typename T>
    T& get() {
        auto real_holder = dynamic_cast<THolder<T>*>(holder.get());
        if (real_holder == nullptr) throw std::logic_error("Bad get() call");
        return real_holder->get();
    }
};

int main()
{
    Any a(5);
    std::cerr << a.get<int>() << std::endl; // 5
//    std::cerr << a.get<std::string>() << std::endl;// error
    Any b(1.0);
    std::cerr << b.get<double>() << std::endl; // 1
    return 0;
}
