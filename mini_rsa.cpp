///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rivest Shamir Adleman ou RSA est un algorithme asymétrique de cryptographie à clé publique
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Un peu de théorie :
//----------------------
//
// 1 - Création des clés :
//   - On choisit p et q deux nombres premiers distincts
//   - On note n leur produit, appelé module de chiffrement : n = p.q
//   - On calcule phi = (p-1)(q-1). C'est l'indicatrice d'Euler de n.
//   - On choisit e un entier premier avec phi, appelé exposant de chiffrement.
//     Dans la pratique, on peut prendre pour e un petit premier (par ex. 65537).
//   - Comme e est premier avec phi, il est inversible modulo phi
//     (i.e. il existe un entier d tel que e.d % phi = 1)
//     d est l'exposant de déchiffrement.
//     Il est important que d soit un très grand nombre.
// --> Le couple (n,e) est appelé clef publique et le couple (n,d) est appelé clef privée.
//
// 2 - Chiffrement du message :
//   - Soit M un entier inférieur à n représentant un message.
//     Le message chiffré C = ( M ^ e ) % n
//     Le message déchiffré M' = ( C ^ d ) % n
//     avec evidemment M = M'
//
// (merci wiki : http://fr.wikipedia.org/wiki/Rivest_Shamir_Adleman)
//
// Remarque non dénuée d'interêt :
//----------------------------------
// Toutes les fonctions qui manipulent des big_int s'implémentent facilement avec
// la librairie (gratuite & magnifique) gmp (GNU Multiple Precision Arithmetic)
// (http://gmplib.org) ce qui permet de donner à ce cas d'école un niveau de sécurtié
// très acceptable.
//
// Hadrien Flammang - dec 2008
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib> // juste pour rand
#include "mini_rsa.h"

using namespace mini_rsa ;

// renvoie un bit aléatoire
static int random_bit ()
    {
    return( rand()&1 ) ;
    }

// retourne le PGCD de a et b (qui doivent être positifs)
static big_int pgcd ( big_int a , big_int b ) // thank's to Euclide
    {
    // return( a ? pgcd( a,b%a ) : b ) ; // version récursive
    big_int c = a % b ;
    while ( c != 0 )
        {
        a = b ;
        b = c ;
        c = a % b ;
        }
    return( b ) ;
    }

// retourne la partie entière de la racine carrée de x (qui doit être positif)
static big_int sqrt ( big_int x ) // thank's to sir Isaac
    {
    big_int r = x ;
    for (;;)
        {
        big_int xx = (x/r + r) / 2 ;
        if ((r == xx) || (r == xx-1)) return( r ) ;
        r = xx ;      // ^---------^ arrive quand x est un carré -1
        }
    }

// retourne true ssi x est impair
static bool is_odd ( big_int x )
    {
    return((x & 1) == 1 ) ;
    }

// retourne la partie entière du log en base 2 de x
// i.e. rang du bit de poids fort (log( 1 ) == 0, log( 2 ) == 1, log( 256 ) == 8, etc)
static int log ( big_int x )
    {
    int res = 0 ;
    for (; x > 0 ; x /= 2 ) res++ ;
    return( res ) ;
    }

// calcule ca et cb tels que a*ca + b*cb = pgcd( a,b )
// attention : ca et/ou cb peuvent être négatifs
static void euclide_etendu ( big_int a , big_int b , big_int * ca , big_int * cb )
    {
    big_int c,d,p,q,r,s,r2,s2 ;
    p = 1 ;
    q = 0 ;
    r = 0 ;
    s = 1 ;
    while ( b != 0 )
        {
        c = a % b ;
        d = a / b ;
        a = b ;
        b = c ;
        r2 = p - d*r ;
        s2 = q - d*s ;
        p = r ;
        q = s ;
        r = r2 ;
        s = s2 ;
        }
    if (ca) *ca = p ;
    if (cb) *cb = q ;
    }

