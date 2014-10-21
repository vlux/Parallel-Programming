# pragma omp parallel num_threads(threads_count) 
        default(none) shared(a,n) private(i,tmp,phase)
    for(phase = 0; phase < n; phase++)
    {
        if(phase % 2 ==0)
#           pragma omp for
            for(i = 1; i < n; i+= 2)
                if(a[i-1] > a[i])
                {
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = tmp;
                }
        else
#           pragma omp for
            for(i = 1; i < n;i+= 2)
                if(a[i] > a[i+1])
                {
                    tmp = a[i+1];
                    a[i+1] = a[i];
                    a[i] = tmp;
                }
    }
