/*
-----------------------------------------------------------------------------------
Nom du fichier :    	henry_labo31.cpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	11.01.2022
Laboratoire n° :    	31
Description    :		Ce laboratoire reprend le laboratoire 16 fait plus tôt dans
 							l'année. Il a pour but de demander à l'utilisateur de
 							sélectionner une taille de clef (pour p et q) et ainsi de
 							générer des clefs pour chiffrer et déchiffrer un texte (
 							voir rsa.cpp). Pour plus d'informations sur les fonctions
 							dans ce laboratoire, voir le laboratoire 16 (
 							https://github.com/Nicnry/RSA_cpp_basique/blob/main/main.cpp).
 							La constante E sert à générer une partie de la clef publique
 							et a été demandée lors du cours.
-----------------------------------------------------------------------------------
*/

#include "Sint.hpp"
#include "Uint.hpp"
#include <iostream>
#include <string>
#include <random>

using namespace std;
/**
 * La graine va servir à générer un nombre aléatoire. Il est déclarer hors du
 * main afin d'être accessible dans toutes les fonctions. C'est un subterfuge
 * pour ce labo, il est fortement décommandé de faire ceci pour de la vrai
 * cryptographie. le nombre choisi pour la graine est aléatoire, d'autres
 * chiffres iraient aussi.
 */
const uint32_t GRAINE = 19283;
const Uint E = 17;
mt19937 mt_rand(GRAINE);
uniform_int_distribution<int32_t> distribution(0, 9);

/**
 * @brief La fonction d’exponentiation modulaire (b^e mod m), où b, e et m sont
 * des entiers positifs. Pour implanter cette fonction efficacement, peut
 * remarquer que si e est pair, sa valeur vaut (((b2) mod m)(e/2)), ce qui
 * permet de diviser par 2 le nombre de  multiplications. Si b est impair, sa
 * valeur vaut : (b * be−1 mod m). On en dérive un algorithme efficace donné
 * dans l'énoncé, et est implanté dans une fonction de ce programme. Enfin, une
 * fonction de verification valide si la fonction de l'exponentiation modulaire
 * est le même résultat que (b^e mod m). Attention, le nom a changé dans ce
 * laboratoire car le fichier fournit pour les tests utilise la fonction
 * "mod_pow".
 * @param Uint base : b
 * @param Uint exposant : e
 * @param Uint& modulo : m
 * @return Uint : resultat
 */
Uint mod_pow(Uint base, Uint exposant, const Uint& modulo);

/**
 * @brief La problématique est la factorisation des nombres en informatiques qui
 * est extrêmement complexe, ici on "factorise" afin de savoir si un nombre est
 * premier ou non.
 * @param Uint& nombre : nombre à tester si il est premier ou non.
 * @return bool : Si le nombre est premier ou non (true = premier).
 */
bool test_rapide_primalite(const Uint& nombre);

/**
 * @brief Cette fonction retourne 2 éléments, le PGDC en return, ainsi
 * que l'inverse par référence. L'inverse est le nombre qui permet de retrouver
 * le même résultat de (nombre^x % modulo) et (nombre^y % modulo), dans ce cas,
 * y est l'inverse de x et le résultat serait identique. Plus d'informations
 * sur : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu.
 * @param Sint& nombre1 : pgdc
 * @param Sint nombre2 : pgdc_prime
 * @param Sint& inverse : retourne l'inverse par référence
 * @return Uint : PGDC de 2 nombres.
 */
Uint euclide_etendue(const Sint& nombre1, Sint nombre2, Sint& inverse);


/**
 * @brief Générateur de nombre (Uint) aléatoire avec une vérification au cas ou
 * le générateur sort un 0 pour le premier nombre.
 * @param size_t nombre : Taille souhaitée par l'utilisateur
 * @return Uint : Un nombre aléatoire de taille choisie par l'utilisateur
 */
Uint generateur_aleatoire(size_t nombre);

