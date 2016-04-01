/* C O N F I G   P A R A M E T E R S */
long MAIN_MEMORY;
int RESOURCE_TYPES;
int TIME_QUANTUM;
int SCHEDULING;
int PREEMPTIVE;


/* L I S T S */
job_t * JOBS_LIST = NULL;
job_t * READY_Q = NULL;
job_t * WAITING_Q = NULL;
job_t * IO_Q = NULL;

system_resource_t * SYSTEM_RESOURCES = NULL;

/* R E U S A B L E   P O I N T E R S */
job_t * current;
operation_t * op_current;
resource_t * resource_current;
reg_t * reg_current;
system_resource_t * sysres_current;
resource_instance_t * inst_current;

/* G E N E R I C   I N T   T Y P E   V A R I A B L E S */
uint32_t i;
uint32_t j;
uint32_t print_count = 0;
uint8_t OP_FINISHED = 0;

/* G E N E R I C   C H A R   T Y P E   V A R I A B L E S */
int8_t c;
char print_string[100];

/* F I L E S */
FILE * job_file;
FILE * log_file;
FILE * config_file;
FILE * resource_file;

/* T I M E */
time_t start_time;
time_t current_time;
int previous_time;
time_t cpu_op_finish_time;
time_t io_op_finish_time;
struct timeval prog_start_time;
struct timeval prog_end_time;
uint64_t prog_total_time;

/* P R O G R A M   C O U N T E R S */

uint64_t CURRENT_IO_COUNT = 0;
uint64_t CURRENT_CPU_COUNT = 0;
uint64_t CURRENT_OS_RUNTIME = 0;
