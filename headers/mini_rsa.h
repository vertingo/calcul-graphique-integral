#ifndef __mini_rsa_h__
#define __mini_rsa_h__


namespace mini_rsa
{

// type des entiers utilisés comme clef
typedef long long big_int ;  // doit être un type entier signé

// partie entière du log en base 2 de la plus grande valeur possible d'un 'big_int' (ici log( 2^63-1 ) == 62)
const int log_big_int = 62 ; // attention : cette valeur doit être mise à jour si bit_int est changé.

// nb max de bits utilisables
const int max_nb_bit = log_big_int/2 ; // comme on a des multiplications, on ne peut utiliser que la moitié des bits

// renvoie un entier aléatoire sur nb_bit bits (le bit de poids fort étant toujours à 1)
// cette fonction n'est là que pour les tests.
big_int random ( int nb_bit ) ;

// génère une bi-clef (= paire clef publique + clef privée) sur nb_bit
// la clef privée = paire ( pri,mod ) et la clef publique = paire ( pub,mod )
void compute_keys ( int nb_bit , big_int * pub , big_int * pri , big_int * mod ) ;

// chiffrement (= déchiffrement avec la clef réciproque)
// 'message' contient le message à chiffrer/dechiffrer sous forme d'un
// entier qui doit être inferieur à 'mod'.
// le paramètre 'exp' doit recevoir le 'pub' ou le 'pri' sorti de 'compute_keys'.
// le paramètre 'mod' doit recevoir le 'mod' sorti de 'compute_keys'.
// le paramètre 'message' contient le message à chiffrer.
//    (Attention : C'est l'appelant qui doit convertir son buffer de données en 'big_int'.)
// le retour est le message chiffré.
big_int encrypt ( big_int exp , big_int mod , big_int message ) ;

}

#endif // __mini_rsa_h__
