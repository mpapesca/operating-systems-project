job_t * JOBS_LIST = NULL;
job_t * READY_Q = NULL;
job_t * WAITING_Q = NULL;
job_t * IO_Q = NULL;
job_t * current;
operation_t * op_current;
reg_t * reg_current;
uint32_t i;
uint32_t j;
