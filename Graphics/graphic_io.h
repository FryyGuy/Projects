#pragma once
#include "graphic_structures.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum PostscriptOpts
{
	LINE = 0,
	POLYGON = 1
};

class GraphicIO
{
protected:
	string file_string1;
	string file_string2;
	string file_string3;
	
public:
	GraphicIO(string const& str) : file_string1(str)
	{}

	GraphicIO(string const& str1, string const& str2, string const& str3) 
	: file_string1(str1), file_string2(str2), file_string3(str3)
	{}
};

class XpmIO : public GraphicIO
{
public:
	XpmIO(string const& str) : GraphicIO(str)
	{}

	Shape* read();
	void write(Shape*);
	void write(Screen*);
	void write(WorldWindow*);
};

class PostScriptIO : public GraphicIO
{
public:
	PostScriptIO(string const& str) : GraphicIO(str)
	{}

	Shape* read();
	void write();
};

class SmfIO : public GraphicIO
{
public:
	SmfIO(string const &str) : GraphicIO(str)
	{}

	SmfIO(string const &str1, string const &str2, string const &str3) 
	: GraphicIO(str1, str2, str3)
	{}

	Shape *read();
};

// shell for basic IO stuff
// encapsulates IO behavior I guess...
class Shell
{
public:
	PostScriptIO ps;
	XpmIO xpm;
};
