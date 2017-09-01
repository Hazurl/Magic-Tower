SRC_DIR := src/Collider src/Utilities src/GameState src/Interface src/Action src/GameObject src/Components src/Components/Camera src/Components/Data src/Components/Renderer src

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))

BUILD_DIR := $(addprefix build/,$(SRC_DIR))

DEST := build/magic_tower

OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

HAZ_LIB_NAME := libframeworkHaz.so
HAZ_LIB_PATH := build/

FLAGS := -std=c++17 -O2 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lframeworkHaz -L$(HAZ_LIB_PATH)
INCLUDE := -Iinclude -IFramework-haz/include
MAKEFLAGS += --no-print-directory

all: $(DEST)

# Main build task
# Compile each file and link them
$(DEST): $(HAZ_LIB_PATH)/$(HAZ_LIB_NAME) $(BUILD_DIR) $(OBJ)
	@echo "\033[32m\033[1m :: Linking of all objects\033[0m"
	@g++ $(INCLUDE) $(FLAGS) -o $(DEST) $(OBJ) $(LIBS) 
	@echo -n "\033[34m"
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"
	@echo -n "\033[0m"

# compile a file into a object
build/%.o: %.cpp
	@echo "\033[1m :: Building" "$<" "\033[0m"
	@g++ -c $(INCLUDE) $(FLAGS) -o "$@" "$<"

#make build folders
$(BUILD_DIR):
	@mkdir -p $@

$(HAZ_LIB_PATH)/$(HAZ_LIB_NAME): $(BUILD_DIR)
	@cd Framework-haz && make lib
	@cp Framework-haz/build/lib/$(HAZ_LIB_NAME) $(HAZ_LIB_PATH)

framework-haz: $(HAZ_LIB_PATH)/$(HAZ_LIB_NAME)

# Clean every build files by destroying the build/ folder.
clean:
	rm -rf build
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "Project  Cleaned"
	@echo "----------------"
	@echo -n "\033[0m"

# run the program
run: $(DEST)
	@clear
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Run       "
	@echo "----------------"
	@echo -n "\033[0m"
	@LD_LIBRARY_PATH=$(HAZ_LIB_PATH):$LD_LIBRARY_PATH $(DEST)
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
	@echo -n "\033[0m"

# delete all objects and recompile them
again:
	@make clean
	@make run

# Use fgen
file:
	fgen -p=include/$(dir)/$(name).h -t=fgenTemplate/hppTemplate.h class=$(name) define=$(name)
	fgen -p=src/$(dir)/$(name).cpp -t=fgenTemplate/cppTemplate.cpp class=$(name) include=$(dir)/$(name).h

valgrind: $(DEST)
	@clear
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Run       "
	@echo "----------------"
	@echo -n "\033[0m"
	@LD_LIBRARY_PATH=$(HAZ_LIB_PATH):$LD_LIBRARY_PATH valgrind $(DEST)
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
	@echo -n "\033[0m"
