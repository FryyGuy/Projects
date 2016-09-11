/*
*	This program demonstrates a rudimentary file parser that checks a file
*	for basic syntax errors. Functions are declared to return what type of
*	error occurred, as well as what line it occurred on
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Macro for length of the array
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

// number of max characters per line
const int MAX_LENGTH = 100;

// ENUMS FOR ERROR TYPES
const int PARANTHESES_ERR = 1;
const int SEMICOLON_ERR   = 2;
const int BRACE_ERR       = 3;
const int COMMENT_ERR     = 4;
const int BRACKET_ERR     = 5;
const int SINGLE_Q_ERR    = 6;
const int DOUBLE_Q_ERR    = 7;
const int NO_ERROR		  = 8;

// FUNCTION PROTOTYPES
int  checkSyntax(string);
void checkLines(string, int[], int[]);
bool paranError(int);					// error ID: 1
bool semicolonError(int);				// error ID: 2
bool braceError(int);					// error ID: 3
bool commentError(int);					// error ID: 4
bool bracketError(int);					// error ID: 5
bool singleQuoteError(int);				// error ID: 6
bool doubleQuoteError(int);				// error ID: 7


// Ints representing total symbols for each type
int totalParan   = 0;
int totalSemi    = 0;
int totalComment = 0;
int totalBrace   = 0;
int totalBracket = 0;
int totalSingleQ = 0;
int totalDoubleQ = 0;

int main()
{
	// int arrays for possible errors and the lines the occur on
	int linesOfError[MAX_LENGTH];
	int errorForLines[MAX_LENGTH];
	               
	// The file to open
	ifstream fptr;
	fptr.open("TempFile.txt", ios_base::in);

	//FILE * fptr = fopen("TempFile.txt", "r");
	
	if (fptr)
	{
		string line;

		while (getline(fptr, line))
		{
			// check all lines for syntax errors
			checkLines(line, linesOfError, errorForLines);
		}
	}

	fptr.close();

	cout << totalSemi << endl << endl;

	system("pause");
	
	// delete all pointers
}

//------------------------------------------------------------------------------------------
/// @Description - the checkSyntax function will open a file, gather all amounts of all syntax
///				   related symbols, determine if any symbols are unbalanced using the check methods
///				   and return an int determining what type of error occurred.
///				   return of 0 indicates line is syntactically correct
///				   Examples include: unbalanced parantheses, braces, missing semicolons etc.
///
/// @param[in] <line>  - The current line in the file 
/// @return    <none> 
//------------------------------------------------------------------------------------------
int checkSyntax(string line)
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
	for (int i = 0; i < line.length(); i++)
	{
		// check to see if the line begins with '#' if so skip it
		if (line.at(i) == '#')
			continue;

		// check to see if line[i] is '(', ')', ';', '[', ']', ' ' ', ' " '
		if (line.at(i) == '(' || line.at(i) == ')')
			totalParan++;
		else if (line.at(i) == ';')
			totalSemi++;
		else if (line.at(i) == '\\' && i++ != line.length() - 1)
		{
			if (line.at(i++) == '\\')
				totalComment++;
		}
		else if (line.at(i) == '}' || line.at(i) == '{')
			totalBrace++;
		else if (line.at(i) == '[' || line.at(i) == ']')
			totalBracket++;
		else if (line.at(i) == '\'')
			totalSingleQ++;
		else if (line.at(i) == '\"')
			totalDoubleQ++;
	}

	//update totals
	if (paranError(totalParan))
		syntaxErrorType = PARANTHESES_ERR;
	else if (semicolonError(totalSemi))
		syntaxErrorType = SEMICOLON_ERR;
	else if (braceError(totalBrace))
		syntaxErrorType = BRACE_ERR;
	else if (commentError(totalComment))
		syntaxErrorType = COMMENT_ERR;
	else if (bracketError(totalBracket))
		syntaxErrorType = BRACKET_ERR;
	else if (singleQuoteError(totalSingleQ))
		syntaxErrorType = SINGLE_Q_ERR;
	else if (doubleQuoteError(totalDoubleQ))
		syntaxErrorType = DOUBLE_Q_ERR;
	else
		syntaxErrorType = NO_ERROR;


	return syntaxErrorType;
}

//------------------------------------------------------------------------------------------
/// @Description - checkLines will check all lines of a file calling checkSyntax to determine 
///                a syntax eror. Int arrays will be passed in to store the error that occurred
///				   as well as what line the error occurred at. 
/// 
/// @param[in] <line>	      - C string pertaining to the current line in the file
/// @param[in] <lineOfError>  - Array that stores what lines errors occurred at
/// @param[in] <errorForLine> - Array that holds the error that occurred at line i
/// @return    <none>
//------------------------------------------------------------------------------------------
void checkLines(string line, int * lineOfError, int * errorForLine)
{
	// variables for line, the error type, and line number
	int  error = 0;
	int  tempLineNumber = 0;

	string lines[MAX_LENGTH];

	// get the current line and store it in line
	if (!line.empty())
	{
		// determine if a syntax error occured
		error = checkSyntax(line);

		// increment line number of error only if an error occurs
		// store the error for the line, and the line the error occurred on.
		if (error)
		{
			lineOfError[tempLineNumber] = tempLineNumber;
			errorForLine[tempLineNumber] = error;
			lines[tempLineNumber] = line;
			tempLineNumber++;
		}
	}

	// print out all errors and their lines
	for (int i = 0; i < LENGTH(lineOfError); i++)
	{
		printf("Error at line %d: %s\n", lineOfError[i], lines[i].c_str());
		printf("Error Type: %d\n\n", errorForLine[i]);
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