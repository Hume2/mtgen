SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:%.cpp=%.d)
TARGET = mtgen

CFLAGS = -std=gnu++14 -O2 -Wall `libpng-config --cflags`
LFLAGS = -lm -O2 `libpng-config --ldflags` -lboost_system -lboost_filesystem -lboost_serialization

all: $(TARGET)

clean:
	rm $(DEPS) $(OBJECTS) $(TARGET)

.cpp.o:
	g++ -ggdb -MMD -MP $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

-include $(DEPS)
