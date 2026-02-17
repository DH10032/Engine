#include "system.h"



namespace memory{
    json Load_Action_json(const std::string path){
        std::ifstream file(path);
        json data = json::parse(file);
        return data;
    }
// 실수 주석 했습니다.
//     Units set_memory_unit(){
//         UnitStorage mem.data = (Unit*)malloc(sizeof(Unit)*unit_count_max);
//         mem.count = 0;
//         mem.capacity = unit_count_max;
//         return mem;
//     }

//     bool append_unit(UnitStorage& storage, const Unit& unit) {
//     if (!storage.data) return false;
//     if (storage.count >= storage.capacity) return false;

//     storage.data[storage.count++] = unit;
//     return true;
// }

// // 정렬은 렌더링 단계에서
//     void sortUnit(UnitStorage& storage) {
//         // render_list 채우기
//         // ...

//         std::sort(render_list, render_list + render_count,
//             [](const RenderCmd& a, const RenderCmd& b) {
//                 return a.img_id < b.img_id;
//             }
//         );
//     }

//     bool SameImg(int ImgId1, int ImgId2){
//         if (ImgId1&0xFFFF == ImgId2&0xFFFF) return true;
//         return false;
//     }
}

