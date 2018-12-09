#include "graphic_io.h"
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define LINE 0
#define CIRCLE 1
#define POLYGON 2

vector<double> pop_vars(vector< vector<double> > d, int i)
{
	vector<double> data;
	vector<double> v = d.at(i);
	for (int j = 0; j < v.size(); j++)
	{
		int xpm_coord = /*499 -*/ v.at(j);
		data.push_back(xpm_coord);
	}

	return data;
}

Shape* PostScriptIO::read()
{
	string info_line;
	vector<string> xpm_info;

	ifstream file_stream(file_string1.c_str());

	while (getline(file_stream, info_line))
	{
		if(any_of(info_line.begin(), info_line.end(), ::isdigit) || strcmp(info_line.c_str(), "stroke") == 0)
			xpm_info.push_back(info_line);
	}

	vector<int> shape_type;
	vector<string> xpm_data;
	vector< vector<double> > shape_data;

	// parse the data from the file
	string tok;
	for (int i = 0; i < xpm_info.size(); i++)
	{
		stringstream ss(xpm_info.at(i));
		
		vector<double> data;
		while (std::getline(ss, tok, ' '))
		{
			char *end;
			if (strcmp(tok.c_str(), "Line") == 0)
				shape_type.push_back(LINE);
			else if (strcmp(tok.c_str(), "Circle") == 0)
				shape_type.push_back(CIRCLE);
			else if (strcmp(tok.c_str(), "moveto") == 0)
				shape_type.push_back(POLYGON);
			else if (strcmp(tok.c_str(), "lineto") == 0)
				continue;
			else if (strcmp(tok.c_str(), "stroke") == 0) 
				break;
			else if (strcmp(tok.c_str(), "") == 0)
				continue;
			else
				data.push_back(strtof(tok.c_str(), &end));
		}

		shape_data.push_back(data);
	}

	// can return a null reference, have to handle this later
	Shape *shapes = new Shape();

	int start_idx = 0;
	for (int i = 0; i < shape_type.size(); i++)
	{
		if (shape_type.at(i) == LINE)
		{
			vector<double> d = pop_vars(shape_data, i);
			Line *l = new Line(d.at(0), d.at(1), d.at(2), d.at(3));
			if(!l->pix.empty())
				shapes->add(l);
		}
		else if (shape_type.at(i) == POLYGON)
		{
			vector<double> d = pop_vars(shape_data, i);

			Polygon *poly = new Polygon();
			for (int j = start_idx; j < shape_data.size(); j++)
			{
				if (shape_data.at(j).empty())
				{
					start_idx = ++j;
					break;
				}

				d = shape_data.at(j);
				Point *q = new Point(d.at(0), d.at(1));
				poly->vertices.push_back(q);
			}
			poly->_fill = true;
			shapes->add(poly);
		}
	}

	return shapes;
}

// writes out an xpm_string to file
void XpmIO::write(Shape *shapes)
{
	fstream out(this->file_string1.c_str(), ios::out);
	out << "static char *pic[] = {\n";

	Matrix mat;
	char info_line[50];
	int n = snprintf(info_line, 50, "\"%d %d %d %d\",\n", mat.width, mat.height, 2, 1);

	out << info_line;
	string color1 = "\"a c #ffffff\",\n";
	string color2 = "\"b c #010101\",\n";

	// build output here.
	out << color1;
	out << color2;

	for (int i = 0; i < shapes->s_list.size(); i++)
		shapes->s_list.at(i)->draw(mat);

	for (int i = 0; i < mat.data.size(); i++)
	{
		vector<double> row = mat.data.at(i);
		string pixel_line = "\"";
		for (int j = 0; j < row.size(); j++)
		{
			if (row.at(j))
				pixel_line += 'X';
			else
				pixel_line += 'a';
		}
		pixel_line += "\",\n";
		out << pixel_line.c_str();
		pixel_line.clear();
	}

	out << "};\n";
	out.close();
}

