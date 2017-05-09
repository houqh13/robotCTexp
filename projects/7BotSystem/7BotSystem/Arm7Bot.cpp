
#include "Arm7Bot.h"
#include "PVector.h"

#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Kinematics */

// Valid range check
// return: [0]-no error, [1]-some angle out of range, [2]-theta1 & theta2 cosntrain
int Arm7Bot::angleRangCheck()
{
	for (int i = 0; i < SERVO_NUM; i ++)
	{
		if (theta[i] < thetaMin[i] || theta[i] > thetaMax[i])
			return 1;
	}
	if (theta[2] + theta[1] > 3.96189733 || theta[2] + theta[1] < 1.44862327 )
		return 2;
	return 0;
}

// Calculate model joints
void Arm7Bot::calcJoints()
{
	joint[1] = PVector(joint[0].x, joint[0].y + LENGTH_D, joint[0].z + LENGTH_E);
	joint[2] = PVector(0, -LENGTH_B * cos(theta[2] - 1.134464), LENGTH_B * sin(theta[2] - 1.134464));
	joint[2].add(joint[1]);
	joint[3] = PVector(0, LENGTH_A * cos(theta[1]), LENGTH_A * sin(theta[1]));
	joint[3].add(joint[1]);
	joint[4] = PVector(0, LENGTH_H * sin(theta[2] - 1.134464), LENGTH_H * cos(theta[2] - 1.134464));
	joint[4].add(joint[3]);
	joint[5] = PVector(0, LENGTH_C * cos(theta[2] - 1.134464), -LENGTH_C * sin(theta[2] - 1.134464));
	joint[5].add(joint[4]);
	joint[6] = PVector(0, LENGTH_F * sin(theta[2] - 1.134464 + theta[4]), LENGTH_F * cos(theta[2] - 1.134464 + theta[4]));
	joint[6].add(joint[5]);
	joint[7] = PVector(0, -LENGTH_G * cos(theta[2] - 1.134464 + theta[4]), LENGTH_G * sin(theta[2] - 1.134464 + theta[4]));
	joint[7].add(joint[6]);
	joint[7] = arbitraryRotate(joint[7], joint[6], joint[5], theta[5]); 
	joint[6] = arbitraryRotate(joint[6], joint[5], joint[4], theta[3] - HALF_PI); 
	joint[7] = arbitraryRotate(joint[7], joint[5], joint[4], theta[3] - HALF_PI); 
	joint[8] = PVector(2 * joint[6].x - joint[7].x, 2 * joint[6].y - joint[7].y, 2 * joint[6].z - joint[7].z);
	for (int i = 1; i < 9; i ++)
	{
		joint[i] = zAxiRotate(joint[i], theta[0] - HALF_PI);
	}
}

PVector Arm7Bot::zAxiRotate(PVector point, double _angle)
{
	PVector pt;
	pt = PVector(cos(_angle) * point.x - sin(_angle) * point.y, sin(_angle) * point.x + cos(_angle) * point.y, point.z );
	return pt;
}

PVector Arm7Bot::arbitraryRotate(PVector point, PVector pointA, PVector pointB, double _angle)
{
	PVector pt = PVector(0, 0, 0);
	double x = point.x, y = point.y, z = point.z;
	double u = pointB.x - pointA.x, v = pointB.y - pointA.y, w = pointB.z - pointA.z;
	double l = sqrt(u * u + v * v + w * w);
	u /= l; v /= l; w /= l;
	double a = pointA.x, b = pointA.y, c = pointA.z;
	double u2 = u * u, v2 = v * v, w2 = w * w;
	double au = a * u, av = a * v, aw = a * w;
	double bu = b * u, bv = b * v, bw = b * w;
	double cu = c * u, cv = c * v, cw = c * w;
	double ux = u * x, uy = u * y, uz = u * z;
	double vx = v * x, vy = v * y, vz = v * z;
	double wx = w * x, wy = w * y, wz = w * z;
	pt.x = (a * (v2 + w2) - u * (bv + cw - ux - vy - wz)) * (1 - cos(_angle)) + x * cos(_angle) + (-cv + bw - wy + vz) * sin(_angle);
	pt.y = (b * (u2 + w2) - v * (au + cw - ux - vy - wz)) * (1 - cos(_angle)) + y * cos(_angle) + (cu - aw + wx - uz) * sin(_angle);
	pt.z = (c * (u2 + v2) - w * (au + bv - ux - vy - wz)) * (1 - cos(_angle)) + z * cos(_angle) + (-bu + av - vx + uy) * sin(_angle);
	return pt;
}

