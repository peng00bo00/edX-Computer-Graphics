// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat3 ret;
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
    float theta = glm::radians(degrees);
    vec3 ax = glm::normalize(axis);

    mat3 skew = mat3(0, -ax.z, ax.y,
                                  ax.z, 0, -ax.x,
                                -ax.y, ax.x, 0);
    skew = glm::transpose(skew);

    ret = (cos(theta) * glm::mat3(1.0)) + ((1 - cos(theta)) * glm::outerProduct(ax, ax)) + sin(theta) * skew;
    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    vec3 axis = up;
    eye = Transform::rotate(degrees, axis) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    vec3 axis = glm::cross(eye, up);
    axis = glm::normalize(axis);

    mat3 R = Transform::rotate(degrees, axis);

    up = R * up;
    eye = R * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
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

    ret = R * T;

    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float theta = glm::radians(fovy) / 2;
    float d = cos(theta)/sin(theta);
    float A = (-zFar + zNear) / (zFar - zNear);
    float B = (-2 * zFar * zNear) / (zFar - zNear);

    mat4 m;

    m = mat4(d/aspect, 0, 0, 0,
                    0, d, 0, 0,
                    0, 0, A, B,
                    0, 0,-1, 0);

    // Convert to column-major.
    return glm::transpose(m);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 m = mat4(); // Start with identity matrix

    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    // sw = 1

    // Conversion to column-major is unnecessary as matrix is diagonal
    return m;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 m = mat4(); // Start with identity

    m[0][3] = tx;
    m[1][3] = ty;
    m[2][3] = tz;

    // Convert to column-major
    return glm::transpose(m);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
