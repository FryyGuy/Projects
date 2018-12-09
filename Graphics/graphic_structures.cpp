#include <cmath>
#include <stdlib.h>

#include "graphic_math.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
	this->compute_code(499, 499);
}

void Point::compute_code(int height=499, int width=499)
{
	// 0010 - y in, x greater
	if (this->x >= 0 && this->x <= width && this->y >= 0 && this->y <= height)
		this->code.reset();
	if (this->x > width && this->y >= 0 && this->y <= height)
		this->code[1] = 1;
	// 1010 - x and y greater
	else if (this->x > width && this->y > height)
	{
		this->code[1] = 1;
		this->code[3] = 1;
	}
	// 1000 - x in, y greater
	else if (this->x >= 0 && this->x <= width && this->y > height)
		this->code[3] = 1;
	// 1001 - x and y less
	else if (this->x < 0 && this->y > height)
	{
		this->code[0] = 1;
		this->code[3] = 1;
	}
	// 0001 - x less, y in
	else if (this->x < 0 && this->y >= 0 && this->y <= height)
		this->code[0] = 1;
	// 0101 - x and y less
	else if (this->x < 0 && this->y < 0)
	{
		this->code[0] = 1;
		this->code[2] = 1;
	}
	// 0100 - x in, y less
	else if (this->x >= 0 && this->x <= width && this->y < 0)
		this->code[2] = 1;
	// 0110 - x in, y less
	else if (this->x > width && this->y < 0)
	{
		this->code[2] = 1;
		this->code[1] = 1;
	}
}

Point::~Point()
{

}

Point3D::Point3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->code = 000000;
}

Point3D::Point3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point3D::compute_code(int z_min=0)
{
	// non zero z_min means persepctive projection
	if (z_min)
	{
		// we're in
		if (this->x <= -1 && this->x <= 1 && this->y >= -1 && this->y <= 1 && this->z >= -1 && this->z <= 0)
			this->code.reset();
		else if (this->x < this->z)
			this->code[2] = 1;
		else if (this->x > -this->z)
			this->code[3] = 1;
		else if (this->y < this->z)
			this->code[4] = 1;
		else if (this->y > -this->z)
			this->code[5] = 1;
		else if (this->z < -1)
			this->code[1] = 1;
		else if (this->z > z_min)
			this->code[0] = 1;
	}
	else
	{
		// we're in
		if (this->x <= -1 && this->x <= 1 && this->y >= -1 && this->y <= 1 && this->z >= -1 && this->z <= 0)
			this->code.reset();
		else if (this->x < -1)
			this->code[2] = 1;
		else if (this->x > 1)
			this->code[3] = 1;
		else if (this->y < -1)
			this->code[4] = 1;
		else if (this->y > 1)
			this->code[5] = 1;
		else if (this->z < -1)
			this->code[1] = 1;
		else if (this->z > 0)
			this->code[0] = 1;
	}
}

Matrix::Matrix()
{
	this->height = 499;
	this->width = 499;

	for (int i = 0; i < this->height; i++)
	{
		vector<double> row;
		for (int j = 0; j < this->width; j++)
		{
			row.push_back(0);
		}
		this->data.push_back(row);
	}
}

Matrix::Matrix(int h, int w)
{
	this->height = h;
	this->width = w;

	for (int i = 0; i < this->height; i++)
	{
		vector<double> row;
		for (int j = 0; j < this->width; j++)
			row.push_back(0);
		this->data.push_back(row);
	}
}

Matrix::Matrix(Matrix *rhs)
{
	for (int y = 0; y < rhs->data.size(); y++)
	{
		vector<double> row_rhs = rhs->data.at(y);
		vector<double> row;
		for (int x = 0; x < row_rhs.size(); x++)
		{
			row.push_back(row_rhs.at(x));
		}
		this->data.push_back(row);
	}
}

void Matrix::flip(int y, int x)
{
	int t_x = x;
	int t_y = y;

	if (t_y == this->height)
		t_y = this->height - 1;
	if (t_x == this->width)
		t_x = this->width - 1;

	vector<double> row = this->data.at(t_y);
	row.at(t_x) = 1;
	this->data.at(t_y) = row;
}


Matrix::~Matrix()
{

}

HomogenousPoint::HomogenousPoint(Point *p)
{
	this->x = p->x;
	this->y = p->y;
	this->on = 1;
}

HomogenousPoint::HomogenousPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

