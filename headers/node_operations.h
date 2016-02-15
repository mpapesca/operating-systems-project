// /* I N C L U D E S */
//
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <stdint.h>







/* F U N C T I O N S */

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createjoblist(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createjoblist(int *data) {
//
//   JOBS_LIST = malloc(sizeof(job_t));
//
//   job_t * head = JOBS_LIST;
//
//   head->id = data[0];
//   head->process_state = WAITING;
//   head->prog_count = 0;
//   head->total_mem = data[1];
//   head->min_mem = data[2];
//
//   head->next = NULL;
//
//   return;
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createjoblist(void)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void createjoblist(int *data, int *ops, int *regs) {

  JOBS_LIST = malloc(sizeof(job_t));
  JOBS_LIST->id = data[0];
  JOBS_LIST->process_state = WAITING;
  JOBS_LIST->prog_count = 0;
  JOBS_LIST->total_mem = data[1];
  JOBS_LIST->min_mem = data[2];

  for(i = 0; i < data[3]; i++) {
    if(JOBS_LIST->registers == NULL) {
      JOBS_LIST->registers = malloc(sizeof(reg_t));
      JOBS_LIST->registers->id = regs[i];
      JOBS_LIST->registers->next = NULL;
    } else {
      reg_current = JOBS_LIST->registers;
      while(reg_current->next != NULL) {
        reg_current = reg_current->next;
      }
      reg_current->next = malloc(sizeof(reg_t));
      reg_current->next->id = regs[i];
      reg_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[4]; i++) {
    if(JOBS_LIST->operations == NULL) {
      JOBS_LIST->operations = malloc(sizeof(operation_t));
      JOBS_LIST->operations->id = i;
      JOBS_LIST->operations->type = ops[2*i];
      JOBS_LIST->operations->duration = ops[2*i + 1];
      JOBS_LIST->operations->next = NULL;
    } else {
      op_current = JOBS_LIST->operations;
      while(op_current->next != NULL) {
        op_current = op_current->next;
      }
      op_current->next = malloc(sizeof(operation_t));
      op_current->next->id = i;
      op_current->next->type = ops[2*i];
      op_current->next->duration = ops[2*i + 1];
      op_current->next->next = NULL;
    }
  }

  JOBS_LIST->next = NULL;

}


/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createreadyq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createreadyq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createwaitq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createwaitq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createioq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createioq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  listempty()

  DISC:     This function determines if the linked list is empty or not.

  ARGS:     None.

  RETURN:   Return bool true if the linked list is empty and false if the
            linked list is not empty.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// bool listempty(void) {
//
//   if(head == NULL) {
//     return true;
//   } else {
//     return false;
//   }
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  appendjobtolist(job_t * head, int *data, int list)

  DISC:     This function is meant to append a new node to the list to be
            the new tail of the linked list.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void appendjobtolist(job_t * head, int *data, int list, int *ops, int *regs) {

  current = head;

  if(current == NULL) {

    createjoblist(data, ops, regs);
    return;
  }

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(job_t));
  current->next->id = data[0];
  current->next->process_state = 0;
  current->next->prog_count = 0;
  current->next->total_mem = data[1];
  current->next->min_mem = data[2];
  current->next->num_regs = data[3];
  current->next->num_ops = data[4];

  for(i = 0; i < data[3]; i++) {
    if(current->next->registers == NULL) {
      current->next->registers = malloc(sizeof(reg_t));
      current->next->registers->id = regs[i];
      current->next->registers->next = NULL;
    } else {
      reg_current = current->next->registers;
      while(reg_current->next != NULL) {
        reg_current = reg_current->next;
      }
      reg_current->next = malloc(sizeof(reg_t));
      reg_current->next->id = regs[i];
      reg_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[4]; i++) {
    if(current->next->operations == NULL) {
      current->next->operations = malloc(sizeof(operation_t));
      current->next->operations->id = i;
      current->next->operations->type = ops[2*i];
      current->next->operations->duration = ops[2*i + 1];
      current->next->operations->next = NULL;
    } else {
      op_current = current->next->operations;
      while(op_current->next != NULL) {
        op_current = op_current->next;
      }
      op_current->next = malloc(sizeof(operation_t));
      op_current->next->id = i;
      op_current->next->type = ops[2*i];
      op_current->next->duration = ops[2*i + 1];
      op_current->next->next = NULL;
    }
  }

  current->next->next = NULL;
}
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  appendjobtolist(job_t * head, int *data, int list)
//
//   DISC:     This function is meant to append a new node to the list to be
//             the new tail of the linked list.
//
//   ARGS:     int id - The id value of the new node.
//
//   RETURN:   None.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// void appendoptolist(job_t * head, int count int *data) {
//
//   job_t * current = head;
//
//   if(current == NULL) {
//
//     createjoblist(data);
//     return;
//   } else {
//
//     while(current->next != NULL) {
//       current = current->next;
//     }
//
//     current->next = malloc(sizeof(job_t));
//     current->next->id = data[0];
//     current->next->process_state = 0;
//     current->next->prog_count = 0;
//     current->next->total_mem = data[1];
//     current->next->min_mem = data[2];
//
//     current->next->next = NULL;
//   }
// }


/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  prependtolist(int)

  DISC:     This function is meant to prepend a new node to the list to be
            the new head of the linked list.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void prependtolist(int id) {
//
//   if(listempty()) {
//     createlist(id);
//     return;
//   }
//
//   job_t * new_node = malloc(sizeof(job_t));
//
//   new_node->id = id;
//   new_node->next = head;
//   head = new_node;
//
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  appendtonode(int, int)
//
//   DISC:     This function is meant to insert a node after the node of the
//             specified index.
//
//   ARGS:     int search_id - The id value of the node that a new node will be
//             inserted after.
//
//             int id - The id of the new node.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int appendtonode(int search_id, int id) {
//
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * new_node = malloc(sizeof(job_t));
//   new_node->id = id;
//
//   current = head;
//   while(current->id != search_id) {
//     if(current->next == NULL) {
//       return 0;
//     }
//     current = current->next;
//   }
//
//   if(head->id == id) {
//     new_node->next = head->next;
//     head->next = new_node;
//   }else{
//     new_node->next = current->next;
//     current->next = new_node;
//   }
//
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  appendtoindex(int, int)
//
//   DISC:     This function is meant to insert a node after the node of the
//             specified index.
//
//   ARGS:     int index - The index the new node will be inserted after.
//
//             int id - The id value of the new node.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int appendtoindex(int index, int id) {
//
//     if(index < 0 || (listempty() && index != 0)) { //Invalid index value.
//       return 0;
//     }
//
//     int i;
//     job_t * new_node = malloc(sizeof(job_t));
//     new_node->id = id;
//
//     current = head;
//
//     for( i = 0; i < index; i++) {
//       if(current->next == NULL) {
//         return 0;
//       }
//       current = current->next;
//     }
//     if(index == 0) {
//       new_node->next = head->next;
//       head->next = new_node;
//     } else {
//       new_node->next = current->next;
//       current->next = new_node;
//     }
//
//     return 1;
// }
//
/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  printlist(void)

  DISC:     This function is meant to diplay the contents of the linked list.

  ARGS:     None.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void printlist(job_t * head) {

  if(head == NULL) {
    current = JOBS_LIST;
  } else {
    current = head;
  }

  if(current == NULL) {
    printf("The list is empty\n");
    return;
  }

  while(current != NULL) {
    printf("ID: %d\n",current->id);
    printf("TOTAL MEMORY: %d\n",current->total_mem);
    printf("MINIMUM MEMORY: %d\n",current->min_mem);

    printf("REGISTERS: ");
    if(current->registers != NULL) {
      reg_current = current->registers;
      while(reg_current != NULL){
        printf("%d ",reg_current->id);
        reg_current = reg_current->next;
      }
    } else {
      printf("NONE");
    }
    printf("\n");

    printf("OPERATIONS: ");
    if(current->operations != NULL) {
      op_current = current->operations;
      while(op_current != NULL){
        printf("%d %d ",op_current->type, op_current->duration);
        op_current = op_current->next;
      }
    } else {
      printf("NONE");
    }
    printf("\n");

    current = current->next;
  }
  printf("\n");
}
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removehead(void)
//
//   DISC:     This function is meant to remove the head node of the linked list.
//
//   ARGS:     None.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removehead(void) {
//   if(listempty()) {
//     return 0;
//   }
//   job_t * temp = malloc(sizeof(job_t));
//
//   temp = head;
//   head = temp -> next;
//   free(temp);
//
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removetail(void)
//
//   DISC:     This function is meant to remove the tail node of the linked list.
//
//   ARGS:     None.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removetail(void) {
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * temp = malloc(sizeof(job_t));
//
//   current = head;
//   while(current->next->next != NULL) {
//     current = current->next;
//   }
//   temp = current->next;
//   current->next = temp->next;
//   free(temp);
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removenode(int)
//
//   DISC:     This function is meant to remove the node of the linked list
//             specified by the id passed into the function.
//
//   ARGS:     int id- The id value of the node in the linked list to be removed.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removenode(int id) {
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * temp = malloc(sizeof(job_t));
//
//   current = head;
//   while(current->next != NULL) {
//     if(current->next->id == id) {
//       break;
//     }
//     current = current->next;
//   }
//
//   temp = current->next;
//   current->next = temp->next;
//   free(temp);
//
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removeindex(int)
//
//   DISC:     This function removes the node from the linked list at the
//             specified index.
//
//   ARGS:     int index- The index of the node in the linked list to be removed.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removeindex(int index) {
//
//   if(listempty()) {
//     return 0;
//   }
//
//   int i;
//   job_t * temp = NULL;
//
//   current = head;
//
//   for( i = 0; i < index-1; i++) {
//     if(current->next->next == NULL) {
//       return 0;
//     }
//     current = current->next;
//   }
//   if(index == 0) {
//     temp = head;
//     head = temp->next;
//   } else {
//     temp = current->next;
//     current->next = temp->next;
//   }
//   free(temp);
//
//
//   return 1;
// }
