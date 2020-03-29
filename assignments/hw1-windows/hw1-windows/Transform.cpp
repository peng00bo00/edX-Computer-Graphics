// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	float theta = glm::radians(degrees);

	mat3 skew = mat3(0, -axis.z, axis.y,
		                           axis.z, 0, -axis.x,
		                          -axis.y, axis.x, 0);
	skew = glm::transpose(skew);

	mat3 R = (cos(theta) * glm::mat3(1.0)) + ((1 - cos(theta)) * glm::outerProduct(axis, axis)) + sin(theta) * skew;
  // You will change this return call
  return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	vec3 axis = up;
	eye = Transform::rotate(degrees, axis) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 axis = glm::cross(eye, up);
	axis = glm::normalize(axis);

	mat3 R = Transform::rotate(degrees, axis);

	up = R * up;
	eye = R * eye;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
	mat4 T = glm::mat4(1, 0, 0, -eye.x, 
		                              0, 1, 0, -eye.y, 
		                              0, 0, 1, -eye.z, 
		                              0, 0, 0, 1);
	T = glm::transpose(T);

	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, eye));
	vec3 v = glm::cross(w, u);

	mat4 R = glm::mat4(u.x, u.y, u.z, 0,
		                            v.x, v.y, v.z, 0,
		                            w.x, w.y, w.z, 0,
	                                0, 0, 0, 1);
	R = glm::transpose(R);

	mat4 m = R * T;

  return m;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}