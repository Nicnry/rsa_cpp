/*
-----------------------------------------------------------------------------------
Nom du fichier :    	Sint.hpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Header du fichier Sint.cpp. Ce header implémente la
 							signature des fonctions présentes dans le fichier Sint.cpp.
-----------------------------------------------------------------------------------
*/

#ifndef LABO31_SINT_HPP
#define LABO31_SINT_HPP

#include "Uint.hpp"

class Sint {

public:
	Sint();
	Sint(std::string nombre);
	Sint(int64_t nombre);
	bool operator<(const Sint& rhs) const;
	bool operator>(const Sint& rhs) const;
	bool operator<=(const Sint& rhs) const;
	bool operator>=(const Sint& rhs) const;
	bool operator==(const Sint& rhs) const;
	bool operator!=(const Sint& rhs) const;

	Sint& operator+=(const Sint& rhs);
	Sint& operator-=(const Sint& rhs);
	Sint& operator*=(const Sint& rhs);
	Sint& operator/=(const Sint& rhs);
	Sint& operator%=(const Sint& rhs);

private:
	Uint nombre;
	bool signe; //(0 = -) (1 = +)

	friend std::ostream& operator<<(std::ostream& lhs, const Sint& rhs);
	friend Sint operator+(Sint lhs,const Sint& rhs);
	friend Sint operator-(Sint lhs, const Sint& rhs);
	friend Sint& operator*(Sint lhs, const Sint& rhs);
	friend Sint operator/(Sint lhs, const Sint& rhs);
	friend Sint operator%(Sint lhs, const Sint& rhs);

	int comp(const Sint& lhs, const Sint& rhs) const;

};


#endif //LABO31_SINT_HPP
