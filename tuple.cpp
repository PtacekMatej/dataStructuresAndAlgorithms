#include <iostream>

template<typename... types_rest>
class CTuple;

template<typename T, typename... types_rest>
class CTuple<T, types_rest...>
{
    public:
        CTuple(T a, types_rest... rest): value(a), rest(rest...){}

        template<int I>
        constexpr auto& get()
        {
            if constexpr(I == 0)
                return value;
            else return rest.template get<I-1>();
        }
       
    private:
        T value;
        CTuple<types_rest...> rest;
        
};

template<>
class CTuple<>{};


template<typename T, typename ...rest>
CTuple(T,  rest...) -> CTuple<T, rest...>;
 

//some basic tests
int main()
{
    CTuple a = CTuple(1, 2, 3, "Hello world", CTuple(12.3, "Banana"));
    std::cout << a.get<1>() << "\n";
    std::cout << a.get<4>().get<1>() << "\n";

}
