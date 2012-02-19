CXX = clang++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
.PHONY : clean all
euler% : %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

progs := $(patsubst %.cc, euler%, $(wildcard *.cc))
all : $(progs)

clean:
	rm -r euler*
