# 엔진
## 추상화가 고려되어야 할 것

```
[Game Layer]
    맵 생성, 유닛 정의, 게임 로직
        ↓ MapData, ActionData
[Engine Layer]
    MovementSystem, CombatSystem, ActionSystem
        ↓
[Data Layer]
    Component 배열들 (Transform[], Action[], ...)
```

## 1.[Game Layer]/[Engine Layer]

## 2.[Engine Layer]/[Data Layer]