HomogenousPoint::HomogenousPoint(int x, int y, int on)
{
	this->x = x;
	this->y = y;
	this->on = on;
}

void HomogenousPoint::mult(const Matrix &m)
{
	double p1_x = m.data.at(0).at(0), p1_y = m.data.at(1).at(0), p1_h = m.data.at(2).at(0);
	double p2_x = m.data.at(0).at(1), p2_y = m.data.at(1).at(1), p2_h = m.data.at(2).at(1);
	double p3_x = m.data.at(0).at(2), p3_y = m.data.at(1).at(2), p3_h = m.data.at(2).at(2);

	this->x = this->x * p1_x + this->y * p2_x + this->h_point * p3_x;
	this->y = this->x * p1_y + this->y * p2_y + this->h_point * p3_y;
	this->h_point = this->x * p1_h + this->y * p2_h + this->h_point * p3_h;
}

HomogenousPoint3D::HomogenousPoint3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

HomogenousPoint3D::HomogenousPoint3D(Point3D *p)
{
	this->x = p->x;
	this->y = p->y;
	this->z = p->z;
	this->code = p->code;
}

double HomogenousPoint3D::magnitude()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

HomogenousPoint3D* HomogenousPoint3D::normalize()
{
	double mag = this->magnitude();
	this->x = this->x / mag;
	this->y = this->y / mag;
	this->z = this->z / mag;

	return this;
}

void HomogenousPoint3D::mult(const Matrix &m)
{
	double a00 = m.data.at(0).at(0), a01 = m.data.at(0).at(1), a02 = m.data.at(0).at(2), a03 = m.data.at(0).at(3);
	double a10 = m.data.at(1).at(0), a11 = m.data.at(1).at(1), a12 = m.data.at(1).at(2), a13 = m.data.at(1).at(3);
	double a20 = m.data.at(2).at(0), a21 = m.data.at(2).at(1), a22 = m.data.at(2).at(2), a23 = m.data.at(2).at(3);
	double a30 = m.data.at(3).at(0), a31 = m.data.at(3).at(1), a32 = m.data.at(3).at(2), a33 = m.data.at(3).at(3);

	this->x = this->x * a00 + this->y * a01 + this->z * a02 + this->h_point * a03;
	this->y = this->x * a10 + this->y * a11 + this->z * a12 + this->h_point * a13;
	this->z = this->x * a20 + this->y * a21 + this->z * a22 + this->h_point * a23;
	this->h_point = this->x * a30 + this->y * a31 + this->z * a32 + this->h_point * a33;
}

HomogenousPoint3D* HomogenousPoint3D::cross(const HomogenousPoint3D &v)
{
	HomogenousPoint3D *ret = new HomogenousPoint3D();
	ret->x = this->y * v.z - this->z * v.y;
	ret->y = this->z * v.x - this->x * v.z;
	ret->z = this->x * v.y - this->y * v.x;
	ret->h_point = 0;
	return ret;
}

HomogenousPoint3D* HomogenousPoint3D::cross(const HomogenousPoint3D *v)
{
	HomogenousPoint3D *ret = new HomogenousPoint3D();
	ret->x = this->y * v->z - this->z * v->y;
	ret->y = this->z * v->x - this->x * v->z;
	ret->z = this->x * v->y - this->y * v->x;
	ret->h_point = 1;

	return ret;
}

vector< vector< double > >& HomogenousPointMatrix::to_mat()
{
	Matrix *new_mat = new Matrix(mat.size(), mat.at(0).size());
	for (int y = 0; y < mat.size(); y++)
	{
		vector<HomogenousPoint> vec = mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			if (vec.at(x).on)
				new_mat->flip(y, x);
		}
	}

	return new_mat->data;
}

void Screen::display()
{
	for (int i = 0; i < this->shapes->s_list.size(); i++)
		this->shapes->s_list.at(i)->draw(*this);
}

void Screen::display_3D()
{
	for (int i = 0; i < this->shapes->s_list.size(); i++)
	{
		Polygon3D *p3d = dynamic_cast<Polygon3D*>(this->shapes->s_list.at(i));
		p3d->draw(*this);
	}
}

void Screen::display_3D(int idx)
{
	Polygon3D *p3d = dynamic_cast<Polygon3D*>(this->shapes->s_list.at(idx));
	p3d->draw(*this);
}

void WorldWindow::prep_transform(double sf, int cc_deg_rot, int x_t, int y_t)
{
	this->scale_factor = sf;
	this->cc_rot_deg = cc_deg_rot;
	this->x_trans = x_t;
	this->y_trans = y_t;
}

