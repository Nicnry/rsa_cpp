/*
--------------------------------------------------------------------------------
Nom du fichier :    	Uint.cpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Classe qui permet de gérer des unsigned int de taille
 							indéfiniment longue. Elle implémente les opérateurs de base
 							(+=, +, -, -=, *=, *, /=, /, %=, %, ++ et --) ainsi que les
 							opérateurs de comparaison (<, >, <=, >=, ==, !=). Cette
 							classe est en réalité un vecteur qui va stocker un nombre en
 							le décomposant en unité, dizaine, centaine, etc...et dans le
 							sens inverse (exemple : 1423 sera stocké {3, 2, 4, 1}) afin
 							d'éviter des opérations trop complexes lors des opérations
 							arithmétiques.
--------------------------------------------------------------------------------
*/

#include "Uint.hpp"

Uint::Uint() = default;

Uint::Uint(std::string nombre) {
	//Inverser le nombre afin de faire des push_back et ne pas devoir tout re-trier.
	for(size_t i = nombre.length() + 1; i > 0; --i) {
		if(i != nombre.length() + 1 && isdigit(nombre[i - 1])) {
			this->nombre.push_back(nombre[i - 1] - 48);
		}
	}
	this->fit();
}

Uint::Uint(uint64_t nombre) {
	//Simple copie
	std::string nombre_string = std::to_string(nombre);
	*this = Uint(nombre_string);
}

Uint::operator uint64_t() const {
	uint64_t nombre = 0;
	int multiplicateur = 1;
	for (size_t i = 0; i < this->nombre.size(); i++)
	{
		if(i){
			multiplicateur *= 10;
		}
		nombre += this->nombre.at(i) * multiplicateur;
	}
	return nombre;
}

bool Uint::operator<(const Uint& rhs) const {
	return comp(*this, rhs) == -1;
}

bool Uint::operator>(const Uint& rhs) const {
	return comp(*this, rhs) == 1;
}

bool Uint::operator<=(const Uint& rhs) const {
	return (comp(*this, rhs) == -1 || comp(*this, rhs) == 0) ;
}

bool Uint::operator>=(const Uint& rhs) const {
	return (comp(*this, rhs) == 1 || comp(*this, rhs) == 0);
}

bool Uint::operator==(const Uint& rhs) const {
	return comp(*this, rhs) == 0;
}

bool Uint::operator!=(const Uint& rhs) const {
	return comp(*this, rhs) != 0;
}

Uint& Uint::operator*=(const Uint& rhs) {
	Uint resultat = 0;
	Uint manipulations;
	int report = 0;
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		manipulations.nombre.clear();
		//*10 en fonction de l'avancée du calcul
		for(size_t k = 0; k < i; ++k) {
			manipulations.nombre.push_back(0);
		}
		//Multiplication basique
		for(int j : rhs.nombre) {
			manipulations.nombre.push_back(this->nombre.at(i) * j);
		}
		//Recalculer chaque cellule
		for(int& l : manipulations.nombre) {
			int temp = l + report;
			l = temp % 10;
			report = temp / 10;
		}

		//Si il y a un dernier report
		if(report) {
			manipulations.nombre.push_back(report);
		}
		report = 0;
		resultat = manipulations + resultat;
		resultat.fit();
	}

	*this = resultat;
	return *this;
}

Uint& Uint::operator/=(const Uint& rhs) {
	Uint temp = rhs;
	*this = this->division_reste(temp);
	return *this;
}

Uint& Uint::operator%=(const Uint& rhs) {
	Uint temp = rhs;
	this->division_reste(temp);
	*this = temp;
	return *this;
}

Uint& Uint::operator+=(const Uint& rhs) {
	Uint temp = rhs;
	//Définir le plus petit pour éviter les overflows
	size_t difference_de_taille = 0;
	if(this->nombre.size() > rhs.nombre.size()) {
		difference_de_taille = this->nombre.size() - rhs.nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			temp.nombre.push_back(0);
		}
	} else {
		difference_de_taille = rhs.nombre.size() - this->nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			this->nombre.push_back(0);
		}
	}
	int report = 0;
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		int somme = this->nombre.at(i) + temp.nombre.at(i) + report;
		this->nombre.at(i) = somme % 10;
		report = somme / 10;
	}
	if(report) {
		this->nombre.push_back(report);
	}
	return *this;
}

