CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
OBJ = main.o indice.o lista_enlazada.o stopwords.o
EXEC = buscador

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp indice.h stopwords.h
	$(CXX) $(CXXFLAGS) -c main.cpp

indice.o: indice.cpp indice.h lista_enlazada.h stopwords.h
	$(CXX) $(CXXFLAGS) -c indice.cpp

lista_enlazada.o: lista_enlazada.cpp lista_enlazada.h
	$(CXX) $(CXXFLAGS) -c lista_enlazada.cpp

stopwords.o: stopwords.cpp stopwords.h
	$(CXX) $(CXXFLAGS) -c stopwords.cpp

clean:
	rm -f $(OBJ) $(EXEC)