void WorldWindow::transform()
{
	HomogenousPointMatrix *mat = nullptr;
	Shape *s = nullptr;

	int min_x = this->world_window->shapes->get_min_x();
	int min_y = this->world_window->shapes->get_min_y();

	s = translate_origin(this->world_window);
	this->world_window->shapes = s;
	if (scale_factor)
	{
		// optimize this to take in shapes later
		s = scale2D(this->world_window, scale_factor);
		this->world_window->shapes = s;
	}

	if (cc_rot_deg)
	{
		this->world_window->shapes = s;

		// optimize this to take in shapes later
		s = rotate2D(this->world_window, cc_rot_deg);
		this->world_window->shapes = s;
	}

	s = translate_back(this->world_window, min_x, min_y);
	this->viewport->shapes = s;

	if (x_trans || y_trans)
	{
		s = translate2D(this->viewport, x_trans, y_trans);
		this->viewport->shapes = s;
	}
}

void WorldWindow::world_viewport_transform()
{
	Shape *s = nullptr;
	double scale_x = (this->viewport->max_x - this->viewport->min_x) / (this->world_window->max_x - this->world_window->min_x);
	double scale_y = (this->viewport->max_y - this->viewport->min_y) / (this->world_window->max_y - this->world_window->min_y);

	s = translate_origin(this->world_window);
	this->viewport->shapes = s;

	s = scale2D(this->viewport, scale_x, scale_y);
	this->viewport->shapes = s;

	s = translate_back(this->viewport, this->viewport->min_x, this->viewport->min_y);
	this->viewport->shapes = s;
}

void WorldWindow::camera_viewport_transform()
{
	translate3Dto2D(viewport, 1, 1);
	scale3Dto2D(viewport, ((viewport->max_x - viewport->min_x) / 2), ((viewport->max_y - viewport->min_y) / 2));
	translate2Dfrom3D(viewport, viewport->min_x, viewport->min_y);
}

Line::Line()
{
	this->p.x = 0;
	this->p.y = 0;

	this->q.x = 0;
	this->q.y = 0;
}

Line::Line(Point *p, Point *q)
{
	this->p.x = p->x;
	this->p.y = p->y;

	this->q.x = q->x;
	this->q.y = q->y;

	this->p.compute_code(499, 499);
	this->q.compute_code(499, 499);

	if (this->cohen_sutherland())
		this->pop_pix();
}

Line::Line(int x1, int y1, int x2, int y2)
{
	this->p.x = x1;
	this->p.y = y1;

	this->q.x = x2;
	this->q.y = y2;

	this->p.compute_code(499, 499);
	this->q.compute_code(499, 499);

	if(this->cohen_sutherland())
		this->pop_pix();
}

Line::~Line()
{

}

double Line::slope()
{
	int x1 = this->p.x, y1 = this->p.y;
	int x2 = this->q.x, y2 = this->q.y;

	double s = (x2 - x1) == 0 ? 0 : (y2 - y1) / (x2 - x1);
	return s;
}

bool Line::horizontal()
{
	double m = slope();

	return m == 0 ? true : false;
}

vector<Point*> Line::dda()
{
	double m = slope();

	vector<Point*> interp_points;
	double dx, dy;
	dx = (q.x - p.x);
	dy = (q.y - p.y);

	double dir;
	if (abs(dx) >= abs(dy))
		dir = abs(dx);
	else
		dir = abs(dy);

	dx /= dir;
	dy /= dir;

	double x, y;
	x = p.x;
	y = p.y;

	double i = 0;
	while (i <= dir)
	{
		Point *interp_p = new Point(x, y);
		interp_points.push_back(interp_p);

		x += dx;
		y += dy;
		i += 1;
	}

	return interp_points;
}

