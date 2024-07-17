#ifndef ENGINE_H
#define ENGINE_H

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
#define get_bit(bitboard,square) ((bitboard) & (1ULL << square))
//sets up a bit on the bitboard
#define set_bit(bitboard,square) ((bitboard) |= (1ULL << square))
//because using it twice will have the effect of setting it (see XOR table)
#define pop_bit(bitboard,square) (get_bit(bitboard,square)) ? ((bitboard) ^= (1ULL << square)) : 0
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
A1,B1,C1,D1,E1,F1,G1,H1,
no_square
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
enum {white,black,both};

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

U64 bishop_masks[64];
U64 rook_masks[64];

//tables -> [square][ocp]
//bishop
U64 bishop_attack_table[64][512];
//THE ROOOOOOK
U64 rook_attack_table[64][4096];



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
//magic numbers stollen from {programming chess}
//magic numbers for bishops
U64 bishop_magics[64] = {
    0x40040844404084ULL,
    0x2004208a004208ULL,
    0x10190041080202ULL,
    0x108060845042010ULL,
    0x581104180800210ULL,
    0x2112080446200010ULL,
    0x1080820820060210ULL,
    0x3c0808410220200ULL,
    0x4050404440404ULL,
    0x21001420088ULL,
    0x24d0080801082102ULL,
    0x1020a0a020400ULL,
    0x40308200402ULL,
    0x4011002100800ULL,
    0x401484104104005ULL,
    0x801010402020200ULL,
    0x400210c3880100ULL,
    0x404022024108200ULL,
    0x810018200204102ULL,
    0x4002801a02003ULL,
    0x85040820080400ULL,
    0x810102c808880400ULL,
    0xe900410884800ULL,
    0x8002020480840102ULL,
    0x220200865090201ULL,
    0x2010100a02021202ULL,
    0x152048408022401ULL,
    0x20080002081110ULL,
    0x4001001021004000ULL,
    0x800040400a011002ULL,
    0xe4004081011002ULL,
    0x1c004001012080ULL,
    0x8004200962a00220ULL,
    0x8422100208500202ULL,
    0x2000402200300c08ULL,
    0x8646020080080080ULL,
    0x80020a0200100808ULL,
    0x2010004880111000ULL,
    0x623000a080011400ULL,
    0x42008c0340209202ULL,
    0x209188240001000ULL,
    0x400408a884001800ULL,
    0x110400a6080400ULL,
    0x1840060a44020800ULL,
    0x90080104000041ULL,
    0x201011000808101ULL,
    0x1a2208080504f080ULL,
    0x8012020600211212ULL,
    0x500861011240000ULL,
    0x180806108200800ULL,
    0x4000020e01040044ULL,
    0x300000261044000aULL,
    0x802241102020002ULL,
    0x20906061210001ULL,
    0x5a84841004010310ULL,
    0x4010801011c04ULL,
    0xa010109502200ULL,
    0x4a02012000ULL,
    0x500201010098b028ULL,
    0x8040002811040900ULL,
    0x28000010020204ULL,
    0x6000020202d0240ULL,
    0x8918844842082200ULL,
    0x4010011029020020ULL
};

//magic numbers for rooks
U64 rook_magics[64] = {
    0x8a80104000800020ULL,
    0x140002000100040ULL,
    0x2801880a0017001ULL,
    0x100081001000420ULL,
    0x200020010080420ULL,
    0x3001c0002010008ULL,
    0x8480008002000100ULL,
    0x2080088004402900ULL,
    0x800098204000ULL,
    0x2024401000200040ULL,
    0x100802000801000ULL,
    0x120800800801000ULL,
    0x208808088000400ULL,
    0x2802200800400ULL,
    0x2200800100020080ULL,
    0x801000060821100ULL,
    0x80044006422000ULL,
    0x100808020004000ULL,
    0x12108a0010204200ULL,
    0x140848010000802ULL,
    0x481828014002800ULL,
    0x8094004002004100ULL,
    0x4010040010010802ULL,
    0x20008806104ULL,
    0x100400080208000ULL,
    0x2040002120081000ULL,
    0x21200680100081ULL,
    0x20100080080080ULL,
    0x2000a00200410ULL,
    0x20080800400ULL,
    0x80088400100102ULL,
    0x80004600042881ULL,
    0x4040008040800020ULL,
    0x440003000200801ULL,
    0x4200011004500ULL,
    0x188020010100100ULL,
    0x14800401802800ULL,
    0x2080040080800200ULL,
    0x124080204001001ULL,
    0x200046502000484ULL,
    0x480400080088020ULL,
    0x1000422010034000ULL,
    0x30200100110040ULL,
    0x100021010009ULL,
    0x2002080100110004ULL,
    0x202008004008002ULL,
    0x20020004010100ULL,
    0x2048440040820001ULL,
    0x101002200408200ULL,
    0x40802000401080ULL,
    0x4008142004410100ULL,
    0x2060820c0120200ULL,
    0x1001004080100ULL,
    0x20c020080040080ULL,
    0x2935610830022400ULL,
    0x44440041009200ULL,
    0x280001040802101ULL,
    0x2100190040002085ULL,
    0x80c0084100102001ULL,
    0x4024081001000421ULL,
    0x20030a0244872ULL,
    0x12001008414402ULL,
    0x2006104900a0804ULL,
    0x1004081002402ULL
};

