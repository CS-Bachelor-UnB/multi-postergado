#
# ------------- DEFINES VARIABLES ------------------- #
#
CC = gcc
CFLAGS = -g -Wall -Iinclude

#
# ------------- TARGETS DIRECTORIES ---------------- #
#
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
EXECS = escalonador executa_postergado fattree torus sleep
# include hypercube when it's done
LIST = $(addprefix $(BIN), $(EXECS))

#
# ------------- DEFINES THE COMPILATION STEPS -------------- #
#
# .PHONY:	depend clean

all: 	$(LIST)
		@echo Source files have been successfully compiled

$(BIN)%:	$(SOURCE)%.c | BIN_DIR
	$(CC) $(INCLUDES) $< $(CFLAGS) -o $@

BIN_DIR:
	mkdir $(BIN)
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