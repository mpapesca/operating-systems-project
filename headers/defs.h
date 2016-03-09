/*** S T R U C T   D E F I N I T I O N S ***/

/* * * * * * * * * * * * * * * * * * * * * * * * *

  TYPEDEF  operation_t

  DISC      This struct is a node for holding the information about a single
            opertation.

  MEMBERS   id:  Unique identifying key of each operation per job.

            type:  Type of operation being performed whether CPU or I/O.

            duration: How much time the operation will require to be completed.

            next: The pointer to the next operation in the list of operation.

 * * * * * * * * * * * * * * * * * * * * * * * * */
typedef struct operation {

  int32_t id;
  int32_t type;
  bool status;
  int32_t duration;

  struct operation *next;

}operation_t;


/* * * * * * * * * * * * * * * * * * * * * * * * *

  TYPEDEF  reg_t

  DISC      This struct is a node for holding the information about a single
            opertation.

  MEMBERS   id:  Unique identifying key of each operation per job.

            type:  Type of operation being performed whether CPU or I/O.

            duration: How much time the operation will require to be completed.

            next: The pointer to the next operation in the list of operation.

 * * * * * * * * * * * * * * * * * * * * * * * * */
typedef struct reg {

  int32_t id;

  struct reg *next;

}reg_t;
/* * * * * * * * * * * * * * * * * * * * * * * * *

  TYPEDEF  job_t

  DISC      This struct is a node for holding the information about a single job.

  MEMBERS   id:  Unique identifying key of each job.

            process_state:  Current state of the job.
                0 - waiting
                1 - ready
                2 - busy

            process_num: ** may want to remove this item **

            program_count:  Current position in the program. Used for returning to
                            the program later.

            total_mem:  Total memory used by the job.

            min_mem: The minimum possible memory required by the job to operate.

            registers:  An array of the registers used by the job.

            operations: The different operations performed by the job with a
                        specification of what type of operation is being
                        performed (CPU, I/O).

            open_files: The files currently being accessed by the job.

            next: The pointer to the next job in the list of jobs.

 * * * * * * * * * * * * * * * * * * * * * * * * */
typedef struct job {

  int32_t id;
  int32_t process_state;
  int32_t process_num;
  int32_t prog_count;
  int32_t total_mem;
  int32_t min_mem;
  int32_t num_regs;
  reg_t *registers;
  int32_t num_ops;

  //These are for timing measurements
  struct timeval start_job;
  struct timeval finish_job;

  struct timeval start_wait;
  struct timeval finish_wait;
  struct timeval start_cpu;
  struct timeval finish_cpu;
  struct timeval on_line;

  uint32_t  total_run_time;
  uint32_t  total_wait_time;
  uint32_t  total_cpu_time;
  uint32_t  response_time;
  float     average_wait_time;

  uint8_t checking_cpu;
  uint8_t checking_wait;
  uint8_t job_started;
  uint8_t response_checked;




  operation_t * operations;
  uint8_t ** open_files;

  struct job *next;

}job_t;


/*** G E N E R A L   D E F I N I T I O N S ***/

/* F I L E   O P E R A T I O N S */
#define MOVE_FILE "cp docs/job_info_bu.txt docs/job_info.txt"
#define FILE_PATH "docs/job_info.txt"

/* P R O C E S S   S T A T E S */
#define BUSY 0
#define READY 1
#define WAITING 2
#define COMPLETE 3
#define ACTIVE 4

/* L I S T S */
#define JOBS 0
#define READY 1 //Repeated.
#define WAITING 2 //Repeated.
#define IO 3

/* O P E R A T I O N   T Y P E S */
#define CPU_OP 0
#define IO_OP 1
#define OP_FIN 2
