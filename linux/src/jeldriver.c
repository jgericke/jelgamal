#include "../include/jelgamal.h"
#include "../include/jelcrypt.h"

/* #define MSWIN */
#define VERBOSE
/* Iterative: iterate through all elements in p/g_table */
/* #define ITERATIVE */
/* Random: perform ROUNDS amount of random p/g_table tests */
#define RANDOM
#define ROUNDS 1024
/* Size of our plaintext/decrypted text buffer */
#define OCTETS BITS/8

int jelgamal_driver(int pos) {

	JELGAMAL_SRV		srv;
	JELGAMAL_CLI		cli;
	unsigned char	    pt[OCTETS]={0};
	unsigned char	    dt[OCTETS]={0};

	bdRandomOctets(pt, OCTETS, NULL, 0);

	construct_jelgamal_srv(&srv, pos);
	construct_jelgamal_cli(&cli);

	init_jelgamal_srv(&srv);
	init_jelgamal_cli(&cli, &srv);

	jelgamal_encrypt(pt, sizeof(pt), &cli, &srv);
	jelgamal_decrypt(dt, sizeof(dt), &cli, &srv);

#ifdef VERBOSE
	printf("\nSRV - pos: %i", srv.pos); printf("\nP: "); bdPrint(srv.p, BD_PRINT_NL); printf("\nG: "); bdPrint(srv.g, BD_PRINT_NL); printf("\nY: "); bdPrint(srv.y, BD_PRINT_NL); printf("\nX: "); bdPrint(srv.x, BD_PRINT_NL); printf("\nCLI"); printf("\nK: "); bdPrint(cli.k, BD_PRINT_NL); printf("\nC1: "); bdPrint(cli.c1, BD_PRINT_NL); printf("\nC2: "); bdPrint(cli.c2, BD_PRINT_NL); printf("\nPT= "); bdPrint(cli.m, BD_PRINT_NL); printf("\nDT= "); bdPrint(srv.m1, BD_PRINT_NL);
#endif

	if(bdIsEqual(cli.m, srv.m1)) {

		destroy_jelgamal_srv(&srv);
	    destroy_jelgamal_cli(&cli);
		return(0);

	} else {

		destroy_jelgamal_srv(&srv);
	    destroy_jelgamal_cli(&cli);
		return(-1);

	}

}

int main(void) {

	int                 r=0,p=0,f=0;
	int					pos_size=0;
	int					pos_rand = 0;

	pos_size = (sizeof(p_table) / sizeof(p_table[0])) - 1;

#ifdef ITERATIVE
	for(r=0; r<=pos_size; r++) {

		if(jelgamal_driver(r) >= 0) {

			p++;
#ifdef VERBOSE
			printf("\n---- round %i passed ----\n", r);
#endif
		} else {

			f++;
#ifdef VERBOSE
			printf("\n---- round %i has failed ----\n", r);
#endif
		}

	}	
#elif defined RANDOM
	srand(time(0));

	for(r=0; r<ROUNDS; r++) {

		pos_rand = rand() % pos_size;
		if(jelgamal_driver(pos_rand) >= 0) {

			p++;
#ifdef VERBOSE
			printf("\n---- round %i passed ----\n", r);
#endif
		} else {

			f++;
#ifdef VERBOSE
			printf("\n---- round %i has failed ----\n", r);
#endif
		}

	}
#endif
	printf("\nTest Rounds:\t%i\nRounds Passed:\t%i\nRounds Failed:\t%i\n", r, p, f);
#ifdef MSWIN
	system("pause");
#endif
return(0);
}
