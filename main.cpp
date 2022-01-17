#include "Sint.hpp"
#include "Uint.hpp"
#include <iostream>
#include <string>
#include <random>

using namespace std;
const uint32_t GRAINE = 18232;
mt19937 mt_rand(GRAINE);
uniform_int_distribution<int32_t> distribution(0, 9);

const Uint E = 17;

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
 * @param base
 * @param exposant
 * @param modulo
 * @return resultat
 */
Uint mod_pow(Uint base, Uint exposant, const Uint& modulo);

/**
 * @brief La problématique est la factorisation des nombres en informatiques qui
 * est extrêmement complexe, ici on "factorise" afin de savoir si un nombre est
 * premier ou non.
 * @param Uint& nombre : nombre à tester si il est premier ou non.
 * @return Si le nombre est premier ou non (true = premier).
 */
bool test_rapide_primalite(const Uint& nombre);

/**
 * @brief Cette fonction retourne 2 éléments, le PGDC en return, ainsi
 * que l'inverse par référence. L'inverse est le nombre qui permet de retrouver
 * le même résultat de (nombre^x % modulo) et (nombre^y % modulo), dans ce cas,
 * y est l'inverse de x et le résultat serait identique. Plus d'informations
 * sur : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu.
 * @param Sint& nombre1 :
 * @param Sint nombre2 :
 * @param Sint& inverse : retourne l'inverse par référence
 * @return Uint : PGDC de 2 nombres.
 */
Uint euclide_etendue(const Sint& nombre1, Sint nombre2, Sint& inverse);


/**
 * @brief Générateur de nombre (Uint) aléatoire
 * @param size_t nombre : Taille souhaitée par l'utilisateur
 * @return Uint : Un nombre aléatoire de taille choisie par l'utilisateur
 */
Uint generateur_aleatoire(size_t nombre);

int main() {
	Uint n, clef_prive, phi_euler, p, q;
	int taille_de_clef;
	cout << "Veuillez choisir une taille de clef : ";
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

	do {
		p = generateur_aleatoire(size_t(taille_de_clef));
	} while (!test_rapide_primalite(p)); //p doit être premier

	do {
		q = generateur_aleatoire(size_t(taille_de_clef));
	} while (!test_rapide_primalite(q)); //q doit être premier

	Sint d = 0;
	n = p * q;
	phi_euler = (p - 1) * (q - 1);
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

Uint generateur_aleatoire(size_t nombre) {
	string random_string; //Créer un string car pas de setter de l'attribut nombre.
	Uint random_sint;
	int random_digit;
	for (size_t i = 0; i < nombre; i++) {
		random_digit = distribution(mt_rand);
		//Gérer le cas si le nombre commence par un 0
		if (!random_digit && !i) {
			do {
				random_digit = distribution(mt_rand);
			} while (!random_digit);
		}
		random_string += to_string(random_digit);
	}
	random_sint = random_string;
	return random_sint;
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
	 * premier. Tester si l'utilisateur rentre 3 (car generateur_aleatoire
	 * retournera 2 et ça ferra modulo 2 donc boucle infinie plus tard dans la
	 * fonction). */
	if (nombre == 2 || nombre == 3) {
		return true;
	}
	Uint nombre_aleatoire;
	//Tester 10 fois pour s'assurer de la primalité
	for (int i = 0; i <= NOMBRE_DE_TOURS; i++) {
		/**
		 * Generation d'un nombre aléatoire, on vérifie avec % si le nombre
		 * dépasse nombre-1
		 */
		do {
			nombre_aleatoire = (uint32_t)distribution(mt_rand) % nombre_moins_1;
		} while (nombre_aleatoire < 2);
		/**
		 * Si l'exponentiation modulaire retourne autre chose que 1, c'est que le
		 * nombre n'est pas premier (le PGDC d'un nombre premier ne peut être que
		 * lui même et 1, donc si on trouve autre chose que 1...)
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