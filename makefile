#######################################################
#
#
#######################################################

# COMPILER FLAGS
# -Wall to display all warnings
COMPILER_FLAGS = -w
# COMPILER_FALGS = -Wall

# OS is cap senstive
ifeq ($(OS), Windows_NT)

	# Define the compiler
	CC = gcc

	#WINDOWS SOURCE DIRECTORY
	SOURCE_PATHS = $(CURDIR)\src

	#SDL_MIXER INCLUDE DIRECTION
	SDL_MIXER_INCLUDE = C:\DevLib\SDL2_mixer-2.8.0\x86_64-w64-mingw32\include\SDL2

	#WINDOWS INCLUDE DIRECTORY
	INCLUDE_PATHS = -IC:\DevLib\SDL2-2.28.4\x86_64-w64-mingw32\include\SDL2 -I$(CURDIR)\include -I$(SDL_MIXER_INCLUDE)

	#SDL_TFF INCLUDE DIRECTORY
	#SDL_TTF_INCLUDE = C:\DevLib\SDL2_ttf-2.20.2\i686-w64-mingw32\include\SDL2

	#SDL_TFF LIB DIRECTORY
	#SDL_TTF_LIB = C:\DevLib\SDL2_ttf-2.20.2\i686-w64-mingw32\lib

	SDL_MIXER_LIB = C:\DevLib\SDL2_mixer-2.8.0\x86_64-w64-mingw32\lib

	#WINDOWS LIB DIRECTORY
	LIB_PATHS = -LC:\DevLib\SDL2-2.28.4\x86_64-w64-mingw32\lib -L$(SDL_MIXER_LIB) -L$(CURDIR)\lib 

	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer #-lSDL2_ttf

	CLEAN = del
	EXECUTABLES = *.exe

else

	# Define the compiler
	CC = gcc

	#MAC INCLUDE DIRECTORY
	INCLUDE_PATHS = -I/usr/local/include/SDL2

	#MAC LIB DIRECTORY
	LIB_PATHS = -L/usr/local/lib

	#MAC Linker FLAGS
	LINKER_FLAGS = -lSDL2main -lSDL2

	CLEAN = rm
	EXECUTABLES = retroWin retroFileUtil

endif

OBJS =  $(SOURCE_PATHS)\pckman_main.c \
$(SOURCE_PATHS)\pckman_utils.c \
$(SOURCE_PATHS)\pckman_puckman.c \
$(SOURCE_PATHS)\pckman_game.c \
$(SOURCE_PATHS)\pckman_audio.c

OBJ_NAME = puckman

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIB_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.PHONY : clean
clean :
	$(CLEAN) $(EXECUTABLES)