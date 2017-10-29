#include "types.hpp"

//ABC for potential classes
class Potential {
public:
	virtual real_t energy(real_vec_t pos) = 0;
	virtual real_vec_t gradient(real_vec_t pos) = 0;
};

class AsymmetricOneWell : Potential {
public:	
	AsymmetricOneWell(real_t a_x_curvature, real_t a_y_curvature);
	real_t energy (real_vec_t position); 
	real_vec_t gradient (real_vec_t position);

	real_t x_curvature;
	real_t y_curvature;
};

class OneWell : Potential {
public:	
	OneWell(real_t a_curvature);
	real_t energy (real_vec_t position);
	real_vec_t gradient (real_vec_t position);

	real_t curvature;
};

class TwoWell : Potential {
public:
	TwoWell() {};
	real_t energy (real_vec_t position);
	real_vec_t gradient (real_vec_t position);
};