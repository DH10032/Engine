#ifndef _GameManager_
#define _GameManager_

#include "../graphic/window/window.h"
#include "../graphic/font/font.h"
#include "../core/assetManager/assetManager.h"
#include "../graphic/animation/animation.h"
#include "../core/core.h"

namespace Engine{
    class GameManager{
        private:
        Asset data;
        int size = 64;
        
        public:
        Registry Reg;
        window_info window_setting = {
            .window_name = "test_game",
            .window = nullptr,
            .renderer = nullptr,
            .Red = 255,
            .Green = 255,
            .Blue = 255,
            .Bright = 255
        };

        std::vector<Parts> p = {
            {
                9,
                {0, 0, 16, 16},
                {200, 200, size, size},
                {size/2, 0},
                0
            },
            {
                9,
                {0, 16, 16, 32},
                {200, 264, size, size},
                {size/2, 0},
                0
            },
            {
                9,
                {48, 48, 64, 64},
                {200, 328, size, size},
                {size/2, 0},
                0
            }
        };

        /**
         * @brief 내장 윈도우 호출 함수
         */
        void ShowWindow();

        /**
         * @brief 위도우 닫기 함수
         */
        void DeleteWindow();

        /**
         * @brief Asset 불러오기 함수
         * @param[in] path json 경로
         * @note 해당 json에 Asset들이 등록이 되어 있어야 함
         */
        void LoadAsset(std::string path);

        /** 
        * @brief render_claer 등 각 프레임 에서 처음으로 호출해야 하는 함수들의 집합
        */
        void FrameStart();
}

        /**
         * @brief Entity 중 업데이트가 필요한 Entity만 업데이트
         * @note Entity에 렌더링 관련 컴포넌트 필수
         */
        void DrawObject();

        /**
         * @brief 
         * @note 현재 스마트 포인터 도입으로 크게 신경쓰지 않아도 됨
         */
        void Destroy_Object();
        
    };
}
std::vector<std::vector<int>> tile_color_datas = {
    [0, 100, 200, 255],
    [120, 180, 80, 255],
    [34, 139, 34, 255],
    [0, 80, 0, 255],
    [240, 200, 100, 255],
    [200, 180, 50, 255],
    [30, 80, 60, 255],
    [100, 200, 50, 255],
    [150, 160, 150, 255],
    [130, 120, 110, 255],
    [47, 79, 79, 255],
    [200, 220, 240, 255],
    [160, 190, 220, 255],
    [245, 250, 255, 255],
    [180, 230, 255, 255],
    [150, 50, 50, 255]
};

#endif