#include "board.h"

/*=============================*/
	 /*func implimentations*/
/*=============================*/


void init_leaper_attacks(){
	//loop over every square 
	for(int s = 0 ; s < 64 ; s++){
		//init pawn attacks
		pawn_attacks[white][s] = musk_pawn_attack(white,s); 
		pawn_attacks[black][s] = musk_pawn_attack(black,s);
		knight_attacks[s] = musk_knight_attack(s);
		king_attacks[s] = musk_king_attack(s);	
	}
}

U64 musk_king_attack(int square){
	U64 attack_map = 0ULL;
	U64 bitboard   = 0ULL;

	set_bit(bitboard,square);
	//finding offsets 
	/*
	8  0 0 0 0 0 0 0 0
	7  0 0 0 0 0 0 0 0
	6  0 0 X X X 0 0 0
	5  0 0 X K X 0 0 0
	4  0 0 X X X 0 0 0
	3  0 0 0 0 0 0 0 0
	2  0 0 0 0 0 0 0 0
	1  0 0 0 0 0 0 0 0
	   
	   a b c d e f g h
	*/ /* >> 1,9,8,7 */
	//up
	attack_map |= (bitboard >> 8);
	if((bitboard >> 1) & NOT_H_FILE) attack_map |= (bitboard >> 1);	
	if((bitboard >> 9) & NOT_H_FILE) attack_map |= (bitboard >> 9); 
	if((bitboard >> 7) & NOT_A_FILE) attack_map |= (bitboard >> 7);	
	//down 
	attack_map |= (bitboard << 8);
	if((bitboard << 1) & NOT_A_FILE) attack_map |= (bitboard << 1);	
	if((bitboard << 9) & NOT_A_FILE) attack_map |= (bitboard << 9); 
	if((bitboard << 7) & NOT_H_FILE) attack_map |= (bitboard << 7);	
	
	return attack_map;
}

U64 musk_knight_attack(int square){
	U64 attack_map = 0ULL;
	U64 bitboard   = 0ULL;

	set_bit(bitboard,square);
	//finding offsets 
	/*
	8  0 0 0 0 0 0 0 0
	7  0 0 x 0 x 0 0 0
	6  0 x 0 0 0 x 0 0
	5  0 0 0 K 0 0 0 0
	4  0 x 0 0 0 x 0 0
	3  0 0 x 0 x 0 0 0
	2  0 0 0 0 0 0 0 0
	1  0 0 0 0 0 0 0 0
	   
	   a b c d e f g h
	*/ /* >> 15 ,17,10, 6 */
	//up attacks ...	
	if((bitboard >> 6) & NOT_AB_FILE) attack_map |= (bitboard >> 6);	
	if((bitboard >> 15) & NOT_A_FILE) attack_map |= (bitboard >> 15);

	if((bitboard >> 17) & NOT_H_FILE) attack_map |= (bitboard >> 17);	
	if((bitboard >> 10) & NOT_GH_FILE) attack_map |= (bitboard >> 10);
	

	//down attacks ...
	if((bitboard << 6) & NOT_GH_FILE) attack_map |= (bitboard << 6);	
	if((bitboard << 15) & NOT_H_FILE) attack_map |= (bitboard << 15);

	if((bitboard << 17) & NOT_A_FILE) attack_map |= (bitboard << 17);	
	if((bitboard << 10) & NOT_AB_FILE) attack_map |= (bitboard << 10);


	return attack_map;
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
	5  0 0 0 K 0 0 0 0
	4  0 0 0 0 0 0 0 0
	3  0 0 0 0 0 | 0 |
	2  0 0 0 0 0 9 8 7
	1  6 5 4 3 2 1 0 0
	   
	   a b c d e f g h
	*/

	//white
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
	init_leaper_attacks();
	for(int i = 0 ; i < 64 ; i++){
		print_bitboard(king_attacks[i]);
	}

	return 0;
}
