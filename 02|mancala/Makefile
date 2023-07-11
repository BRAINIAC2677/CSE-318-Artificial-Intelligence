all: main

GameState.o: GameState.cpp
	g++ -c GameState.cpp

Heuristic.o: Heuristic.cpp
	g++ -c Heuristic.cpp

Game.o: Game.cpp
	g++ -c Game.cpp

GameAnalytics.o: GameAnalytics.cpp 
	g++ -c GameAnalytics.cpp

GamePlay.o: GamePlay.cpp
	g++ -c GamePlay.cpp

main.o: main.cpp
	g++ -c main.cpp

main: main.o GameState.o Heuristic.o Game.o GameAnalytics.o GamePlay.o
	@ g++ -o $@ $^

run: main
	@ ./main

clean:
	@ rm -f *.o main

