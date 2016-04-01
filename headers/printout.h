void printout(FILE *file, char *string) {

  if(DEBUG_MODE) {
    printf("%s",string);
  } else {
    fprintf(file, "%s", string);
  }

}
