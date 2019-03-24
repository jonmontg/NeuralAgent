# NeuralAgent
This is a sample of the code I wrote for my Cognitive Science research with Dr. Randall Beer at Indiana University. 
Our research focused on the behavior of agents in simulated environments given the dynamic interactions between the agent's brain, body, and environment.
Each agent is controlled by a continuous time recurrent neural network (CTRNN) developed by Dr. Beer. I developed an agent to perform
the biologically inspired task of chemotaxis, or chemical gradient ascent. The agents were trained with an evolutionary algorithm
(not shown here), developed by Dr. Beer. 

## Chemotactic Agent
The physics of the chemotactic agent are representative of a circular agent with two wheels. Each agent has a CTRNN brain, an
arbitrary number of "eyes". The brain is a CTRNN with at least 2 neurons. Each eye is a point on the boundary of the agent 
that reads the inverse square of its distance to the chemical source as an input into the brain.

The eyes can have fixed locations or they can be controlled by the brain. Each eye is paired with an input neuron on initialization
and when the eyes are not fixed, the paired neuron drives the eye location.

At each time step in the simulation, the eyes read in their signal strengths and feed them to the brain. The brain performs an 
Euler Step proportional to the step size to update the neuron states and outputs and the new brain state updates the wheel 
speeds and possibly the eye positions. Finally, the agent's position is updated according to first order physics.
