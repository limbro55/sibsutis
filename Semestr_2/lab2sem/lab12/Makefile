CXX = clang++ -arch arm64
CXXFLAGS = -std=c++11 -Wall -Werror -MMD 

# Пути к файлам исходного кода
SRC_DIR = .
OBJ_DIR = kash
BIN_DIR = make

# Имена исполняемых файлов и объектных файлов
EXECUTABLE = main
OBJ_FILES = main.o Sort.o 

# Цель по умолчанию
all: $(BIN_DIR)/$(EXECUTABLE)

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Линковка исполняемого файла
$(BIN_DIR)/$(EXECUTABLE): $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
	$(CXX) $(CXXFLAGS) $^ -o $@

# Очистка сгенерированных файлов
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

# Правило для создания каталогов, если они не существуют
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))
