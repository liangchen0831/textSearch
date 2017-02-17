CXX = g++
# CXX = clang++

CXXFLAGS = -Wall -Wno-uninitialized

BINARIES = seachByPsition


seachByPostion: seachByPostion.o utility.o manageDict.o guessProc.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

manageDict: mangeDict.o utility.o 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

guessProc: guessProc.o manageDict.o utility.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@




clean:
	/bin/rm -f ${BINARIES} *.o
