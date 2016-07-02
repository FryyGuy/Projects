/*
*	This program demonstrates a rudimentary file parser that checks a file
*	for basic syntax errors. Functions are declared to return what type of
*	error occurred, as well as what line it occurred on
*/
#include <stdio.h>

// Macro for length of the array
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

// number of max characters per line
const int MAX_LENGTH = 100;

// FUNCTION PROTOTYPES
void checkSyntax(FILE *, char[]);
bool checkLine(char[]);
int lineOfError();
bool paranError();
bool semicolonError();
bool braceError();
bool commentError();
bool bracketError();
bool singleQuoteError();
bool doubleQuoteError();

int main()
{
	// The file to open
	FILE * fptr = fopen("C:\\Users\Matt Fry\Desktop\TempFile.txt", "w");
}

//------------------------------------------------------------------------------------------
/// @Description - the checkSyntax function will open a file, and check 
///				   the file for rudimentary syntax errors
///				   Examples include: unbalanced parantheses, braces, missing semicolons etc.
///
/// @param[in] <fptr>  - pointer to the file to parse
/// @param[in] <line>  - the current line of the file
//------------------------------------------------------------------------------------------
void checkSyntax(FILE * fptr, char line[])
{	
	// Ints representing how many of each possible symbol is on a line
	int numParan   = 0;
	int numSemi    = 0;
	int numComment = 0;
	int numBracket = 0;
	int numSingleQ = 0;
	int numDoubleQ = 0;

	// loop over the line, and get a count of each symbol
	for (int i = 0; i < LENGTH(line); i++)
	{
		// check to see if line[i] is '(', ')', ';', '[', ']', ' ' ', ' " '

	}
}

//------------------------------------------------------------------------------------------
/// 
//------------------------------------------------------------------------------------------