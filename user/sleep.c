#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{

  if(argc != 2){
    fprintf(2, "Usage: sleep seconds\n");
    exit(1);
  }

  int seconds = atoi(argv[1]);

  if (seconds<1){
    fprintf(2, "Errors: sleep times must be positive");
  }

  sleep(seconds);

  exit(0);
}
