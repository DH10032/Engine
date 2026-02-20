#include "animation.h"

/*

*/
namespace Animation{

    void Assemble_Texture(SDL_Renderer* renderer, SDL_Texture* picture ,std::vector<Parts> p){

        for(Parts part:p){
            SDL_RenderCopyEx(
                renderer,           // 렌더러
                picture,            // 텍스처
                &(part.src),        // 소스 영역 (NULL = 전체)
                &(part.dst),        // 목적지 영역
                part.angle,         // 각도 (도 단위, 시계방향)
                &(part.center),     // 회전중심(dst기준 상대 좌표)
                SDL_FLIP_NONE       // 뒤집기 옵션
            );
        }
    }

    /**
     * @brief action에 목표 degee를 입력하면 int tmp동안 각도를 업데이팅
     */
    void UpdateTraslation(std::vector<Parts>& part, std::vector<int> action, int tmp){
        std::vector<Parts> Newpart;
        Newpart.push_back(part[0]);
    
        for(int i=0; i < part.capacity()-1; i++){
            Parts Newp;
            float s = sin(action[i]*M_PI/180);
            float c = cos(action[i]*M_PI/180);

            std::cout<< "raw:" << action[i] <<std::endl;
            std::cout<< "s:" << s <<std::endl;
            std::cout<< "c:" << c <<std::endl;

            glm::vec3 x = glm::vec3(part[i+1].dst.x-part[i].dst.x, part[i+1].dst.y-part[i].dst.y, 1);
            glm::mat3 m = glm::mat3(
                c,  s,  0, // 1열
                -s, c,  0,  // 2열
                0,  0,  1   // 3열
            );

            x = m*x;
            part[i].angle = action[i];
            
            if(i+1<part.capacity()){
                Newp.dst = {part[i].dst.x+x[0], part[i].dst.y+x[1], 64, 64};
            }

        }
        std::cout<< "x1:" << part[0].dst.x <<std::endl;
        std::cout<< "y1:" << part[0].dst.y <<std::endl;
        std::cout<< "x2:" << part[1].dst.x <<std::endl;
        std::cout<< "y2:" << part[1].dst.y <<std::endl;
        std::cout<< "x3:" << part[2].dst.x <<std::endl;
        std::cout<< "y3:" << part[2].dst.y <<std::endl;
    }

    void update_Texture(std::vector<Parts> p){

    }
}
