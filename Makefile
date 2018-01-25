SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:%.cpp=%.d)
TARGET = mtgen

CFLAGS = -std=gnu++14 -O2 `libpng-config --cflags`
LFLAGS = -lm -O2 `libpng-config --ldflags`

all: $(TARGET)

clean:
	rm $(DEPS) $(OBJECTS) $(TARGET)

.cpp.o:
	g++ -ggdb -MMD -MP $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

-include $(DEPS)