// ===================================================
/// cohen-sutherland returns true if line is either valid
/// at the outset, or valid after recomputation because of
/// out-of-bound points.
///
/// returns false if the line is completely out.
// ===================================================
bool Line::cohen_sutherland()
{
	bool valid = true;
	while (true)
	{
		if ((this->p.code | this->q.code) == 0)
			break;
		else if ((this->p.code & this->q.code) != 0)
		{
			valid = false;
			break;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (this->p.code[i] ^ this->q.code[i])
				{
					// update x and y of point using point-slope form
					// recompute code
					Point t;
					int out;
					if (this->p.code[i] == 1)
					{
						t.x = p.x;
						t.y = p.y;
						t.code = p.code;
						out = 1;
					}
					else
					{
						t.x = q.x;
						t.y = q.y;
						t.code = q.code;
						out = 0;
					}

					if (t.code[3] == 1)
					{
						t.y = 499;
						t.x = p.x + (q.x - p.x) * ((t.y - p.y) / (q.y - p.y));
						t.code[3] = 0;

						t.compute_code(499, 499);
					}
					else if (t.code[1] == 1)
					{
						t.x = 499;
						t.y = p.y + (q.y - p.y) * ((t.x - p.x) / (q.x - p.x));
						t.code[1] = 0;

						t.compute_code(499, 499);
					}
					else if (t.code[0] == 1)
					{
						t.x = 0;
						t.y = p.y + (q.y - p.y) * ((t.x - p.x) / (q.x - p.x));
						t.code[0] = 0;

						t.compute_code(499, 499);
					}
					else if (t.code[2] == 1)
					{
						t.y = 0;
						t.x = p.x + (q.x - p.x) * ((t.y - p.y) / (q.y - p.y));
						t.code[2] = 0;

						t.compute_code(499, 499);
					}

					if (out)
					{
						p.x = t.x;
						p.y = t.y;
						p.code = t.code;
					}
					else
					{
						q.x = t.x;
						q.y = t.y;
						q.code = t.code;
					}
				}
			}
		}
	}

	return valid;
}

bool Line::cohen_sutherland3D()
{
	bool valid = false;
	

	return valid;
}

void Line::draw(Matrix &m)
{
	for (int j = 0; j < this->pix.size(); j++)
	{
		Point *p = this->pix.at(j);
		m.flip(p->y, p->x);
	}
}

Line& Line::operator+=(const Line &rhs)
{
	this->p += rhs.p;
	this->q += rhs.q;

	return *this;
}

Line& Line::operator-=(const Line &rhs)
{
	this->p -= rhs.p;
	this->q -= rhs.q;

	return *this;
}

void Polygon::sutherland_hodgman(int x_min, int x_max, int y_min, int y_max)
{
	Point *p = this->vertices.at(0), *q;
	for (int i = 0; i < this->vertices.size(); i++)
	{
		if (i + 1 >= this->vertices.size())
			q = this->vertices.at(0);
		else
			q = this->vertices.at(i + 1);

		Line l(p, q);
		double m = l.slope();
		if (!this->v_in(x_min, x_max, y_min, y_max, p))
		{
			double x, y;
			// left of screen
			if (p->code[0] == 1)
			{
				x = x_min;
				y = m * (x_min - p->x) + p->y;
			}

			// right of screen
			if (p->code[1] == 1)
			{
				x = x_max;
				y = m * (p->x - x_max) + p->y;
			}

			// bottom of screen
			if (p->code[2] == 1)
			{
				x = p->x + (y_max - p->y) / m;
				y = y_max;
			}

			// top of screen
			if (p->code[3] == 1)
			{
				x = p->x + (y_min - p->y) / m;
				y = y_min;
			}

			p->x = x;
			p->y = y;

			p->compute_code();
		}
		p = q;
	}
}

bool Polygon::v_in(int x_min, int x_max, int y_min, int y_max, Point *p)
{
	if (p->x < x_min || p->x > x_max || p->y < y_min || p->y > y_max)
		return false;
	else
		return true;
}

int Polygon::gen_edges()
{
	if (this->vertices.empty())
		return 0;
	else
	{
		// create edges from/to each successive point
		for (int i = 0; i < this->vertices.size(); i++)
		{
			Point *p = this->vertices.at(i);
			Point *q;

			if (i + 1 >= this->vertices.size())
				break;
			else
				q = this->vertices.at(i + 1);

			Line *l = new Line(p, q);
			if (!l->pix.empty())
				this->edges.push_back(l);
		}
	}

	return 1;
}

// determine if a point p rests on an edge l
bool Polygon::on_edge(Point *p, Line *l)
{
	for (Point *q : l->pix)
		if (p->x == q->x && p->y == q->y)
			return true;

	return false;
}

bool Polygon::contains_edge(Line *edge)
{
	for (Line *e : this->edges)
	{
		if ((int)edge->p.x == (int)e->p.x && (int)edge->p.y == (int)e->p.y
			&& (int)edge->q.x == (int)e->q.x && (int)edge->q.y == (int)e->q.y)
			return true;
	}

	return false;
}

