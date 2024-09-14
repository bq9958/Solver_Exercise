# 编译器和编译器标志
CXX = g++                      # 使用的编译器
CXXFLAGS = -DPRINT_DEBUG -std=c++11 -g     # 编译选项，启用 C++11 标准并显示所有警告

# 项目名称（生成的可执行文件名称）
TARGET = Test

# 源文件和头文件
SRCS = ../src/AuxilaryFunctions.cpp \
       ../src/StructuredMesh.cpp \
       ../src/CoeffMatrix.cpp \
       ../src/Material.cpp \
       ../src/IterativeSolver.cpp \
       ../src/postprocessing.cpp \
       ../src/Test.cpp
HEADERS = ../src/AuxilaryFunctions.h \
          ../src/StructuredMesh.h \
          ../src/CoeffMatrix.h \
          ../src/Material.h \
          ../src/IterativeSolver.h \
          ../src/input.h \
          ../src/postprocessing.h \
          ../src/precisionFloat.h

# 生成的目标文件（根据源文件生成 .o 文件）
OBJS = $(patsubst ../src/%.cpp, %.o, $(SRCS))

# 默认目标：生成可执行文件
all: $(TARGET)

# 规则：将源文件链接为可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 规则：生成目标文件（.o 文件），依赖对应的源文件和头文件
%.o: ../src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的目标文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)

run:
	./Test > Test.txt

# 伪目标：不依赖于文件的特殊目标
.PHONY: all clean
