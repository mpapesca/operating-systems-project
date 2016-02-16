/* L I S T S */
job_t * JOBS_LIST = NULL;
job_t * READY_Q = NULL;
job_t * WAITING_Q = NULL;
job_t * IO_Q = NULL;

/* R E U S A B L E   P O I N T E R S */
job_t * current;
operation_t * op_current;
reg_t * reg_current;

/* G E N E R I C   I N T   T Y P E   V A R I A B L E S */
uint32_t i;
uint32_t j;

/* G E N E R I C   C H A R   T Y P E   V A R I A B L E S */
int8_t c;

/* F I L E S */
FILE * job_file;
