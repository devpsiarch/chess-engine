#include "board.h"

/*=============================*/
	 /*func implimentations*/
/*=============================*/


void init_pawn_attacks(){
	//loop over every square 
	for(int s = 0 ; s < 64 ; s++){
		//init pawn attacks
		pawn_attacks[white][s] = musk_pawn_attack(white,s); 
		pawn_attacks[black][s] = musk_pawn_attack(black,s);
	}
}

U64 musk_pawn_attack(int color,int square){
	U64 attack_map = 0ULL;
	U64 bitboard   = 0ULL;
	
	set_bit(bitboard,square);

	//cases for white and black
	// we need to take care also for wrapping around
	// attacks 	
	
	//white we shift to left >>
	//we shift 7 and 9 cuz :
	/*
	8  0 0 0 0 0 0 0 0
	7  0 0 0 0 0 0 0 0
	6  0 0 0 0 0 0 0 0
	5  0 0 0 0 0 0 0 0
	4  0 0 0 0 0 0 0 0
	3  0 0 0 0 0 | 0 |
	2  0 0 0 0 0 9 8 7
	1  6 5 4 3 2 1 0 0
	   
	   a b c d e f g h
	*/


	if(!color){
		if((bitboard >> 7) & NOT_A_FILE) attack_map |= (bitboard >> 7);	
		if((bitboard >> 9) & NOT_H_FILE) attack_map |= (bitboard >> 9);
	}
	//balck we shift right   <<
	else{
		if((bitboard << 7) & NOT_H_FILE) attack_map |= (bitboard << 7);	
		if((bitboard << 9) & NOT_A_FILE) attack_map |= (bitboard << 9);	
	}

	return attack_map;	
}

void print_bitboard(U64 bitboard){
	int loc;
	for(int rank = 0 ; rank < 8 ; rank++){
		for(int file = 0 ;file < 8 ; file++){
			if(!file)
				printf("%d  ",8 - rank);
			loc = rank*8+file;
			printf("%d ",get_bit(bitboard,loc)?1:0);	
		}
		printf("\n");
	}
	printf("\n   A B C D E F G H\n");
	printf("   board value :%llud\n\n",bitboard);
}

int main(void){
	init_pawn_attacks();
	for(int i = 0 ; i <= 64 ; i++){
		print_bitboard(pawn_attacks[black][i]);
	}

	return 0;
}
