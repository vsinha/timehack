# timehack

Towards the beginning of 2015 my mac developed this glitch: it would spontanously lose the current OS-level clock setting and decide the time was December 11th 2013, something around 11:30pm.

This was a big hassle! SSL Certs would suddenly fail to validate, f.lux would click on in the middle of the day, and so on. I tried all the Apple recommended debugging steps: systematically disable all the various background apps, tools, and services which are usually running. Reset [SMC](https://support.apple.com/en-us/HT201295), [PRAM](https://gigaom.com/2011/07/26/when-to-reset-your-macs-pram-and-smc/), and [NVRAM](https://support.apple.com/en-us/HT204063). No effect.

I discovered forcing an NTP update (by even opening the OSX clock settings page) would fix the problem, the clock would regain an understanding of the current time until the next time it decied to forget.

This happened at least once a day.

So I automated it: in here lies a python prototype and then a C version of a periodic loop of:
- check the system time
- make sure it's not _before_ the time we had the last loop around
- if it is, call `ntpupdate`
- sleep

I ran this little baby on my mac (added to my on-boot crontab) for several months before wiping and reinstalling the OS, which fixed the problem.
