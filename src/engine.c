#include "engine.h"

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
	unsigned int result = state;
	//xor algo 
	result ^= result << 13;
	result ^= result >> 17;
	result ^= result << 5;

	state = result;
	return result;	
}

U64 rand_U64(){
	U64 n1,n2,n3,n4;
	n1 = (U64)(rand_U32()) & 0xFFFF;
	n2 = (U64)(rand_U32()) & 0xFFFF;
	n3 = (U64)(rand_U32()) & 0xFFFF;
	n4 = (U64)(rand_U32()) & 0xFFFF;

	return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

//magic

U64 rand_magic(){
	return rand_U64() & rand_U64() & rand_U64();
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
	for(i = 0;i < 100000000;i++){

		//gets randome magic number candidate
		magic_number = rand_magic();
		
		//skip bad ones from the start
		if(bitlen((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;
		

		//init used attacks for ech trial
		memset(used_attacks,0ULL,sizeof(used_attacks));
		
		
		//test if index is correct (checl hashing)	
		int fail,index,magic_index;
		for(fail = 0 , index = 0;!fail && index < rob;index++){
			//core expression for validity of a magic number	
			magic_index = (int)((ocp[index] * magic_number) >> (64-rob));
	

			//not used attack yet
			if(used_attacks[magic_index] == 0ULL) 
				used_attacks[magic_index] = attacks[index];
			
			else if(used_attacks[magic_index] != attacks[index]){
				//magic number fails
				fail = 1;
			}

		}
		if(!fail) return magic_number;
	}
	printf("magic number was never found!!!\n");
	return 0ULL;
}

//doesnt generate correct magic numbers althought they must be
//for now am stealing ones from a youtube tutorial!!!
void init_magic_numbers(){
	//loop through all squares
	for(int i = 0 ; i < 64 ; i++){
		//for bishops
		//printf("0x%llxULL,\n",find_magic_number(i,bishop_rob[i],bishop));
		//for rooks
		printf("0x%llxULL,\n",find_magic_number(i,rook_rob[i],rook));
		}
	printf("--------init-done----------\n");

}

void init_sliders_attacks(int bishop){
	int robc,magic_index,ocp_indicies;
	U64 attack_mask,ocp;
	for(int i = 0 ; i < 64 ; i++){
		bishop_masks[i] = musk_bishop_attack(i);
		rook_masks[i] = musk_rook_attack(i);
		
		attack_mask = bishop ? bishop_masks[i] : rook_masks[i];

		robc = bitlen(attack_mask);

		ocp_indicies = (1 << robc);
		
		for(int index = 0 ; index < ocp_indicies;index++){
			if(bishop){
				ocp = set_occupancy(index,robc,attack_mask);
				magic_index = (ocp * bishop_magics[i]) >> (64 - bishop_rob[i]);
				bishop_attack_table[i][magic_index] = otf_bishop_attacks(i,ocp);
			}
			else{
				ocp = set_occupancy(index,robc,attack_mask);
				magic_index = (ocp * rook_magics[i]) >> (64 - rook_rob[i]);
				rook_attack_table[i][magic_index] = otf_rook_attacks(i,ocp);		
			}

		}

	}
}

static inline U64 get_bishop_attacks(int square,U64 ocp){
	ocp &= bishop_masks[square];
	ocp *= bishop_magics[square];
	ocp >>= 64 - bishop_rob[square];
	return bishop_attack_table[square][ocp];
}

static inline U64 get_rook_attacks(int square,U64 ocp){
	ocp &= rook_masks[square];
	ocp *= rook_magics[square];
	ocp >>= 64 - rook_rob[square];
	return rook_attack_table[square][ocp];
}


void board_init(chessboard *X){
	init_leaper_attacks();
	init_sliders_attacks(bishop);
	init_sliders_attacks(rook);

	X->side = 0;
	X->enpassant = no_square;
	X->castle = 0;
}


void print_chessboard(chessboard *board){
	int square,fail;
	for(int rank = 0 ; rank < 8;rank++){
		for(int file = 0 ; file < 8;file++){
			if(!file) printf("%d  ",8-rank);
			square = rank*8+file;
			fail = 0;
			for(int i = 0 ; i < 12;i++){
				if(get_bit(board->bitboards[i],square)){
					printf("%c ",ASCII_pieces[i]);
					fail++;
				}
			}
			if(!fail) printf(". ");
		}
		printf("\n");
	}
	printf("\n   A B C D E F G H\n");
	printf("   side to move : %s", !(board->side) ? "white" : "black");
	printf("\n");
	printf("   enpassant : %s",(board->enpassant != no_square) ? possitions[board->enpassant] : "no");
	printf("\n");
	printf("   castling rights : %c%c%c%c",
			(board->castle & wk) ? ASCII_pieces[K] : '-',
			(board->castle & wq) ? ASCII_pieces[Q] : '-',
			(board->castle & bk) ? ASCII_pieces[k] : '-',
			(board->castle & bq) ? ASCII_pieces[q] : '-'
	  );	
	printf("\n\n");
}

char **parse_fen(char *fen){
	//13 tokens >=>	8 for each rank
	//				1 side to move
	//				1 castle rights
	//				1 enpassant
	//				1 50 moves rule
	//				1 full move counter	
	char *token;
	char **tokens = (char **)malloc(13*sizeof(char *));
	int pos = 0;
	if(tokens == NULL){
		printf("error allocating memory!\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(fen,FEN_DELIM);
	while(token != NULL){
		tokens[pos] = token;
		pos++;
		token = strtok(NULL,FEN_DELIM);	
	}
	return tokens;	
}


void fenget_chessboard(char *fen,chessboard *board){
	memset(board->bitboards,0ULL,sizeof(board->bitboards));
	memset(board->occupancies,0ULL,sizeof(board->occupancies));
	int piece,digit;
	for(int rank = 0 ; rank < 8 ; rank++){	
		for(int file = 0 ; file < 8 ; file++){
			int square = rank*8+file;
			//we are dealing with black pieces
			if((*fen >= 'a') && (*fen <= 'z')){
				piece = char_pieces[*fen];
				set_bit(board->bitboards[piece],square);
				set_bit(board->occupancies[1],square);
				set_bit(board->occupancies[2],square);
				fen++;
			}
			//dealing with white pieces
			if((*fen >= 'A') && (*fen <= 'Z')){
				piece = char_pieces[*fen];
				set_bit(board->bitboards[piece],square);
				set_bit(board->occupancies[0],square);
				set_bit(board->occupancies[2],square);
				fen++;
			}
			//in this case we handle skips of squares
			if((*fen >= '0') && (*fen <= '9')){
				digit = *fen - '0';
				piece = -1;
				for(int i = P ;i <= k ;i++){
					if(get_bit(board->bitboards[i],square)){
						piece = i;
					}
				}
				if(piece == -1)
					file--;

				file += digit;
				fen++;
			}

			if(*fen == '/'){
				fen++;
			}
		}
	}
			fen++;
			//side to move
			if(*fen == 'w'){
				board->side = white;
			}
			else{
				board->side = black;
			}
			
			fen +=2;
			
			//castle rights
			while(*fen != ' '){
				switch (*fen){
					case 'K': board->castle |= wk;break;
					case 'Q': board->castle |= wq;break;
					case 'k': board->castle |= bk;break;
					case 'q': board->castle |= bq;break;
					case '-': break;
				}
				fen++;
			}
			fen++;
			if(*fen != '-'){
		        int f = fen[0] - 'a';
				int r = 8 - (fen[1] - '0');
				board->enpassant = r*8+f;
			}
			else{
				board->enpassant = no_square;
			}

	
}

int main(void){
	chessboard main;
	board_init(&main);
	print_chessboard(&main);
	fenget_chessboard(killer_position,&main);
	print_chessboard(&main);

	
	return 0;
}

