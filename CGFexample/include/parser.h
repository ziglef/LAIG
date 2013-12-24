#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// These methods prepare the string to use with prolog
char *endGame( int **board );
char *validateMove( int line, int column, int Dline, int Dcolumn );
char *possibleMoves( int line, int column );
char *moveComputer( int line, int column, int random );

// Transforms an 8*8 board into a string ready to be parsed by prolog
char *cmatrix2pllist( int **src );

// Transforms a Pair ex.:[1,2] of prolog values into two variables
void pair2variable( char *pair, int *line, int *column );

// Takes a line of pairs of coordinates and parses them
int *line2results( char *line, int *resultsLength );