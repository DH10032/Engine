#include "main.h"

// Engine::GameManager system;
// system.ShowWindow();
// system.LoadAsset("Game/data/asset.json");
// for(;;){
//     system.DrawObject();
//     SDL_Delay(30);
// }

// system.Destroy_Object();

/*
먼저 아래틑 테스트 코드 입니다.
*/
struct test{
    int a;
    int b;
};

int main()
{
    
    test d = {
        .a = 1,
        .b = 2
    };

    /************************************************************************/
    DenseComponentPool<test> A;
    A.add(d);

    test r = A[0];

    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;
    
    /************************************************************************/
    DenseComponentPool<test> B;
    B=A;

    r = B[0];
    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;
    
    /************************************************************************/
    SparseComponentPool<test> C;

    C.add(d, 0);

    r = C[0];

    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;
    
    /************************************************************************/
    SparseComponentPool<test> D;

    D=C;

    r = D[0];
    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;

    /************************************************************************/
    Engine::GameManager system;
    system.ShowWindow();
    system.LoadAsset("Game/data/asset.json");

    for(;;){
        system.DrawObject();
        SDL_Delay(30);
    }

    system.Destroy_Object();

}