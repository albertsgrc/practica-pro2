pro2.exe: pro2.o Sistema.o Ranking.o Organisme.o Celula.o
	g++ -o pro2.exe pro2.o Sistema.o Ranking.o Organisme.o Celula.o
pro2.o: pro2.cpp
	g++ -c pro2.cpp -I$(INCLUDES_CPP) -D_GLIBCXX_DEBUG
Sistema.o: Sistema.cpp
	g++ -c Sistema.cpp -I$(INCLUDES_CPP) -D_GLIBCXX_DEBUG
Ranking.o: Ranking.cpp
	g++ -c Ranking.cpp -I$(INCLUDES_CPP) -D_GLIBCXX_DEBUG
Organisme.o: Organisme.cpp
	g++ -c Organisme.cpp -I$(INCLUDES_CPP) -D_GLIBCXX_DEBUG
Celula.o: Celula.cpp
	g++ -c Celula.cpp -I$(INCLUDES_CPP) -D_GLIBCXX_DEBUG
clean:
	rm *.o
	rm *.exe
