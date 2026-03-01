#ifndef CORE
#define CORE

/*
컴포넌틑 매니저 정리 중
*/

class Registry{
    private:
    enum flag{
        Dense,
        Saprse
    };
    public:
    map<std::type_index, void*> Components;
    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = new vector<DenseComponent> Data;
                break;

            case Sparse:
                Components[typeid(T)] = new vector<SaprseComponent> Data;
                break;
        }
    };

};

template <typename T>
class SaprseComponent{
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

#endif
