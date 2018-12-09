#pragma once
#include <vector>
#include <set>
#include <bitset>

using namespace std;

#define LINE_PARAMS 4
#define CIRCLE_PARAMS 6

// (x, y) coordinate, location code
//	attributes:
//		+=, -=, == : add_two, sub_two, equal 
class Point
{
public:
	double x;
	double y;

	// strictly for z-interpolation
	double z;

	// note bitset.set() has 0 as rightmost bit
	// i.e - foo[1] = 1 [0010]
	//		 foo[2] = 1 [0110]
	bitset<4> code;

	Point();
	Point(double, double);

	void compute_code(int, int);

	~Point();

	Point operator+(const Point &q)
	{
		this->x += q.x;
		this->y += q.y;

		return *this;
	}

	Point& operator+=(const Point &q)
	{
		this->x += q.x;
		this->y += q.y;

		return *this;
	}

	Point& operator-=(const Point &q)
	{
		this->x -= q.x;
		this->y -= q.y;

		return *this;
	}

	bool operator==(const Point &q)
	{
		bool ret;
		if (q.x == this->x && q.y == this->y)
			ret = true;
		else
			ret = false;

		return ret;
	}
};

class Point3D
{
public:
	double x;
	double y;
	double z;

	bitset<6> code;
	void compute_code(int);

	Point3D();
	Point3D(double, double, double);

	~Point3D() {};

	Point3D operator+(const Point3D &q)
	{
		this->x += q.x;
		this->y += q.y;
		this->z += q.z;

		return *this;
	}

	Point3D& operator+=(const Point3D &q)
	{
		this->x += q.x;
		this->y += q.y;
		this->z += q.z;

		return *this;
	}

	Point3D& operator-=(const Point3D &q)
	{
		this->x -= q.x;
		this->y -= q.y;
		this->z -= q.z;

		return *this;
	}

	bool operator==(const Point3D &q)
	{
		bool ret;
		if (q.x == this->x && q.y == this->y && q.z == this->z)
			ret = true;
		else
			ret = false;

		return ret;
	}
};

// matrix of bits representing pixels
class Matrix
{
public:
	int height;
	int width;
	
	vector< vector<double> > data;

	Matrix();
	Matrix(int, int);
	Matrix(int, int, int, int);
	Matrix(Matrix *);

	void flip(int, int);

	~Matrix();

};

// homogenous points are used for matrix-vector multiplcation
class HomogenousPoint
{
public:
	double x;
	double y;

	// used strictly for z interpolation and z buffering
	double z;
	int h_point = 1;
	int on = 0;

	HomogenousPoint() {}

	HomogenousPoint(Point *p);
	HomogenousPoint(double x, double y);
	HomogenousPoint(int x, int y, int on);

	void mult(const Matrix &m);
};

class HomogenousPoint3D
{
public:
	double x = 0;
	double y = 0;
	double z = 0;
	double h_point = 1;
	int on = 0;

	bitset<6> code;

	HomogenousPoint3D() {};
	HomogenousPoint3D(double x, double y, double z);
	HomogenousPoint3D(Point3D *p);

	double magnitude();
	void mult(const Matrix &m);
	HomogenousPoint3D* normalize();
	HomogenousPoint3D* cross(const HomogenousPoint3D &v);
	HomogenousPoint3D* cross(const HomogenousPoint3D *v);
};

// matrix of homogenous points
class HomogenousPointMatrix : public Matrix
{
public:
	vector< vector<HomogenousPoint> > mat;

	HomogenousPointMatrix(int h, int w) : Matrix(h, w) {}
	HomogenousPointMatrix(Matrix *m) : Matrix(m->height, m->width)
	{
		for (int y = 0; y < m->data.size(); y++)
		{
			vector<double> row = m->data.at(y);
			vector<HomogenousPoint> pts;
			for (int x = 0; x < row.size(); x++)
			{
				HomogenousPoint pt(x, y, row.at(x));
				pts.push_back(pt);
			}
			mat.push_back(pts);
		}
	}

	~HomogenousPointMatrix() {}

	vector< vector< double > >& to_mat();
};

// abstract drawable, for all shapes
//		+ all shapes need to be drawn.
//		+ so we create abstract base class
//		+ that can be used for polymorphism later
class IDrawable
{
public:
	int min_x, max_x;
	int min_y, max_y;
	virtual void draw(Matrix &) = 0;
};


// line
// attributes:
//		+=, -= : add_line, sub_line
//		various things like clipping and point generation
class Line : virtual public IDrawable
{
private:
	vector<Point*> dda();
	bool cohen_sutherland();
	bool cohen_sutherland3D();

public:
	Point p;
	Point q;

	int min_x = 0, max_x = 0;
	int min_y = 0, max_y = 0;

	vector<Point *> pix;

	Line();
	~Line();
	Line(Point*, Point*);
	Line(int, int, int, int);

	void draw(Matrix &);

	Line& operator+=(const Line &l);
	Line& operator-=(const Line &l);

	double slope();
	bool horizontal();

	inline void pop_pix()
	{
		this->pix = this->dda();
	};
};

class ZBuffer
{
public:
	char background = 'a';

	vector< vector<string> > frame_buffer;
	vector< vector<double> > z_buffer;

	ZBuffer();
};