int main() {
	int taille_de_clef;
	cout << "Veuillez choisir une taille de clef  : ";
	bool saisie_fausse;
	do {
		cin >> taille_de_clef;
		if (cin.fail() || taille_de_clef <= 0) {
			saisie_fausse = true;
			cin.clear(); //Reset des bits d'erreurs
			cout << "Saisie incorrecte. Veuillez entrer une taille de clef." << endl;
		} else {
			saisie_fausse = false;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //vide le buffer.
	} while(saisie_fausse);

	/**
	 * p et q sont des nombres premiers généré de manière aléatoire dont la taille
	 * de la clé est choisie par l'utilisateur. Dans ce programme, ils sont
	 * nommés de cette manière car cela reprend le nommage du
	 * chiffrement RSA. la variable e fait partie de la clé publique mais c'est
	 * une constante à 17 (demandé par l'enseignant).
	 * On vérifie si p et q sont différents, ainsi que s'ils sont premier.
	 */
	Uint p, q;
	do {
		p = generateur_aleatoire(size_t(taille_de_clef));
	} while (!test_rapide_primalite(p)); //p doit être premier

	do {
		q = generateur_aleatoire(size_t(taille_de_clef));
	} while (!test_rapide_primalite(q) && q != p); //q doit être premier

	/**
	 * d est l’inverse de e modulo phi_euler avec l’algorithme d’Euclide étendu.
	 * On l'instancie à 0 vu qu'il sera passé par référence et que (dans mon
	 * environnement en tout cas) une variable qui n'a pas une valeur assignée
	 * lors de la déclaration peut avoir n'importe quelle valeur, c'est important.
	 * (Evidemment on sait ce que va faire la fonction, mais on ne le sait pas
	 * toujours.
	 */
	Sint d = 0;

	/**
	 * n est la 2ème partie de la clé publique (avec e) calculé par p * q qui
	 * doivent rester secret (voir
	 * https://fr.wikipedia.org/wiki/Chiffrement_RSA#Cr%C3%A9ation_des_cl%C3%A9s
	 * point 2).
	 */
	Uint n = p * q;

	/**
	 * (p - 1) * (q - 1) = phi, dans le cadre de RSA, on utilise une notion
	 * découverte par Euler voir
	 * https://fr.wikipedia.org/wiki/Indicatrice_d%27Euler.
	 */
	Uint phi_euler = (p - 1) * (q - 1);
	if (
		!(
			euclide_etendue((Sint)phi_euler, (Sint)E, d) == 1
			&& E < phi_euler)
		) {
		cout << "Les clefs ont rencontré on probleme " << endl;
	}
	cout << "Clefs de cryptage (n et e) : " << n << " " << E << endl;
	cout << "Clefs de decryptage (n et d) : " << n << " " << (Uint)d <<endl;
	return 0;
}

Uint mod_pow(Uint base, Uint exposant, const Uint& modulo) {
	Uint resultat = 1;
	while (exposant > 0) {
		if ((exposant % 2) == 0) {
			base = base * base % modulo;
			exposant /= 2;
		} else {
			resultat = resultat * base % modulo;
			exposant--;
		}
	}
	return resultat;
}

bool test_rapide_primalite(const Uint& nombre) {
	//Utilisation d'une variable, car souvent répété dans la fonction.
	Uint nombre_moins_1 = nombre - 1;
	const int NOMBRE_DE_TOURS = 10;
	//1 et 0 ne sont pas premier,
	if (nombre < 2) {
		return false;
	}

	/**
	 * 2 est le premier nombre premier et empêche tous les nombres paires d'être
	 * premier. Tester si l'utilisateur rentre 3 (car notre nombre aléatoire
	 * retournera 2 et ça ferra modulo 2 donc boucle infinie plus tard dans la
	 * fonction).
	 */
	if (nombre == 2 || nombre == 3) {
		return true;
	}
	Uint nombre_aleatoire;
	//Tester 10 fois pour s'assurer de la primalité
	for (int i = 0; i <= NOMBRE_DE_TOURS; i++) {
		/**
		 * Generation d'un nombre aléatoire, on vérifie avec % si le nombre
		 * dépasse nombre - 1.
		 */
		do {
			nombre_aleatoire = (uint32_t)distribution(mt_rand) % nombre_moins_1;
		} while (nombre_aleatoire < 2);
		/**
		 * Si l'exponentiation modulaire retourne autre chose que 1, c'est que le
		 * nombre n'est pas premier (le PGDC d'un nombre premier ne peut être que
		 * lui même et 1, donc si on trouve autre chose que 1...).
		 */
		if (mod_pow(nombre_aleatoire, nombre_moins_1,
						nombre) != 1) {
			return false;
		}
		/**
		 * les noms de variables q et u viennent de la formule mathématique fournie
		 * ici : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu,
		 * mais pour résumer, ce sont des variables temporaires qu'on doit utiliser
		 * en informatique et qui ne sont pas expliquée mathématiquement, c'est une
		 * contrainte du language C++ qui ne permet pas d'affecter plusieurs
		 * variables en une seule fois.
		 */
		Uint q = 1;
		Uint u = nombre_moins_1;
		//Tant que u n'est pas pair (divisible par 2) il est candidat.
		while ((u % 2) == 0 && q == 1) {
			u /= 2;
			q = mod_pow(nombre_aleatoire, u, nombre);
			//Si q n'est pas premier et (nombre - 1), c'est qu'il n'est pas premier...
			if (q != 1 && q != nombre_moins_1) {
				return false;
			}
		}
	}
	return true;
}

Uint euclide_etendue(const Sint& nombre1, Sint nombre2, Sint& inverse) {
	Sint pgdc = nombre1;
	Sint pgdc_prime = nombre2;
	inverse = 0;
	Sint inverse_prime = 1;
	while (pgdc_prime != 0) {
		// partie entière de pgdc et pgdc' car int, q est le nom fournit dans l'algo.
		Sint q = pgdc / pgdc_prime;
		Sint pgdc_temp = pgdc;
		Sint inverse_temp = inverse;
		pgdc = pgdc_prime;
		inverse = inverse_prime;
		pgdc_prime = pgdc_temp - q * pgdc_prime;
		inverse_prime = inverse_temp - q * inverse_prime;
	}
	if (inverse < 0) {
		inverse = inverse + nombre1;
	}
	return (Uint)pgdc;
}

Uint generateur_aleatoire(size_t nombre) {
	//Créer une string car pas de setter dans notre classe.
	string nombre_aleatoire_text;
	int valeur_aleatoire;
	for (size_t i = 0; i < nombre; i++) {
		valeur_aleatoire = distribution(mt_rand);
		/**
		 * Si le premier nombre est 0, re-générer pour ne pas avoir de nombre
		 * comme suit : 012 -> 12 donc 2 chiffres au lieu de 3.
		 */
		if (!i) {
			do {
				valeur_aleatoire = distribution(mt_rand);
			} while (!valeur_aleatoire);
		}
		nombre_aleatoire_text += to_string(valeur_aleatoire);
	}
	return Uint(nombre_aleatoire_text);
}
