#include "bitstream.h"
#include "bits.h"

/*
 * Oon écrit les "nb" bits de droite de "v"
 * dans le fichier (toujours du poids fort au faible).
 *
 * Pour v=11 nb=8 on va écrire les bits : 00001011 dans le fichier
 */

void put_bits(struct bitstream *b, unsigned int nb, unsigned long v)
{
	for (int i = nb-1; i >= 0; --i){ // Correction a faire pour les unsigned
		put_bit(b, prend_bit(v, i));
	}
}


/*
 * Lecture de "nb" bits venant du fichier.
 * et on retourne un entier contenant ces bits cadrés à droite (poids faibles)
 * Par exemple pour nb=2 on peut retourner des valeurs de 0 à 3 inclu.
 * Suivant les 2 bits dans le fichier on obtiendra :
 * 00->0 01->1 10->2 11->3
 */

unsigned int get_bits(struct bitstream *b, unsigned int nb)
{
	// Autre solution : shéma de horner
	unsigned int res = 0;
	for (int i = nb - 1;  i >= 0; --i){ // correction à faire pour les unsigned
		int bit = get_bit(b);
		res = pose_bit(res, i, bit);
	}
	return res;
}

/*
 * Pour vous simplifier la programmation.
 * Cette fonction stocke une chaine de la forme "0011010101010111010101001"
 * dans le flot de bit sous la forme d'une suite de bit 0 et 1.
 *
 * Comme d'habitude le caractère '0' c'est Faux les autres sont vrai
 */

void put_bit_string(struct bitstream *b, const char *bits)
{
	while( *bits )
		put_bit(b, *bits++ != '0') ;

	// int i = 0;
	// char c;
	// while((c = bits[i]) != '\0'){
	// 	if(c == '0')
	// 		put_bit(b, 0);
	// 	else
	// 		put_bit(b, 1);
	// 	++i;
	// }
}
