#include "common.h"
#include <stdio.h>
#include <mpi.h>
const char* version_name = "A naive base-line";

void create_dist_grid(dist_grid_info_t *grid_info, int stencil_type) {
    /* Naive implementation uses Process 0 to do all computations */
    if(grid_info->p_id == 0||grid_info->p_id == 15) {
        grid_info->local_size_x = 512;
        grid_info->local_size_y = 512;
        grid_info->local_size_z = 33;
    } else {
        grid_info->local_size_x = 512;
        grid_info->local_size_y = 512;
        grid_info->local_size_z = 34;
    }

	/*grid_info->local_size_x = 512;
        grid_info->local_size_y = 512;
        grid_info->local_size_z = 34;*/

if(grid_info->p_id == 0){
    grid_info->offset_x = 0;
    grid_info->offset_y = 0;
    grid_info->offset_z = 0;
    grid_info->halo_size_x = 1;
    grid_info->halo_size_y = 1;
    grid_info->halo_size_z = 1;
	}
else if(grid_info->p_id == 15){
    grid_info->offset_x = 0;
    grid_info->offset_y = 0;
    grid_info->offset_z = (grid_info->p_id)*32-1;
    grid_info->halo_size_x = 1;
    grid_info->halo_size_y = 1;
    grid_info->halo_size_z = 1;
	}

else {
    grid_info->offset_x = 0;
    grid_info->offset_y = 0;
    grid_info->offset_z = (grid_info->p_id)*32-1 ;
    grid_info->halo_size_x = 1;
    grid_info->halo_size_y = 1;
    grid_info->halo_size_z = 0;

	}

}

void destroy_dist_grid(dist_grid_info_t *grid_info) {

}

