/*
--------------------------------------------------------------------------------
Nom du fichier :    	Uint.hpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Header du fichier Uint.cpp. Ce header implémente la
 							signature des fonctions présentes dans le fichier Uint.cpp.
--------------------------------------------------------------------------------
*/

#ifndef LABO30_UINT_HPP
#define LABO30_UINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Uint {

public:
	Uint();
	Uint(std::string nombre);
	Uint(uint64_t nombre);
	explicit operator uint64_t() const;
	bool operator<(const Uint& rhs) const;
	bool operator>(const Uint& rhs) const;
	bool operator<=(const Uint& rhs) const;
	bool operator>=(const Uint& rhs) const;
	bool operator==(const Uint& rhs) const;
	bool operator!=(const Uint& rhs) const;

	Uint& operator*=(const Uint& rhs);
	Uint& operator/=(const Uint& rhs);
	Uint& operator%=(const Uint& rhs);
	Uint& operator+=(const Uint& rhs);
	Uint& operator-=(const Uint& rhs);
	Uint& operator-=(const size_t& rhs);

	Uint& operator++();
	const Uint operator++(int);
	Uint& operator--();
	const Uint operator--(int);

private:
	std::vector<int> nombre;

	friend std::ostream& operator<<(std::ostream& lhs, const Uint& rhs);
	friend std::istream& operator>>(std::istream& is, Uint& premierNombre);
	friend Uint operator+(Uint lhs, const Uint& rhs);
	friend Uint operator-(Uint lhs, const Uint& rhs);
	friend Uint operator-(Uint lhs, const size_t& rhs);
	friend Uint operator*(Uint lhs, const size_t& rhs);
	friend Uint& operator*(Uint lhs, const Uint& rhs);
	friend Uint operator/(Uint lhs, const Uint& rhs);
	friend Uint operator%(Uint lhs, const Uint& rhs);
	friend class Sint;

	int comp(const Uint& a, const Uint& b) const;
	void fit();
	Uint& division_par2();
	Uint division_reste(Uint& diviseur);
};

#endif //LABO30_UINT_HPP
