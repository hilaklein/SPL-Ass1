# All Targets
all: cTrace

# Tool invocations
# Executable "cTrace" depends on the files Session.o Agent.o Tree.o Graph.o main.o ContactTracer.o CycleTree.o MaxRankTree.o RootTree.o Virus.o 
cTrace: bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o bin/CycleTree.o bin/MaxRankTree.o bin/RootTree.o bin/ContactTracer.o bin/Virus.o 
	@echo 'Building target: cTrace'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o bin/CycleTree.o bin/MaxRankTree.o bin/RootTree.o bin/ContactTracer.o bin/Virus.o  
	@echo 'Finished building target: cTrace'
	@echo ' '


# Depends on the source and header files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	
# Depends on the source and header files
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

# Depends on the source and header files
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp
	
# Depends on the source and header files
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp
	
# Depends on the source and header files
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp
	
# Depends on the source and header files
bin/CycleTree.o: src/CycleTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CycleTree.o src/CycleTree.cpp
	
# Depends on the source and header files
bin/MaxRankTree.o: src/MaxRankTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MaxRankTree.o src/MaxRankTree.cpp
	
# Depends on the source and header files
bin/RootTree.o: src/RootTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RootTree.o src/RootTree.cpp
	
# Depends on the source and header files
bin/ContactTracer.o: src/ContactTracer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ContactTracer.o src/ContactTracer.cpp

# Depends on the source and header files
bin/Virus.o: src/Virus.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Virus.o src/Virus.cpp


#Clean the build directory
clean: 
	rm -f bin/*
