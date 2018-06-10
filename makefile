CC = g++
CFLAGS = -std=c++11
OBJECTS = main.o bmp.o camera.o obj.o scene.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
	
main.o: main.cpp include/tracer.h
	$(CC) $(CFLAGS) -c main.cpp

%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -c $<

# bmp.o: src/bmp.cpp include/bmp.h
# 	$(CC) $(CFLAGS) -c src/bmp.cpp

# # camera.o: src/camera.cpp include/camera.h
# # 	$(CC) $(CFLAGS) -c src/camera.cpp

# # obj.o: src/obj.cpp include/obj.h
# # 	$(CC) $(CFLAGS) -c src/obj.cpp

# # scene.o: src/scene.cpp include/scene.h
# # 	$(CC) $(CFLAGS) -c src/scene.cpp

clean:
	rm *.o