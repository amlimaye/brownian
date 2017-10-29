#include "potential.hpp"

AsymmetricOneWell::AsymmetricOneWell(real_t a_x_curvature, real_t a_y_curvature) {
	x_curvature = a_x_curvature;
	y_curvature = a_y_curvature;
};

real_t AsymmetricOneWell::energy (real_vec_t position) {
	real_t x_sq = position[0]*position[0];
	real_t y_sq = position[1]*position[1];
	return (x_curvature*x_sq + y_curvature*y_sq);
};

real_vec_t AsymmetricOneWell::gradient (real_vec_t position) {
	real_t x_two = 2*position[0];
	real_t y_two = 2*position[1];
	real_vec_t grad = {x_curvature * x_two, y_curvature * y_two};
	return grad;	
};


OneWell::OneWell(real_t a_curvature) {
	curvature = a_curvature;
};

real_t OneWell::energy (real_vec_t position) {
	real_t x_sq = position[0]*position[0];
	real_t y_sq = position[1]*position[1];
	return curvature*(x_sq + y_sq);
};

real_vec_t OneWell::gradient (real_vec_t position) {
	real_t x_two = 2*position[0];
	real_t y_two = 2*position[1];
	real_vec_t grad = {x_two, y_two};
	return curvature*grad;	
};


real_t TwoWell::energy (real_vec_t position) {
	auto x = position[0];
	auto y = position[1];

	auto x2 = x*x;
	auto x4 = x2*x2;
	auto y2 = y*y;

	auto energy = x4 - x2 + y2 + 0.25;
	return energy;
};

real_vec_t TwoWell::gradient (real_vec_t position) {
	auto x = position[0];
	auto y = position[1];

	auto x3 = x * x * x;

	auto grad_x = 4 * x3 - 2*x;
	auto grad_y = 2*y;
	real_vec_t grad = {grad_x, grad_y};
	return grad;
};