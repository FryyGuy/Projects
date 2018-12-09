#include "graphic_math.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265
#define degrees(x) x * PI / 180.0

Matrix* translate_matrix(int dx, int dy)
{
	Matrix *translate = new Matrix(3, 3);

	vector<double> row1;
	row1.push_back(1);
	row1.push_back(0);
	row1.push_back(dx);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(1);
	row2.push_back(dy);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1);

	translate->data.at(0) = row1;
	translate->data.at(1) = row2;
	translate->data.at(2) = row3;

	return translate;
}

Matrix* rotate_matrix(int r_degrees_cc)
{
	Matrix *rotate = new Matrix(3, 3);

	vector<double> row1;
	row1.push_back(cos(degrees(r_degrees_cc)));
	row1.push_back(-sin(degrees(r_degrees_cc)));
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(sin(degrees(r_degrees_cc)));
	row2.push_back(cos(degrees(r_degrees_cc)));
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1);

	rotate->data.at(0) = row1;
	rotate->data.at(1) = row2;
	rotate->data.at(2) = row3;

	return rotate;
}

Matrix* scale_matrix(double scale_factor)
{
	Matrix *scale = new Matrix(3, 3);

	vector<double> row1;
	row1.push_back(scale_factor);
	row1.push_back(0);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(scale_factor);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1);

	scale->data.at(0) = row1;
	scale->data.at(1) = row2;
	scale->data.at(2) = row3;

	return scale;
}

Matrix* scale_matrix(double scale_factor_x, double scale_factor_y)
{
	Matrix *scale = new Matrix(3, 3);

	vector<double> row1;
	row1.push_back(scale_factor_x);
	row1.push_back(0);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(scale_factor_y);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1);

	scale->data.at(0) = row1;
	scale->data.at(1) = row2;
	scale->data.at(2) = row3;

	return scale;
}

Matrix* rotate3D_matrix(HomogenousPoint3D *u, HomogenousPoint3D *v, HomogenousPoint3D *n)
{
	Matrix* rotate3D = new Matrix(4, 4);

	vector<double> row1;
	row1.push_back(u->x);
	row1.push_back(u->y);
	row1.push_back(u->z);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(v->x);
	row2.push_back(v->y);
	row2.push_back(v->z);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(n->x);
	row3.push_back(n->y);
	row3.push_back(n->z);
	row3.push_back(0);

	vector<double> row4;
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(1);

	rotate3D->data.at(0) = row1;
	rotate3D->data.at(1) = row2;
	rotate3D->data.at(2) = row3;
	rotate3D->data.at(3) = row4;

	return rotate3D;
}

Matrix* scale3D_matrix(Point3D *s)
{
	Matrix* scale3D = new Matrix(4, 4);

	vector<double> row1;
	row1.push_back(s->x);
	row1.push_back(0);
	row1.push_back(0);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(s->y);
	row2.push_back(0);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(s->z);
	row3.push_back(0);

	vector<double> row4;
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(1);

	scale3D->data.at(0) = row1;
	scale3D->data.at(1) = row2;
	scale3D->data.at(2) = row3;
	scale3D->data.at(3) = row4;

	return scale3D;
}

Matrix* translate3D_matrix(HomogenousPoint3D *vrp)
{
	Matrix* translate3D = new Matrix(4, 4);

	vector<double> row1;
	row1.push_back(1);
	row1.push_back(0);
	row1.push_back(0);
	row1.push_back(vrp->x);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(1);
	row2.push_back(0);
	row2.push_back(vrp->y);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1);
	row3.push_back(vrp->z);

	vector<double> row4;
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(1);

	translate3D->data.at(0) = row1;
	translate3D->data.at(1) = row2;
	translate3D->data.at(2) = row3;
	translate3D->data.at(3) = row4;

	return translate3D;
}

Matrix* perspective_matrix(HomogenousPoint3D *prp, double u_min, double u_max, double v_min, double v_max, double front, double back)
{
	Matrix* perspective3D = new Matrix(4, 4);

	vector<double> row1;
	row1.push_back(2 * prp->z / ((u_max - u_min)*(prp->z - back)));
	row1.push_back(0);
	row1.push_back(0);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(2 * prp->z / ((v_max - v_min)*(prp->z - back)));
	row2.push_back(0);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1 / (prp->z - back));
	row3.push_back(-prp->z / (prp->z - back));

	vector<double> row4;
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(1);

	perspective3D->data.at(0) = row1;
	perspective3D->data.at(1) = row2;
	perspective3D->data.at(2) = row3;
	perspective3D->data.at(3) = row4;

	return perspective3D;
}