PVector Arm7Bot::calcProjectionPt(PVector pt0, PVector pt1, PVector nVec)
{
	PVector n = PVector(nVec.x, nVec.y, nVec.z);
	n.normalize();
	PVector vec10 = PVector(pt0.x - pt1.x, pt0.y - pt1.y, pt0.z - pt1.z);
	double dot = vec10.dot(n);
	PVector projectionPt = PVector(pt0.x - dot * n.x, pt0.y - dot * n.y, pt0.z - dot * n.z);
	return projectionPt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Invers Kinematics */

// Function: IK, input Joint[5], calculate theta[0]~[2]
// return: [0]no error; [1]out of valid range
// input unit:mm
int Arm7Bot::IK3(PVector pt)
{
	double x = pt.x, y = pt.y, z = pt.z;
	if (z < -26.9)
		return 1;
	theta[0] = atan(y / x);
	if (theta[0] < 0)
		theta[0] = PI + theta[0];
	x -= LENGTH_D * cos(theta[0]);
	y -= LENGTH_D * sin(theta[0]);
	z -= LENGTH_E;
	double lengthA = sqrt(x * x + y * y + z * z); 
	double lengthC = sqrt(LENGTH_H * LENGTH_H + LENGTH_C * LENGTH_C); 
	double offsetAngle = atan(LENGTH_H / LENGTH_C);
	double angleA = acos((LENGTH_A * LENGTH_A + lengthC * lengthC - lengthA * lengthA) / (2 * LENGTH_A * lengthC));
	double angleB = atan(z / sqrt(x * x + y * y));
	double angleC = acos((LENGTH_A * LENGTH_A + lengthA * lengthA - lengthC * lengthC) / (2 * LENGTH_A * lengthA));
	theta[1] = angleB + angleC;
	theta[2] = PI - angleA - angleB - angleC + offsetAngle;
	theta[2] += 1.134464;

	// range check
	if (theta[1] > thetaMin[1] && theta[1] < thetaMax[1] &&
		theta[2] > thetaMin[2] && theta[2] < thetaMax[2] &&
		theta[2] - 0.8203047 + theta[1] < PI && theta[2] + theta[1] > 1.44862327) 
	{
		return 0;
	}
	return 1;
}

// Function: IK, input joint[6] & Vector(joint[5] to joint[6] direction), calculate theta[0]~[4]
// return: [0]no error; [1]IK3 out of valid range; [2]IK5-theta4 out of range
int Arm7Bot::IK5(PVector j6, PVector vec56_d)
{
	PVector vec56_u = PVector(vec56_d.x, vec56_d.y, vec56_d.z); 
	vec56_u.normalize();
	PVector j5 = PVector(j6.x - LENGTH_F * vec56_u.x, j6.y - LENGTH_F * vec56_u.y, j6.z - LENGTH_F * vec56_u.z);
	PVector vec56 = PVector(j6.x - j5.x, j6.y - j5.y, j6.z - j5.z);
	int IK3_status = IK3(j5);
	if (IK3_status != 0)
		return IK3_status;
	joint[5] = j5;
	theta[3] = 0.0;
	theta[4] = 0.0;
	calcJoints();
	PVector j6_0 = joint[6];
	PVector vec56_0 = PVector(j6_0.x - j5.x, j6_0.y - j5.y, j6_0.z - j5.z);
	PVector vec45 = PVector(joint[5].x - joint[4].x, joint[5].y - joint[4].y, joint[5].z - joint[4].z);
	PVector j6p = calcProjectionPt(j6, j5, vec45);
	PVector vec56p = PVector(j6p.x - j5.x, j6p.y - j5.y, j6p.z - j5.z);
	theta[3] = acos(vec56_0.dot(vec56p) / (j5.dist(j6_0) * j5.dist(j6p)));
	theta[4] = acos(vec56.dot(vec56p) / (j5.dist(j6) * j5.dist(j6p)));
	calcJoints();
	double dist = j6.dist(joint[6]);
	if (dist < 1)
		return 0;
	theta[3] = PI - theta[3]; 
	theta[4] = PI - theta[4]; 
	calcJoints();
	dist = j6.dist(joint[6]);
	if (dist < 1) 
		return 0;
	else
		return 2;
}

// Function: IK, input joint[6], Vector(joint[5] to joint[6] direction) & Vector(joint[6] to joint[7]), calculate theta[0]~[5]
// return: [0]no error; [1]IK3 out of valid range; [2]IK5-theta4 out of range;
int Arm7Bot::IK6(PVector j6, PVector vec56_d, PVector vec67_d)
{
	int IK5_status = IK5(j6, vec56_d);
	if (IK5_status != 0)
		return IK5_status;
	PVector vec67_u = PVector(vec67_d.x, vec67_d.y, vec67_d.z);
	vec67_u.normalize();
	PVector j7 = PVector(j6.x + LENGTH_G * vec67_u.x, j6.y + LENGTH_G * vec67_u.y, j6.z + LENGTH_G * vec67_u.z);
	PVector j7p = calcProjectionPt(j7, j6, vec56_d);
	theta[5] = 0;
	calcJoints();
	PVector j7_0 = joint[7];
	PVector vec67_0 = PVector(j7_0.x - j6.x, j7_0.y - j6.y, j7_0.z - j6.z);
	PVector vec67p = PVector(j7p.x - j6.x, j7p.y - j6.y, j7p.z - j6.z);
	//(3)- calculate theta[5]
	double thetaTmp5 = acos(vec67_0.dot(vec67p) / (j6.dist(j7_0) * j6.dist(j7p)));
	theta[5] = -thetaTmp5;
	if (vec67_d.x < 0)
		theta[5] = -theta[5];
	if (theta[5] < 0)
		theta[5] = PI + theta[5]; 
	calcJoints();
	return 0;
}
