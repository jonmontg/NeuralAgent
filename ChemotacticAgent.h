//
// Created by jonmo on 10/15/2018.
//
#include "CTRNN.h"
#include "LinkedList.h"

#pragma once

#ifndef PI
#define PI
const double Pi = 3.1415926;
#endif

using namespace std;


class ChemotacticAgent {
public:
    // The constructor
    ChemotacticAgent() {};
    // The destructor
    ~ChemotacticAgent() {};

    // Control
    void Step(double StepSize);
    void SetSource(double x, double y) {SourceX=x;SourceY=y;};
    void Reset(double ix, double iy, int randomize = 0);
    void Reset(double ix, double iy, int randomize, RandomState &rs);
    void AddEye(double angle, int linkedneuron);
    void SetEyeAngle(int eyenum, double angle);
    void SetRadius(double r) {Radius=r;};
    void FixEyes();

    double cx, cy, Angle, Radius=2, SourceX, SourceY;
    int FixedEyes = 0, RightDriver=1, LeftDriver=2;
    TVector<double> InputWeights;
    LinkedList<int> EyeNeurons;
    LinkedList<double> EyeAngles;
    CTRNN NervousSystem;
};