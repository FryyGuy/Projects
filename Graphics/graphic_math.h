#pragma once
#include "graphic_structures.h"

// This file is being used as the math "library" of sorts

// Motivation:
//	Rather than having operations associated with types
//	we keep the various types as primitive or atomic as possible
//	give them the ability to interact with other objects of the same type
//	and have them be able to draw.

//	Separating out the math decouples the math from the object.
//	This allows us to possibly express math as homogenous operations
//	associated with any kind of type of object instead of bound
//	to the object in question

// Hopefully I'm not sounding dumb... I might be...
// We'll see if it works out okay... I might be wrong. 
// In which case we can change things using abstract classing 
// or binding to classes later...S

HomogenousPointMatrix* translate_back(Matrix *, int, int, int);
HomogenousPointMatrix* translate_origin(Matrix *, int, int);
HomogenousPointMatrix* translate2D(Matrix *, int, int);
HomogenousPointMatrix* rotate2D(Matrix *, double);
HomogenousPointMatrix* scale2D(Matrix*, double);

HomogenousPointMatrix* scale3D(Matrix*, double);
HomogenousPointMatrix* rotate3D(Matrix*, double);
HomogenousPointMatrix* translate3D(Matrix*, double);

Matrix* view_matrix(HomogenousPoint3D *vrp, HomogenousPoint3D *u, HomogenousPoint3D *v, HomogenousPoint3D *n);
Matrix* perspective_matrix(HomogenousPoint3D *prp, double u_min, double u_max, double v_min, double v_max, double front, double back);
Matrix* orthographic_matrix(double u_min, double u_max, double v_min, double v_max, double front, double back);

Shape* translate_back(Screen *, double, double);
Shape* translate_origin(Screen *);
Shape* translate2D(Screen *, double, double);
Shape* rotate2D(Screen *, double);
Shape* scale2D(Screen *, double);
Shape* scale2D(Screen*, double, double);

Shape* translate3D(Screen *, Point3D*);
Shape* rotate3D(Screen *, Point3D*, Point3D*, Point3D*);
Shape* scale3D(Screen *, Point3D*);

void translate3Dto2D(Screen *screen, int x_trans, int y_trans);
void scale3Dto2D(Screen *s, double scale_factor_x, double scale_factor_y);
void translate2Dfrom3D(Screen *s, double x_trans, double y_trans);