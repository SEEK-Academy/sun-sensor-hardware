#include <cmath>

namespace math{
    template <typename T, typename S>
    T rootMeanSquare(const S data){
        static_assert(std::is_same<typename S::value_type,T>::value, "type in the container is different than return type");

        int divider = 0; 
        T aggregate = 0;      
        
        for(auto elem : data){
            aggregate += elem * elem;
            divider++;
        }
        if(divider != 0) aggregate / divider;
        return std::sqrt(aggregate);
    }
}