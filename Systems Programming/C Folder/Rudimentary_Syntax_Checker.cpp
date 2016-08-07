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
int checkSyntax(char []);
int checkLines(FILE * fptr, int &);
bool paranError(int);					// error ID: 1
bool semicolonError(int);				// error ID: 2
bool braceError(int);					// error ID: 3
bool commentError(int);					// error ID: 4
bool bracketError(int);					// error ID: 5
bool singleQuoteError(int);				// error ID: 6
bool doubleQuoteError(int);				// error ID: 7

int main()
{
	// The file to open
	FILE * fptr = fopen("C:\\Users\\\"Matt Fry\"\\Desktop\\TempFile.txt", "w");
}

//------------------------------------------------------------------------------------------
/// @Description - the checkSyntax function will open a file, gather all amounts of all syntax
///				   related symbols, determine if any symbols are unbalanced using the check methods
///				   and return an int determining what type of error occurred.
///				   return of 0 indicates line is syntactically correct
///				   Examples include: unbalanced parantheses, braces, missing semicolons etc.
///
/// @param[in] <fptr>  - pointer to the file to parse
/// @return    <none> 
//------------------------------------------------------------------------------------------
int checkSyntax(char line[])
{
	// int for type of snytax error
	int  syntaxErrorType = -1;

	// Ints representing how many of each possible symbol is on a line
	int numParan   = 0;
	int numSemi    = 0;
	int numComment = 0;
	int numBrace   = 0;
	int numBracket = 0;
	int numSingleQ = 0;
	int numDoubleQ = 0;

	// loop over the line, and get a count of each symbol
	for (int i = 0; i < LENGTH(line) - 1; i++)
	{
		// check to see if line[i] is '(', ')', ';', '[', ']', ' ' ', ' " '
		if (line[i] == '(' || line[i] == ')')
			numParan++;
		else if (line[i] == ';')
			numSemi++;
		else if (line[i] == '\\' && i++ != (LENGTH(line) - 1))
		{
			if (line[i++] == '\\')
				numComment++;
		}
		else if (line[i] == '}' || line[i] == '{')
			numBrace++;
		else if (line[i] == '[' || line[i] == ']')
			numBracket++;
		else if (line[i] == '\'')
			numSingleQ++;
		else if (line[i] == '\"')
			numDoubleQ++;
	}

	return syntaxErrorType;
}

//------------------------------------------------------------------------------------------
/// @Description - checkLines will check all lines of a file calling checkSyntax to determine 
///                a syntax eror. An int will be returned determiningg what line the error occured on.
/// 
/// @param[in] <fptr>	 - a pointer to the file we're checking
/// @param[in] <lineNum> - The line where the error occurs
/// @return    <bool>	 - bool determining if the lines in a file are syntactically correct.
///						   true = correct, false = not correct.
//------------------------------------------------------------------------------------------
int checkLines(FILE * fptr, int &lineNum)
{
	// variables for line, the error type, and line number
	char line[MAX_LENGTH];
	int  error          = 0;
	int  tempLineNumber = 0;
	
	// while we have not reached end of file
	while (!feof(fptr))
	{
		// get the current line and store it in line
		if (fgets(line, MAX_LENGTH, fptr) != nullptr)
		{
			// determine if a syntax error occured
			error = checkSyntax(line);

			// increment line number of error only if an error occurs
			if (error)
				tempLineNumber++;
		}
	}

	// close the file
	fclose(fptr);

	// store line
	lineNum = tempLineNumber; 

	if (error)
		return error;
	else
	{
		lineNum = -1;
		return 0;
	}
		
}


//------------------------------------------------------------------------------------------
/// @Description -  The various 'Error' functions determine if the int passed % 2 == 0
///					in this way we can determine if a syntax error occurs at a certain symbol
///
/// @param[in] <num>  - the number of syntactical items on each line
/// @return    <bool> - return true if there is an error with the particular symbol, false otherwise 
//------------------------------------------------------------------------------------------
bool paranError(int numP)
{
	if (numP % 2 == 0)
		return false;
	else
		return true;
}

bool semicolonError(int numSc)
{
	if (numSc % 2 == 0)
		return false;
	else
		return true;
}

bool braceError(int numB)
{
	if (numB % 2 == 0)
		return false;
	else
		return true;
}

bool commentError(int numC)
{
	if (numC % 2 == 0)
		return false;
	else
		return true;
}

bool bracketError(int numB)
{
	if (numB % 2 == 0)
		return false;
	else
		return true;
}

bool singleQuoteError(int numSq)
{
	if (numSq % 2 == 0)
		return false;
	else
		return true;
}

bool doubleQuoteError(int numDq)
{
	if (numDq % 2 == 0)
		return false;
	else
		return true;
}