#ifndef H__JELCRYPT
#define H__JELCRYPT

#include "jelgamal.h"

/* size of x (private key) and k */
#define BITS 512

/* SRV struct */
typedef struct jelgamal_srv {
   BIGD       p;
   BIGD       g;
   BIGD       y;
   BIGD       x;
   BIGD       m1;
   int        pos;
} JELGAMAL_SRV;

/* CLI struct */
typedef struct jelgamal_cli {
   BIGD       k;
   BIGD       m;
   BIGD       c1;
   BIGD       c2;
} JELGAMAL_CLI;

/* SRV/CLI constructors */
void construct_jelgamal_srv(struct jelgamal_srv *srv, int pos);
void construct_jelgamal_cli(struct jelgamal_cli *cli); 
/* Initialize CLI/SRV struct objects with values */
void init_jelgamal_srv(struct jelgamal_srv *srv);
void init_jelgamal_cli(struct jelgamal_cli *cli, struct jelgamal_srv *srv);
/* Encrypt/decrypt buf of size buf_size */
void jelgamal_encrypt(unsigned char *buf, size_t buf_size, struct jelgamal_cli *cli, struct jelgamal_srv *srv);
void jelgamal_decrypt(unsigned char *buf, size_t buf_size, struct jelgamal_cli *cli, struct jelgamal_srv *srv);
/* Free/destroy struct objects */
void destroy_jelgamal_srv(struct jelgamal_srv *srv);
void destroy_jelgamal_cli(struct jelgamal_cli *cli);

#endif