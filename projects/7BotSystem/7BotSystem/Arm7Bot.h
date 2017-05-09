#pragma once

#include "Define.h"

const double thetaMin[SERVO_NUM] = {0, 0, 0, 0.17453292, 0, 0, 0};
const double thetaMax[SERVO_NUM] = {PI, PI, PI, 2.9670596, PI, PI, PI/2};

class Arm7Bot
{
private:
    // Kinematics & IK
    PVector joint[9];
    int angleRangCheck();
    void calcJoints();
    PVector arbitraryRotate(PVector point, PVector pointA, PVector pointB, double _angle);
    PVector zAxiRotate(PVector point, double _angle);
    PVector calcProjectionPt(PVector pt0, PVector pt1, PVector nVec);

public:
    // IK
    double theta[SERVO_NUM];  // angles
    int IK3(PVector pt);
    int IK5(PVector j6, PVector vec56_d);
    int IK6(PVector j6, PVector vec56_d, PVector vec67_d);
};