void XpmIO::write(Screen *s)
{
	fstream out(this->file_string1.c_str(), ios::out);
	out << "static char *pic[] = {\n";

	char info_line[50];
	int n = snprintf(info_line, 50, "\"%d %d %d %d\",\n", s->width, s->height, 2, 1);

	out << info_line;
	string color1 = "\"a c #ffffff\",\n";
	string color2 = "\"b c #010101\",\n";

	// build output here.
	out << color1;
	out << color2;

	s->display();

	// add code here for transformations on viewports

	// general flow is like so:
	//	we gather our shapes, and fill them to the screen.
	//	we then generate viewports that act as crop_windows on the screen
	//	display() simply draws all shapes on the screens matrix
	//	we seek to create another screen within that screen
	//	and only display all points within that screen (viewport)
	//	we then display pixels on viewport from world window perspective

	// end viewport transformation code

	for (int i = 0; i < s->data.size(); i++)
	{
		vector<double> row = s->data.at(i);
		string pixel_line = "\"";
		for (int j = 0; j < row.size(); j++)
		{
			if (row.at(j))
				pixel_line += 'b';
			else
				pixel_line += 'a';
		}
		pixel_line += "\",\n";
		out << pixel_line.c_str();
		pixel_line.clear();
	}

	out << "};\n";
	out.close();
}

void XpmIO::write(WorldWindow *ww)
{
	fstream out(this->file_string1.c_str(), ios::out);
	out << "static char *pic[] = {\n";

	char info_line[50];
	int n = snprintf(info_line, 50, "\"%d %d %d %d\",\n", ww->viewport->width, ww->viewport->height, 4, 1);

	out << info_line;
	string background = "\"a c #000000\",\n";

	string model1 = "\"r c #ff0000\",\n";
	string model2 = "\"g c #00ff00\",\n";
	string model3 = "\"b c #0000ff\",\n";

	
	char pic;

	//// build output here.
	out << model1;
	out << model2;
	out << model3;
	out << background;

	//// this is for 2D transforms
	////ww->transform();
	////ww->world_viewport_transform();

	vector< string > output;
	for (int i = 0; i < ww->world_window->data.size(); i++)
	{
		string pixel_line = "\"";
		for (int k = 0; k < ww->world_window->data.size(); k++)
			pixel_line += 'a';
		pixel_line += "\",\n";
		output.push_back(pixel_line);
		pixel_line.clear();
	}

	for (int i = 0; i < ww->world_window->shapes->s_list.size(); i++)
	{
		if (i == 0)
			pic = ww->colors[0];
		else if (i == 1)
			pic = ww->colors[1];
		else
			pic = ww->colors[2];
		
		Polygon3D *p3d = dynamic_cast<Polygon3D*>(ww->world_window->shapes->s_list.at(i));
		p3d->gen_edges();
		for (Line *l : p3d->poly2D->edges)
		{
			for (Point *p : l->pix)
			{
				if (p->y == ww->world_window->height)
					p->y -= 1;
				if (p->x == ww->world_window->width)
					p->x -= 1;

				string line = output.at(p->y);
				line.at(p->x + 1) = pic;
				output.at(p->y) = line;
			}
		}
	}

	for (string l : output)
		out << l;

	out << "};\n";
	out.close();
}