//=================================================
//	Below are helper functions for fill
//=================================================
int get_count(int val, vector<Point*> extrema_list)
{
	int count = 0;
	for (Point *p : extrema_list)
	{
		int v = (int)p->x;
		if (v == val)
			count++;
	}

	return count;
}

Point* find_pt(int x, int y, Line *l)
{
	Point *ex = new Point();
	for (Point *p : l->pix)
		if (x == p->x && y == p->y)
			ex = p;
	return ex;
}

bool contains_pt(vector<Point*> ex_list, Point *pt)
{
	bool in = false;
	for (Point *p : ex_list)
		if (pt->x == p->x && pt->y == p->y)
			in = true;

	return in;
}

void Polygon::fill(Matrix &m)
{
	// in order to fill, we need to loop over all the vertices
	// and get our maximum bounds so that way we can make a window
	// around our polygon. This reduces runtime speed too hopefully.

	// key point location?
	int min_x = this->vertices.at(0)->x, max_x = this->vertices.at(0)->x;
	int min_y = this->vertices.at(0)->y, max_y = this->vertices.at(0)->y;
	for (Point *p : this->vertices)
	{
		if (p->x > max_x)
			max_x = p->x;
		else if (p->x < min_x)
			min_x = p->x;

		if (p->y > max_y)
			max_y = p->y;
		else if (p->y < min_y)
			min_y = p->y;
	}

	for (int y = 0; y < m.height; y++)
	{
		vector< Point* > extrema_list;
		for (Line *e : this->edges)
		{
			int min_y = e->p.y < e->q.y ? e->p.y : e->q.y;
			int max_y = e->p.y > e->q.y ? e->p.y : e->q.y;

			if (y >= min_y && y < max_y)
			{
				if ((int)e->p.y == (int)e->q.y)
					continue;
				if (y == max_y)
					continue;

				int x = (y - e->p.y) * (e->q.x - e->p.x) / (e->q.y - e->p.y) + e->p.x;
				Point *extrema = new Point(x, y);
				extrema_list.push_back(extrema);
				break;
			}
		}

		for (int i = 0; i < extrema_list.size(); i++)
		{
			for (int j = 1; j < extrema_list.size() - i - 1; j++)
			{
				if (extrema_list.at(j)->x > extrema_list.at(j + 1)->x)
				{
					Point *p = extrema_list.at(j);
					Point *q = extrema_list.at(j + 1);
					extrema_list.at(j) = q;
					extrema_list.at(j + 1) = p;
				}
			}
		}

		bool parity = false;
		vector<double> scanline = m.data.at(y);
		for (int x = 0; x < scanline.size(); x++)
		{
			int cnt = get_count(x, extrema_list);
			if (cnt % 2 == 1)
				parity = !parity;
			if (parity)
				m.flip(y, x);
		}
	}
}

Polygon::Polygon()
{

}

Polygon::Polygon(int min_x, int max_x, int min_y, int max_y)
{
	this->min_x = min_x;
	this->max_x = max_x;

	this->min_y = min_y;
	this->max_y = max_y;
}

Polygon::Polygon(Polygon &p)
{
	for (Point *_p : p.vertices)
	{
		this->vertices.push_back(_p);
	}

	for (Line *l : p.edges)
	{
		this->edges.push_back(l);
	}

	this->_fill = true;
}

void Polygon::draw(Matrix &m)
{
	if(min_x == 0 && max_x == 0 && min_y == 0 && max_y == 0)
		this->sutherland_hodgman(0, m.width, 0, m.height);
	else
		this->sutherland_hodgman(min_x, max_x, min_y, max_y);

	this->gen_edges();

	for (int i = 0; i < this->edges.size(); i++)
		this->edges.at(i)->draw(m);

	if (_fill)
		this->fill(m);
}

Triangle::Triangle(Point *a, Point *b, Point *c, Line *e1, Line *e2, Line *e3)
{
	this->verts.push_back(a);
	this->verts.push_back(b);
	this->verts.push_back(c);

	this->edges.push_back(e1);
	this->edges.push_back(e2);
	this->edges.push_back(e3);
}

