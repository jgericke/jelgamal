#include "../include/jelgamal.h"

BIGD gen_rand(size_t nbits) {

	BIGD          r;

	r = bdNew();

	bdRandomSeeded(r, nbits, NULL, 0, bdRandomOctets);

	return(r);
}

BIGD gen_p(int pos) {

	BIGD		p;

	p = bdNew();

	bdConvFromHex(p, p_table[pos]);

	return(p);
}

BIGD gen_g(int pos) {

	BIGD 	g;

	g = bdNew();

	bdConvFromHex(g, g_table[pos]);

	return(g);
}

BIGD gen_x(BIGD p, size_t nbits) { /* 0 < x < p - 2 */

	BIGD 		 x; 
	BIGD         p2;
	BIGD         tmp; 

	x = bdNew();
	p2 = bdNew();
	tmp = bdNew();

	bdConvFromDecimal(tmp, "2");
	bdSubtract(p2, p, tmp);
	x = gen_rand(nbits);  

	while(bdCompare(p2, x) < 0) {
		x = gen_rand(nbits);
	} 

	bdFree(&p2);
	bdFree(&tmp);

	return(x);
}

BIGD gen_y(BIGD p, BIGD g, BIGD x) { /* y = g^x mod p */

	BIGD		y;

	y = bdNew();

	bdModExp(y, g, x, p);

	return(y);
}

BIGD gen_k(BIGD p, size_t nbits) { /* k = gcd(k, p-1) = 1 */

	BIGD		 k; 
	BIGD         p1; 
	BIGD         tmp; 
	BIGD         tmp2; 

	k = bdNew();
	p1 = bdNew();
	tmp = bdNew();
	tmp2 = bdNew();

	bdConvFromDecimal(tmp2, "1");
	bdSetEqual(p1, p);
	bdDecrement(p1);

	k = gen_rand(nbits);
	bdGcd(tmp, k, p1);

	while(!bdIsEqual(tmp2, tmp)) {
		k = gen_rand(nbits);
		bdGcd(tmp, k, p1);
	}

	bdFree(&p1);
	bdFree(&tmp); 
	bdFree(&tmp2);

	return(k);
}

BIGD gen_a(BIGD p, BIGD g, BIGD k) { /* a = g^k MOD p */

	BIGD		a; 

	a = bdNew();

	bdModExp(a, g, k, p);

	return(a);
}

BIGD gen_b(BIGD p, BIGD y, BIGD k, BIGD m) { /* b = (m mod p-1) * (y^k mod p) */

	BIGD		b; 
	BIGD		p1; 
	BIGD		tmp; 
	BIGD		tmp2; 

	b = bdNew();
	p1 = bdNew();
	tmp = bdNew();
	tmp2 = bdNew();

	bdSetEqual(p1, p);
	bdDecrement(p1);
	bdModExp(tmp, y, k, p);
	bdModulo(tmp2, m, p1);
	bdMultiply(b, tmp, tmp2);

	bdFree(&p1);
	bdFree(&tmp);
	bdFree(&tmp2);

	return(b);
}

BIGD gen_c(BIGD p, BIGD x, BIGD a, BIGD b) { /* c = b / (a^x mod p) */

	BIGD		r; 
	BIGD		c;
	BIGD		tmp; 

	r = bdNew();
	c = bdNew();
	tmp = bdNew();

	bdModExp(r, a, x, p);
	bdDivide(c, tmp, b, r);

	bdFree(&r);
	bdFree(&tmp);

	return(c);
}