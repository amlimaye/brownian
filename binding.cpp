#include "potential.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(potential, m) {
	py::class_<OneWell>(m, "OneWell")
		.def(py::init<real_t>())
		.def("energy", &OneWell::energy)
		.def("gradient", &OneWell::gradient);

	py::class_<TwoWell>(m, "TwoWell")
		.def(py::init<>())
		.def("energy", &TwoWell::energy)
		.def("gradient", &TwoWell::gradient);

	py::class_<AsymmetricOneWell>(m, "AsymmetricOneWell")
		.def(py::init<real_t, real_t>())
		.def("energy", &AsymmetricOneWell::energy)
		.def("gradient", &AsymmetricOneWell::gradient);
}