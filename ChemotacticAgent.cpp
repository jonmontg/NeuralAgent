//
// Created by Jon Montgomery on 10/15/2018.
//

#include "ChemotacticAgent.h"
#include "random.h"
#include <math.h>

using namespace std;


double MaxSpeed = 0.1;
double MaxSignal = 10;


/*
 * Reset Chemotactic Agent to the specified location. If randomized, given random angle and nervous system parameters
 */
void ChemotacticAgent::Reset(double ix, double iy, int randomize)
{
    cx=ix; cy=iy;
    Angle=(randomize)?UniformRandom(-Pi,Pi):0;
    if (randomize) NervousSystem.RandomizeCircuitState(-0.1,0.1);
    else NervousSystem.RandomizeCircuitState(0.0,0.0);
}

/*
 * Reset Chemotactic Agnet to specified location. If randomized, given random angel and nervous system parameters
 * from given random state
 * */
void ChemotacticAgent::Reset(double ix, double iy, int randomize, RandomState &rs)
{
    cx=ix; cy=iy;
    Angle=(randomize)?rs.UniformRandom(-Pi,Pi):0;
    if (randomize) NervousSystem.RandomizeCircuitState(-0.1,0.1,rs);
    else NervousSystem.RandomizeCircuitState(0.0,0.0,rs);
}

/*
 * Adds a Chemotactic agent eye at the given angle that gives a signal to the given neuron number
 */
void ChemotacticAgent::AddEye(double angle, int eyeneuron)
{
    EyeAngles.add(angle);
    EyeNeurons.add(eyeneuron);
}

/*
 * Sets the eye to the given angle on the Agent
 */
void ChemotacticAgent::SetEyeAngle(int eyenum, double angle)
{
    EyeAngles.set(eyenum, angle);
}

/*
 * Updates the nervous system with signals from the eyes and Euler Steps the nervous system. Then updates
 * the forces on the Chemotactic Agent to update its position
 */
void ChemotacticAgent::Step(double StepSize)
{
    SetNeuronInputSignals();
    NervousSystem.EulerStep(StepSize);
    UpdatePhysics();

    // if eyes are fixed, stop
    if (FixedEyes)
        return;

    // if eyes are not fixed, update eye locations
    EyeNeurons.iterator();
    for (int eye=1; eye<=EyeAngles.Size; eye++) {
        EyeAngles.set(eye, NervousSystem.NeuronOutput(EyeNeurons.next())*Pi);
    }
}

/*
 * Update the input for each neuron based on the signal strength measured by the agent's eyes.
 */
ChemotacticAgent::SetNeuronInputSignals()
{
     // updates eye signals to 1/r^2 where r is the distance to the signal source
    EyeAngles.iterator();
    EyeNeurons.iterator();
    for (int eye=1; eye<=EyeAngles.Size; eye++) {
        double EyeAngle = EyeAngles.next();
        double EyeX = cx + (Radius*cos(EyeAngle+Angle));
        double EyeY = cy + (Radius*sin(EyeAngle+Angle));
        double d = ((SourceX - EyeX) * (SourceX - EyeX)) + ((SourceY - EyeY) * (SourceY - EyeY));
        double signal = (d == 0) ? MaxSignal : 1 / d;
        if (signal > MaxSignal)
            signal = MaxSignal;

        int eyen = EyeNeurons.next();
        NervousSystem.SetNeuronExternalInput(eyen, signal*InputWeights[eyen]);
    }
}

/*
 * Update the first order kinematics of the chemotactic agent.
 */
ChemotacticAgent::UpdatePhysics()
{
    double RightVel = NervousSystem.NeuronOutput(RightDriver)*MaxSpeed;
    double LeftVel = NervousSystem.NeuronOutput(LeftDriver)*MaxSpeed;
    double Linear = RightVel+LeftVel;
    cx += Linear*cos(Angle);
    cy += Linear*sin(Angle);
    Angle += (RightVel-LeftVel)/Radius;
}
