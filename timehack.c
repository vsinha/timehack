#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LAST_SECOND_OF_2013 1388491199

int main () {
    time_t rawtime;
    FILE *fp;

    if(geteuid() != 0) {
        // Tell user to run app as root, then exit.
        printf("Run this as root kthxbye\n");
        return 1;
    }

    // check the time forever
    while ( 1 ) {
        time ( &rawtime );

        if ( (int)rawtime < LAST_SECOND_OF_2013 ) {
            // print for logs
            printf("System clock thinks the year is before 2014 (%d)\n", 
                    (int)rawtime );

            // TODO check that we're connected to wifi

            // execute the mighty ntp update command
            fp = popen("/usr/sbin/ntpdate -vu time.apple.com", "r");

            // get the time again for more logs
            printf("time is now: %d\n", (int)time(&rawtime));
        }

        // sleep for a reasonable amount of time before checking again
        // we want to minimize processor overhead for this script should
        // run forever and always...
        sleep( 2 );
    }

    return 0;
}
