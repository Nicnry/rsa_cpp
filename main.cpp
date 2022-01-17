#include "Sint.hpp"
#include "Uint.hpp"
#include <iostream>
#include <string>
#include <random>
#include <functional>

using namespace std;
const uint32_t GRAINE = 34032;
mt19937 mt_rand(GRAINE);
uniform_int_distribution<int32_t> distribution(0, 9);

const Uint E = 17;


/**
 *
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
 * @param base
 * @param exposant
 * @param modulo
 * @return resultat
 */
Uint mod_pow(Uint base, Uint exposant, Uint modulo);

/**
 * @brief La problématique est la factorisation des nombres en informatiques qui
 * est extrêmement complexe, ici on "factorise" afin de savoir si un nombre est
 * premier ou non.
 * @param nombre
 * @return Si le nombre est premier ou non (true = premier).
 */
bool test_rapide_primalite(Uint nombre);

/**
 * @brief Cette fonction retourne 2 éléments, le PGDC en return, ainsi
 * que l'inverse par référence. L'inverse est le nombre qui permet de retrouver
 * le même résultat de (nombre^x % modulo) et (nombre^y % modulo), dans ce cas,
 * y est l'inverse de x et le résultat serait identique. Plus d'informations
 * sur : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu.
 * @param nombre1
 * @param nombre2
 * @param inverse : retourne l'inverse par référence
 * @return PGDC de 2 nombres.
 */
Uint euclide_etendue(Sint nombre1, Sint nombre2, Sint& inverse);


/**
 * @brief Cette fonction retourne 2 éléments, le PGDC en return, ainsi
 * que l'inverse par référence. L'inverse est le nombre qui permet de retrouver
 * le même résultat de (nombre^x % modulo) et (nombre^y % modulo), dans ce cas,
 * y est l'inverse de x et le résultat serait identique. Plus d'informations
 * sur : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu.
 * @param nombre
 * @param nombre2
 * @param inverse : retourne l'inverse par référence
 * @return PGDC de 2 nombres.
 */
Uint generateur_aleatoire(size_t nombre);

int main() {
	Sint inverse = 0;
	bool e_correct;
	Uint n, clef_prive, verification_e, p, q;
	size_t taille_clef;
	cout << "Veuillez entrer la taille de vos clefs: ";
	cin >> taille_clef;
	do {
		p = generateur_aleatoire(taille_clef);
	} while (!test_rapide_primalite(p)); //p doit être premier
	do {
		q = generateur_aleatoire(taille_clef);
	} while (!test_rapide_primalite(q)); //q doit être premier

	verification_e = (p - 1) * (q - 1);
	e_correct = euclide_etendue((Sint)verification_e, (Sint)E, inverse) == 1 && E < verification_e;
	if(!e_correct){
		cout << "Erreur avec e " << endl;
	}
	clef_prive = (Uint)inverse;

	n = p * q;
	cout << "Pair de clef pour crypter : " << n << " " << E << endl;
	cout << "Pair de clef pour decrypter : " << n << " " << clef_prive <<endl;
}

Uint generateur_aleatoire(size_t nombre) {
	string random_string;
	Uint random_sint;
	int random_digit;
	for (size_t i = 0; i < nombre; i++) {
		random_digit = distribution(mt_rand);
		//On supprime
		if (i == 0) {
			do {
				random_digit = distribution(mt_rand);
			} while (random_digit == 0);
		}
		random_string += to_string(random_digit);
	}
	random_sint = random_string;
	return random_sint;
}

bool test_rapide_primalite(Uint nombre) {
	//Utilisation d'une variable, car souvent répété dans la fonction.
	Uint nombre_moins_1 = nombre - 1;
	//1 et 0 ne sont pas premier,
	if (nombre < 2) {
		return false;
	}
	/**
	 * 2 est le premier nombre premier et empêche tous les nombres paires d'être
	 * premier. Tester si l'utilisateur rentre 3 (car generateur_aleatoire
	 * retournera 2 et ça ferra modulo 2 donc boucle infinie plus tard dans la
	 * fonction). */
	if (nombre == 2 || nombre == 3) {
		return true;
	}
	Uint nombre_aleatoire;
	//Tester 10 fois pour s'assurer de la primalité
	for (int i = 0; i <= 10; i++) {
		//Generation d'un nombre aléatoire, on vérifie avec % si le nombre dépasse nombre-1
		do {
			nombre_aleatoire = (uint32_t)distribution(mt_rand) % nombre_moins_1;
		} while (nombre_aleatoire < 2);
		/**
		 * Si l'exponentiation modulaire retourne autre chose que 1, c'est que le
		 * nombre n'est pas premier (le PGDC d'un nombre premier ne peut être que
		 * lui même et 1, donc si on trouve autre chose que 1...)
		 */
		if (mod_pow(nombre_aleatoire, nombre_moins_1, nombre) != 1) {
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

Uint mod_pow(Uint base, Uint exposant, Uint modulo) {
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

Uint euclide_etendue(Sint nombre1, Sint nombre2, Sint& inverse) {
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