/**********************************\
 ==================================
 
            Chess board
 
 ==================================

\**********************************/


// castling rights binary encoding

/*

    bin  dec
    
   0001    1  white king can castle to the king side
   0010    2  white king can castle to the queen side
   0100    4  black king can castle to the king side
   1000    8  black king can castle to the queen side

   examples

   1111       both sides an castle both directions
   1001       black king => queen side
              white king => king side

*/

//caps for white pieces and lower for black pieces
enum {P,N,B,R,Q,K,p,n,b,r,q,k}; 
enum {wk = 1,wq = 2, bk = 4 , bq = 8};

char ASCII_pieces[12] = "PNBRQKpnbrqk"; 

//this wont print on windows , use WIN64
char *unicode_pieces[12] = {"♙","♘","♗","♖","♕","♔","♟︎","♞","♝","♜","♛","♚"};

//converty ascci chars to hardcoded consts
int char_pieces[] = {
	['P'] = P,
	['N'] = N,
	['B'] = B,
	['R'] = R,
	['Q'] = Q,
	['K'] = K,
	['p'] = p,
	['n'] = n,
	['b'] = b,
	['r'] = r,
	['q'] = q,
	['k'] = k
};


					  //just for visualization
/*
                            WHITE PIECES


        Pawns                  Knights              Bishops
        
  8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
  7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
  6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
  5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
  4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
  3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
  2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
  1  0 0 0 0 0 0 0 0    1  0 1 0 0 0 0 1 0    1  0 0 1 0 0 1 0 0

     a b c d e f g h       a b c d e f g h       a b c d e f g h


         Rooks                 Queens                 King

  8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
  7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
  6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
  5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
  4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
  3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
  2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
  1  1 0 0 0 0 0 0 1    1  0 0 0 1 0 0 0 0    1  0 0 0 0 1 0 0 0

     a b c d e f g h       a b c d e f g h       a b c d e f g h


                            BLACK PIECES


        Pawns                  Knights              Bishops
        
  8  0 0 0 0 0 0 0 0    8  0 1 0 0 0 0 1 0    8  0 0 1 0 0 1 0 0
  7  1 1 1 1 1 1 1 1    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
  6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
  5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
  4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
  3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
  2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
  1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0

     a b c d e f g h       a b c d e f g h       a b c d e f g h


         Rooks                 Queens                 King

  8  1 0 0 0 0 0 0 1    8  0 0 0 1 0 0 0 0    8  0 0 0 0 1 0 0 0
  7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
  6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
  5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
  4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
  3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
  2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
  1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0

     a b c d e f g h       a b c d e f g h       a b c d e f g h



                             OCCUPANCIES


     White occupancy       Black occupancy       All occupancies

  8  0 0 0 0 0 0 0 0    8  1 1 1 1 1 1 1 1    8  1 1 1 1 1 1 1 1
  7  0 0 0 0 0 0 0 0    7  1 1 1 1 1 1 1 1    7  1 1 1 1 1 1 1 1
  6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
  5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
  4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
  3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
  2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  1 1 1 1 1 1 1 1
  1  1 1 1 1 1 1 1 1    1  0 0 0 0 0 0 0 0    1  1 1 1 1 1 1 1 1



                            ALL TOGETHER

                        8  ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
                        7  ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎
                        6  . . . . . . . .
                        5  . . . . . . . .
                        4  . . . . . . . .
                        3  . . . . . . . .
                        2  ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
                        1  ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

                           a b c d e f g h

*/


	//for each piece including diff colors
	U64 bitboards[12];

	//all black , all white and all colors (captures and stuff)
	U64 occupancies[3];

	//side to move white or black
	int side = 0;

	//enpassant square
	int enpassant = no_square;

	//castle rights
	int castle;
	

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
void init_sliders_attacks();

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


static inline U64 get_bishop_attacks(int square,U64 ocp);
static inline U64 get_rook_attacks(int square,U64 ocp);


void print_chessboard(U64 chessboard[12]);

#endif
