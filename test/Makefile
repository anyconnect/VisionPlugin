CPP=g++
CPPFLAGS=-I. -std=c++17 -ldl -pthread
DEPS = Test.h VisionPlugin.h
OBJ = Test.o

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

TARGET = visionplugintest

all: $(TARGET)

clean: 
	rm -f $(OBJ) $(TARGET)


$(TARGET): $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS)
