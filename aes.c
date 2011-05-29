#include "aes.h"

/* Clef de test */
aes_keys keys = {
	/* Original User Key */
	{
	  0x2b7e1516,	
	  0x28aed2a6,	
	  0xabf71588, 
	  0x09cf4f3c
       	},

	/* Round keys generated by the key schedule */
	{
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000
	}
};

aes_keys keys2 = {
	/* Original User Key */
	{
	  0x2b7e1516,	
	  0x28aed2a6,	
	  0xabf71588, 
	  0x09cf4f3c
       	},

	/* Round keys generated by the key schedule */
	{
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000
	}
};

/* Rijnadel S-Box utilisee pour realiser l'operation SubBytes de l'algorithme AES */
const u16 rij_sbox[] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/* Rijnadel Inverse S-Box utilisee pour realiser l'operation InvSubBytes de l'algorithme AES */
const u16 rij_invsbox[] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};	

u32 aes_MemState[4] = {
	0x0000000,
	0x0000000,
	0x0000000,
	0x0000000
};
	
void SubByte( void ) {
	u16 i;
	u32 tmp;

	DumpState( (u32*) aes_MemState );

	for ( i = 0 ; i < 4 ; i++ ) {
		/* Fetch row from memory */
		tmp	= aes_MemState[i];

		/* Performs RIJ S-BOX Substitution on row */
		tmp	= ( rij_sbox[ ( ( tmp & 0xFF000000) >> 24) ] << 24 ) 
			| ( rij_sbox[ ( ( tmp & 0x00FF0000) >> 16) ] << 16 )
			| ( rij_sbox[ ( ( tmp & 0x0000FF00) >> 8) ] << 8 )
			| ( rij_sbox[   ( tmp & 0x000000FF)       ] );

		/* Performs RoBytes Transform on row */
		tmp	= ( tmp << i*8 ) | ( tmp >> (32 - i*8) );
		aes_MemState[i]	= tmp;
	}

	SetState( (u32*) aes_MemState );
}

/* Returns S-Box Substitution performed on halfwords */
u16 aes_SubBytes( u16 val ) {
	return	rij_sbox[ val ];
}

/* Performs S-Box on words */
u32 aes_SubWord( u32 val ) {
	val	= ( rij_sbox[ ( ( val & 0xFF000000) >> 24) ] << 24 ) 
		| ( rij_sbox[ ( ( val & 0x00FF0000) >> 16) ] << 16 )
		| ( rij_sbox[ ( ( val & 0x0000FF00) >> 8) ] << 8 )
		| ( rij_sbox[   ( val & 0x000000FF)       ] );
	return	val;
}

/* Rorate ony byte to the left */
u32 aes_RotWord( u32 val ) {
	val	= ( (val << 8) | (val >> 24) ) & 0xFFFFFFFF;
	return	val;
}

/* 
 * Cette fonction genere les cles de tour d'AES a partir du bloc cle 128, 192 ou 256
 * definir dans la structure aes_keys 
 * Se rérérer au documents décrivant le fonctionnement d'AES pour plus d'informations
 *
 */
