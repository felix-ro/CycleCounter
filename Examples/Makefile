CXX = clang++ 
OPT_FLAG = -O2 -march=armv8-a

CXX_FLAGS = -Wall -Werror

all: SanityCheck AdditionCycles

SanityCheck: SanityCheck.cc
	$(CXX) $(OPT_FLAG) $(CXX_FLAGS) SanityCheck.cc -o SanityCheck

AdditionCycles: AdditionCycles.cc
	$(CXX) $(OPT_FLAG) $(CXX_FLAGS) AdditionCycles.cc -o AdditionCycles

clean: 
	rm SanityCheck AdditionCycles
