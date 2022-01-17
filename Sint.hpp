/*
-----------------------------------------------------------------------------------
Nom du fichier :    	Sint.hpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Header du fichier Sint.cpp. Ce header implémente la
 							signature des fonctions présentes dans le fichier Sint.cpp.
 							L'attribut nombre étant un Uint, nous pouvons accéder aux
 							fonctions de cette classe pour les différentes opérations
 							arithmétiques.
-----------------------------------------------------------------------------------
*/

#ifndef LABO31_SINT_HPP
#define LABO31_SINT_HPP

#include "Uint.hpp"

class Sint {

public:
	Sint();

	/**
	 * @brief On vérifie si le premier caractère est le signe '-' afin de définir
	 * notre attribut signe (0 = -) (1 = +) puis appel du constructeur de Uint.
	 * @param std::string nombre : valeur de notre Sint
	 */
	Sint(std::string nombre);

	/**
	 * @brief Ce constructeur va appeler le constructeur par string
	 * @param int64_t nombre : valeur de notre Uint
	 */
	Sint(int64_t nombre);

	/**
	 * @brief Cast Sint en Uint
	 * @return Uint : nombre
	 */
	explicit operator Uint() const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator<(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator>(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator<=(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator>=(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator==(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator!=(const Sint& rhs) const;

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint& : *this
	 */
	Sint& operator+=(const Sint& rhs);

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint& : *this
	 */
	Sint& operator-=(const Sint& rhs);

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint& : *this
	 */
	Sint& operator*=(const Sint& rhs);

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint& : *this
	 */
	Sint& operator/=(const Sint& rhs);

	/**
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint& : *this
	 */
	Sint& operator%=(const Sint& rhs);

	/**
	 * @brief opérateur -- pré-fixé (exemple : --i) qui appelle l'opérateur -=
	 * @return Sint& : *this
	 */
	Sint& operator--();

	/**
	 * @brief opérateur -- post-fixé (exemple : i--) qui appelle l'opérateur
	 * pré-fixé (--i).
	 * @return Sint : temp
	 */
	const Sint operator--(int);

private:
	Uint nombre;
	bool signe; //(0 = -) (1 = +)

	/**
	 * @param ostream& lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return ostream& : lhs
	 */
	friend std::ostream& operator<<(std::ostream& lhs, const Sint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur +=
	 * @param Sint lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint : lhs
	 */
	friend Sint operator+(Sint lhs,const Sint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur -=
	 * @param Sint lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint : lhs
	 */
	friend Sint operator-(Sint lhs, const Sint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur *=
	 * @param Sint lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint : lhs
	 */
	friend Sint& operator*(Sint& lhs, const Sint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur /=
	 * @param Sint lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint : lhs
	 */
	friend Sint operator/(Sint lhs, const Sint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur %=
	 * @param Sint lhs : Valeur de gauche
	 * @param Sint& rhs : Valeur de droite
	 * @return Sint : lhs
	 */
	friend Sint operator%(Sint lhs, const Sint& rhs);

	/**
	 * @brief Fonction qui va comparer 2 vecteurs et retourner 0 si ils sont
	 * égaux -1 si a est plus petit que b et 1 sinon.
	 * @param Sint& a : Valeur de gauche
	 * @param Sint& b : Valeur de droite
	 * @return int : constante
	 */
	int comp(const Sint& lhs, const Sint& rhs) const;

	/**
	 * @brief Vu le le nombre 0 n'est pas signé, si le vecteur contient 0 il faut
	 * lui retirer le signe si il était négatif avant.
	 * @return void
	 */
	void retirer_signe_neutralite();

};


#endif //LABO31_SINT_HPP
