void opcpu(void) {
  // printf("opcpu()\n");

  if(READY_Q == NULL) {
    return;
  } else if(READY_Q->process_state == ACTIVE) {
    CURRENT_CPU_COUNT++;
    op_current = READY_Q->operations;
    // printf("check\n");
    while(op_current != NULL) {
      // printf("check\n");
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }
    if(op_current != NULL && CURRENT_CPU_COUNT >= op_current->duration) {
      // op_current->status = 1;
      // READY_Q->process_state = WAITING;
      current = JOBS_LIST;
      while(current->id != READY_Q->id) {
        if(current == NULL) {
          printf("no id found for io\n");
        }
        current = current->next;
      }
      // printf("check\n");
      current->prog_count += CURRENT_CPU_COUNT;
      op_current = current->operations;
      while(op_current != NULL) {
        // printf("check\n");
        if(op_current->status == 0) {
          break;
        }
        op_current = op_current->next;
      }
      // printf("check\n");
      // printf("check\n");
      op_current->status = 1;
      current->process_state = WAITING;
      removehead(READY);
      // printf("--------------------------------------------------------------------\n");
      // printf("JOB LIST\n");
      // printlist(JOBS_LIST);
      //
      // printf("READY QUEUE\n");
      // printlist(READY_Q);
      //
      // printf("IO QUEUE\n");
      // printlist(IO_Q);
      // printf("--------------------------------------------------------------------\n");
    }
    // if(op_current == NULL) {
      // printf("null operation\n");
    // }
  }
}

void opio(void) {
  // printf("opio()\n");

  if(IO_Q == NULL){
    return;
  } else if(IO_Q->process_state == ACTIVE) {
    // printf("here\n");
    CURRENT_IO_COUNT++;
    op_current = IO_Q->operations;
    while(op_current != NULL) {
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }

    if(op_current != NULL && CURRENT_IO_COUNT >= op_current->duration) {
      // op_current->status = 1;
      // IO_Q->process_state = WAITING;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        if(current == NULL) {
          printf("no id found for io\n");
        }
        current = current->next;

      }
      current->prog_count += CURRENT_IO_COUNT;
      op_current = current->operations;
      while(op_current != NULL) {
        // printf("check\n");
        if(op_current->status == 0) {
          break;
        }
        op_current = op_current->next;
      }
      // printf("check\n");
      op_current->status = 1;
      current->process_state = WAITING;
      removehead(IO);
      // printf("--------------------------------------------------------------------\n");
      // printf("JOB LIST\n");
      // printlist(JOBS_LIST);
      //
      // printf("READY QUEUE\n");
      // printlist(READY_Q);
      //
      // printf("IO QUEUE\n");
      // printlist(IO_Q);
      // printf("--------------------------------------------------------------------\n");
    }
  } else if (IO_Q->process_state == READY) {
    op_current = IO_Q->operations;
    // elapsed = op_current->duration;

    while(op_current != NULL) {
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }

    if(op_current == NULL) {
      IO_Q->process_state = COMPLETE;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        current = current->next;
      }
      current->process_state = COMPLETE;
      removehead(IO);


    }

    if(op_current->status == 0) {
      printf("NEW IO OPERTATION\n");
      // cpu_op_finish_time = current_time + op_current->duration;
      // previous_time = op_current->duration;
      IO_Q->process_state = ACTIVE;
      CURRENT_IO_COUNT = 0;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        current = current->next;
      }
      current->process_state = BUSY;

    }
    printf("--------------------------------------------------------------------\n");
    printf("JOB LIST\n");
    printlist(JOBS_LIST);

    printf("READY QUEUE\n");
    printlist(READY_Q);

    printf("IO QUEUE\n");
    printlist(IO_Q);
    printf("--------------------------------------------------------------------\n");
  }


}
