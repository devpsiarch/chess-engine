#include "board.h"

/*=============================*/
	 /*func implimentations*/
/*=============================*/

static inline int getlsbi(U64 bitboard){
	assert(bitboard);
	bitboard = ((bitboard & - bitboard) - 1); 
	return bitlen(bitboard);
}

static inline int bitlen(U64 bitboard){
	int size = 0;
	while(bitboard &= bitboard -1){
		size ++;
	}
	return size+1;
}

U64 set_occupancy(int index,int bits_mask,U64 atk_map){
	U64 ocp = 0ULL;
	int sqr = 0;
	for(int i = 0 ; i < bits_mask ; i++){
		sqr = getlsbi(atk_map);
		pop_bit(atk_map,sqr);
		
		if(index & (1 << i)){
			ocp |= (1ULL << sqr);
		}
	}
	return ocp;
}


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

U64 otf_rook_attacks(int square,U64 block){
	
	U64 attack_map = 0ULL;

	int r = 0;
	int f = 0; 

	int tr = square/8;
	int tf = square%8;

	//mask relevant rook occupency
	for(r = tr + 1 ; r <= 7;r++){ 
		attack_map|= (1ULL << (r*8+tf));
		if((1ULL << (r*8+tf)) & block){
			break;
		}
	}
	for(f = tf + 1 ; f <= 7;f++){ 
		attack_map|= (1ULL << (tr*8+f));
		if((1ULL << (tr*8+f)) & block){
			break;
		}
	}
		
	for(r = tr - 1 ; r >= 0;r--){ 
		attack_map|= (1ULL << (r*8+tf));
		if((1ULL << (r*8+tf)) & block){
			break;
		}
	}
	for(f = tf - 1 ; f >= 0;f--){ 
		attack_map|= (1ULL << (tr*8+f));
		if((1ULL << (tr*8+f)) & block){
			break;
		}
	}
	
	return attack_map;
}

U64 otf_bishop_attacks(int square,U64 block){
	U64 attack_map = 0ULL;

	int r = 0;
	int f = 0; 

	int tr = square/8;
	int tf = square%8;

	//mast relevant bishop accupency
	for(r = tr+1,f = tf+1;r<=7 && f<=7;r++,f++){ 
		attack_map|= (1ULL << (r*8+f));
		if((1ULL << (r*8+f)) & block){
			break;
		}
	}
	for(r = tr-1,f = tf+1;r>=0 && f<=7;r--,f++){ 
		attack_map|= (1ULL << (r*8+f));
		if((1ULL << (r*8+f)) & block){
			break;
		}
	}
	for(r = tr+1,f = tf-1;r<=7 && f>=0;r++,f--){ 
		attack_map|= (1ULL << (r*8+f));
		if((1ULL << (r*8+f)) & block){
			break;
		}
	}
	for(r = tr-1,f = tf-1;r>=0 && f>=0;r--,f--){ 
		attack_map|= (1ULL << (r*8+f));
		if((1ULL << (r*8+f)) & block){
			break;
		}
	}	
	return attack_map;	
}

U64 musk_rook_attack(int square){
	
	U64 attack_map = 0ULL;

	int r = 0;
	int f = 0; 

	int tr = square/8;
	int tf = square%8;

	//mask relevant rook occupency
	for(r = tr + 1 ; r <= 6;r++) attack_map|= (1ULL << (r*8+tf));
	for(f = tf + 1 ; f <= 6;f++) attack_map|= (1ULL << (tr*8+f));
		
	for(r = tr - 1 ; r >= 1;r--) attack_map|= (1ULL << (r*8+tf));
	for(f = tf - 1 ; f >= 1;f--) attack_map|= (1ULL << (tr*8+f));
	
	return attack_map;
}


