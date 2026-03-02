#ifndef CORE
#define CORE

#include "../hal/HAL.h"

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

class BaseComponent {};
template <typename T>
class SmartPointer : BaseComponent{
    private:
    std::unique_ptr<std::vector<T>> Data;

    public:
    SmartPointer() : Data(std::make_unique<std::vector<T>>()) {}
};


enum flag{
    Dense,
    Sparse
};

class Registry{
    private:

    
    public:
    std::map<std::type_index, BaseComponent*> Components;


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