Uint& Uint::operator-=(const Uint& rhs) {
	Uint temp = rhs;
	// Check for underflow.
	if(*this < temp) {
		std::cerr << "Underflow";
		*this = 0;
		return *this;
	}
	while(this->nombre.size() != temp.nombre.size()) {
		temp.nombre.push_back(0);
	}
	for(size_t i = 0; i < temp.nombre.size(); ++i) {
		//
		if (this->nombre.at(i) >= temp.nombre.at(i)) {
			this->nombre.at(i) = this->nombre.at(i) - temp.nombre.at(i);
		} else if(i != this->nombre.size() - 1 && this->nombre.at(i) < temp.nombre.at(i)) {
			this->nombre.at(i) = this->nombre.at(i) + 10 - temp.nombre.at(i);
			this->nombre.at(i + 1) = this->nombre.at(i + 1) - 1;
		}
	}
	this->fit();
	return *this;
}

Uint& Uint::operator-=(const size_t& rhs) {
	Uint temp = rhs;
	return *this -= temp;
}

Uint& Uint::operator++() {
	return *this += 1; //++n
}

const Uint Uint::operator++(int) {
	//n++
	Uint temp = *this;
	++*this;
	return temp;
}

Uint& Uint::operator--() {
	return *this -= 1; //Appel de -=
}

const Uint Uint::operator--(int) {
	Uint temp = *this;
	--*this;
	return temp;
}

std::ostream& operator<<(std::ostream& lhs, const Uint& rhs) {
	for (size_t i = rhs.nombre.size(); i > 0; --i) {
		lhs << rhs.nombre.at(i - 1);
	}
	return lhs;
}

std::istream& operator>>(std::istream& is, Uint& premierNombre) {
	std::string temp;
	if (is >> temp) {
		premierNombre = temp;
	} else {
		is.clear(std::ios::badbit | is.rdstate());
	}
	return is;
}

Uint operator+(Uint lhs, const Uint& rhs) {
	return lhs += rhs; //Appel à +=
}

Uint operator-(Uint lhs, const Uint& rhs) {
	return lhs -= rhs; //Appel à -=
}

Uint operator-(Uint lhs, const size_t &rhs) {
	Uint temp = rhs;
	return lhs -= temp; //Appel à -=
}

Uint operator*(Uint lhs, const size_t& rhs) {
	return lhs *= rhs; //Appel à *=
}

Uint& operator*(Uint lhs, const Uint& rhs) {
	const Uint& temp = rhs;
	return lhs *= temp; //Appel à *=
}

Uint operator/(Uint lhs, const Uint& rhs) {
	return lhs /= rhs; //Appel à /=
}

Uint operator%(Uint lhs, const Uint& rhs) {
	return lhs %= rhs; //Appel à %=
}

int Uint::comp(const Uint& a, const Uint& b) const {
	if(a.nombre == b.nombre) {
		return 0;
	}
	//lhs < rhs
	if (a.nombre.size() < b.nombre.size()) {
		return -1;
	}
	//lhs < rhs
	if(a.nombre.size() == b.nombre.size()) {
		for (size_t i = a.nombre.size(); i > 0; --i) {
			if(a.nombre.at(i - 1) < b.nombre.at(i - 1)) {
				return -1;
			}
			if(a.nombre.at(i - 1) > b.nombre.at(i - 1)) {
				return 1;
			}
		}
	}
	return 1;
}

void Uint::fit() {
	while (!this->nombre.back() && this->nombre.size() > 1) {
		this->nombre.pop_back();
	}
}

Uint& Uint::division_par2() {
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		if(i && this->nombre.at(i) % 2) {
			this->nombre.at(i - 1) += 5;
		}
		this->nombre.at(i) /= 2;
	}
	if(!this->nombre.back()) {this->nombre.pop_back();}
	return *this;
}

Uint Uint::division_reste(Uint& diviseur) {
	Uint p2 = 1;
	Uint b = diviseur;
	while (b <= *this) {
		p2 *= 2;
		b *= 2;
	}
	Uint quotient = 0;
	Uint reste = *this;
	while (reste >= diviseur) {
		b.division_par2();
		p2.division_par2();
		if (reste >= b) {
			quotient = quotient + p2;
			reste = reste - b;
		}
	}
	if(reste.nombre.empty()) {
		reste.nombre.push_back(0);
	}
	diviseur = reste;
	return quotient;
}