void Polygon3D::gen_edges()
{
	for(int i = 0; i < this->faces.size(); i++)
	{
		vector< int > faces = this->faces.at(i);
		int f1 = faces.at(0);
		int f2 = faces.at(1);
		int f3 = faces.at(2);

		Point *v1 = this->poly2D->vertices.at(f1);
		Point *v2 = this->poly2D->vertices.at(f2);
		Point *v3 = this->poly2D->vertices.at(f3);

		Line *e1 = new Line(v1, v2);
		Line *e2 = new Line(v2, v3);
		Line *e3 = new Line(v3, v1);

		Triangle *tri = new Triangle(v1, v2, v3, e1, e2, e3);
		this->triangles.push_back(tri);

		this->poly2D->edges.push_back(e1);
		this->poly2D->edges.push_back(e2);
		this->poly2D->edges.push_back(e3);
	}
}

bool Polygon3D::v_in(int x_min, int y_min, int x_max, int y_max, Point3D *p)
{
	bool valid = false;
	return valid;
}

bool Polygon3D::cohen_sutherland()
{
	bool valid = true;
	for (int i = 0; i < this->vertices3D.size(); i++)
	{
		if (i + 1 == this->vertices3D.size())
			break;

		HomogenousPoint3D *p = this->verticesH3D.at(i);
		HomogenousPoint3D *q = this->verticesH3D.at(i + 1);

		if ((p->code & q->code) != 0)
			valid = false;
	}

	return valid;
}

void Polygon3D::sutherland_hodgman(int z_min=0)
{
	
}

void Polygon3D::draw(Matrix &m)
{
	this->gen_edges();
	for (int i = 0; i < this->poly2D->edges.size(); i++)
		this->poly2D->edges.at(i)->draw(m);
} 

void Polygon3D::fill(Matrix &m)
{
	// in order to fill, we need to loop over all the vertices
	// and get our maximum bounds so that way we can make a window
	// around our polygon. This reduces runtime speed too hopefully.

	for (int y = 0; y < m.height; y++)
	{
		vector< Point* > extrema_list;
		double za, zb, zp;
		for (Triangle *tri : this->triangles)
		{
			for (Line *e : tri->edges)
			{
				int min_y = e->p.y < e->q.y ? e->p.y : e->q.y;
				int max_y = e->p.y > e->q.y ? e->p.y : e->q.y;

				if (y >= min_y && y < max_y)
				{
					if ((int)e->p.y == (int)e->q.y)
						continue;
					if (y == max_y)
						continue;

					Point *a = tri->verts.at(0), *b = tri->verts.at(1), *c = tri->verts.at(2);

					za = a->z - (a->z - b->z) * ((a->y - y) / (a->z - b->z));
					zb = a->z - (a->z - c->z) * ((a->y - y) / (a->y - y));

					int x = (y - e->p.y) * (e->q.x - e->p.x) / (e->q.y - e->p.y) + e->p.x;
					Point *extrema = new Point(x, y);
					extrema_list.push_back(extrema);
					break;
				}
			}

			Point *pa = nullptr, *pb = nullptr;
			if (extrema_list.size() == 2)
			{
				pa = extrema_list.at(0);
				pb = extrema_list.at(1);
			}
			else
				continue;

			bool parity = false;
			vector<double> scanline = m.data.at(y);
			for (int x = pa->x; x < pb->x; x++)
			{
				zp = zb - (zb - za) / ((pb->x - x) / (pb->x - pa->x));
				if (zp > this->z_buf->z_buffer.at(y).at(x))
				{
					double r = abs((zp - back) / (front - back));
					int idx = (int)r / (0.05);
					if (idx >= this->colors->size())
						idx = this->colors->size() - 1;
					string color = this->colors->at(idx);
					this->z_buf->z_buffer.at(y).at(x) = zp;
					this->z_buf->frame_buffer.at(y).at(x) = color;
				}

				/*m.flip(y, x);*/
			}
		}

		/*for (int i = 0; i < extrema_list.size(); i++)
		{
			for (int j = 1; j < extrema_list.size() - i - 1; j++)
			{
				if (extrema_list.at(j)->x > extrema_list.at(j + 1)->x)
				{
					Point *p = extrema_list.at(j);
					Point *q = extrema_list.at(j + 1);
					extrema_list.at(j) = q;
					extrema_list.at(j + 1) = p;
				}
			}
		}*/

		//Point *pa = nullptr, *pb = nullptr;
		//if (extrema_list.size() == 2)
		//{
		//	pa = extrema_list.at(0);
		//	pb = extrema_list.at(1);
		//}
		//else
		//	continue;

		//bool parity = false;
		//vector<double> scanline = m.data.at(y);
		//for (int x = pa->x; x < pb->x; x++)
		//{
		//	zp = zb - (zb - za) / ((pb->x - x) / (pb->x - pa->x));
		//	if (zp > this->z_buf->z_buffer.at(y).at(x))
		//	{
		//		double r = (zp - back) / (front - back);
		//		this->z_buf->z_buffer.at(y).at(x) = zp;
		//		this->z_buf->frame_buffer.at(y).at(x) = this->color;
		//	}

		//	/*m.flip(y, x);*/
		//}
	}
}

