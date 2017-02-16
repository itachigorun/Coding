/* uid query example */
/* itachigorun 2017-02-16 */

/********************************************************
getresuid() and seteuid() are GNU extension function, add
#define _GNU_SOURCE
before including all the headers, or add -D_GNU_SOURCE in GCC options.
*********************************************************/


#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    uid_t uid, euid, suid;
    getresuid(&uid, &euid, &suid);
    printf("uid = %d, euid = %d, suid = %d\n",uid, euid, suid);

    return 0;
}