Matrix* orthographic_matrix(double u_min, double u_max, double v_min, double v_max, double front, double back)
{
	Matrix* orthographic3D = new Matrix(4, 4);

	double dif_u = (u_max - u_min) == 0 ? 1 : u_max - u_min;
	double dif_v = (v_max - v_min) == 0 ? 1 : v_max - v_min;
	double dif_f_b = front - back == 0 ? 1 : front - back;

	vector<double> row1;
	row1.push_back(2 / dif_u);
	row1.push_back(0);
	row1.push_back(0);
	row1.push_back(0);

	vector<double> row2;
	row2.push_back(0);
	row2.push_back(2 / dif_v);
	row2.push_back(0);
	row2.push_back(0);

	vector<double> row3;
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(1 / (dif_f_b));
	row3.push_back(-(front / (dif_f_b)));

	vector<double> row4;
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(0);
	row4.push_back(1);

	orthographic3D->data.at(0) = row1;
	orthographic3D->data.at(1) = row2;
	orthographic3D->data.at(2) = row3;
	orthographic3D->data.at(3) = row4;

	return orthographic3D;
}

Matrix* view_matrix(HomogenousPoint3D *vrp, HomogenousPoint3D *u, HomogenousPoint3D *v, HomogenousPoint3D *n)
{
	vrp->x = -vrp->x;
	vrp->y = -vrp->y;
	vrp->z = -vrp->z;
	Matrix *t = translate3D_matrix(vrp);
	Matrix *r = rotate3D_matrix(u, v, n);

	Matrix *view = new Matrix(4, 4);

	vector<double> r1 = t->data.at(0);
	vector<double> l1 = r->data.at(0);

	vector<double> r2 = t->data.at(1);
	vector<double> l2 = r->data.at(1);

	vector<double> r3 = t->data.at(2);
	vector<double> l3 = r->data.at(2);

	vector<double> r4 = t->data.at(3);
	vector<double> l4 = r->data.at(3);

	vector<double> v1;
	vector<double> v2;
	vector<double> v3;
	vector<double> v4;

	double v1x, v2x, v3x, v4x;
	double v1y, v2y, v3y, v4y;
	double v1z, v2z, v3z, v4z;
	double v1h, v2h, v3h, v4h;

	double b00 = r1.at(0), b01 = r1.at(1), b02 = r1.at(2), b03 = r1.at(3);
	double b10 = r2.at(0), b11 = r2.at(1), b12 = r2.at(2), b13 = r2.at(3);
	double b20 = r3.at(0), b21 = r3.at(1), b22 = r3.at(2), b23 = r3.at(3);
	double b30 = r4.at(0), b31 = r4.at(1), b32 = r4.at(2), b33 = r4.at(3);

	double a00 = l1.at(0), a01 = l1.at(1), a02 = l1.at(2), a03 = l1.at(3);
	double a10 = l2.at(0), a11 = l2.at(1), a12 = l2.at(2), a13 = l2.at(3);
	double a20 = l3.at(0), a21 = l3.at(1), a22 = l3.at(2), a23 = l3.at(3);
	double a30 = l4.at(0), a31 = l4.at(1), a32 = l4.at(2), a33 = l4.at(3);

	v1x = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
	v1y = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
	v1z = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
	v1h = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;

	v2x = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
	v2y = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
	v2z = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
	v2h = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;

	v3x = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
	v3y = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
	v3z = a20 * b02 + a12 * b12 + a22 * b22 + a23 * b32;
	v3h = a30 * b02 + a13 * b12 + a32 * b22 + a33 * b32;

	v4x = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;
	v4y = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;
	v4z = a20 * b03 + a12 * b13 + a22 * b23 + a23 * b33;
	v4h = a30 * b03 + a13 * b13 + a32 * b23 + a33 * b33;

	v1.push_back(v1x);
	v1.push_back(v2x);
	v1.push_back(v3x);
	v1.push_back(v4x);

	v2.push_back(v1y);
	v2.push_back(v2y);
	v2.push_back(v3y);
	v2.push_back(v4y);

	v3.push_back(v1z);
	v3.push_back(v2z);
	v3.push_back(v3z);
	v3.push_back(v4z);

	v4.push_back(v1h);
	v4.push_back(v2h);
	v4.push_back(v3h);
	v4.push_back(v4h);

	view->data.at(0) = v1;
	view->data.at(1) = v2;
	view->data.at(2) = v3;
	view->data.at(3) = v4;

	return view;
}

