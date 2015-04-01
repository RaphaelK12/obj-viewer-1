#include "Arcball.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>

Arcball::Arcball(const Vector3f& center, const float& radius) : center_(center) {
}

void Arcball::setCenter(const Vector3f& center) {
	center_ = center;
}

Vector3f Arcball::center() {
	return center_;
}

void Arcball::setRadius(const float& radius) {
	radius_ = radius;
}

float Arcball::radius() {
	return radius_;
}


Matrix3f Arcball::rotation(const Vector2f& start, const Vector2f& end) {
	 //for simplicity we assume the eye is at the origin since that's all we need for this application.
	GLdouble x, y, z;
	
	GLdouble projectionMatrix[16];
	GLdouble modelViewMatrix[16];
	int viewportMatrix[4];
	
	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
	glGetIntegerv(GL_VIEWPORT, viewportMatrix);
	
	gluUnProject(start.x(), start.y(), 0.0, modelViewMatrix, projectionMatrix, viewportMatrix, &x, &y, &z);
	Vector3f v1(x, y, z);
	
	gluUnProject(end.x(), end.y(), 0.0, modelViewMatrix, projectionMatrix, viewportMatrix, &x, &y, &z);
	Vector3f v2(x, y, z);
	
	//find intersection with sphere
	float c = (center_ * center_) - (radius_ * radius_);
	
	float a1 = v1 * v1;
	float b1 = 2.0 * (v1 * center_);
	
	float a2 = v2 * v2;
	float b2 = 2.0 * (v2 * center_);
	
	float d1 = b1 * b1 - 4.0 * a1 * c;
	float d2 = b2 * b2 - 4.0 * a2 * c;
	
	//if either one of the rays does not intersect the sphere, then do nothing
	if (d1 < 0.0 || d2 < 0.0)
		return Matrix3f::identity();
		
	float r11 = (-b1 - std::sqrt(d1)) / (2.0 * a1);
	float r12 = (-b1 + std::sqrt(d1)) / (2.0 * a1);
	
	float r21 = (-b2 - std::sqrt(d2)) / (2.0 * a2);
	float r22 = (-b2 + std::sqrt(d2)) / (2.0 * a2);
	
	float t1 = (r11 > r12) ? r11 : r12;
	float t2 = (r21 > r22) ? r21 : r22;
	
	//find points on sphere and make them relative to the center
	v1 *= t1;
	v2 *= t2;
	
	v1 -= center_;
	v2 -= center_;
	
	v1 /= v1.norm();
	v2 /= v2.norm();
	
	//find matrix corresponding to a rotating v1 to v2
	return Matrix3f::rotation(v1.cross(v2), std::acos(v1 * v2));
}