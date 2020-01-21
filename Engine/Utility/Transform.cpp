#include "Transform.h"

#define PI 3.14

Transform::Transform() : position(0, 0, 0), scale(1, 1, 1), forward(0, 0, 1), up(0, 1, 0)
{
}

// Converts a quaternion to an euler angle
void Transform::QuaternionToEuler(const glm::quat &q1, glm::vec3 &TEuler)
{

	double test = q1.x*q1.y + q1.z*q1.w;
	if (test > 0.499)
	{ // singularity at north pole
		TEuler.y = 2 * atan2(q1.x, q1.w);
		TEuler.x = PI / 2;
		TEuler.y = 0;
		TEuler *= (180 / 3.14);
		return;
	}
	if (test < -0.499) { // singularity at south pole
		TEuler.y = -2 * atan2(q1.x, q1.w);
		TEuler.x = -PI / 2;
		TEuler.z = 0;
		TEuler *= (180 / 3.14);
		return;
	}
	double sqx = q1.x*q1.x;
	double sqy = q1.y*q1.y;
	double sqz = q1.z*q1.z;
	TEuler.y = atan2(2 * q1.y*q1.w - 2 * q1.x*q1.z, 1 - 2 * sqy - 2 * sqz);
	TEuler.x = asin(2 * test);
	TEuler.z = atan2(2 * q1.x*q1.w - 2 * q1.y*q1.z, 1 - 2 * sqx - 2 * sqz);
	TEuler *= (180 / 3.14);
}