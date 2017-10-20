#include "types.hpp"
#include <iomanip>

class PositionTrajectory {
public:
	PositionTrajectory() {};

	PositionTrajectory(std::string fname) {
		std::ifstream fin(fname);
		std::string line;

		while (fin >> line) {
			auto pos = line.find(" ");
			std::string x_str = line.substr(0,pos);
			auto x_num = std::stod(x_str);
			line.erase(0,pos+1); 				//erase up to the dlm length
			auto y_num = std::stod(line);

			real_vec_t entry = {x_num, y_num};
			positions.push_back(entry);
		}
	};

	real_vec_t get_frame(size_t index) {
		if (index > positions.size()) {
			throw std::out_of_range("Index out of range.");
		}
		else {
			return positions[index];
		}
	};

	void add_frame(const real_vec_t& frame) {
		positions.push_back(frame);
	};

	void dump(std::string fname) {
		std::ofstream fout(fname);
		for (auto p : positions) {
			fout << std::setprecision(8) << p[0] << " " 
				 << std::setprecision(8) << p[1] << std::endl;
		}
	};

private:
	std::vector<real_vec_t> positions;
};

class EnergyTrajectory {
public:
	EnergyTrajectory() {};

	EnergyTrajectory(std::string fname) {
		std::ifstream fin(fname);
		std::string line;

		while (fin >> line) {
			auto e_num = std::stod(line);
			energies.push_back(e_num);
		}
	};

	real_t get_frame(size_t index) {
		if (index > energies.size()) {
			throw std::out_of_range("Index out of range.");
		}
		else {
			return energies[index];
		}
	};

	void add_frame(const real_t& frame) {
		energies.push_back(frame);
	};

	void dump(std::string fname) {
		std::ofstream fout(fname);
		for (auto e : energies) {
			fout << std::setprecision(8) << e << std::endl;
		}
	};

private:
	std::vector<real_t> energies;
};