#ifndef _MUSIC_H
#define _MUSIC_H

#define MUSIC_R 1.0594630943592952645618252949463

#define MUSIC_la 440
#define MUSIC__la MUSIC_la*MUSIC_R
#define MUSIC_si MUSIC__la*MUSIC_R
#define MUSIC_do1 MUSIC_si*MUSIC_R
#define MUSIC__sol MUSIC_la/MUSIC_R
#define MUSIC_sol MUSIC__sol/MUSIC_R
#define MUSIC__fa MUSIC_sol/MUSIC_R
#define MUSIC_fa MUSIC__fa/MUSIC_R
#define MUSIC_mi MUSIC_fa/MUSIC_R
#define MUSIC__re MUSIC_mi/MUSIC_R
#define MUSIC_re MUSIC__re/MUSIC_R
#define MUSIC__do MUSIC_re/MUSIC_R
#define MUSIC_do MUSIC__do/MUSIC_R

#define MUSIC_beat 200

#endif // _MUSIC_H
