#!/usr/local/bin/python

import subprocess
from time import sleep, time

LAST_SECOND_OF_2013 = 1388491199

def timehack():
    # check the time forever
    while True:
        if time() < LAST_SECOND_OF_2013:
            # call ntp update command and block until we're done
            subprocess.call(["/usr/sbin/ntpdate",  "-vu", "time.apple.com"])

        sleep(2)


if __name__ == '__main__':
    # TODO check that we're running as root
    print ("time hacks initialized")
    timehack()
