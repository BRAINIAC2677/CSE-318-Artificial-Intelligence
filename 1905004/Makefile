CXX=g++
CXXFLAGS=

all: main

GameState.o: GameState.cpp
	$(CXX) $(CXXFLAGS) -c GameState.cpp

Heuristic.o: Heuristic.cpp
	$(CXX) $(CXXFLAGS) -c Heuristic.cpp

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

GameAnalytics.o: GameAnalytics.cpp 
	$(CXX) $(CXXFLAGS) -c GameAnalytics.cpp

GamePlay.o: GamePlay.cpp
	$(CXX) $(CXXFLAGS) -c GamePlay.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

main: main.o GameState.o Heuristic.o Game.o GameAnalytics.o GamePlay.o
	@ $(CXX) $(CXXFLAGS) -o $@ $^

run: main
	@ ./main

clean:
	@ rm -f *.o main

