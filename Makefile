# Tên file thực thi
TARGET = snake.exe

# Compiler và flags
CXX = g++
CXXFLAGS = -I C:/raylib/w64devkit/include -std=c++17
LDFLAGS = -L C:/raylib/w64devkit/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Các file nguồn và file đối tượng
SRC = src/main.cpp src/Game.cpp src/Food.cpp src/Snake.cpp src/utils.cpp
OBJ = $(SRC:.cpp=.o)

# Quy tắc build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean: xóa file thực thi và object nếu cần
clean:
	del /Q *.exe *.o 2>nul || true

# Phù hợp cho VSCode task.json
.PHONY: all clean
