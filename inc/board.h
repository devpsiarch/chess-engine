#ifndef BOARD_H
#define BOARD_H

/*=============================*/
      /*includes headers*/
/*=============================*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
/*=============================*/
		/*bit minuplation*/
/*=============================*/
#define U64 unsigned long long
//gets the bit from the square at the bit board
#define get_bit(bitboard,square) (bitboard & (1ULL << square))
//sets up a bit on the bitboard
#define set_bit(bitboard,square) bitboard |= (1ULL << square)
//because using it twice will have the effect of setting it (see XOR table)
#define pop_bit(bitboard,square) (get_bit(bitboard,square)) ? bitboard ^= (1ULL << square) : 0
// calcs the square in a macro
#define bit_at(R,F) R*8+F

//counts the bits in a ULL int
static inline int bitlen(U64 bitboard);
//gets first least significant bit in a board 
static inline int getlsbi(U64 bitboard);

//gets the row and col based on square number
#define map_at(x) printf("%s\n",possitions[x])

/*=============================*/
		/*data to use*/
/*=============================*/

enum {
A8,B8,C8,D8,E8,F8,G8,H8,
A7,B7,C7,D7,E7,F7,G7,H7,
A6,B6,C6,D6,E6,F6,G6,H6,
A5,B5,C5,D5,E5,F5,G5,H5,
A4,B4,C4,D4,E4,F4,G4,H4,
A3,B3,C3,D3,E3,F3,G3,H3,
A2,B2,C2,D2,E2,F2,G2,H2,
A1,B1,C1,D1,E1,F1,G1,H1
};

const char *possitions[] = {
"A8","B8","C8","D8","E8","F8","G8","H8",
"A7","B7","C7","D7","E7","F7","G7","H7",
"A6","B6","C6","D6","E6","F6","G6","H6",
"A5","B5","C5","D5","E5","F5","G5","H5",
"A4","B4","C4","D4","E4","F4","G4","H4",
"A3","B3","C3","D3","E3","F3","G3","H3",
"A2","B2","C2","D2","E2","F2","G2","H2",
"A1","B1","C1","D1","E1","F1","G1","H1"
};

//sides aka colors
enum {white,black};

/*=============================*/
		/*attacks*/
/*=============================*/
/*
	NOT_A_FILE				  NOT_H_FILE
8  0 1 1 1 1 1 1 1			1 1 1 1 1 1 1 0     
7  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0
6  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0	
5  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0
4  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0
3  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0
2  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0
1  0 1 1 1 1 1 1 1			1 1	1 1 1 1 1 0

   A B C D E F G H


     NOT_GH_FILE

8  1 1 1 1 1 1 0 0
7  1 1 1 1 1 1 0 0
6  1 1 1 1 1 1 0 0
5  1 1 1 1 1 1 0 0
4  1 1 1 1 1 1 0 0
3  1 1 1 1 1 1 0 0
2  1 1 1 1 1 1 0 0
1  1 1 1 1 1 1 0 0

   A B C D E F G H
   board value :4557430888798830399d

	NOT_AB_FILE

8  0 0 1 1 1 1 1 1
7  0 0 1 1 1 1 1 1
6  0 0 1 1 1 1 1 1
5  0 0 1 1 1 1 1 1
4  0 0 1 1 1 1 1 1
3  0 0 1 1 1 1 1 1
2  0 0 1 1 1 1 1 1
1  0 0 1 1 1 1 1 1

   A B C D E F G H
   board value :18229723555195321596d


*/
U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

// bishop relavant occupancy count for each possition
const int bishop_roc[64] = {
 6, 5, 5, 5, 5, 5, 5, 6,
 5, 5, 5, 5, 5, 5, 5, 5,
 5, 5, 7, 7, 7, 7, 5, 5,
 5, 5, 7, 9, 9, 7, 5, 5,
 5, 5, 7, 9, 9, 7, 5, 5,
 5, 5, 7, 7, 7, 7, 5, 5,
 5, 5, 5, 5, 5, 5, 5, 5,
 6, 5, 5, 5, 5, 5, 5, 6
};

// rook relavant occupancy count for each possition
const int rook_roc[64] = {
 12, 11, 11, 11, 11, 11, 11, 12,
 11, 10, 10, 10, 10, 10, 10, 11,
 11, 10, 10, 10, 10, 10, 10, 11,
 11, 10, 10, 10, 10, 10, 10, 11,
 11, 10, 10, 10, 10, 10, 10, 11,
 11, 10, 10, 10, 10, 10, 10, 11,
 11, 10, 10, 10, 10, 10, 10, 11,
 12, 11, 11, 11, 11, 11, 11, 12
};

const U64 NOT_A_FILE = 18374403900871474942ULL;
const U64 NOT_H_FILE = 9187201950435737471ULL;
const U64 NOT_GH_FILE = 4557430888798830399ULL;
const U64 NOT_AB_FILE = 18229723555195321596ULL; 

/*=============================*/
		/*func defs*/
/*=============================*/

//get precalculated attack table for pawn for every square
U64 musk_pawn_attack(int color,int square);
U64 musk_knight_attack(int square);
U64 musk_king_attack(int square);
U64 musk_bishop_attack(int square);
U64 musk_rook_attack(int square);

U64 otf_bishop_attacks(int square,U64 block);
U64 otf_rook_attacks(int square,U64 block);

//find possible blockage at a certain index
U64 set_occupancy(int index,int bits_mask,U64 atk_map);

void print_bitboard(U64 bitboard);

void init_leaper_attacks();


#endif
