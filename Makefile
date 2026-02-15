CC = g++
Target = run_file
dll = -lSDL2 -lSDL2_image

# gcc -c main.c -o main.o
%.o: %.cpp
	$(CC) -c $< -o $@

$(Target): %.o
	$(CC) $^ -o $(Target) $(dll)