class Polygon : virtual public IDrawable
{
private:
	void sutherland_hodgman(int, int, int, int);
	bool v_in(int, int, int, int, Point *);
	int gen_edges();
	bool on_edge(Point*, Line*);
	bool contains_edge(Line*);

public:
	bool _fill = false;
	int min_x = 0, max_x = 0;
	int min_y = 0, max_y = 0;

	Polygon();
	Polygon(int min_x, int max_x, int min_y, int max_y);
	Polygon(Polygon &p);

	vector<Line*> edges;
	vector<Point*> vertices;

	void draw(Matrix &);
	void fill(Matrix &);
};

class Triangle
{
public:
	vector< Point* > verts;
	vector< Line* > edges;
	Triangle(Point *a, Point *b, Point *c,
		Line *e1, Line *e2, Line *e3);
};

class Polygon3D : virtual public IDrawable
{
private:
	bool orthographic = false;
	void sutherland_hodgman(int);
	bool v_in(int, int, int, int, Point3D *);

public:
	char color;
	double front, back;

	Polygon *poly2D;

	vector< Point3D* > vertices3D;
	vector< Point* > vertices2D;

	vector< HomogenousPoint* > verticesH2D;
	vector < HomogenousPoint3D* > verticesH3D;

	vector< vector<int> > faces;
	vector<Line*> edges;
	vector<Point*> vertices;
	vector< Triangle * > triangles;

	ZBuffer *z_buf;
	vector<string> *colors;

	Polygon3D() {};

	bool cohen_sutherland();
	void gen_edges();

	void draw(Matrix &);
	void fill(Matrix &);
};

// contiainer for drawable objects
class Shape
{
public:
	vector<IDrawable*> s_list;

	~Shape()
	{}

	void add(IDrawable *d)
	{
		s_list.push_back(d);
	}

	int get_min_x();
	int get_min_y();
};

// the screen contains a matrix
// the screen has a cursor that is used for drawing things.
// the cursor indexes into the matrix
class Screen : public Matrix
{
public:
	double min_x = 0, max_x = 0;
	double min_y = 0, max_y = 0;

	Shape *shapes;

	Screen() : Matrix(499, 499) {};
	Screen(int h, int w) : Matrix(h, w) {};

	Screen(int min_x, int min_y, int max_x, int max_y, Shape *s = nullptr) : Matrix(((max_y == 0 ? 499 : max_y) - min_y), ((max_x == 0 ? 499 : max_x) - min_x))
	{
		this->min_x = min_x;
		this->max_x = max_x == 0 ? 499 : max_x;

		this->min_y = min_y;
		this->max_y = max_y == 0 ? 499 : max_y;

		this->shapes = s;

		if (shapes)
			for (IDrawable *s : shapes->s_list)
			{
				s->min_x = min_x;
				s->max_x = max_x;
				s->min_y = min_y;
				s->max_y = max_y;
			}
	};

	Screen(int h, int w, Shape *s) : Matrix(h, w)
	{
		this->shapes = s;
	};

	void display();
	void display_3D();
	void display_3D(int);
};

class Camera
{
public:
	vector<Polygon3D*> polygons;
	Shape *s;

	HomogenousPoint3D *vrp;
	HomogenousPoint3D *vpn;
	HomogenousPoint3D *vup;
	HomogenousPoint3D *prp;

	HomogenousPoint3D *n;
	HomogenousPoint3D *u;
	HomogenousPoint3D *v;

	double u_min, u_max;
	double v_min, v_max;
	double front = 0.6, back = -0.6;

	// used only for parallel projection
	int z_min;

	bool orthographic_perspective;

	Matrix *perspective;
	Matrix *view;

	Camera(double x_prp, double y_prp, double z_prp, double x_vrp, double y_vrp, double z_vrp,
		double x_vpn, double y_vpn, double z_vpn, double x_vup, double y_vup, double z_vup,
		double u_min_vrc, double v_min_vrc, double u_max_vrc, double v_max_vrc,
		bool parallel_proj);

	void project_polygons_to_3D(Screen *);
	void project_3Dpolygon_to_2D(Screen *);
};

class WorldWindow
{
public:
	double scale_factor;
	double cc_rot_deg, x_trans, y_trans;

	char colors[3] = { 'r', 'g', 'b' };

	ZBuffer *z_buf;
	Screen *world_window;
	Screen *viewport;
	Camera *camera;
	HomogenousPointMatrix *h_mat;

	vector< string > *reds;
	vector< string > *greens;
	vector< string > *blues;

	WorldWindow(int min_x_ww, int min_y_ww, int max_x_ww, int max_y_ww,
		int min_x_vp, int min_y_vp, int max_x_vp, int max_y_vp, Shape *s);

	// for 3D transforms
	WorldWindow(int min_x_vp, int min_y_vp, int max_x_vp, int max_y_vp,
		double x_prp, double y_prp, double z_prp,
		double x_vrp, double y_vrp, double z_vrp,
		double x_vpn, double y_vpn, double z_vpn,
		double x_vup, double y_vup, double z_vup,
		double u_min_vrc, double v_min_vrc, double u_max_vrc, double v_max_vrc,
		bool parallel_proj, double front, double back, Shape *s, vector<string> *reds, vector<string> *greens, vector<string> *blues);

	// this method exists simply to avoid having the constructor have like 80 billion args
	void prep_transform(double scale_factor, int cc_rot_deg, int x_trans, int y_trans);
	void transform();

	void world_viewport_transform();
	void camera_viewport_transform();

	~WorldWindow()
	{};
};