ptr_t stencil_7(ptr_t grid, ptr_t aux, const dist_grid_info_t *grid_info, int nt) {
    ptr_t buffer[2] = {grid, aux};

	//printf("this pid = %d",grid_info->p_id);

    int x_start = grid_info->halo_size_x, x_end = grid_info->local_size_x + grid_info->halo_size_x;
    int y_start = grid_info->halo_size_y, y_end = grid_info->local_size_y + grid_info->halo_size_y;
	int z_start,z_end;
	//if((grid_info->p_id == 0)||(grid_info->p_id == 15))
   // {z_start = grid_info->halo_size_z; z_end = grid_info->local_size_z + grid_info->halo_size_z;}
	if(grid_info->p_id == 15)
	{z_start = 2;z_end = 34;}
	else
	{z_start = 1;z_end = 33;}
    int ldx = grid_info->local_size_x + 2 * grid_info->halo_size_x;
    int ldy = grid_info->local_size_y + 2 * grid_info->halo_size_y;
    int ldz = grid_info->local_size_z + 2 * grid_info->halo_size_z;

    for(int t = 0; t < nt; ++t) {


        cptr_t a0 = buffer[t % 2];
        ptr_t a1 = buffer[(t + 1) % 2];
        for(int z = z_start; z < z_end; ++z) {
            for(int y = y_start; y < y_end; ++y) {
                for(int x = x_start; x < x_end; ++x) {
                    a1[INDEX(x, y, z, ldx, ldy)] \
                        = ALPHA_ZZZ * a0[INDEX(x, y, z, ldx, ldy)] \
                        + ALPHA_NZZ * a0[INDEX(x-1, y, z, ldx, ldy)] \
                        + ALPHA_PZZ * a0[INDEX(x+1, y, z, ldx, ldy)] \
                        + ALPHA_ZNZ * a0[INDEX(x, y-1, z, ldx, ldy)] \
                        + ALPHA_ZPZ * a0[INDEX(x, y+1, z, ldx, ldy)] \
                        + ALPHA_ZZN * a0[INDEX(x, y, z-1, ldx, ldy)] \
                        + ALPHA_ZZP * a0[INDEX(x, y, z+1, ldx, ldy)];
                }
            }
        }


	if(grid_info->p_id != 15)
	{
		MPI_Ssend(&a1[INDEX(0,0,32,ldx,ldy)], 514*514, MPI_DOUBLE, grid_info->p_id+1, 1,MPI_COMM_WORLD);
	}
	if(grid_info->p_id != 0)
	{
		if(grid_info->p_id != 15)
		MPI_Recv(&a1[INDEX(0,0,0,ldx,ldy)], 514*514,  MPI_DOUBLE, grid_info->p_id-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(grid_info->p_id == 15)
		MPI_Recv(&a1[INDEX(0,0,1,ldx,ldy)], 514*514,  MPI_DOUBLE, grid_info->p_id-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(grid_info->p_id != 15)
		MPI_Ssend(&a1[INDEX(0,0,1,ldx,ldy)], 514*514, MPI_DOUBLE, grid_info->p_id-1, 1,MPI_COMM_WORLD);
		if(grid_info->p_id == 15)
		MPI_Ssend(&a1[INDEX(0,0,2,ldx,ldy)], 514*514, MPI_DOUBLE, grid_info->p_id-1, 1,MPI_COMM_WORLD);
	}
	if(grid_info->p_id != 15)
	{
		MPI_Recv(&a1[INDEX(0,0,33,ldx,ldy)], 514*514,  MPI_DOUBLE, grid_info->p_id+1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}

    }
    return buffer[nt % 2];
}

ptr_t stencil_27(ptr_t grid, ptr_t aux, const dist_grid_info_t *grid_info, int nt) {
    ptr_t buffer[2] = {grid, aux};
    int x_start = grid_info->halo_size_x, x_end = grid_info->local_size_x + grid_info->halo_size_x;
    int y_start = grid_info->halo_size_y, y_end = grid_info->local_size_y + grid_info->halo_size_y;
    int z_start = grid_info->halo_size_z, z_end = grid_info->local_size_z + grid_info->halo_size_z;
    int ldx = grid_info->local_size_x + 2 * grid_info->halo_size_x;
    int ldy = grid_info->local_size_y + 2 * grid_info->halo_size_y;
    int ldz = grid_info->local_size_z + 2 * grid_info->halo_size_z;
    for(int t = 0; t < nt; ++t) {
        cptr_t a0 = buffer[t % 2];
        ptr_t a1 = buffer[(t + 1) % 2];
        for(int z = z_start; z < z_end; ++z) {
            for(int y = y_start; y < y_end; ++y) {
                for(int x = x_start; x < x_end; ++x) {
                    a1[INDEX(x, y, z, ldx, ldy)] \
                        = ALPHA_ZZZ * a0[INDEX(x, y, z, ldx, ldy)] \
                        + ALPHA_NZZ * a0[INDEX(x-1, y, z, ldx, ldy)] \
                        + ALPHA_PZZ * a0[INDEX(x+1, y, z, ldx, ldy)] \
                        + ALPHA_ZNZ * a0[INDEX(x, y-1, z, ldx, ldy)] \
                        + ALPHA_ZPZ * a0[INDEX(x, y+1, z, ldx, ldy)] \
                        + ALPHA_ZZN * a0[INDEX(x, y, z-1, ldx, ldy)] \
                        + ALPHA_ZZP * a0[INDEX(x, y, z+1, ldx, ldy)] \
                        + ALPHA_NNZ * a0[INDEX(x-1, y-1, z, ldx, ldy)] \
                        + ALPHA_PNZ * a0[INDEX(x+1, y-1, z, ldx, ldy)] \
                        + ALPHA_NPZ * a0[INDEX(x-1, y+1, z, ldx, ldy)] \
                        + ALPHA_PPZ * a0[INDEX(x+1, y+1, z, ldx, ldy)] \
                        + ALPHA_NZN * a0[INDEX(x-1, y, z-1, ldx, ldy)] \
                        + ALPHA_PZN * a0[INDEX(x+1, y, z-1, ldx, ldy)] \
                        + ALPHA_NZP * a0[INDEX(x-1, y, z+1, ldx, ldy)] \
                        + ALPHA_PZP * a0[INDEX(x+1, y, z+1, ldx, ldy)] \
                        + ALPHA_ZNN * a0[INDEX(x, y-1, z-1, ldx, ldy)] \
                        + ALPHA_ZPN * a0[INDEX(x, y+1, z-1, ldx, ldy)] \
                        + ALPHA_ZNP * a0[INDEX(x, y-1, z+1, ldx, ldy)] \
                        + ALPHA_ZPP * a0[INDEX(x, y+1, z+1, ldx, ldy)] \
                        + ALPHA_NNN * a0[INDEX(x-1, y-1, z-1, ldx, ldy)] \
                        + ALPHA_PNN * a0[INDEX(x+1, y-1, z-1, ldx, ldy)] \
                        + ALPHA_NPN * a0[INDEX(x-1, y+1, z-1, ldx, ldy)] \
                        + ALPHA_PPN * a0[INDEX(x+1, y+1, z-1, ldx, ldy)] \
                        + ALPHA_NNP * a0[INDEX(x-1, y-1, z+1, ldx, ldy)] \
                        + ALPHA_PNP * a0[INDEX(x+1, y-1, z+1, ldx, ldy)] \
                        + ALPHA_NPP * a0[INDEX(x-1, y+1, z+1, ldx, ldy)] \
                        + ALPHA_PPP * a0[INDEX(x+1, y+1, z+1, ldx, ldy)];
                }
            }
        }
    }
    return buffer[nt % 2];
}