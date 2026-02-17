# 컴파일러 종류
CC = g++
# 실행파일 이름
Target = core
# 라이브러리 추가되면 여기 넣어주세요
lib = -lSDL2 -lSDL2_image

# 루트 폴더 하위 폴대 내부에 있는 모든 cpp 파일 탐색
SRCS = $(shell find . -name '*.cpp')
# SRCS .cpp 대신 .o로 기입한 목록 (목적어 파일)
OBJS = $(SRCS:.cpp=.o)

all: $(Target)


# =====================      빌드     =======================
# 컴파일 과정, .cpp -> .o로 변환, g++ -c main.cpp -o main.o
%.o: %.cpp
	$(CC) -c $< -o $@

# 링킹 과정
# 예시 g++ memory.o ai_system.o render.o core.o -o core -lSDL2 -lSDL2_image
$(Target): $(OBJS)
	$(CC) $^ -o $@ $(lib)

# =====================파일 정리 플래그=======================
# 파일 전체 삭제
clean:
	rm -f $(OBJS) $(Target)

# 목적어 파일만 정리
rm:
	rm -f $(OBJS)