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

#ifndef LABO31_UINT_HPP
#define LABO31_UINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Sint;

class Uint {

public:
	Uint();

	/**
	 * @param std::string nombre : valeur de notre Uint
	 */
	Uint(std::string nombre);

	/**
	 * @brief Ce constructeur va appeler le constructeur par string.
	 * @param uint64_t nombre : valeur de notre Uint
	 */
	Uint(uint64_t nombre);

	/**
	 * @brief Convertit un Uint en uint64_t.
	 * @return uint64_t : nombre
	 */
	explicit operator uint64_t() const;
	explicit operator Sint() const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator<(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator>(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator<=(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator>=(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator==(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return bool
	 */
	bool operator!=(const Uint& rhs) const;

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator*=(const Uint& rhs);

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator/=(const Uint& rhs);

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator%=(const Uint& rhs);

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator+=(const Uint& rhs);

	/**
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator-=(const Uint& rhs);

	/**
	 * @param size_t& rhs : Valeur de droite
	 * @return Uint& : *this
	 */
	Uint& operator-=(const size_t& rhs);

	/**
	 * @brief opérateur ++ pré-fixé (exemple : ++i) qui appelle l'opérateur +=.
	 * @return Uint& : *this
	 */
	Uint& operator++();

	/**
	 * @brief opérateur ++ post-fixé (exemple : i++) qui appelle l'opérateur
	 * pré-fixé (++i).
	 * @return Uint : temp
	 */
	const Uint operator++(int);

	/**
	 * @brief opérateur -- pré-fixé (exemple : --i) qui appelle l'opérateur -=.
	 * @return Uint& : *this
	 */
	Uint& operator--();

	/**
	 * @brief opérateur -- post-fixé (exemple : i--) qui appelle l'opérateur
	 * pré-fixé (--i).
	 * @return Uint : temp
	 */
	const Uint operator--(int);

private:
	std::vector<int> nombre;

	/**
	 * @param ostream& lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return ostream& : lhs
	 */
	friend std::ostream& operator<<(std::ostream& lhs, const Uint& rhs);

	/**
	 * @brief Opérateur de sortie utile pour rsa.cpp.
	 * @param istream& is : Fichier
	 * @param Uint& rhs : Valeur lue
	 * @return istream& : is
	 */
	friend std::istream& operator>>(std::istream& is, Uint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur +=.
	 * @param Uint lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator+(Uint lhs, const Uint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur -=.
	 * @param Uint lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator-(Uint lhs, const Uint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur -=.
	 * @param Uint lhs : Valeur de gauche
	 * @param size_t& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator-(Uint lhs, const size_t& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur *=.
	 * @param Uint lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator*(Uint lhs, const Uint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur /=.
	 * @param Uint lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator/(Uint lhs, const Uint& rhs);

	/**
	 * @brief Appel de la surcharge de l'opérateur %=.
	 * @param Uint lhs : Valeur de gauche
	 * @param Uint& rhs : Valeur de droite
	 * @return Uint : lhs
	 */
	friend Uint operator%(Uint lhs, const Uint& rhs);

	/**
	 * @brief Fonction qui va comparer 2 vecteurs et retourner 0 si ils sont
	 * égaux -1 si a est plus petit que b et 1 sinon.
	 * @param Uint& a : Valeur de gauche
	 * @param Uint& b : Valeur de droite
	 * @return int : constante
	 */
	int comp(const Uint& a, const Uint& b) const;

	/**
	 * @brief Lors des opérations sur notre vecteur, il peut arriver qu'il contient
	 * des 0 dans les dernières positions (par exemple si je soustrait 10 à 100 le
	 * résultat serait 090).
	 * @return void
	 */
	void fit();

	/**
	 * @return Uint& : *this
	 */
	Uint& division_par2();

	/**
	 * @param Uint& diviseur : sert aussi pour l'opération %.
	 * @return Uint : quotient
	 */
	Uint division_reste(Uint& diviseur);
};

#endif //LABO31_UINT_HPP
