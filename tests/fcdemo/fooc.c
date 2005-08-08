#include "foo.h"
#include <stdio.h>

int csub(int arg)
{
  return (2*arg);
}


int fwrapper(int arg)
{
  int res;
  printf("Calling the Fortran subroutine from the C wrapper...\n");
  FC_FUNC(fsub,FSUB)(&arg,&res);
  printf("Returned from the Fortran subroutine...\n");
  return res;
}
