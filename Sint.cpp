/*
--------------------------------------------------------------------------------
Nom du fichier :    	Sint.cpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Cette classe est relativement similaire à Uint, mais elle
 							gère les nombres signés. Elle implémente aussi les
 							opérateurs arithmétiques de base (+=, +, -, -=, *=, *, /=,
 							/, %= et %) ainsi que les opérateurs de comparaison (<, >,
 							<=, >=, ==, !=). Cette classe va appeler les constructeurs
 							de Uint et stocker le signe afin de savoir si le nombre est
 							positif ou négatif.
--------------------------------------------------------------------------------
*/

#include "Sint.hpp"

Sint::Sint() = default;

Sint::Sint(std::string nombre) {
	//Verifier si premier caractère est '-'
	if(nombre.at(0) == 45) {
		this->signe = false;
		nombre.erase(nombre.begin());
	} else {
		this->signe = true;
	}
	this->nombre = nombre;
}

Sint::Sint(int64_t nombre) {
	//Simple copie
	std::string nombre_string = std::to_string(nombre);
	if(nombre_string.at(0) == 45) {
		this->signe = false;
		nombre_string.erase(nombre_string.begin());
	} else {
		this->signe = true;
	}
	this->nombre = Uint(nombre_string);
}

bool Sint::operator<(const Sint &rhs) const {
	return comp(*this, rhs) == -1;
}

bool Sint::operator>(const Sint& rhs) const {
	return comp(*this, rhs) == 1;
}

bool Sint::operator<=(const Sint& rhs) const {
	return (comp(*this, rhs) == -1 || comp(*this, rhs) == 0);
}

bool Sint::operator>=(const Sint& rhs) const {
	return (comp(*this, rhs) == 1 || comp(*this, rhs) == 0);
}

bool Sint::operator==(const Sint& rhs) const {
	return comp(*this, rhs) == 0;
}

bool Sint::operator!=(const Sint& rhs) const {
	return comp(*this, rhs) != 0;
}

Sint& Sint::operator+=(const Sint& rhs) {
	if (this->signe == rhs.signe) {
		this->nombre += rhs.nombre;
	} else {
		if (this->nombre > rhs.nombre) {
			this->nombre = this->nombre - rhs.nombre;
		} else {
			this->nombre = rhs.nombre - this->nombre;
			//On inverse seulement le signe quand le deuxième nombre est plus grand
			this->signe = !this->signe;
		}
	}
	return *this;
}

Sint& Sint::operator-=(const Sint& rhs) {
	if (this->signe == rhs.signe) {
		if (this->nombre > rhs.nombre) {
			this->nombre = this->nombre - rhs.nombre;
		} else {
			this->nombre = rhs.nombre - this->nombre;
			//On inverse seulement le signe quand le deuxième nombre est plus grand
			this->signe = !this->signe;
		}

	} else {
		this->nombre += rhs.nombre;
	}

	return *this;
}

Sint& Sint::operator*=(const Sint& rhs) {
	this->signe = !((this->signe + rhs.signe) % 2);
	this->nombre *= rhs.nombre;
	return *this;
}

Sint& Sint::operator/=(const Sint& rhs) {
	this->signe = !((this->signe + rhs.signe) % 2);
	this->nombre /= rhs.nombre;
	return *this;
}

Sint& Sint::operator%=(const Sint& rhs) {
	this->nombre %= rhs.nombre;
	return *this;
}

std::ostream& operator<<(std::ostream& lhs, const Sint& rhs) {
	if (!rhs.signe) {
		lhs << '-';
	}
	lhs << rhs.nombre;
	return lhs;
}

Sint operator+(Sint lhs, const Sint& rhs) {
	return lhs += rhs; //Appel à +=
}

Sint operator-(Sint lhs, const Sint& rhs) {
	return lhs -= rhs; //Appel à -=
}

Sint& operator*(Sint lhs, const Sint& rhs) {
	return lhs *= rhs;
}

Sint operator/(Sint lhs, const Sint& rhs) {
	return lhs /= rhs;
}

Sint operator%(Sint lhs, const Sint& rhs) {
	lhs %= rhs;
	return lhs;
}

int Sint::comp(const Sint& lhs, const Sint& rhs) const {
	if (lhs.signe < rhs.signe) {
		return -1;
	} else if (lhs.signe > rhs.signe) {
		return 1;
	}
	if (lhs.signe == rhs.signe) {
		if (lhs.signe == 0) {
			if (this->nombre > rhs.nombre) {
				return 1;
			}
			if (this->nombre < rhs.nombre) {
				return -1;
			}
		} else {
			if (this->nombre < rhs.nombre) {
				return -1;
			}
			if (this->nombre > rhs.nombre) {
				return 1;
			}
		}
	}
	return 0;
}
