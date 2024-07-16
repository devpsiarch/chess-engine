#ifndef BOARD_H
#define BOARD_H

/*=============================*/
      /*includes headers*/
/*=============================*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>


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

//bishop and rook enum
enum {rook,bishop};

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

// bishop relavant occupancy bits for each possition
const int bishop_rob[64] = {
 6, 5, 5, 5, 5, 5, 5, 6,
 5, 5, 5, 5, 5, 5, 5, 5,
 5, 5, 7, 7, 7, 7, 5, 5,
 5, 5, 7, 9, 9, 7, 5, 5,
 5, 5, 7, 9, 9, 7, 5, 5,
 5, 5, 7, 7, 7, 7, 5, 5,
 5, 5, 5, 5, 5, 5, 5, 5,
 6, 5, 5, 5, 5, 5, 5, 6
};

// rook relavant occupancy bits for each possition
const int rook_rob[64] = {
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
	  /*rand magic nums*/
/*=============================*/

//a kind of seed for the xor shift algo
//that gens randoms nums cross platform
unsigned int state = 1804289383;

//magic numbers for bishops
U64 bishop_magics[64] = {
0x88104402811000a0ULL,
0x10108480d0002008ULL,
0x32008000000095ULL,
0x21a0c0071400100ULL,
0x24860000a01c800ULL,
0x1002210100800280ULL,
0x100410888800000ULL,
0x40a0854040008020ULL,
0x19288708010410ULL,
0x88819000020ULL,
0x8000700120002c84ULL,
0x30922000108ULL,
0x70052208008000ULL,
0x208110000c0002ULL,
0x300d2200000ULL,
0x4000444054108008ULL,
0x4023844006018023ULL,
0x4008a102102080e0ULL,
0x89084060010200ULL,
0x4c1260908000080ULL,
0x202080060050000ULL,
0x1002004409288080ULL,
0x801100a84080000ULL,
0x20d0489410002ULL,
0x8288041400022ULL,
0x8208284010001ULL,
0x8420b20840000004ULL,
0x440c820008ba081ULL,
0x1210840c10002806ULL,
0x804031420011002ULL,
0x80b005061000eULL,
0x82025008200012ULL,
0x8408992880409008ULL,
0x1aa1104a80000000ULL,
0x2020100008080ULL,
0x2004a10404400088ULL,
0x2802049008050194ULL,
0x400a820000000ULL,
0x2836042080040780ULL,
0x209004060400039ULL,
0x44109820024801ULL,
0x8580580014008ULL,
0x622b03045010210ULL,
0x440622080180500ULL,
0x208a00040024ULL,
0x20830a1030000000ULL,
0x48c1800110000ULL,
0x2410067070000022ULL,
0x14010500820002ULL,
0x680218400018010ULL,
0x40018421000020ULL,
0x20a0004084010100ULL,
0x128a400000ULL,
0x4080d0928110080ULL,
0x80a0890001800ULL,
0x4010018a27008200ULL,
0x24004202a600ULL,
0x81a2408401200110ULL,
0x9040200288a60404ULL,
0x110800340000ULL,
0x600120020208080ULL,
0x802905006880008ULL,
0x8362a0210100810ULL,
0x4001c110004110ULL
};

//magic numbers for rooks
U64 rook_magics[64] = {
0xb0040300c100008ULL,
0x100408800f000001ULL,
0x7040004004000800ULL,
0x2200041041040010ULL,
0x1a480002800000a0ULL,
0x200060400000000ULL,
0x1000089c0000032ULL,
0x20900402880000ULL,
0x8009400000002010ULL,
0x106000018004ULL,
0x3008068080041801ULL,
0x2040802000a44280ULL,
0x8200800040041020ULL,
0x800102a02080ULL,
0x1020400010220600ULL,
0x10108480d0002008ULL,
0x2002005301000042ULL,
0x8105005000051002ULL,
0xa201920080005020ULL,
0x32008000000095ULL,
0x422020a000100ULL,
0x80808000040002ULL,
0x8040048208204102ULL,
0x8010088140060010ULL,
0x2804006000812850ULL,
0x1040040e008f2000ULL,
0x4202042204000022ULL,
0x91014406d0000200ULL,
0x3008010102800900ULL,
0x80200000000ULL,
0x100f100000aULL,
0x401007004812028ULL,
0x2008040031604000ULL,
0x842080180509001ULL,
0x84090010000824ULL,
0x500826020220102ULL,
0x4008020060010000ULL,
0x2081086090080ULL,
0x4dd041101800ULL,
0x45001020020840ULL,
0x2000209c00800000ULL,
0xa002a0410800002ULL,
0x2020009200804100ULL,
0x6808038020404000ULL,
0x8401040008001000ULL,
0x2000889401020000ULL,
0x888014400092ULL,
0x82401e0102008ULL,
0x28010088000182ULL,
0x6204168520002000ULL,
0x840c110086480000ULL,
0x90540721031ULL,
0x2008080040140109ULL,
0x8e01001950400451ULL,
0x110a4a002211401ULL,
0x8040118206880c00ULL,
0x2d40100480040c0ULL,
0x80c2004c100804aULL,
0x10402020844009ULL,
0x4000444054108008ULL,
0xc800a0004000402ULL,
0x1100010e000002ULL,
0x400400a041080006ULL,
0x14148100020eaULL
};

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

unsigned int rand_U32();

U64 rand_U64();

//gets rand magic number
U64 rand_magic();

//searches for possible magic number
U64 find_magic_number(int square,int rob,int bishop);

//get all needed magic numbers
void init_magic_numbers();

//init everything function
void board_init();

#endif