// retourne true ssi x est premier
static bool is_prime ( big_int x )
    {
    // élimine les cas triviaux + divisibles par 2 ou 3
    if ( x < 2 ) return( false ) ;
    if ((x == 2) || (x == 3)) return( true ) ;
    if ((x % 2) == 0) return( false ) ;
    if ((x % 3) == 0) return( false ) ;
    // ne teste plus la divisibilité par 2 ou 3
    big_int sx = sqrt( x ) ;
    big_int d  = 5 ;
    for ( int dd = 2 ; d <= sx ; d += dd , dd = 6-dd )
        if ((x % d) == 0) // ruse : d n'est multiple ni de 2 ni de 3
            return( false ) ;
    return( true ) ;
    }

// renvoie un nombre aléatoire dans { 2^nb_bit ... 2^(nb_bit+1)-1 }
static big_int big_random ( int nb_bit )
    {
    big_int res = 1 ; // assure que le bit de poids fort est à 1
    for ( --nb_bit ; nb_bit > 0 ; --nb_bit )
        res = res*2 + random_bit() ;
    return( res ) ;
    }

// renvoie un nb premier dans { 2^nb_bit ... 2^(nb_bit+1)-1 }
static big_int find_big_prime ( int nb_bit )
    {
    big_int res = big_random( nb_bit ) ;
    if (!is_odd( res )) ++res ;
    while ( !is_prime( res ))
        res += 2 ;  // bug potentiel : s'il n'y a aucun premier entre le res initial et
    return( res ) ; // 2^(nb_bit+1)-1 on va dépasser 2^(nb_bit+1)-1 ce qui peut être fâcheux.
    }

// retourne y tel que x et y soient premiers entre eux
static big_int find_prime_with ( int nb_bit , big_int x )
    {
    big_int res = big_random( nb_bit ) ;
    while ( pgcd( res,x ) != 1 )
        ++res ;
    return( res ) ;
    }

// retourne y tel que ( x*y ) % m == 1
static big_int inverse ( big_int x , big_int m )
    {
    big_int res ;
    euclide_etendu( x,m,&res,NULL ) ;
    while ( res < 1 ) res += m ;
    return( res ) ;
    }

// calcule x^y % m
static big_int modulus_exp ( big_int x , big_int y , big_int m )
    {
    if (y <= 0) return( 1 ) ;
    big_int res = 1 ;
    for ( x %= m ; y > 0 ; y /= 2 , x = (x*x)%m )
        if (is_odd( y ))
            res = (res*x)%m ;
    return( res ) ;
    }

// calcule un jeu de clefs RSA
static void compute_keys ( int nb_bit , big_int * modulus , big_int * private_exponant , big_int * public_exponant , bool symetric = false )
    {
    do  {
        big_int p,q ;
        do  {
            p = find_big_prime( (nb_bit+1)/2 ) ;

            do  q = find_big_prime( nb_bit/2 ) ;
                while ( p == q ) ; // p et q doivent être distincts

            *modulus = p*q ;
            }
            while ( log( *modulus ) != nb_bit ) ; // le modulo doit être assez grand mais pas trop

         big_int phi = (p-1)*(q-1) ;

         if (symetric) // on veut que la clef publique soit ~ aussi grande que la clef privée
            *public_exponant = find_prime_with( nb_bit,phi ) ;
         else
            *public_exponant = 65537 ; // on trouve souvent 65537 dans la litterature

        *private_exponant = inverse( *public_exponant,phi ) ;
        }
        // On recommence jusqu'à ce que l'exposant de déchiffrement (private_exponant) soit assez grand
        // et different de l'exposant de chiffrement
        while ((log( *private_exponant ) < nb_bit-1) || (*public_exponant == *private_exponant)) ;
    }

//-----------------------------------------------------------------------------

namespace mini_rsa
{

void compute_keys ( int nb_bit , big_int * pub , big_int * pri , big_int * mod )
    {
    ::compute_keys( nb_bit,mod,pri,pub ) ;
    }

big_int encrypt ( big_int exp , big_int mod , big_int message )
    {
    return( modulus_exp( message,exp,mod )) ;
    }

big_int random ( int nb_bit )
    {
    return( big_random( nb_bit )) ;
    }

}