U64 musk_bishop_attack(int square){
	U64 attack_map = 0ULL;

	//finding offsets 
	/*
	8  0 0 0 0 0 0 0 0
	7  0 0 0 0 0 0 0 0
	6  0 0 0 0 0 0 0 0
	5  0 0 0 x 0 x 0 0
	4  0 0 0 0 b 0 0 0
	3  0 0 0 x 0 x 0 0
	2  0 0 0 0 0 0 0 0
	1  0 0 0 0 0 0 0 0
	   
	   a b c d e f g h
*/
	int r = 0;
	int f = 0; 

	int tr = square/8;
	int tf = square%8;

	//mast relevant bishop accupency
	for(r = tr+1,f = tf+1;r<=6 && f<=6;r++,f++) attack_map|= (1ULL << (r*8+f));
	for(r = tr-1,f = tf+1;r>=1 && f<=6;r--,f++) attack_map|= (1ULL << (r*8+f));

	for(r = tr+1,f = tf-1;r<=6 && f>=1;r++,f--) attack_map|= (1ULL << (r*8+f));
	for(r = tr-1,f = tf-1;r>=1 && f>=1;r--,f--) attack_map|= (1ULL << (r*8+f));
	
	return attack_map;	
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
			if(get_bit(bitboard,loc)){
				printf("\033[31m%d\033[0m ",1);
			}else{
				printf("%d ",0);
			}
		}
		printf("\n");
	}
	printf("\n   A B C D E F G H\n");
	printf("   board value :%llud\n\n",bitboard);
}


unsigned int rand_U32(){
	int result = state;
	//xor algo 
	result ^= result << 13;
	result ^= result >> 17;
	result ^= result << 5;

	state = result;
	return result;	
}

U64 rand_U64(){
	U64 n1,n2,n3,n4;
	n1 = ((U64)rand_U32()) & 0xffff;
	n2 = ((U64)rand_U32()) & 0xffff;
	n3 = ((U64)rand_U32()) & 0xffff;
	n4 = ((U64)rand_U32()) & 0xffff;

	return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

//magic

U64 rand_magic(){
	return (rand_U64() & rand_U64() & rand_U64());
}


U64 find_magic_number(int square,int rob,int bishop){
	U64 ocp[4096];

	U64 attacks[4096];

	U64 used_attacks[4096];

	U64 attack_mask = bishop ? musk_bishop_attack(square) : musk_rook_attack(square);

	//init ocp indices 
	int ocp_idc = 1 << rob;
	
	
	//for counts
	int i;

	for(i = 0 ; i < ocp_idc ; i++){
		//init ocp
		ocp[i]	= set_occupancy(i,rob,attack_mask);
		
		//init attacks	
		attacks[i] = bishop ? otf_bishop_attacks(square,ocp[i]) : 
							  otf_rook_attacks(square,ocp[i]);
	}

	U64 magic_number;
	//test magic number loop throught trial and error 
	for(i = 0;i < 100000;i++){
		//skip bad ones from the start
		if(bitlen((attack_mask * magic_number) & 0xff00000000000000) < 6) continue;
		
		//gets randome magic number candidate
		magic_number = rand_magic();

		//init used attacks for ech trial
		memset(used_attacks,0ULL,sizeof(used_attacks));
		
		
		//test if index is correct (checl hashing)	
		int fail,index,magic_index;
		for(fail = 0 , index = 0;!fail && index < rob;index++){
			//core expression for validity of a magic number	
			magic_index = (int)((ocp[index] * magic_number) >> (64-rob));
			printf("magic index is %d\n",magic_index);
			printf("index is %d\n",index);
			//not used attack yet
			if(used_attacks[magic_index] == 0ULL) 
				used_attacks[magic_index] = attacks[index];
			
			else if(used_attacks[magic_number] != attacks[index]){
				//magic number fails
				fail = 1;
			}

		}
		if(!fail) return magic_number;
	}
	printf("magic number was never found!!!\n");
	return 0ULL;
}


void init_magic_numbers(){
	//loop through all squares
	for(int i = 0 ; i < 64 ; i++){
		//for bishops
		printf("0x%lluxULL\n",find_magic_number(i,bishop_rob[i],bishop));
		//for rooks
		//printf("0x%lluxULL\n",find_magic_number(i,rook_rob[i],rook));

	}
}

int main(void){
	init_leaper_attacks();
	
	init_magic_numbers();


	return 0;
}
