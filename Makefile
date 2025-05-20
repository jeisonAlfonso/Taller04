# Nombre del ejecutable
EXEC = grafos

# Compilador y flags
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

# Fuentes y objetos
SRCS = main.cpp GrafoCitaciones.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
