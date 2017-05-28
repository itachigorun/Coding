int msgget(key_t key, int msgflg);
int msgsend(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);
int msgrcv(int msgid, void *msg_ptr, size_t msg_st, long int msgtype, int msgflg);
int msgctl(int msgid, int command, struct msgid_ds *buf);

