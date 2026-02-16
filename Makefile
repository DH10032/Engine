CC = g++
Target = run_file
# 라이브러리 추가되면 여기 넣어주세요
lib = -lSDL2 -lSDL2_image

SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

all: $(Target)

# gcc -c main.c -o main.o
%.o: %.cpp
	$(CC) -c $< -o $@

$(Target): $(OBJS)
	$(CC) $^ -o $@ $(lib)

clean:
	rm -f $(OBJS) $(Target)