int Shape::get_min_x()
{
	long min_x = 10000000000000;
	for (IDrawable *p : s_list)
	{
		Polygon *poly = dynamic_cast<Polygon *>(p);

		int t_min_x = poly->vertices.at(0)->x;
		for (Point *p : poly->vertices)
			if (p->x < t_min_x)
				t_min_x = p->x;

		if (t_min_x < min_x)
			min_x = t_min_x;
	}

	return min_x;
}

int Shape::get_min_y()
{
	long min_y = 10000000000000;
	for (IDrawable *p : s_list)
	{
		Polygon *poly = dynamic_cast<Polygon *>(p);

		int t_min_y = poly->vertices.at(0)->y;
		for (Point *p : poly->vertices)
			if (p->y < t_min_y)
				t_min_y = p->y;

		if (t_min_y < min_y)
			min_y = t_min_y;
	}

	return min_y;
}

ZBuffer::ZBuffer()
{
	for (int i = 0; i < 499; i++)
	{
		vector<double> z_buf;
		for (int j = 0; j < 499; j++)
			z_buf.push_back(-100000000000);
		z_buffer.push_back(z_buf);

		vector<string> line;
		for (int j = 0; j < 499; j++)
			line.push_back("x");
		frame_buffer.push_back(line);
	}
}

Camera::Camera(double x_prp = 0.0, double y_prp = 1.0, double z_prp = 1.0, double x_vrp = 0.0, double y_vrp = 0.0, double z_vrp = 0.0,
	double x_vpn = 0.0, double y_vpn = 0.0, double z_vpn = -1.0, double x_vup = 0.0, double y_vup = 1.0, double z_vup = 0.0,
	double u_min_vrc = -0.7, double v_min_vrc = -0.7, double u_max_vrc = 0.7, double v_max_vrc = 0.7,
	bool parallel_proj = false)
{
	vrp = new HomogenousPoint3D(x_vrp, y_vrp, z_vrp);
	vpn = new HomogenousPoint3D(x_vpn, y_vpn, z_vpn);
	vup = new HomogenousPoint3D(x_vup, y_vup, z_vup);
	prp = new HomogenousPoint3D(x_prp, y_prp, z_prp);

	n = new HomogenousPoint3D();
	u = new HomogenousPoint3D();
	v = new HomogenousPoint3D();

	this->n->x = vpn->x;
	this->n->y = vpn->y;
	this->n->z = vpn->z;
	this->n->h_point = 0;

	this->u = vup->cross(vpn);
	this->u->h_point = 0;

	this->v = this->n->cross(u);
	this->v->h_point = 0;

	this->n = n->normalize();
	this->u = u->normalize();
	this->v = v->normalize();

	u_min = u_min_vrc;
	u_max = u_max_vrc;
	v_min = v_min_vrc;
	v_max = v_max_vrc;

	orthographic_perspective = parallel_proj;

	if (parallel_proj)
		z_min = (prp->z - front) / (back - prp->z);
}

void Camera::project_polygons_to_3D(Screen *viewport)
{
	s = new Shape();

	if (this->orthographic_perspective)
		perspective = orthographic_matrix(u_min, u_max, v_min, v_max, front, back);
	else
		perspective = perspective_matrix(this->prp, u_min, u_max, v_min, v_max, front, back);

	view = view_matrix(this->vrp, this->u, this->v, this->n);

	for (int i = 0; i < viewport->shapes->s_list.size(); i++)
	{
		Polygon3D *p = dynamic_cast<Polygon3D *>(viewport->shapes->s_list.at(i));
		for (int j = 0; j < p->vertices3D.size(); j++)
		{
			HomogenousPoint3D *hp = new HomogenousPoint3D(p->vertices3D.at(j));
			hp->mult(view);
			hp->mult(perspective);
			p->verticesH3D.push_back(hp);
		}
		p->cohen_sutherland();
		s->add(p);
	}

	viewport->shapes = s;
}

