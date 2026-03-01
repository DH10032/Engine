#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

#include <map>
#include <typeindex>
#include <vector>

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

class Registry{
    private:
    enum flag{
        Dense,
        Sparse
    };
    public:
    std::map<std::type_index, void*> Components;
    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = new std::vector<DenseComponent<T>>();
                break;

            case Sparse:
                Components[typeid(T)] = new std::vector<SparseComponent<T>>();
                break;
        }
    };

};
