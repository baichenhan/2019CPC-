#include "common.h"
#include <stdio.h>
#include <math.h>
#include <slave.h>
//#include <simd.h>

#define cut_x 256
__thread_local cptr_t a0_slave;
__thread_local ptr_t a1_slave;
__thread_local int x, y, z_slave, thistime_y_slave, t, the_slave, a4;
__thread_local volatile int my_id, get_reply, put_reply;
__thread_local double b0[4][6][264], b1[4][264]; 
//__thread_local doublev4 va1,vb[8],vc[8];
extern ptr_t t_a0;
extern ptr_t t_a1;
extern int z, thistime_y;
void stencil_7_slave() {
	my_id = athread_get_id(-1);
	get_reply = 0;
	put_reply = 0;

	athread_get(PE_MODE, &t_a0, &a0_slave, sizeof(ptr_t), &get_reply, 0, 0, 0);
	athread_get(PE_MODE, &t_a1, &a1_slave, sizeof(ptr_t), &get_reply, 0, 0, 0);
	while (get_reply != 2);

	for (a4 = 0; a4 < 3; ++a4) {
		thistime_y_slave = 0;
		for(the_slave = 1;the_slave <= 3 ; ++the_slave)  {
		get_reply = 0;

		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave, 0, 770, 770)], &b0[0][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 1, 0, 770, 770)], &b0[0][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 2, 0, 770, 770)], &b0[0][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 3, 0, 770, 770)], &b0[0][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 4, 0, 770, 770)], &b0[0][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 5, 0, 770, 770)], &b0[0][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);


		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave, 1, 770, 770)], &b0[1][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 1, 1, 770, 770)], &b0[1][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 2, 1, 770, 770)], &b0[1][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 3, 1, 770, 770)], &b0[1][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 4, 1, 770, 770)], &b0[1][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 5, 1, 770, 770)], &b0[1][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);


		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave, 2, 770, 770)], &b0[2][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 1, 2, 770, 770)], &b0[2][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 2, 2, 770, 770)], &b0[2][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 3, 2, 770, 770)], &b0[2][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 4, 2, 770, 770)], &b0[2][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
		athread_get(PE_MODE, &a0_slave[INDEX(cut_x * a4, my_id * 4+thistime_y_slave + 5, 2, 770, 770)], &b0[2][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);


		while (get_reply != 18);

		for (z_slave = 1; z_slave < 13; ++z_slave) {
			get_reply = 0;
			if(z_slave<12){
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave,     z_slave + 2, 770, 770)], &b0[3][0][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave + 1, z_slave + 2, 770, 770)], &b0[3][1][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave + 2, z_slave + 2, 770, 770)], &b0[3][2][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave + 3, z_slave + 2, 770, 770)], &b0[3][3][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave + 4, z_slave + 2, 770, 770)], &b0[3][4][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);
			athread_get(PE_MODE, &a0_slave[INDEX(cut_x*a4, my_id * 4+thistime_y_slave + 5, z_slave + 2, 770, 770)], &b0[3][5][3], (cut_x + 2) * sizeof(double), &get_reply, 0, 0, 0);

					}
			//while (get_reply != 10);


			for (y = 1; y < 5; ++y) {
				for (t = 1; t < 65; ++t)
					/*for(x=1;x<513;++x)	*/ {


					b1[y - 1][t * 4] = ALPHA_NZZ * b0[1][y][4 * t - 1];
					b1[y - 1][t * 4 + 1] = ALPHA_NZZ * b0[1][y][4 * t];
					b1[y - 1][t * 4 + 2] = ALPHA_NZZ * b0[1][y][4 * t + 1];
					b1[y - 1][t * 4 + 3] = ALPHA_NZZ * b0[1][y][4 * t + 2];

					b1[y - 1][t * 4] += ALPHA_ZZZ * b0[1][y][4 * t];
					b1[y - 1][t * 4 + 1] += ALPHA_ZZZ * b0[1][y][4 * t + 1];
					b1[y - 1][t * 4 + 2] += ALPHA_ZZZ * b0[1][y][4 * t + 2];
					b1[y - 1][t * 4 + 3] += ALPHA_ZZZ * b0[1][y][4 * t + 3];

					b1[y - 1][t * 4] += ALPHA_PZZ * b0[1][y][4 * t + 1];
					b1[y - 1][t * 4 + 1] += ALPHA_PZZ * b0[1][y][4 * t + 2];
					b1[y - 1][t * 4 + 2] += ALPHA_PZZ * b0[1][y][4 * t + 3];
					b1[y - 1][t * 4 + 3] += ALPHA_PZZ * b0[1][y][4 * t + 4];

					b1[y - 1][t * 4] += ALPHA_ZNZ * b0[1][y - 1][4 * t];
					b1[y - 1][t * 4 + 1] += ALPHA_ZNZ * b0[1][y - 1][4 * t + 1];
					b1[y - 1][t * 4 + 2] += ALPHA_ZNZ * b0[1][y - 1][4 * t + 2];
					b1[y - 1][t * 4 + 3] += ALPHA_ZNZ * b0[1][y - 1][4 * t + 3];

					b1[y - 1][t * 4] += ALPHA_ZPZ * b0[1][y + 1][4 * t];
					b1[y - 1][t * 4 + 1] += ALPHA_ZPZ * b0[1][y + 1][4 * t + 1];
					b1[y - 1][t * 4 + 2] += ALPHA_ZPZ * b0[1][y + 1][4 * t + 2];
					b1[y - 1][t * 4 + 3] += ALPHA_ZPZ * b0[1][y + 1][4 * t + 3];

					b1[y - 1][t * 4] += ALPHA_ZZN * b0[0][y][4 * t];
					b1[y - 1][t * 4 + 1] += ALPHA_ZZN * b0[0][y][4 * t + 1];
					b1[y - 1][t * 4 + 2] += ALPHA_ZZN * b0[0][y][4 * t + 2];
					b1[y - 1][t * 4 + 3] += ALPHA_ZZN * b0[0][y][4 * t + 3];

					b1[y - 1][t * 4] += ALPHA_ZZP * b0[2][y][4 * t];
					b1[y - 1][t * 4 + 1] += ALPHA_ZZP * b0[2][y][4 * t + 1];
					b1[y - 1][t * 4 + 2] += ALPHA_ZZP * b0[2][y][4 * t + 2];
					b1[y - 1][t * 4 + 3] += ALPHA_ZZP * b0[2][y][4 * t + 3];


				}
			}
			if(z_slave<12)
			while (get_reply != 6);

			put_reply = 0;
			for (int i = 0; i < 4; i++)
			{
				athread_put(PE_MODE, &b1[i][4], &a1_slave[INDEX(cut_x*a4 + 1, my_id * 4 +thistime_y_slave+ i + 1 , z_slave, 770, 770)], cut_x * sizeof(double), &put_reply, 0, 0);
			}
			//while (put_reply != 8);
			for (int bz = 1; bz < 4; bz++)
				for (int by = 0; by < 6; by++)
					for (int bx = 0; bx < 264; bx++)
					{
						b0[bz - 1][by][bx] = b0[bz][by][bx];
					}
			while (put_reply != 4);
		}
	thistime_y_slave += 256;
	}//ÕûÌåslaveÑ­»·
	
       
       
  }
}