// ignore bogus, compiler was being dumb.
HomogenousPointMatrix* translate_back(Matrix *mat, int min_x, int min_y, int bogus)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *translate = translate_matrix(min_x, min_y);

	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				p.mult(translate);
				m->flip(p.y, p.x);
			}
		}
	}

	return m;
}

HomogenousPointMatrix* translate_origin(Matrix *mat, int min_x, int min_y)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *translate = translate_matrix(-min_x, -min_y);

	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				p.mult(translate);
				m->flip(p.y, p.x);
			}
		}
	}

	return m;
}

HomogenousPointMatrix* translate2D(Matrix * mat, int x_t, int y_t)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *translate = translate_matrix(x_t, y_t);

	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				p.mult(translate);
				m->flip(p.y, p.x);
			}
		}
	}

	return m;
}

HomogenousPointMatrix* rotate2D(Matrix *mat, double cc_rot_degree)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *rotate = rotate_matrix(cc_rot_degree);

	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				p.mult(rotate);

				if (p.x == -1 || p.y == -1)
					std::cout << "Hi";
				m->flip((unsigned int)p.y, (unsigned int)p.x);
			}
		}
	}

	return m;
}

HomogenousPointMatrix* scale2D(Matrix *mat, double scale_factor)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *scale = scale_matrix(scale_factor);
	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				HomogenousPoint rep(p.x, p.y, 0);
				p.mult(scale);

				HomogenousPoint n_h(p.x, p.y, p.on);
				m->mat.at(n_h.y).at(n_h.x) = n_h;
				m->mat.at(y).at(x) = rep;
			}
		}
	}

	return m;
}

Shape* rotate2D(Screen *screen, double cc_rot_deg)
{
	Shape *s = new Shape();
	Matrix *rotate = rotate_matrix(cc_rot_deg);

	for (IDrawable* p : screen->shapes->s_list)
	{
		Polygon *poly = dynamic_cast<Polygon *>(p);
		Polygon *new_poly = new Polygon();

		for (Point * v : poly->vertices)
		{
			Point *new_v = new Point();

			HomogenousPoint h(v);
			h.mult(rotate);

			new_v->x = h.x;
			new_v->y = h.y;
			new_v->compute_code(screen->height, screen->width);

			new_poly->vertices.push_back(new_v);
		}

		new_poly->_fill = true;
		s->s_list.push_back(new_poly);
	}

	return s;
}

Shape* translate2D(Screen *screen, double x_trans, double y_trans)
{
	Shape *s = new Shape();
	Matrix *translate = translate_matrix(x_trans, y_trans);

	for (IDrawable* p : screen->shapes->s_list)
	{
		Polygon *poly = dynamic_cast<Polygon *>(p);
		Polygon *new_poly = new Polygon();

		for (Point * v : poly->vertices)
		{
			Point *new_v = new Point();

			HomogenousPoint h(v);
			h.mult(translate);

			new_v->x = h.x >= screen->width ? screen->width - 1 : h.x;
			new_v->y = h.y >= screen->height ? screen->height - 1 : h.y;
			new_v->compute_code(screen->height, screen->width);

			new_poly->vertices.push_back(new_v);
		}

		new_poly->_fill = true;
		s->s_list.push_back(new_poly);
	}

	return s;
}

void translate3Dto2D(Screen *screen, int x_trans, int y_trans)
{
	Matrix *translate = translate_matrix(x_trans, y_trans);

	for (IDrawable* p : screen->shapes->s_list)
	{
		Polygon3D *poly = dynamic_cast<Polygon3D *>(p);
		poly->poly2D = new Polygon();
		for (HomogenousPoint * v : poly->verticesH2D)
		{
			Point *new_v = new Point();
			v->mult(translate);

			new_v->x = v->x;
			new_v->y = v->y;
			new_v->z = v->z;
			new_v->compute_code(poly->max_y, poly->max_x);

			poly->poly2D->vertices.push_back(new_v);
		}
	}
}

void translate2Dfrom3D(Screen *screen, double x_trans, double y_trans)
{
	Matrix *translate = translate_matrix(x_trans, y_trans);

	for (IDrawable* p : screen->shapes->s_list)
	{
		Polygon3D *poly3d = dynamic_cast<Polygon3D *>(p);
		Polygon *poly2d = poly3d->poly2D;
		Polygon *new_poly = new Polygon();
		for (int j = 0; j < poly2d->vertices.size(); j++)
		{
			Point *q = poly2d->vertices.at(j);
			Point *new_q = new Point();

			HomogenousPoint h(q);
			h.mult(translate);

			new_q->x = h.x;
			new_q->y = h.y;
			new_q->z = q->z;
			new_q->compute_code(screen->height, screen->width);

			new_poly->vertices.push_back(new_q);
		}

		poly3d->poly2D = new_poly;
	}
}

