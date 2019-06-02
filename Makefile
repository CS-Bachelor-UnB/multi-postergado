#
# ------------- DEFINES VARIABLES ------------------- #
#
CC = gcc
CFLAGS = -g -Wall -Iinclude

#
# ------------- TARGETS DIRECTORIES ---------------- #
#
ROOT_DIR := $(realpath ./)
INCLUDES =./include/data_structures.h
BIN =./bin/
SOURCE =./source/

# > library paths
# LFALGS = -L./lib

# > custom libraries to link
# LIBS = -lcustom_lib1 -lcustom_lib2 ...

#
# ------------- DEFINES THE EXECUTABLE FILES -------------- #
#
EXECS = escalonador executa_postergado fattree torus hypercube sleeps30
LINKS = escalonador executa_postergado fattree torus hypercube
# include hypercube when it's done
LIST = $(addprefix $(BIN), $(EXECS))
LIST_LINKS = $(addprefix $(ROOT_DIR)/, $(LINKS))

#
# ------------- DEFINES THE COMPILATION STEPS -------------- #
#
# .PHONY:	depend clean

all: 	$(LIST)
		@echo Source files have been successfully compiled

$(BIN)%:	$(SOURCE)%.c | BIN_DIR
	$(CC) $(INCLUDES) $< $(CFLAGS) -o $@


links:	$(LIST_LINKS)
		@echo Symbolic links for main executables have been created in root folder

$(ROOT_DIR)%:	$(BIN)%
	ln -s $< $@



#
# ------------- BINDING '.c' TO '.o's ---------------------- #
#
# .c.o:
# 		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# clean:
#         $(RM) *.o *~ $(MAIN)

# depend: $(SOURCE)
# 		makedepend $(INCLUDES) $^
clean:	$(LIST)
	rm -f $(LIST)

BIN_DIR:
	mkdir -p $(BIN)