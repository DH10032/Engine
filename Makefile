CC = g++
Target = main
lib = -lEngine -lSDL2 -lSDL2_image -lSDL2_ttf

Game_SRCS = $(shell find ./Game/ -name '*.cpp')
Engine_SRCS = $(shell find ./Engine/ -name '*.cpp')

Game_OBJS = $(Game_SRCS:.cpp=.o)
Engine_OBJS = $(Engine_SRCS:.cpp=.o)

all: $(Target)

%.o: %.cpp
	$(CC) -c $< -o $@

# 엔진 → 라이브러리로 묶기
Engine: $(Engine_OBJS)
	ar rcs libEngine.a $(Engine_OBJS)

# 게임 → 엔진 라이브러리 링크
$(Target): $(Game_OBJS)
	$(CC) $(Game_OBJS) $@.cpp -L. -o $@ $(lib)

clean:
	rm -f $(Game_OBJS) $(Engine_OBJS) libEngine.a $(Target)

gitclean:
	git rm -f $(Game_OBJS) $(Engine_OBJS) libEngine.a $(Target)