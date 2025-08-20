# Ten file thuc thi se duoc tao ra sau khi build
TARGET = snake.exe

# Trinh bien dich su dung va cac tuy chon bien dich
CXX = g++
CXXFLAGS = -I C:/raylib/w64devkit/include -std=c++17

# Lien ket cac thu vien can thiet cua raylib va Windows
LDFLAGS = -L C:/raylib/w64devkit/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Cac file nguon C++ va tao danh sach file doi tuong tuong ung
SRC = src/main.cpp src/Game.cpp src/Food.cpp src/Snake.cpp src/utils.cpp
OBJ = $(SRC:.cpp=.o)

# Mac dinh: build chuong trinh
all: $(TARGET)

# Quy tac tao file thuc thi tu cac file nguon
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Quy tac xoa file thuc thi va cac file .o (neu co)
clean:
	del /Q *.exe *.o 2>nul || true

# Danh dau quy tac khong tao file cung ten (phan dung cho VSCode)
.PHONY: all clean
