#ifndef INTERFACE
#define INTERFACE

#include "../graphic/window/window.h"
#include "../graphic/font/font.h"
#include "../core/assetManager/assetManager.h"
#include "../graphic/animation/animation.h"
#include "../core/core.h"

namespace Engine{
    class GameManager{
        private:
        Registry Reg;
        Asset data;
        int size = 64;

        public:
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
         * @brief core내부 컴포넌트 매니저 초기화
         */
        void init();

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

#endif