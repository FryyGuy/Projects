#include <cmath>
#include <stdlib.h>

#include "graphic_math.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
	this->compute_code(500, 500);
}

void Point::compute_code(int height=500, int width=500)
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

Point& Point::operator+(const Point &q)
{
	this->x += q.x;
	this->y += q.y;

	return *this;
}

Point& Point::operator+=(const Point &q)
{
	this->x += q.x;
	this->y += q.y;

	return *this;
}

Point& Point::operator-=(const Point &q)
{
	this->x -= q.x;
	this->y -= q.y;

	return *this;
}

bool Point::operator==(const Point &q)
{
	bool ret;
	if (q.x == this->x && q.y == this->y)
		ret = true;
	else
		ret = false;

	return ret;
}

Point::~Point()
{

}

Point3D& Point3D::operator+(const Point3D &q)
{
	this->x += q.x;
	this->y += q.y;
	this->z += q.z;

	return *this;
}

Point3D& Point3D::operator+=(const Point3D &q)
{
	this->x += q.x;
	this->y += q.y;
	this->z += q.z;

	return *this;
}

Point3D& Point3D::operator-=(const Point3D &q)
{
	this->x -= q.x;
	this->y -= q.y;
	this->z -= q.z;

	return *this;
}

bool Point3D::operator==(const Point3D &q)
{
	bool ret;
	if (q.x == this->x && q.y == this->y && q.z == this->z)
		ret = true;
	else
		ret = false;

	return ret;
}

Matrix::Matrix()
{
	this->height = 500;
	this->width = 500;

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

	if (t_y == 500)
		--t_y;
	if (t_x == 500)
		--t_x;

	vector<double> row = this->data.at(t_y);
	row.at(t_x) = 1;
	this->data.at(t_y) = row;
}

Matrix::~Matrix()
{

}

// we use this when dealing with edges so assume on
HomogeneousPoint::HomogeneousPoint(Point *p)
{
	this->x = p->x;
	this->y = p->y;
	this->on = 1;
}

HomogeneousPoint::HomogeneousPoint(int x, int y, int on)
{
	this->x = x;
	this->y = y;
	this->on = on;
};

void HomogeneousPoint::mult(const Matrix &m)
{
	double p1_x = m.data.at(0).at(0), p1_y = m.data.at(1).at(0), p1_h = m.data.at(2).at(0);
	double p2_x = m.data.at(0).at(1), p2_y = m.data.at(1).at(1), p2_h = m.data.at(2).at(1);
	double p3_x = m.data.at(0).at(2), p3_y = m.data.at(1).at(2), p3_h = m.data.at(2).at(2);

	this->x = this->x * p1_x + this->y * p2_x + this->h_point * p3_x;
	this->y = this->x * p1_y + this->y * p2_y + this->h_point * p3_y;
	this->h_point = this->x * p1_h + this->y * p2_h + this->h_point * p3_h;
}

void HomogenousPoint3D::mult(const Matrix3D &m)
{
	double p1_x = m.data.at(0).at(0).at(0), p1_y = m.data.at(0).at(1).at(0), p1_z = m.data.at(0).at(2).at(0), p1_h = m.data.at(0).at(3).at(0);
	double p2_x = m.data.at(1).at(0).at(0), p2_y = m.data.at(1).at(1).at(1), p2_z = m.data.at(1).at(2).at(1), p2_h = m.data.at(1).at(3).at(1);
	double p3_x = m.data.at(2).at(0).at(0), p3_y = m.data.at(2).at(1).at(2), p3_z = m.data.at(2).at(2).at(2), p3_h = m.data.at(2).at(3).at(2);

	this->x = this->x * p1_x + this->y * p2_x + this->h_point * p3_x;
	this->y = this->x * p1_y + this->y * p2_y + this->h_point * p3_y;
	this->z = this->z * p1_z + this->z * p2_z + this->h_point * p3_z;
	this->h_point = this->x * p1_h + this->y * p2_h + this->z * p3_h + this->h_point * p3_h;
}

HomogenousPoint3D* HomogenousPoint3D::cross(const HomogenousPoint3D &v)
{
	HomogenousPoint3D *ret = new HomogenousPoint3D();
	ret->x = this->y * v.z - this->z * v.y;
	ret->y = this->z * v.x - this->x * v.z;
	ret->z = this->x * v.y - this->y * v.x;

	return ret;
}

HomogenousPoint3D* HomogenousPoint3D::cross(const HomogenousPoint3D *v)
{
	HomogenousPoint3D *ret = new HomogenousPoint3D();
	ret->x = this->y * v->z - this->z * v->y;
	ret->y = this->z * v->x - this->x * v->z;
	ret->z = this->x * v->y - this->y * v->x;

	return ret;
}

HomogenousPointMatrix(Matrix *m) : Matrix(m->height, m->width)
{
	for (int y = 0; y < m->data.size(); y++)
	{
		vector<double> row = m->data.at(y);
		vector<HomogeneousPoint> pts;
		for (int x = 0; x < row.size(); x++)
		{
			HomogeneousPoint pt(x, y, row.at(x));
			pts.push_back(pt);
		}
		mat.push_back(pts);
	}
}

vector< vector< double > >& HomogenousPointMatrix::to_mat()
{
	Matrix *new_mat = new Matrix(mat.size(), mat.at(0).size());
	for (int y = 0; y < mat.size(); y++)
	{
		vector<HomogeneousPoint> vec = mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			if (vec.at(x).on)
				new_mat->flip(y, x);
		}
	}

	return new_mat->data;
}

HomogenousPoint3DMatrix::HomogenousPoint3DMatrix(Matrix3D *m) : Matrix3D(m->height, m->width, m->depth)
{
	for (int z = 0; z < m->data.size(); z++)
	{
		vector< vector<double> > mat_z = m->data.at(z);
		vector< vector<HomogenousPoint3D> > pt_mat;
		for (int y = 0; y < mat_z.size(); y++)
		{
			vector<double> row = mat_z.at(y);
			vector<HomogenousPoint3D> pts;
			for (int x = 0; x < row.size(); x++)
			{
				HomogenousPoint3D pt(x, y, z, row.at(x));
				pts.push_back(pt);
			}
			pt_mat.push_back(pts);
		}
		mat.push_back(pt_mat);
	}
}

// need to project 3d points onto 2d
vector< vector< double > >& HomogenousPoint3DMatrix::to_mat()
{
	Matrix *new_mat = new Matrix(mat.size(), mat.at(0).size());
	/*for (int y = 0; y < mat.size(); y++)
	{
		vector<HomogenousPoint3D> vec = mat.at(y);
		for (int x = 0; x < vec.size(); x++)
		{
			if (vec.at(x).on)
				new_mat->flip(y, x);
		}
	}*/

	return new_mat->data;
}