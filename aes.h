#ifndef AES_H
#define AES_H

/* Parametres de l'encodeur AES */
#define KEY_SIZE	4
#define KEY_ROUNDS	( 10 + ( KEY_SIZE - 4 ) )
#define BLOCK_SIZE	4

#include "main.h"

/* Structure de stockage des clefs */
typedef struct {
    /* Pointeur sur la clé : AES-128, AES-192 ou AES-256 */
    u32 key[KEY_SIZE];

    /* Tableau contenant les différentes variantes de clé */
    u32 round_keys[(KEY_ROUNDS+1)*BLOCK_SIZE];

} aes_keys;

/* Prototypes de fonctions à utiliser en assemblxmeur
 * Le cdecl est utilisé pour etre sur de ne pas defaulter 
 * en stdcall (gcc rajouterait des manips sur la pile)
 */
u32 AesInit(void) __attribute__ ((cdecl)) ;
u32 SetState( u32* ) __attribute__ ((cdecl)) ;
u32 DumpState( u32* ) __attribute__ ((cdecl)) ;
u32 SubBytes( u32 a, u32 b, u32* c ) __attribute__ ((cdecl)) ;

void aes_print_round_keys( void );
void aes_generate_roundkeys( void );

#endif