TARGET = daytime_client
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
