TARGET = echo_client  # Имя готовой программы
CXX = g++             # Компилятор C++
CXXFLAGS = -Wall -O2  # Включить проверки и оптимизацию

#собрать программу
all: $(TARGET)

# скомпилировать main.cpp в файл TARGET
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

# Очистка папки от результатов сборки
clean:
	rm -f $(TARGET) *.o
