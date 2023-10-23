COMP = g++
FLAGS = -Wall -pedantic -std=c++17
LINK = g++

LIB=-lstdc++fs

# Helpers
HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

# All - compile, create documentation using Doxygen
.PHONY: all
all: compile doc
#--------------------------------------------------------------------------------------

# Run - run compiled application
.PHONY: run
run: compile
		./chladja4
#--------------------------------------------------------------------------------------

# valgrind - run with valgrind
.PHONY: valgrind
valgrind: compile
		valgrind ./chladja4 --track-origins=yes -s
#--------------------------------------------------------------------------------------

# Compile - compile the application
.PHONY: compile
compile: chladja4
#--------------------------------------------------------------------------------------

# Test - running shell script
.PHONY: test
test:
		./tests/testAll.sh
#--------------------------------------------------------------------------------------

# Linking all the .o files together ($^ -> comma separated prerequisites, $@ -> target)
chladja4 : $(OBJECTS)
		mkdir -p build
		$(LINK) $^ -o chladja4 $(LIB)
#--------------------------------------------------------------------------------------

# Compiling all the src/*.cpp into build/*.o ($< -> first of prerequisites)
build/%.o: src/%.cpp
		mkdir -p build
		$(COMP) $(FLAGS) $< -c -o $@ $(LIB)
#--------------------------------------------------------------------------------------

# Generate documentation using Doxygen
doc : Doxyfile $(HEADERS)
		doxygen Doxyfile
#--------------------------------------------------------------------------------------

# Cleaning everything
.PHONY: clean
clean:
		rm -rf chladja4 build doc 2> /dev/null
#--------------------------------------------------------------------------------------


# Dependencies
CAIPlayer.o: src/CAIPlayer.cpp src/CAIPlayer.h src/CPlayer.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CCardDeck.h \
 src/CCard.h src/CBaseChange.h src/CChangeEffect.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CCommandHandler.h
CBaseChange.o: src/CBaseChange.cpp src/CBaseChange.h src/CChangeEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CEffect.h
CBase.o: src/CBase.cpp src/CBase.h
CCard.o: src/CCard.cpp src/CCard.h src/CBaseChange.h src/CChangeEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CRefillEffect.h
CCardDeck.o: src/CCardDeck.cpp src/CCardDeck.h src/CCard.h \
 src/CBaseChange.h src/CChangeEffect.h src/CPlayerInfo.h src/CBase.h \
 src/CColorizer.h src/CEffect.h src/CResourceChange.h src/CUnitChange.h \
 src/EEffectType.h src/CCardSwap.h
CCardSwap.o: src/CCardSwap.cpp src/CCardSwap.h src/CEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h
CChangeEffect.o: src/CChangeEffect.cpp src/CChangeEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CEffect.h
CColorizer.o: src/CColorizer.cpp src/CColorizer.h
CCommandHandler.o: src/CCommandHandler.cpp src/CCommandHandler.h
CGame.o: src/CGame.cpp src/CGame.h src/CLocalPlayer.h src/CPlayer.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CCardDeck.h \
 src/CCard.h src/CBaseChange.h src/CChangeEffect.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CInterface.h src/CCommandHandler.h src/CAIPlayer.h \
 src/EGameType.h
CInterface.o: src/CInterface.cpp src/CInterface.h src/CPlayer.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CCardDeck.h \
 src/CCard.h src/CBaseChange.h src/CChangeEffect.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CCommandHandler.h
CLocalPlayer.o: src/CLocalPlayer.cpp src/CLocalPlayer.h src/CPlayer.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CCardDeck.h \
 src/CCard.h src/CBaseChange.h src/CChangeEffect.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CInterface.h src/CCommandHandler.h
CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CPlayerInfo.h src/CBase.h \
 src/CColorizer.h src/CCardDeck.h src/CCard.h src/CBaseChange.h \
 src/CChangeEffect.h src/CEffect.h src/CResourceChange.h \
 src/CUnitChange.h src/EEffectType.h src/CCardSwap.h
CPlayerInfo.o: src/CPlayerInfo.cpp src/CPlayerInfo.h src/CBase.h
CRefillEffect.o: src/CRefillEffect.cpp src/CRefillEffect.h src/CEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h
CResourceChange.o: src/CResourceChange.cpp src/CResourceChange.h \
 src/CChangeEffect.h src/CPlayerInfo.h src/CBase.h src/CColorizer.h \
 src/CEffect.h
CUnitChange.o: src/CUnitChange.cpp src/CUnitChange.h src/CChangeEffect.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CEffect.h
main.o: src/main.cpp src/CGame.h src/CLocalPlayer.h src/CPlayer.h \
 src/CPlayerInfo.h src/CBase.h src/CColorizer.h src/CCardDeck.h \
 src/CCard.h src/CBaseChange.h src/CChangeEffect.h src/CEffect.h \
 src/CResourceChange.h src/CUnitChange.h src/EEffectType.h \
 src/CCardSwap.h src/CInterface.h src/CCommandHandler.h src/CAIPlayer.h \
 src/EGameType.h
