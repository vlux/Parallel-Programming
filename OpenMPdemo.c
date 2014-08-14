#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
int main()
{
    int i,n=100;
    omp_set_num_threads(6);
#   pragma omp parallel default(none) shared(n) private(i)
    {
#       pragma   omp for
        for(i=0;i<n;++i)
            printf("Thread %d executes loop iteration %d\n",omp_get_thread_num(),i);
    }
    return 0;
}