Shape* scale2D(Screen *s, double scale_factor)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(s);
	Shape *shapes = new Shape();

	Matrix *scale = scale_matrix(scale_factor);

	for (int i = 0; i < s->shapes->s_list.size(); i++)
	{
		Polygon *p = dynamic_cast<Polygon *>(s->shapes->s_list.at(i));
		Polygon *new_p = new Polygon();
		for (int j = 0; j < p->vertices.size(); j++)
		{
			Point *q = p->vertices.at(j);
			Point *new_q = new Point();

			HomogenousPoint h(q);
			h.mult(scale);

			new_q->x = h.x;
			new_q->y = h.y;
			new_q->compute_code(s->height, s->width);

			new_p->vertices.push_back(new_q);
		}

		new_p->_fill = true;
		shapes->s_list.push_back(new_p);
	}

	return shapes;
}

Shape* scale2D(Screen *s, double scale_factor_x, double scale_factor_y)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(s);
	Shape *shapes = new Shape();

	Matrix *scale = scale_matrix(scale_factor_x, scale_factor_y);

	for (int i = 0; i < s->shapes->s_list.size(); i++)
	{
		Polygon *p = dynamic_cast<Polygon *>(s->shapes->s_list.at(i));
		Polygon *new_p = new Polygon();
		for (int j = 0; j < p->vertices.size(); j++)
		{
			Point *q = p->vertices.at(j);
			Point *new_q = new Point();

			HomogenousPoint h(q);
			h.mult(scale);

			new_q->x = h.x;
			new_q->y = h.y;
			new_q->compute_code(s->height, s->width);

			new_p->vertices.push_back(new_q);
		}

		new_p->_fill = true;
		shapes->s_list.push_back(new_p);
	}

	return shapes;
}

void scale3Dto2D(Screen *s, double scale_factor_x, double scale_factor_y)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(s);
	Matrix *scale = scale_matrix(scale_factor_x, scale_factor_y);

	for (int i = 0; i < s->shapes->s_list.size(); i++)
	{
		Polygon3D *poly3d = dynamic_cast<Polygon3D *>(s->shapes->s_list.at(i));
		Polygon *p2d = poly3d->poly2D;
		Polygon *new_p = new Polygon();
		for (int j = 0; j < p2d->vertices.size(); j++)
		{
			Point *q = p2d->vertices.at(j);
			Point *new_q = new Point();

			HomogenousPoint h(q);
			h.mult(scale);

			new_q->x = h.x;
			new_q->y = h.y;
			new_q->z = q->z;
			new_q->compute_code(s->height, s->width);

			new_p->vertices.push_back(new_q);
		}

		poly3d->poly2D = new_p;
	}
}

Shape* translate_back(Screen *screen, double min_x, double min_y)
{
	Shape *s = new Shape();

	s = translate2D(screen, min_x, min_y);

	return s;
}

Shape* translate_origin(Screen *screen)
{
	Shape *s = new Shape();

	double min_x = screen->shapes->get_min_x();
	double min_y = screen->shapes->get_min_y();

	s = translate2D(screen, -min_x, -min_y);

	return s;
}

HomogenousPointMatrix* rotate3D(Matrix *mat, HomogenousPoint3D *u, HomogenousPoint3D *v, HomogenousPoint3D *n)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *rotate = rotate3D_matrix(u, v, n);
	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				HomogenousPoint rep(p.x, p.y, 0);
				p.mult(rotate);

				HomogenousPoint n_h(p.x, p.y, p.on);
				m->mat.at(n_h.y).at(n_h.x) = n_h;
				m->mat.at(y).at(x) = rep;
			}
		}
	}

	return m;
}

HomogenousPointMatrix* translate3D(Matrix *mat, HomogenousPoint3D *x)
{
	HomogenousPointMatrix *m = new HomogenousPointMatrix(mat);
	Matrix *translate = translate3D_matrix(x);

	for (int y = 0; y < m->mat.size(); y++)
	{
		vector < HomogenousPoint > vec = m->mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			HomogenousPoint p = vec.at(x);

			if (p.on)
			{
				HomogenousPoint rep(p.x, p.y, 0);
				p.mult(translate);

				HomogenousPoint n_h(p.x, p.y, p.on);
				m->mat.at(n_h.y).at(n_h.x) = n_h;
				m->mat.at(y).at(x) = rep;
			}
		}
	}

	return m;
}
