#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

bench: benchtree.o countint.o
	g++ -o benchtree benchtree.o countint.o

rst: test_RST.o countint.o
	g++ -o rst test_RST.o countint.o

bst: test_BST.o 
	g++ -o bst test_BST.o

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp
test_RST.o: RST.hpp countint.hpp BSTNode.hpp BST.hpp BSTIterator.hpp
benchtree.o: BST.hpp countint.hpp RST.hpp
