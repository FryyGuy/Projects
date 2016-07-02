#include <stdio.h>
#include <cmath>

// This Program demonstrates the function htoi(s)
// which converts a string of hexadecmial digits
// into its equivalent integer form

// Macro to determine max length of a string
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

//prototype
int htoi(char[]);
int determineValue(char);

int main()
{
	char number[] = "0x1";

	int sum = htoi(number);

	printf("%d\n", sum);

	return 0;
}

int htoi(char string[])
{
	// sum to return
	int sum = 0;
	int position = 0;

	// determine if the string begins with 0x or 0X
	// Since x or X is the second character,
	// we can either begin at position 0 or 2
	if (string[1] == 'x' || string[1] == 'X')
		position = 2;

	for (int i = position; i < LENGTH(string); i++)
	{
		sum += determineValue(string[i]);
	}

	return sum;
}

int determineValue(char c)
{
	int val = 0;

	switch (c)
	{
		case '0':
			val = pow(16, 0);
			break;
		case '1':
			val = pow(16, 1);
			break;
		case '2':
			val = pow(16, 2);
			break;
		case '3':
			val = pow(16, 3);
			break;
		case '4':
			val = pow(16, 4);
			break;
		case '5':
			val = pow(16, 5);
			break;
		case '6':
			val = pow(16, 6);
			break;
		case '7':
			val = pow(16, 7);
			break;
		case '8':
			val = pow(16, 8);
			break;
		case '9':
			val = pow(16, 9);
			break;
		case 'a':
			val = pow(16, 10);
			break;
		case 'b':
			val = pow(16, 11);
			break;
		case 'c':
			val = pow(16, 12);
			break;
		case 'd':
			val = pow(16, 13);
			break;
		case 'e':
			val = pow(16, 14);
			break;
		case 'f':
			val = pow(16, 15);
			break;
	}

	return val;
}