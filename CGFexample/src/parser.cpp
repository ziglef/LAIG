#include "Parser.h"

char *endGame( int **board ){

	char *result = (char *)malloc(sizeof(char) * (128));
	char *itoaaux = (char *)malloc(sizeof(char) * 65);
	strcpy(result, "endGame(");
	
	strcat(result, cmatrix2pllist(board));
	strcat(result, ").\n");
	
	return result;
}

char *validateMove( int line, int column, int Dline, int Dcolumn ){

	char *result = (char *)malloc(sizeof(char) * (128));
	char *itoaaux = (char *)malloc(sizeof(char) * 65);
	strcpy(result, "validateMove(");
	
	itoa(line, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(column, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(Dline, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(Dcolumn, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ").\n");
	
	return result;
}

char *possibleMoves( int line, int column ){

	char *result = (char *)malloc(sizeof(char) * (128));
	char *itoaaux = (char *)malloc(sizeof(char) * 65);
	strcpy(result, "possibleMoves(");
	
	itoa(line, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(column, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ").\n");
	
	return result;
}

char *moveComputer( int line, int column, int random ){

	char *result = (char *)malloc(sizeof(char) * (128));
	char *itoaaux = (char *)malloc(sizeof(char) * 65);
	strcpy(result, "moveComputer(");
	
	itoa(line, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(column, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ",");
	
	itoa(random, itoaaux, 10);
	strcat(result, itoaaux);
	strcat(result, ").\n");
	
	return result;
}

// Transforms an 8*8 board into a string ready to be parsed by prolog
char *cmatrix2pllist( int **src ){
	// 146 - the number of characters for the structure above +1 for '\0'
	char *pllist = (char *)malloc(sizeof(char) * 146);
	int i, j;
	
	// Prepare the beggining of the string
	pllist[0] = '[';
	
	for(i=0; i<8; i++){
		pllist[1+(i*18)] = '[';
		for(j=0; j<8; j++){
			pllist[2+(i*18)+(j*2)] = (char)src[i][j]+48;
			pllist[3+(i*18)+(j*2)] = ',';
		}
		pllist[17+(i*18)] = ']';
		if( i != 7 ) pllist[18+(i*18)] = ',';
	}
	
	pllist[144] = ']';
	pllist[145] = '\0';
	return pllist;
}

// Transforms a Pair ex.:[1,2] of prolog values into two variables
void pair2variable( char *pair, int *line, int *column ){
	*line = (int)pair[1]-48;
	*column = (int)pair[3]-48;
}

// Takes a line of pairs of coordinates and parses them
int *line2results( char *line, int *resultsLength ){

	int *result, i;
	*resultsLength = (strlen(line)/6)*2;
	
	result = (int *)malloc(sizeof(int) * (*resultsLength * 2));
	
	for(i=0; i<(*resultsLength)/2; i++)
		pair2variable( (line+(1+(i*6))), &(result[i*2]), &(result[i*2+1]) );

	return result;
}
/*
// Testing Purposes the above functions
int main(){

	// Matrix parse test
	int **matrix = (int **)malloc(sizeof(int *)*8);
	int i,j;
	
	for(i=0; i<8; i++)
		matrix[i] = (int *)malloc(sizeof(int)*8);
		
	for(i=0; i<8; i++)
		for(j=0; j<8; j++)
			matrix[i][j] = 1;
			
	char *pllist = cmatrix2pllist( matrix );
	
	printf("Here's your starting list:\n");
	for(i=0; i<8; i++){
		printf("Line %d: ", i+1);
		for(j=0; j<8; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("There's your final list:\n%s\n", pllist);

	// Pair parse test
	printf("Here's a pair:\n[1,1]\n");
	
	int line=0, column=0;
	pair2variable( "[1,1]", &line, &column);
	
	printf("Here are the results for the parsing of that pair:\n%d %d\n", line, column);
	
	// Line parse test
	printf("Here are your original lines:\n1: [[1,1]]\n2: [[1,1],[1,1]]\n3: [[1,1],[1,1],[1,1]]\n4: [[1,1],[1,1],[1,1],[1,1]]\n");
	
	printf("Here's the parsing result of the lines:\n");
	
	int *result1, result1length;
	result1 = line2results( "[[1,1]]", &result1length );
	printf("Line 1: ");
	for(i=0; i<result1length; i++)
		printf("%d ", result1[i]);
	printf("\n");
	
	int *result2, result2length;
	result2 = line2results( "[[1,1],[1,1]]", &result2length );
	printf("Line 2: ");
	for(i=0; i<result2length; i++)
		printf("%d ", result2[i]);
	printf("\n");
	
	int *result3, result3length;
	result3 = line2results( "[[1,1],[1,1],[1,1]]", &result3length );
	printf("Line 3: ");
	for(i=0; i<result3length; i++)
		printf("%d ", result3[i]);
	printf("\n");
	
	int *result4, result4length;
	result4 = line2results( "[[1,1],[1,1],[1,1],[1,1]]", &result4length );
	printf("Line 4: ");
	for(i=0; i<result4length; i++)
		printf("%d ", result4[i]);
	printf("\n");
	
	return 0;
}
*/