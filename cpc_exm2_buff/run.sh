#前台提交
bsub -b -I -q q_sw_cpc_2  -host_stack 1024 -share_size 4096 -n 16 -cgsp 64 ./benchmark-optimized 27 512 512 512 16 /home/export/online1/cpc/pre/stencil_data_27_512x512x512_16steps /home/export/online1/cpc/pre/stencil_answer_27_512x512x512_16steps 2>&1 | tee compute.log
# -sw3runarg "-p -f"