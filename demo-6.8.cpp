typedef struct{
    my_stack_t new_stack;
    int threads_in_cond_wait;
    pthread_cond_t term_cond_var;
    pthread_mutex_t term_mutex;
}term_struct;
typedef term_struct *term_t;
term_t term;

Terminated()
{
    if(my_stack_size >= 2 && threads_in_cond_wait > 0 && new_stack == NULL)
    {
        lock term_mutex;
        if(threads_in_cond_wait > 0 && new_stack == NULL)
        {
            split my_stack creating new_stack;
            pthread_cond_signal(&term_cond_var);
        }
        unlock term_mutex;
        return 0;
    }
    else if(!empty(my_stack))
        return 0;
    else        //My stack is empty
    {
        lock term_mutex;
        if(threads_in_cond_wait == thread_count-1)        //Last thread running
        {
            threads_in_cond_wait++;
            pthread_cond_broadcast(&term_cond_var);
            unlock mutex;
            return 1;
        }
        else        //Other threads still working,wait for work
        {
            threads_in_cond_wait++;
            while(pthread_cond_wait(&term_cond_var, &term_mutex) != 0)
                ;
            //We've been awakened
            if(threads_in_cond_wait < thread_count)
            {
                my_stack = new_stack;
                new_stack = NULL;
                threads_in_cond_wait--;
                unlock mutex;
                return 0;
            }
            else
            {
                unlock mutex;
                return 1;
            }
        }
    }
}
