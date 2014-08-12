P162

for(sent_msgs = 0; sent_msgs < send_max; sent_msgs++)
{
    //Send_msg()
    mesg = random();
    dest = random() % thread_count;
#   pragma omp critical
    Enqueue(queue, dest, my_rank, mesg);

    //Try_receive()
    queue_size = enqueued - dequeued;
    if(queue_size == 0)
        return;
    else if(queue_size == 1)
#       pragma omp critical
        Dequeue(queue, &src, &mesg);
    else
        Dequeue(queue, &src, &mesg);
    Print_message(src, mesg);
}

while(!Done())
    Try_receive();

//Done()
queue_size = enqueued - dequeued;
if(queue_size == 0 && done_sending == thread_count)
    return true;
else
    return false;
