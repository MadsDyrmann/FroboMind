#include "roboteq/regulator.hpp"

Regulator::Regulator()
{
	p = i = d = i_max = out_max = 0;
	integrator = previous = 0;
}

/* PID regulator. Input and output must be in equal units */
double Regulator::output_from_input( double setpoint , double input , double period)
{
	// Implement max period
	if(period > 0.5)
		period = 0.5;

	// Calculate errors
	double error = setpoint - input;

	// Calculate integrator
	integrator += error;

	// Implement anti wind up
	if(integrator > i_max)
		integrator = i_max;
	else if(integrator < -i_max)
		integrator = -i_max;

	// Calculate differentiator
	double differentiator = previous - error;

	// Calculate output
	double output = (error * p) + ((integrator * period) * i) + ((differentiator / period)* d);
	//std::cout << "P: " << (error * p) << " I: " << (integrator * i * period) << " D: " << ((differentiator * d) / period) << std::endl;
	//std::cout << setpoint  << "," <<  input << "," << error << std::endl;

	// Implement output max
	if(output > out_max)
		output = out_max;
	else if(output < -out_max)
		output = -out_max;

	// Upkeep
	previous = error;
	return output;
}