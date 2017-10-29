#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include <tuple>
#include <json/json.h>
#include "types.hpp"
#include "langevin.hpp"
#include "potential.hpp"
#include "trajectory.hpp"

std::ostream& operator<<(std::ostream& stream, const real_vec_t vector) {
	stream << "(" << vector[0] << "," << vector[1] << ")";
	return stream;
}

inline std::string parse_args(const int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " cfg.json" << std::endl;
		std::exit(1);
	}

	return std::string(argv[1]);
}

std::tuple<unsigned long, uint32_t, real_t> parse_json(std::string fname) {
	std::ifstream input_file(fname);
	Json::Value input;
	input_file >> input;

	unsigned long nsteps = input["nsteps"].asInt();
	uint32_t rand_seed = input["seed"].asInt();
	real_t kt = input["kt"].asDouble();

	return std::make_tuple(nsteps,rand_seed,kt);
}

int main(int argc, char* argv[]) {
	//parse cmdline args
	unsigned long nsteps;
	real_t kt;
	uint32_t seed;
	std::tie(nsteps,seed,kt) = parse_json(parse_args(argc,argv));

	const real_vec_t initial_position = {0.0,0.0};
	const real_t d_coeff = 1.00;
	const real_t beta = 1.0/kt;
	const real_t mass = 1.00;
	const real_t dt = 0.001;
	// const real_t x_curvature = 1.0;
	// const real_t y_curvature = 0.1;

	// AsymmetricOneWell potfunc(x_curvature, y_curvature);
	TwoWell potfunc;
	Langevin integrator(seed,dt,beta,d_coeff);
	PositionTrajectory p_traj;
	EnergyTrajectory e_traj;
	
	p_traj.add_frame(initial_position);
	e_traj.add_frame(potfunc.energy(initial_position));
	
	for (unsigned long i = 0; i < nsteps; i++) {
		auto pos = p_traj.get_frame(i);
		integrator.take_step(pos,mass,potfunc.gradient(pos));
		auto energy = potfunc.energy(pos);

		p_traj.add_frame(pos);
		e_traj.add_frame(energy);
	};

	p_traj.dump("trajectory.txt");
	e_traj.dump("energy.txt");

	return 0;
}