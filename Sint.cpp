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
	//Vérifier si premier caractère est '-'
	if(nombre.at(0) == 45) {
		this->signe = false;
		nombre.erase(nombre.begin());
	} else {
		this->signe = true;
	}
	//Appeler constructeur de Uint.
	this->nombre = nombre;
}

Sint::Sint(int64_t nombre) {
	//Simple copie puis constructeur par string
	std::string nombre_string = std::to_string(nombre);
	*this = Sint(nombre_string);
}


Sint::operator Uint() const {
	Uint nombre_uint;
	nombre_uint = this->nombre;
	return nombre_uint;
}

bool Sint::operator<(const Sint& rhs) const {
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
		//Vu que les signes sont différents, on peut appliquer les lois des maths.
		if (this->nombre > rhs.nombre) {
			this->nombre -= rhs.nombre;
		} else {
			this->nombre = rhs.nombre - this->nombre;
			//On inverse seulement le signe quand le deuxième nombre est plus grand
			this->signe = !this->signe;
		}
	}
	this->retirer_signe_neutralite();
	return *this;
}

Sint& Sint::operator-=(const Sint& rhs) {
	/*
	1. Exemple 2 - 4
	2. Exemple 6 - 3
	3. Exemple -6 - 4
	 */
	if (this->signe == rhs.signe) {
		if (this->nombre > rhs.nombre) {
			this->nombre -= rhs.nombre; //2. 6 - 3 = 3
		} else {
			this->nombre = rhs.nombre - this->nombre; //1. 4 - 2 = 2
			this->signe = !this->signe; //-2
		}
	} else {
		//3. 6 + 4 = 10 Mais, le signe de 6 est - donc -10
		this->nombre += rhs.nombre;
	}
	this->retirer_signe_neutralite();
	return *this;
}

Sint& Sint::operator*=(const Sint& rhs) {
	//Vu que - = 0 et + = 1, donc 1 + 1 = 2 et 2 % 2 = 0 donc si on inverse...
	this->signe = !((this->signe + rhs.signe) % 2);
	this->nombre *= rhs.nombre;
	this->retirer_signe_neutralite();
	return *this;
}

Sint& Sint::operator/=(const Sint& rhs) {
	//Vu que - = 0 et + = 1, donc 1 + 1 = 2 et 2 % 2 = 0 donc si on inverse...
	this->signe = !((this->signe + rhs.signe) % 2);
	this->nombre /= rhs.nombre;
	this->retirer_signe_neutralite();
	return *this;
}

Sint& Sint::operator%=(const Sint& rhs) {
	//Pas besoin de gérer le signe, il va dépendre de *this
	this->nombre %= rhs.nombre;
	this->retirer_signe_neutralite();
	return *this;
}

Sint& Sint::operator--() {
	*this -= 1;
	this->retirer_signe_neutralite();
	return *this;
}

const Sint Sint::operator--(int) {
	Sint temp = *this;
	--*this;
	this->retirer_signe_neutralite();
	temp.retirer_signe_neutralite();
	return temp;
}

std::ostream& operator<<(std::ostream& lhs, const Sint& rhs) {
	if (!rhs.signe) {
		lhs << '-';
	}
	lhs << rhs.nombre;
	return lhs;
}

Sint operator+(Sint lhs, const Sint& rhs) {
	return lhs += rhs;
}

Sint operator-(Sint lhs, const Sint& rhs) {
	return lhs -= rhs;
}

Sint operator*(Sint lhs, const Sint& rhs) {
	return lhs *= rhs;
}

Sint operator/(Sint lhs, const Sint& rhs) {
	return lhs /= rhs;
}

Sint operator%(Sint lhs, const Sint& rhs) {
	return lhs %= rhs;
}

int Sint::comp(const Sint& lhs, const Sint& rhs) const {
	if(lhs.signe == rhs.signe && lhs.nombre == rhs.nombre) {
		return 0;
	}

	//Gérer les cas -1
	if (lhs.signe < rhs.signe) {
		return -1;
	}

	if (!lhs.signe) {
		if (lhs.nombre > rhs.nombre) {
			return -1;
		}
	} else {
		if (lhs.nombre < rhs.nombre) {
			return -1;
		}
	}
	//Sinon, on retourne 1 dans tout les cas
	return 1;
}

void Sint::retirer_signe_neutralite(){
	//On peut mettre un ! mais je préfère m'assurer que c'est la valeur 0
	if(this->nombre == 0) {
		this->signe = true;
	}
}