Shape* SmfIO::read()
{
	string info_line;
	vector<string> smf_info1;
	vector<string> smf_info2;
	vector<string> smf_info3;

	ifstream file_stream1(file_string1.c_str());
	ifstream file_stream2(file_string2.c_str());
	ifstream file_stream3(file_string3.c_str());

	while (getline(file_stream1, info_line))
	{
		if (any_of(info_line.begin(), info_line.end(), ::isdigit))
			smf_info1.push_back(info_line);
	}

	while (getline(file_stream2, info_line))
	{
		if (any_of(info_line.begin(), info_line.end(), ::isdigit))
			smf_info2.push_back(info_line);
	}

	while (getline(file_stream3, info_line))
	{
		if (any_of(info_line.begin(), info_line.end(), ::isdigit))
			smf_info3.push_back(info_line);
	}

	vector<int> shape_type;
	vector<string> smf_data;

	vector< vector<double> > vert_data1;
	vector< vector<int> > face_data1;

	vector< vector<double> > vert_data2;
	vector< vector<int> > face_data2;

	vector< vector<double> > vert_data3;
	vector< vector<int> > face_data3;

	// parse the data from the file
	string tok;
	for (int i = 0; i < smf_info1.size(); i++)
	{
		stringstream ss(smf_info1.at(i));

		vector<double> v_data;
		vector<int> f_data;
		bool v = false;
		bool f = false;

		while (std::getline(ss, tok, ' '))
		{
			char *end;
			if (strcmp(tok.c_str(), "v") == 0 && !v)
			{
				v = true;
				continue;
			}

			if (strcmp(tok.c_str(), "f") == 0 && !f)
			{
				f = true;
				continue;
			}

			if (v)
				v_data.push_back(strtof(tok.c_str(), &end));

			if (f)
				f_data.push_back(strtod(tok.c_str(), &end) - 1);
		}

		if (!v_data.empty())
			vert_data1.push_back(v_data);

		if (!f_data.empty())
			face_data1.push_back(f_data);
	}

	for (int i = 0; i < smf_info2.size(); i++)
	{
		stringstream ss(smf_info2.at(i));

		vector<double> v_data;
		vector<int> f_data;
		bool v = false;
		bool f = false;

		while (std::getline(ss, tok, ' '))
		{
			char *end;
			if (strcmp(tok.c_str(), "v") == 0 && !v)
			{
				v = true;
				continue;
			}

			if (strcmp(tok.c_str(), "f") == 0 && !f)
			{
				f = true;
				continue;
			}

			if (v)
				v_data.push_back(strtof(tok.c_str(), &end));

			if (f)
				f_data.push_back(strtod(tok.c_str(), &end) - 1);
		}

		if (!v_data.empty())
			vert_data2.push_back(v_data);

		if (!f_data.empty())
			face_data2.push_back(f_data);
	}

	for (int i = 0; i < smf_info3.size(); i++)
	{
		stringstream ss(smf_info3.at(i));

		vector<double> v_data;
		vector<int> f_data;
		bool v = false;
		bool f = false;

		while (std::getline(ss, tok, ' '))
		{
			char *end;
			if (strcmp(tok.c_str(), "v") == 0 && !v)
			{
				v = true;
				continue;
			}

			if (strcmp(tok.c_str(), "f") == 0 && !f)
			{
				f = true;
				continue;
			}

			if (v)
				v_data.push_back(strtof(tok.c_str(), &end));

			if (f)
				f_data.push_back(strtod(tok.c_str(), &end) - 1);
		}

		if (!v_data.empty())
			vert_data3.push_back(v_data);

		if (!f_data.empty())
			face_data3.push_back(f_data);
	}

	// can return a null reference, have to handle this later
	Shape *shapes = new Shape();
	Polygon3D *poly3d_1 = new Polygon3D();
	Polygon3D *poly3d_2 = new Polygon3D();
	Polygon3D *poly3d_3 = new Polygon3D();

	for (vector<double> v_d : vert_data1)
		poly3d_1->vertices3D.push_back(new Point3D(v_d.at(0), v_d.at(1), v_d.at(2)));

	for (vector<int> v_f : face_data1)
		poly3d_1->faces.push_back(v_f);

	for (vector<double> v_d : vert_data2)
		poly3d_2->vertices3D.push_back(new Point3D(v_d.at(0), v_d.at(1), v_d.at(2)));

	for (vector<int> v_f : face_data2)
		poly3d_2->faces.push_back(v_f);

	for (vector<double> v_d : vert_data3)
		poly3d_3->vertices3D.push_back(new Point3D(v_d.at(0), v_d.at(1), v_d.at(2)));

	for (vector<int> v_f : face_data3)
		poly3d_3->faces.push_back(v_f);

	shapes->add(poly3d_1);
	shapes->add(poly3d_2);
	shapes->add(poly3d_3);

	return shapes;
}