void Camera::project_3Dpolygon_to_2D(Screen *viewport)
{
	for (int i = 0; i < viewport->shapes->s_list.size(); i++)
	{
		Polygon3D *poly3d = dynamic_cast<Polygon3D *>(viewport->shapes->s_list.at(i));
		for (int j = 0; j < poly3d->verticesH3D.size(); j++)
		{
			HomogenousPoint3D *hp3d = poly3d->verticesH3D.at(j);
			
			if (this->orthographic_perspective)
			{
				HomogenousPoint *p2d = new HomogenousPoint(hp3d->x, hp3d->y);
				p2d->z = hp3d->z;
				poly3d->verticesH2D.push_back(p2d);
			}
			else
			{
				HomogenousPoint *p2d = new HomogenousPoint(hp3d->x / -hp3d->z, hp3d->y / -hp3d->z);
				p2d->z = hp3d->z;
				poly3d->verticesH2D.push_back(p2d);
			}
		}
	}
}

WorldWindow::WorldWindow(int min_x_ww, int min_y_ww, int max_x_ww, int max_y_ww,
	int min_x_vp, int min_y_vp, int max_x_vp, int max_y_vp, Shape *s)
{
	// this is the window we clip against
	this->world_window = new Screen(min_x_ww, min_y_ww, max_x_ww, max_y_ww, s);

	// generate homogenous point matrix for the world_window
	this->h_mat = new HomogenousPointMatrix(this->world_window);

	// viewport to look at for final viewing
	this->viewport = new Screen(min_x_vp, min_y_vp, max_x_vp, max_y_vp);
};

// for 3D transforms
WorldWindow::WorldWindow(int min_x_vp = 0, int min_y_vp = 0, int max_x_vp = 499, int max_y_vp = 499,
	double x_prp = 0.0, double y_prp = 1.0, double z_prp = 1.0,
	double x_vrp = 0.0, double y_vrp = 0.0, double z_vrp = 0.0,
	double x_vpn = 0.0, double y_vpn = 0.0, double z_vpn = -1.0,
	double x_vup = 0.0, double y_vup = 1.0, double z_vup = 0.0,
	double u_min_vrc = -0.7, double v_min_vrc = -0.7, double u_max_vrc = 0.7, double v_max_vrc = 0.7,
	bool parallel_proj = false, double front = 0.6, double back = -0.6, Shape *s = nullptr, 
	vector<string> *reds = nullptr, vector<string> *greens = nullptr, vector<string> *blues = nullptr)
{
	this->viewport = new Screen(min_x_vp, min_y_vp, max_x_vp, max_y_vp, s);

	this->world_window = new Screen(0, 0, 499, 499);

	this->h_mat = new HomogenousPointMatrix(this->viewport);

	this->camera = new Camera(x_prp, y_prp, z_prp, x_vrp, y_vrp, z_vrp,
		x_vpn, y_vpn, z_vpn, x_vup, y_vup, z_vup,
		u_min_vrc, v_min_vrc, u_max_vrc, v_max_vrc, parallel_proj);

	this->reds = reds;
	this->greens = greens;
	this->blues = blues;

	this->z_buf = new ZBuffer();

	this->camera->project_polygons_to_3D(this->viewport);
	this->camera->project_3Dpolygon_to_2D(this->viewport);

	camera_viewport_transform();
	this->world_window->shapes = this->viewport->shapes;

	for (int i = 0; i < this->world_window->shapes->s_list.size(); i++)
	{
		Polygon3D *p3d = dynamic_cast<Polygon3D*>(this->world_window->shapes->s_list.at(i));
		p3d->z_buf = this->z_buf;
		p3d->front = front;
		p3d->back = back;

		if (colors[i] == 'r')
			p3d->colors = reds;
		else if (colors[i] == 'g')
			p3d->colors = greens;
		else
			p3d->colors = blues;
		/*p3d->color = this->colors[i];

		for (Point *p : p3d->poly2D->vertices)
		{
			if (p->z < front && p->z > this->z_buf->z_buffer.at(p->y).at(p->x))
			{
				string color;
				double r = p->z - back / (front - back);

				if (p3d->color == 'r')
					color = reds->at((int)r / (0.05));
				else if (p3d->color == 'g')
					color = greens->at((int)r / (0.05));
				else
					color = blues->at((int)r / (0.05));

				this->z_buf->z_buffer.at(p->y).at(p->x) = p->z;
				this->z_buf->frame_buffer.at(p->y).at(p->x) = color;
			}
		}*/
	}
}