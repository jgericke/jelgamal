#include "../include/jelcrypt.h"

void construct_jelgamal_srv(struct jelgamal_srv *srv, int pos) {

	/* Ensure size of p_table/g_table are equal, pos < element count */
	if((sizeof(p_table) / sizeof(p_table[0])) != (sizeof(g_table) / sizeof(g_table[0])) || 
		pos > (sizeof(p_table) / sizeof(p_table[0]))-1) {

		fprintf(stderr, "Mismatched element count in p_table/g_table or pos > element count");
		exit(1);

	} 

	srv->p = bdNew();
	srv->g = bdNew();
	srv->y = bdNew();
	srv->x = bdNew();
	srv->m1 = bdNew();

	srv->pos = pos;
	bdSetZero(srv->p);
	bdSetZero(srv->g);
	bdSetZero(srv->y);
	bdSetZero(srv->x);
	bdSetZero(srv->m1);
}

void construct_jelgamal_cli(struct jelgamal_cli *cli) {

	cli->k = bdNew();
	cli->m = bdNew();
	cli->c1 = bdNew();
	cli->c2 = bdNew();

	bdSetZero(cli->k);
	bdSetZero(cli->m);
	bdSetZero(cli->c1);
	bdSetZero(cli->c2);
}

void init_jelgamal_srv(struct jelgamal_srv *srv) {

	srv->p = gen_p(srv->pos);
	srv->g = gen_g(srv->pos);
	srv->x = gen_x(srv->p, BITS);
	srv->y = gen_y(srv->p, srv->g, srv->x);
}

void init_jelgamal_cli(struct jelgamal_cli *cli, struct jelgamal_srv *srv) {

	cli->k = gen_k(srv->p, BITS);
}

void jelgamal_encrypt(unsigned char *buf, size_t buf_size, struct jelgamal_cli *cli, struct jelgamal_srv *srv) {

	bdConvFromOctets(cli->m, (unsigned char *)buf, buf_size);
	cli->c1 = gen_a(srv->p, srv->g, cli->k);
	cli->c2 = gen_b(srv->p, srv->y, cli->k, cli->m);
}

void jelgamal_decrypt(unsigned char *buf, size_t buf_size, struct jelgamal_cli *cli, struct jelgamal_srv *srv) {

	srv->m1 = gen_c(srv->p, srv->x, cli->c1, cli->c2);
	bdConvToOctets(srv->m1, (unsigned char *)buf, buf_size);
}

void destroy_jelgamal_srv(struct jelgamal_srv *srv) {

	srv->pos=0;
	bdFree(&srv->p);
	bdFree(&srv->g);
	bdFree(&srv->y);
	bdFree(&srv->x);
	bdFree(&srv->m1);
}

void destroy_jelgamal_cli(struct jelgamal_cli *cli) {

	bdFree(&cli->k);
	bdFree(&cli->m);
	bdFree(&cli->c1);
	bdFree(&cli->c2);
}