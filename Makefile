CC = g++
Target = run_file
dll = -lSDL2 -lSDL2_image
All_C_file = ()

-d: Debug = 0
-c: Debug = 1
-l: Debig = 2

ifeq (Debug, 0)
	$(CC) -c $< -o $@
	$(CC) $^ -o $(Target) $(dll)
endif

ifeq (Debug, 0)
	$(CC) -c $< -o $@
	$(CC) $^ -o $(Target) $(dll)
endif

ifeq (Debug, 0)
	$(CC) -c $< -o $@
	$(CC) $^ -o $(Target) $(dll)
endif

# gcc -c main.c -o main.o
%.o: %.cpp
	$(CC) -c $< -o $@

$(Target): %.o
	$(CC) $^ -o $(Target) $(dll)