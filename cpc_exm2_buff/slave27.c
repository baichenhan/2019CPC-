#include "common.h"
#include <stdio.h>
#include <math.h>
#include <slave.h>
//#include <simd.h>

#define cut_x 128
__thread_local cptr_t a0_slave;
__thread_local ptr_t a1_slave;
__thread_local int x, y, z_slave, thistime_y_slave, t, the_slave, a4;
__thread_local volatile int my_id, get_reply, put_reply;
__thread_local double b0[4][10][136], b1[8][136];
//__thread_local doublev4 va1,vb[8],vc[8];
extern ptr_t t_a0;
extern ptr_t t_a1;
extern int z, thistime_y;
void stencil_27_slave() {
	my_id = athread_get_id(-1);
	get_reply = 0;
	put_reply = 0;

	athread_get(PE_MODE, &t_a0, &a0_slave, sizeof(ptr_t), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &t_a1, &a1_slave, sizeof(ptr_t), &get_reply, 0, 0, 0);
	while (get_reply != 2);

	for (a4 = 0; a4 < 4; ++a4) {
		thistime_y_slave = 0;
		get_reply = 0;

		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8, 0, 514, 514)], &b0[0][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 1, 0, 514, 514)], &b0[0][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 2, 0, 514, 514)], &b0[0][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 3, 0, 514, 514)], &b0[0][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 4, 0, 514, 514)], &b0[0][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 5, 0, 514, 514)], &b0[0][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 6, 0, 514, 514)], &b0[0][6][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 7, 0, 514, 514)], &b0[0][7][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 8, 0, 514, 514)], &b0[0][8][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 9, 0, 514, 514)], &b0[0][9][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);

		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8, 1, 514, 514)], &b0[1][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 1, 1, 514, 514)], &b0[1][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 2, 1, 514, 514)], &b0[1][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 3, 1, 514, 514)], &b0[1][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 4, 1, 514, 514)], &b0[1][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 5, 1, 514, 514)], &b0[1][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 6, 1, 514, 514)], &b0[1][6][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 7, 1, 514, 514)], &b0[1][7][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 8, 1, 514, 514)], &b0[1][8][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 9, 1, 514, 514)], &b0[1][9][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);

		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8, 2, 514, 514)], &b0[2][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 1, 2, 514, 514)], &b0[2][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 2, 2, 514, 514)], &b0[2][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 3, 2, 514, 514)], &b0[2][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 4, 2, 514, 514)], &b0[2][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 5, 2, 514, 514)], &b0[2][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 6, 2, 514, 514)], &b0[2][6][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 7, 2, 514, 514)], &b0[2][7][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 8, 2, 514, 514)], &b0[2][8][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 9, 2, 514, 514)], &b0[2][9][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);

	/*	athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8,     3, 514, 514)], &b0[3][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 1, 3, 514, 514)], &b0[3][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 2, 3, 514, 514)], &b0[3][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 3, 3, 514, 514)], &b0[3][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 4, 3, 514, 514)], &b0[3][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 5, 3, 514, 514)], &b0[3][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 6, 3, 514, 514)], &b0[3][6][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 7, 3, 514, 514)], &b0[3][7][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 8, 3, 514, 514)], &b0[3][8][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 8 + 9, 3, 514, 514)], &b0[3][9][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);    */


		while (get_reply != 30);

		for (z_slave = 1; z_slave < 33; ++z_slave) {
			get_reply = 0;
			if(z_slave<32){
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8,     z_slave + 2, 514, 514)], &b0[3][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 1, z_slave + 2, 514, 514)], &b0[3][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 2, z_slave + 2, 514, 514)], &b0[3][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 3, z_slave + 2, 514, 514)], &b0[3][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 4, z_slave + 2, 514, 514)], &b0[3][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 5, z_slave + 2, 514, 514)], &b0[3][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 6, z_slave + 2, 514, 514)], &b0[3][6][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 7, z_slave + 2, 514, 514)], &b0[3][7][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 8, z_slave + 2, 514, 514)], &b0[3][8][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 8 + 9, z_slave + 2, 514, 514)], &b0[3][9][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
					}
			//while (get_reply != 10);


			for (y = 1; y < 9; ++y) {
				for (x = 4; x < 132; ++x)
					 {


					b1[y-1][x]  =  \
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
			if(z_slave<32)
			while (get_reply != 10);

			put_reply = 0;
			for (int i = 0; i < 8; i++)
			{
				athread_put(PE_MODE, &b1[i][4], &a1_slave[INDEX(cut_x*a4 + 1, my_id * 8 + i + 1 , z_slave, 514, 514)], cut_x * sizeof(double), &put_reply, 0, 0);
			}
			while (put_reply != 8);
			for (int bz = 1; bz < 4; bz++)
				for (int by = 0; by < 10; by++)
					for (int bx = 0; bx < 136; bx++)
					{
						b0[bz - 1][by][bx] = b0[bz][by][bx];
					}
			//while (put_reply != 8);
		}
	}//ÕûÌåslaveÑ­»·
}
