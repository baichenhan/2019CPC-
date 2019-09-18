#include "common.h"
#include <stdio.h>
#include <math.h>
#include <slave.h>
	__thread_local cptr_t a0_slave;
	__thread_local ptr_t a1_slave;
	__thread_local int x,y, z_slave,thistime_y_slave;
	__thread_local volatile int my_id, get_reply, put_reply;
	__thread_local double b0[3][4][514], b1[2][512];
extern ptr_t t_a0;
extern ptr_t t_a1;
extern int z,thistime_y;
void stencil_27_slave( ) {
int putrec1,putrec2 ;
my_id = athread_get_id(-1);
	get_reply = 0;
	put_reply = 0;
	athread_get(PE_MODE, &t_a0, &a0_slave, sizeof(ptr_t ), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &t_a1, &a1_slave, sizeof(ptr_t ), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &z, &z_slave, sizeof(int), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &thistime_y, &thistime_y_slave, sizeof(int), &get_reply, 0, 0, 0);
	while (get_reply != 4);
	putrec1 = athread_get(PE_MODE, &a0_slave[INDEX(0, my_id * 2+thistime_y_slave, z_slave - 1, 514, 514)], &b0[0][0][0], 514* 4 * sizeof(double), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &a0_slave[INDEX(0, my_id * 2+thistime_y_slave, z_slave , 514, 514)], &b0[1][0][0], 514 * 4 * sizeof(double), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &a0_slave[INDEX(0, my_id * 2+thistime_y_slave, z_slave + 1, 514, 514)], &b0[2][0][0], 514 * 4 * sizeof(double), &get_reply, 0, 0, 0);
	while (get_reply != 7);
	for(y = 1; y < 3; ++y) {
                for(x = 1; x < 513; ++x) {
                   b1[y-1][x-1]  =  \
                       			     ALPHA_NNN * b0[0][y - 1][x - 1] \
					   + ALPHA_ZNN * b0[0][y - 1][x] \
					   + ALPHA_PNN * b0[0][y - 1][x + 1] \
                        		   + ALPHA_NZN * b0[0][y][x-1] \
					   + ALPHA_ZZN * b0[0][y][x] \
                       			   + ALPHA_PZN * b0[0][y][x+1] \
					   + ALPHA_NPN * b0[0][y + 1][x - 1] \
					   + ALPHA_ZPN * b0[0][y + 1][x] \
					   + ALPHA_PPN * b0[0][y + 1][x + 1] \
					   + ALPHA_NNZ * b0[1][y - 1][x - 1] \
					   + ALPHA_ZNZ * b0[1][y - 1][x] \
					   + ALPHA_PNZ * b0[1][y - 1][x + 1] \
					   + ALPHA_NZZ * b0[1][y][x - 1] \
					   + ALPHA_ZZZ * b0[1][y][x] \
					   + ALPHA_PZZ * b0[1][y][x + 1] \
					   + ALPHA_NPZ * b0[1][y + 1][x - 1] \
					   + ALPHA_ZPZ * b0[1][y + 1][x] \
					   + ALPHA_PPZ * b0[1][y + 1][x + 1] \
					   + ALPHA_NNP * b0[2][y - 1][x - 1] \
					   + ALPHA_ZNP * b0[2][y - 1][x] \
					   + ALPHA_PNP * b0[2][y - 1][x + 1] \
                        		   + ALPHA_NZP * b0[2][y][x-1] \
					   + ALPHA_ZZP * b0[2][y][x] \
                        		   + ALPHA_PZP * b0[2][y][x+1] \
					   + ALPHA_NPP * b0[2][y + 1][x - 1] \
					   + ALPHA_ZPP * b0[2][y + 1][x] \
					   + ALPHA_PPP * b0[2][y + 1][x + 1]; 
                }
             }       
	 athread_put(PE_MODE, &b1[0][0], (&a1_slave[INDEX(1, my_id * 2 + 1 + thistime_y_slave, z_slave, 514, 514)]), 512 * sizeof(double), &put_reply, 0, 0);
	 athread_put(PE_MODE, &b1[1][0], &a1_slave[INDEX(1, my_id * 2 + 2 +thistime_y_slave, z_slave, 514, 514)], 512 * sizeof(double), &put_reply, 0, 0);

}

