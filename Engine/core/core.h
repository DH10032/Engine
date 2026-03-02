#ifndef CORE
#define CORE

#include "../hal/HAL.h"

/*
컴포넌틑 매니저 정리 중
*/

template <typename T>
class SparseComponent{
    private:

    public:
    int UUID;
    T data;
};

template <typename T>
class DenseComponent{
    private:
    
    public:
    T data;
};

/*
    스마트 포인터 추상화
*/
class BaseComponent {};
template <typename T>
class SmartPointer : BaseComponent{
    private:
    std::unique_ptr<std::vector<T>> Data;

    public:
    SmartPointer() : Data(std::make_unique<std::vector<T>>()) {}
};


class Registry{
    private:

    enum flag{
        Dense,
        Sparse
    };
    std::map<std::type_index, BaseComponent*> Components;

    public:

    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = SmartPointer<DenseComponent<T>>();
                break;

            case Sparse:
                Components[typeid(T)] = SmartPointer<SparseComponent<T>>();
                break;
        }
    };
};

#endif
