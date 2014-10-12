C99		=	gcc -std=c99
CFLAGS	=	-Wall -pedantic -Werror
OBJ		=	version.o recover.o checkbackup.o backup.o filesummary.o time.o

version : $(OBJ)
	$(C99) $(CFLAGS) -o version $(OBJ)

%.o : %.c version.h
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f version $(OBJ)
