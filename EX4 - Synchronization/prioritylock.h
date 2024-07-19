struct prioritylock
{
    unsigned int locked;       // Is the lock held?
    struct spinlock lk; // spinlock protecting this sleep lock
    // For debugging:
    char *name;        // Name of lock.

    struct pqueue *priority_queue;
    int pid;
};

struct pqueue
{
    struct proc* proc;
    struct pqueue* next;
};
