#include <cmath>

class Langevin {
public:
	Langevin(uint32_t seed, real_t a_dt, real_t a_beta, real_t a_d_coeff) {
	    generator.seed(seed);

		//still need to divide these off by mass when doing integration
		grad_scale = -1 * a_d_coeff * a_beta * a_dt;
		kick_scale = std::sqrt(2 * a_d_coeff * a_dt);
	};

	void take_step(real_vec_t& last_position, real_t mass, const real_vec_t& gradient) {
		//get the force with scaled position
		auto scaled_force = grad_scale * gradient / mass;

		//get the langevin kick
    	std::normal_distribution<real_t> normal(0.0,1.0);
		real_vec_t kick = {normal(generator), normal(generator)};
		auto scaled_kick = kick_scale * kick / std::sqrt(mass);

		//std::cout << "grad: " << scaled_force << std::endl;
		//std::cout << "kick: " << scaled_kick << std::endl;

		//update the last position
		last_position += scaled_force + scaled_kick;
	};

private:
	//RNG
    std::mt19937 generator;

	//derived values
	real_t grad_scale;
	real_t kick_scale;
};
