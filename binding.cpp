#include "potential.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <sstream>

namespace py = pybind11;

PYBIND11_MODULE(potential, m) {
	py::class_<OneWell>(m, "OneWell")
		.def(py::init<real_t>())
		.def("energy", &OneWell::energy)
		.def("energy",
			[](OneWell o, real_t x, real_t y) {
			 	real_vec_t pos = {x,y};
			 	return o.energy(pos);
			})
		.def("gradient", &OneWell::gradient)
		.def("gradient", 
			[](OneWell o, real_t x, real_t y) {
				real_vec_t pos = {x,y};
				return o.gradient(pos);
			})
		.def("__repr__",
			[](const OneWell& o) {
				std::stringstream s;
				s.precision(4);
				s << "<potential.OneWell with curvature " << o.curvature << ">";
				return s.str();
			});

	py::class_<TwoWell>(m, "TwoWell")
		.def(py::init<>())
		.def("energy", &TwoWell::energy)
		.def("energy",
			[](TwoWell o, real_t x, real_t y) {
			 	real_vec_t pos = {x,y};
			 	return o.energy(pos);
			})
		.def("gradient", &TwoWell::gradient)
		.def("gradient", 
			[](TwoWell o, real_t x, real_t y) {
				real_vec_t pos = {x,y};
				return o.gradient(pos);
			})
		.def("__repr__",
			[](const TwoWell& o) {
				return "<potential.TwoWell>";
			});

	py::class_<AsymmetricOneWell>(m, "AsymmetricOneWell")
		.def(py::init<real_t, real_t>())
		.def("energy", &AsymmetricOneWell::energy)
		.def("energy",
			[](AsymmetricOneWell o, real_t x, real_t y) {
			 	real_vec_t pos = {x,y};
			 	return o.energy(pos);
			})
		.def("gradient", &AsymmetricOneWell::gradient)
		.def("gradient", 
			[](AsymmetricOneWell o, real_t x, real_t y) {
				real_vec_t pos = {x,y};
				return o.gradient(pos);
			})
		.def("__repr__",
			[](const AsymmetricOneWell& o) {
				std::stringstream s;
				s.precision(4);
				s << "<potential.AsymmetricOneWell with curvatures (" 
				  << o.x_curvature << ", " << o.y_curvature << ")>";
				return s.str();
			});
}