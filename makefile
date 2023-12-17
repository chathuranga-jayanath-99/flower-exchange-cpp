# Makefile with two terminals running different executables

# Executables
TARGET1 = myprogram1
TARGET2 = myprogram2

# Source files
SRCS1 = ./src/Trader.cpp 
SRCS2 = ./src/Heap.cpp ./src/Order.cpp ./src/OrderBook.cpp ./src/OrderEntry.cpp ./src/Utils.cpp ./src/ExchangeApplication.cpp

# Object files
OBJS1 = $(SRCS1:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)

# Compiler and compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: $(TARGET2)

# Rule to build the first executable
$(TARGET1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(OBJS1)

# Rule to build the second executable
$(TARGET2): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(OBJS2)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Phony target to run the programs in separate terminals
.PHONY: run
run: $(TARGET1) $(TARGET2)
	gnome-terminal --tab --title="Terminal 2" --command="make execute2"
	sleep 2
	gnome-terminal --tab --title="Terminal 1" --command="make execute1"
	
# Phony target to execute the first program
.PHONY: execute1
execute1:
	./$(TARGET1)

# Phony target to execute the second program
.PHONY: execute2
execute2:
	./$(TARGET2)

# Phony target to clean the project
.PHONY: clean
clean:
	rm -f $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2)
