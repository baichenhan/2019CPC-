#include "common.h"
#include <stdio.h>
#include <mpi.h>
#include <athread.h>

extern SLAVE_FUN(stencil_7_slave)();
//extern SLAVE_FUN(stencil_27_slave)();
const char* version_name = "Optimized version";

void create_dist_grid(dist_grid_info_t *grid_info, int stencil_type) {

   
        grid_info->local_size_x = grid_info->global_size_x;
        grid_info->local_size_y = grid_info->global_size_y;
        grid_info->local_size_z = grid_info->global_size_z / grid_info->p_num;
   

    grid_info->offset_x = 0;
    grid_info->offset_y = 0;
    grid_info->offset_z = grid_info->p_id*(grid_info->global_size_z / grid_info->p_num);
    grid_info->halo_size_x = 1;
    grid_info->halo_size_y = 1;
    grid_info->halo_size_z = 1;

}

void destroy_dist_grid(dist_grid_info_t *grid_info) {
	

}

ptr_t stencil_7(ptr_t grid, ptr_t aux, const dist_grid_info_t *grid_info, int nt) {
    
	ptr_t buffer[2] = {grid, aux};
	if (nt != 1)
		end = 1;
	else
		end = 0;

	if (!end)
		{athread_init();   ;}      /*1. 从核线程初始化*/
    int x_start = grid_info->halo_size_x, x_end = grid_info->local_size_x + grid_info->halo_size_x;
    int y_start = grid_info->halo_size_y, y_end = grid_info->local_size_y + grid_info->halo_size_y;
    int z_start = grid_info->halo_size_z , z_end = grid_info->local_size_z + grid_info->halo_size_z;
    int ldx = grid_info->local_size_x + 2 * grid_info->halo_size_x;
    int ldy = grid_info->local_size_y + 2 * grid_info->halo_size_y;
    int ldz = grid_info->local_size_z + 2 * grid_info->halo_size_z;
    for(int t = 0; t < nt; ++t) {

	
	 t_a0 = buffer[t % 2];
         t_a1 = buffer[(t + 1) % 2];
	
	//MPI_Barrier(MPI_COMM_WORLD);


	if(grid_info->p_id != grid_info->p_num -1)
	{
		MPI_Send(&t_a0[INDEX(0,0,grid_info->global_size_z / grid_info->p_num,ldx,ldy)], ldx*ldy, MPI_DOUBLE, grid_info->p_id+1, 1,MPI_COMM_WORLD);
	}
	if(grid_info->p_id != 0)
	{
		MPI_Recv(&t_a0[INDEX(0,0,0,ldx,ldy)], ldx*ldy,  MPI_DOUBLE, grid_info->p_id-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
	}
	if(grid_info->p_id != 0) 
	{
		MPI_Send(&t_a0[INDEX(0,0,1,ldx,ldy)], ldx*ldy, MPI_DOUBLE, grid_info->p_id-1, 1,MPI_COMM_WORLD);
	}	
	if(grid_info->p_id !=grid_info->p_num -1)
	{
		MPI_Recv(&t_a0[INDEX(0,0,grid_info->global_size_z / grid_info->p_num + 1,ldx,ldy)], ldx*ldy,  MPI_DOUBLE, grid_info->p_id+1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

			// MPI_Barrier(MPI_COMM_WORLD);
	athread_spawn(stencil_7_slave, 0); /*2. 从核线程启动*/

	/*for(int y = y_start; y < y_end; ++y) {
                for(int x = x_start; x < x_end; ++x) {
                    t_a1[INDEX(x, y, 31, ldx, ldy)] \
                        = ALPHA_ZZZ * t_a0[INDEX(x, y, 31, ldx, ldy)] \
                        + ALPHA_NZZ * t_a0[INDEX(x-1, y, 31, ldx, ldy)] \
                        + ALPHA_PZZ * t_a0[INDEX(x+1, y, 31, ldx, ldy)] \
                        + ALPHA_ZNZ * t_a0[INDEX(x, y-1, 31, ldx, ldy)] \
                        + ALPHA_ZPZ * t_a0[INDEX(x, y+1, 31, ldx, ldy)] \
                        + ALPHA_ZZN * t_a0[INDEX(x, y, 30, ldx, ldy)] \
                        + ALPHA_ZZP * t_a0[INDEX(x, y, 32, ldx, ldy)];    

		t_a1[INDEX(x, y, 32, ldx, ldy)] \
                        = ALPHA_ZZZ * t_a0[INDEX(x, y, 32, ldx, ldy)] \
                        + ALPHA_NZZ * t_a0[INDEX(x-1, y, 32, ldx, ldy)] \
                        + ALPHA_PZZ * t_a0[INDEX(x+1, y, 32, ldx, ldy)] \
                        + ALPHA_ZNZ * t_a0[INDEX(x, y-1, 32, ldx, ldy)] \
                        + ALPHA_ZPZ * t_a0[INDEX(x, y+1, 32, ldx, ldy)] \
                        + ALPHA_ZZN * t_a0[INDEX(x, y, 31, ldx, ldy)] \
                        + ALPHA_ZZP * t_a0[INDEX(x, y, 33, ldx, ldy)];
                }
            }*/
				
	athread_join();         /*3. 从核线程回收 */
    }//一次迭代结束
    if (end)

   { 
	athread_halt();}/*4. 从核线程终止*/
    return buffer[nt % 2];
	
}

ptr_t stencil_27(ptr_t grid, ptr_t aux, const dist_grid_info_t *grid_info, int nt) {

   
}
