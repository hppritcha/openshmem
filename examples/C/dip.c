#include <stdio.h>

#include <shmem.h>

int
main(void)
{
  double *f;
  int me;

  shmem_init();
  me = shmem_my_pe();

  f = (double *) shmalloc( sizeof(*f) );

  *f = 3.1415927;
  shmem_barrier_all();

  printf("BEFORE %d: f = %f\n", me, *f);

  if (me == 0) {
    shmem_double_p(f, 2.71828182, 1);
  }

  shmem_barrier_all();

  printf("AFTER %d: f = %f\n", me, *f);
}