void aes_generate_roundkeys( void ) {
	u16 i;
	u32 temp;
	u32 rcon;

	/* Lors des premiers rounds, la cle est la cle d'origine */
	for ( i = 0 ; i < KEY_SIZE ; i++ ) {
		keys.round_keys[ i ]	= keys.key[ i ];
	}

	/* Par la suite on realise une KeyExpansion pour les tours suivants */
	for ( i = KEY_SIZE ; i < ( KEY_ROUNDS + 1 ) * BLOCK_SIZE ; i++ ) {
		temp	= keys.round_keys[i-1];

		if ( ( i % KEY_SIZE ) == 0 ) {

			/* << 25 ) {02},{00},{00},{00} = Rconv[1] */

			rcon	= ( i / KEY_SIZE < 9 ) ?
		       		(1 << (23 + (i / KEY_SIZE) ) ) :
			        (0x1b << (23 + (i / KEY_SIZE) - 8 ));

			temp	= aes_SubWord( aes_RotWord( temp ) ) ^ rcon;

		} else if ( (KEY_SIZE > 6) && ( ( i % KEY_SIZE ) == 0) ) {
			temp	= aes_SubWord( temp );
		}
		keys.round_keys[ i ]	= keys.round_keys[ i - KEY_SIZE ] ^ temp;
	}

	/* Reorganise la clef pour qu'elle soit prête à l'emploi en mémoire */

	for ( i = 0 ; i < ( KEY_ROUNDS + 1 ) * BLOCK_SIZE ; i = i + 4 ) {
		keys2.round_keys[ i ]	= 
			(( keys.round_keys[ i ] ) & 0xFF000000) |
			((( keys.round_keys[ i + 1 ] ) & 0xFF000000) >> 8) |
			((( keys.round_keys[ i + 2 ] ) & 0xFF000000) >> 16) |
			((( keys.round_keys[ i + 3 ] ) & 0xFF000000) >> 24);

		keys2.round_keys[ i + 1 ]	= 
			((( keys.round_keys[ i ] ) & 0x00FF0000) << 8 ) |
			(( keys.round_keys[ i + 1 ] ) & 0x00FF0000) |
			((( keys.round_keys[ i + 2 ] ) & 0x00FF0000) >> 8) |
			((( keys.round_keys[ i + 3 ] ) & 0x00FF0000) >> 16);

		keys2.round_keys[ i + 2 ]	= 
			((( keys.round_keys[ i ] ) & 0x0000FF00) << 16) |
			((( keys.round_keys[ i + 1 ] ) & 0x0000FF00) << 8) |
			(( keys.round_keys[ i + 2 ] ) & 0x0000FF00) |
			((( keys.round_keys[ i + 3 ] ) & 0x0000FF00) >> 8);

		keys2.round_keys[ i + 3 ]	=
			((( keys.round_keys[ i ] ) & 0x000000FF) << 24) |
			((( keys.round_keys[ i + 1 ] ) & 0x000000FF) << 16) |
			((( keys.round_keys[ i + 2 ] ) & 0x000000FF) << 8) |
			(( keys.round_keys[ i + 3 ] ) & 0x000000FF) ;

		printf( "%x " , keys2.round_keys[ i ] );
		printf( "%x " , keys2.round_keys[ i + 1 ] );

	}

	keys	= keys2;
}

void aes_print_round_keys( void ) {
	u16 i;
	printf( "Here are your keys\n" );

	printf( "%x \n" , aes_SubWord( 0x000ff0ff ) );

	for ( i = 0 ; i < ( (KEY_ROUNDS+1) * BLOCK_SIZE ) ; i++ ) {
		if ( ( i % 4 == 0 ) && ( i != 0 ) )
			printf( "\n" );
		
		printf( "%x " , keys.round_keys[ i ] );

	}	

	printf( "\nLove that ?\n" );

}

u32 VState[4] = { 
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
};

void aes_ViewState( void ) {
	u16 a;

	DumpState( (u32 *) VState );

	printf("Test de la valeur chargee :\n");
	for ( a = 0 ; a < 4 ; a++ ) {
		printf( "Val %i %x\n" , a, VState[a] ); 
	}
}

void aes_cipher( u32* plaintext ) {
	int i;

	SetState( plaintext );

	AesInitXmm( );

	AddRoundKey( (u32 *) keys.round_keys );

	for ( i = 0 ; i < KEY_ROUNDS-1 ; i++ ) {

		SubByte( );
		MixColumns( );
		
		AddRoundKey( ( keys.round_keys + 4*(i+1) ) );
	}

	SubByte( );
	AddRoundKey( keys.round_keys + 4*KEY_ROUNDS );

/*	aes_ViewState( ); */
}

void aes_setkey( /*int key[KEY_SIZE]*/ ) {
	// memcpy( aes_keys.key , key , KEY_SIZE*4 );

	// aes_generate_roundkeys( );
}


