J(ules)'s ElGamal Implementation

My own ElGamal implementation, using DI's BigDigits library (http://www.di-mgt.com.au/bigdigits.html). 
Jelgamal was created purely for my own learning purposes, and as such I wouldn't recommend using it anywhere 
near important data ;)

Currently jelgamal does not handle the generation of P/g groups, which are instead hard-coded (see p/g_table within
jelgamal.h) - this may come at a later date.

For Linux, run a 'make' within the src directory. MS version compiles fine in visual studio 2005.

- julian@jbg.za.org



