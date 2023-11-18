#define _GNU_SOURCE
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>

char name[16];
const char* chain[80][44] = {{"+,-.", "+,-.", "+\0,-", "f+,-", "+lp\0", "+\0,-", "+\0,-", "f+,-", "-+,.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+\0,-", "+f\0,", "+\0-,", "f+,-", "+,-.", "+\0,-", "+\0f,", "+\0f,", "+\0f,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", },{"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", },{"+,-.", "+,-.", "tilm", "clts", "cnsf", "scwr", "cdsr", "wcpl", "lecs", "mecp", "lcts", "mcsp", "msag", "stcd", "gsca", "c1ds", "gcr2", "gcsd", "gacl", "gcds", "g2b3", "vabc", "ds1a", "abd1", "3b1a", "3ae+", "+,-.", "+,-.", "i+,-", "+,-.", "i+,-", "+,-.", "+,-.", "+,-.", "x+,-", "+,-.", "+,-.", "+,-.", "s+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", },{"+,-.", "+,-.", "+,-.", "bgls", "3dg+", "efmb", "sf19", "1flp", "1s7l", "s1p0", "01s+", "102f", "02cp", "0psa", "p05d", "014b", "5bls", "0bg+", "06p+", "s2+,", "bs+,", "0s26", "0b+,", "0+,-", "2Fs+", "02+,", "02+,", "02+,", "0+,-", "1+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "2+,-", "\0+,-", "0\0-+", "1x\0+", "\003b", "1\0x+", "-.\0+", ".\0-0", "\0-0+", "\0-+,", "-.\0+", "-\0+,", "-x\0+", "\0+,-", "\0-1+", "+,-.", "1+,-", "\0+,-", "\0-+,", "-\0+,", "+,-.", "\0+,-", "\0+,-", "\0+,-", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "17rd", "t01p", "256C", "-2a\0", "0\01D", "\06_-", "0-1\0", "1\0.0", ".0\0-", "\0.12", ".612", ".+,-", ".\0+,", ".k+,", ".035", "02+,", "\0+,-", "036+", ".+,-", "0+,-", "29\0+", "2+,-", "2+,-", "3+,-", "+,-.", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "t\0+,", "fp6s", "-p\0g", "rtx\0", "\0dop", "s\0w_", "\0f-.", "\05f-", "\0f3c", "\0-.d", "\0b+,", "\0.8d", "\0.i+", "\0-.+", "\0+,-", "-\01n", "\0.l+", "-\0.5", "5l+,", ".\0+,", ".\0+,", ".l\0+", ".l+,", ".l\0+", ".\0+,", ".\0+,", ".+,-", ".+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "B\0+,", "-b8t", "_\0rt", "-\0d.", "\0.2d", ".\0-2", ".2\0-", "\02.4", "\02d+", "\0.2d", "2+,-", "2\0+,", "2+,-", "289\0", "2-+,", "29+,", "20+,", "2-+,", "+,-.", ".23\0", ".+,-", "-+,.", "-+,.", "2+,-", "2+,-", ".2+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "1c\0+", "m2l\0", "chlp", "-e.h", "\0hs+", "-hs\0", "-\0m2", "-\0.e", "mpv\0", "-\02l", "\0e+,", "_-+,", "+,-.", "\0+,-", "\0e+,", "\0+,-", "\0+,-", "\0e+,", "-_+,", "-_+,", "-+,.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "cdfr", "+\0.c", ".-_\0", "-.\00", "\0.16", "6\0+,", "\016+", "\0.6+", "\02+,", "\0+,-", "\0+,-", "\0+,-", "\0+,-", "\06+,", "\0+,-", ".0\0+", "+,-.", "\03+,", "5+,-", "1+,-", "+,-.", "\0+,-", "\0+,-", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "8+,-", "_t4\0", "-4+,", "4\005", "4\0rs", "4\08+", "-4\0_", "4\0_-", "4-05", "4\0+,", "\0+,-", "79+,", "8+,-", "\04_+", "_4+,", "_4+,", "4\0_+", "4\0+,", "4+,-", "\0+,-", "4+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "\0+,-", "+,-.", "n\0+,", "+,-.", "\07+,", "+,-.", "3\0+,", "\0+,-", "-+,.", "+,-.", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "69+,", "6e+,", "-m+,", ".4\0+", "\0.s+", "-6+,", "6k+,", "5+,-", "+,-.", "+,-.", "\0+,-", "+,-.", "6\0+,", "6k+,", "6x+,", "6\0+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "\09+,", "e+,-", "+,-.", "04+,", "\0+,-", "1+,-", ".0+,", ".+,-", ".+,-", "+,-.", "+,-.", "+,-.", "9+,-", "03+,", "+,-.", "2+,-", "+,-.", "+,-.", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "Dm+,", "+,-.", "+,-.", "vu+,", "+,-.", "+,-.", "p+,-", "+,-.", "+,-.", "p+,-", "p+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "a+,-", "ai+,", "f+,-", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "y+,-", "+,-.", "+,-.", "oC\0+", "ho+,", "+,-.", "o+,-", "o+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "r+,-", "L+,-", "+,-.", "ey+,", "e+,-", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "Qn+,", "Q+,-", "Q+,-", "n+,-", "n+,-", "+,-.", "a+,-", "Q+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "i+,-", "+,-.", "r+,-", "+,-.", "io+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "o+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "r+,-", "+,-.", "i+,-", "aEr+", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "\0+,-", "m+,-", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "x+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "s+,-", "p+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "i+,-", "+,-.", "+,-.", "i+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "aV+,", "+,-.", "ua+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "e+,-", "+,-.", "p+,-", "+,-.", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "P+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "i+,-", "N+,-", "i+,-", "h+,-", "ao+,", "e+,-", "+,-.", "+,-.", "a+,-", "l+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "2+,-", "3\0+,", "+,-.", "+,-.", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "o+,-", "+,-.", "+,-.", "+,-.", "e+,-", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "vo+,", "+,-.", "+,-.", "+,-.", "+,-.", "hp+,", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "h+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "u+,-", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "n+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "I+,-", "+,-.", "+,-.", "I+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "e+,-", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"\0+,-", "enov", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "2+,-", "+,-.", "+,-.", "+,-.", "2+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "a+,-", "+,-.", "+,-.", "+,-.", "i+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "r+,-", "crtd", "6pcj", "rcpl", "dreo", "tcrs", "scrd", "prns", "pu6d", "decs", "psac", "cdbr", "pcia", "labc", "d6sw", "6pcd", "6hls", "d6cp", "vdij", "vn+,", "t+,-", "dh+,", "+,-.", "+,-.", "+,-.", "c+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "rvul", "mucr", "ndtc", "trbl", "tcrl", "trcn", "tndl", "tcpr", "tdrl", "trlc", "btr_", "tlnr", "tclp", "ctnl", "rtde", "nt\0c", "tn\0c", "lnst", "tdlr", "tdn\0", "lndm", "trd+", "mnrk", "tnr+", "nkmp", "ndgt", "ns+,", "+,-.", "t+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "l+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "rtli", "emio", "iut2", "a\0-e", "lu\02", "l\0ua", "m\0ei", "u\0oa", "\0l-m", "o\0lu", "lu\0o", "i\0la", "\0io.", "ujry", "onru", "\0jne", "\0a-e", "lu\0f", "\0j-+", "ja+,", "ujf\0", "ufi\0", "\0fu+", "uir\0", "u+,-", "\0g+,", "\0+,-", "\0+,-", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "aloh", "o\0ra", "-oak", "ovah", "o\0ah", "o\0he", "ok\0a", "o-ek", "okeh", "otlk", "oeah", "ohka", "ke\0a", "otcl", "kr-h", "ocet", "t-ah", "l+ao", "co+h", "-coe", "c-o+", "c-lt", "-oks", "hl\0+", "eo\0+", "+,-.", "o+,-", "o+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "r+,-", "+,-.", "+,-.", "+,-.", }, {"+,-.", "vebi", "fben", "i\0oe", "tei\0", "e\0fi", "\0eia", "-\0ei", "e\0ai", "e\0-i", "e-\0a", "e\0ad", "-e\0a", "e\0-a", "ae\0g", "a\0eu", "eado", "\0erb", "-lea", "\0_-.", "\0edl", "e\0-r", "u_ei", "ueim", "\0u-i", "e\0u+", "\0+,-", "\0e+,", "\0s+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "xnub", "mxts", "dnav", "xnsr", "rncm", "\0xr-", "\0rsn", "\0-sr", "\0rln", "\0ram", "r\0ls", "\0r-s", "\0rns", "\0rs-", "r\0s-", "\0rna", "\0rs-", "r\0s-", "\0rts", "\0rsn", "r\0ds", "r\0-c", "ldrs", "\0aln", "r\0sa", "\0a_p", "n\0+,", "rn+,", "+,-.", "\0+,-", "+,-.", "nt+,", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "aiol", "st-i", "st2f", "is\0o", "o\0if", "o\0il", "i\0ol", "io\0f", "is\0l", "is\0-", "-ito", "ito\0", "ioae", "io\0s", "ies+", "afis", "ilyd", "\0iel", "defi", "e\0ft", "ieo\0", "dei\0", "i\0do", "d\0+,", "\0+,-", "i+,-", "+,-.", "i+,-", "+,-.", "+,-.", "io+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "elsr", "m_rl", "-eri", "eor2", "-e\0r", "\0eri", "\0eir", "\0ehm", "e\0-i", "\0eil", "\0eiu", "\0e-a", "w\0-c", "\0ne-", "wn\0c", "\0i-p", "n-ea", "cn\0+", "ce+l", "nc\0+", "c+-e", "\0+,-", "-is\0", "su\0+", "s+,-", "c\0+,", "e\0+,", "+,-.", "\0+,-", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "p5wt", "aoie", "-ao\0", "io\0e", "aei_", "e\0ta", "\0eai", "\0aei", "\0eot", "\0e-_", "\0eld", "\0ae.", "\0eai", "\046d", "\0oti", "\0eab", "\06e+", "eik\0", "\0a+,", "\0emo", "e\06+", "\0+,-", "o+,-", "e+,-", "o\0+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "6pdn", "nsbr", "-nsl", "ntbc", "nlcs", "nlts", "nctl", "nlps", "nlgs", "ngol", "nslg", "ngcp", "n-gl", "gnop", "gnt\0", "tgln", "pndo", "npco", "lcno", "lp\0d", "npbc", "npbc", "lnbo", "lnbc", "nlpt", "bln+", "lbdg", "abo+", "bgn+", "+,-.", "n+,-", "g+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "p+,-", "+,-.", }, {"+,-.", "sapb", "vspa", "_\0ad", "aiu\0", "a426", "ipbv", "aios", "acde", "a\0+,", "aos+", "sa\0+", "ro+,", "a+,-", "la+,", "cdeo", "u+,-", "cd+,", "+,-.", "+,-.", "cd+,", "cds+", "cd+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "pdea", "ftbd", "e-\04", "e\0.t", "\0e-d", "\0eg-", "\0-eu", "\0_et", "\0eus", "\0e_-", "\0u-e", "e-\0g", "\0e_c", "\0egs", "\0g-s", "\0-_a", "e\0+,", "ga\0+", "e\0+,", ".dg+", "+,-.", "gr+,", "\0+,-", "-er\0", "+,-.", "e\0+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "lido", "va-i", "tiao", "aio\0", "iea\0", "se\0i", "\0eia", "\0iae", "i\0le", "ef\0i", "ei\0o", "e\0i.", "\0ead", "ei\0d", "\0aei", "e\0ia", "e\0il", "\0eid", "\0ela", "eidt", "deil", "ieos", "i\0ae", "diae", "id\0e", "di\0+", "di\0+", "di+,", "+,-.", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "l\0+,", "-+,.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "boka", "lbaw", "tup-", "-ae\0", "ap\0o", "pd\0i", "\0pae", "\0alp", "a\0po", "ip\0e", "-p\0a", "ipe\0", "iope", "alei", "o\0bp", "oe\0a", "o\0al", "\0el_", "ep\0o", "pe\0+", "ap+,", "op\0a", ".op\0", "epac", "pe\0+", "pe+,", "p+,-", "+,-.", "p+,-", "+,-.", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "l+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "leaf", "mdsi", "esod", "tgdc", "of\0t", "ft\0d", "eft\0", "dft\0", "f\0td", "ft\0s", "uf\0g", "gft-", "sftu", "gef\0", "u\0gd", "uste", "dt\0a", "u\0te", "adeg", "adef", "asel", "-adf", "gems", "\0dla", "cefl", "dekl", "efl\0", "p+,-", "t\0+,", "fm+,", "+,-.", "st+,", "t+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "prsc", "nuro", "mntc", "ncp-", "pnro", "np\0o", "n\0lp", "nr\0l", "nlro", "nlro", "nrlm", "nglr", "nrlm", "ndro", "nrl-", "tplr", "lnrt", "nrbl", "rnab", "v-bn", "nvlr", "rv-f", "n\0.f", "nopd", "lor+", "lrno", "l+,-", "m+,-", "n+,-", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "apnb", "m-ei", "se-\0", "d\0al", "\0alr", "\0pla", "\0aml", "\0lra", "\0-al", "\0rli", "\0dpl", "\0ale", "\0la-", "p\0el", "l\0sa", "\0dei", "ta\0k", "et\0y", "plr\0", "\0lre", "\0-kp", "\0r+,", "\0lpt", "\0ory", "\0y+,", "\0+,-", "\0+,-", "+,-.", "r+,-", "l+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "t+,-", }, {"+,-.", "emud", "lfnu", "-lnu", "udta", "utd-", "u\0t+", "t-\0u", "tu\0+", "tul+", "t\0+,", "t_+,", "ut+,", "tu+,", "t+,-", "t\0+,", "t+,-", "m+,-", "t+,-", "+,-.", "+,-.", "+,-.", "t+,-", "t+,-", "+,-.", "t+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "ieau", "iaem", "e-ac", "eao\0", "eai\0", "eia\0", "ae\0i", "\0iea", "\0eot", "\0eao", "\0eta", "\0eat", "\0eai", "\0e-i", "\0eia", "\0iea", "\0itv", "\0ei-", "\0aec", "\0eai", "\0io-", "\0aei", "aes-", "\0aet", "a\0be", "\0itv", "+,-.", "o\0+,", "s+,-", "i+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "i+,-", "+,-.", "+,-.", }, {"+,-.", "eymn", "tcld", "tce_", "te-h", "t\0e-", "ty\0e", "_\0te", "t\0-e", "\0te-", "\0eta", "\0teo", "t\0he", "\0tei", "\0hes", "\0teh", "th\0i", "\0tah", "\0te.", "\0-te", "\0tsh", "\0seh", "h\0-c", "\0lty", "\0-e+", "\0hs+", "\0+,-", "+,-.", "y\0+,", "\0+,-", "+,-.", "+,-.", "+,-.", "t+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "c+,-", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "resi", "prka", "e-oa", "oea\0", "2e\0l", "\0eri", "\0eor", "\0eoa", "e\0o-", "\0eai", "\0e-i", "\0eoa", "\0eo-", "\0eo-", "i\0er", "\0oae", "e\0ao", "\0eoi", "o\05e", "e\0or", "oirc", "\0reu", "ocl\0", "\0o5e", "o\0e+", "e5+,", "-i+,", "+,-.", "\0+,-", "e+,-", "+,-.", "+,-.", "-e\0+", "a+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "\0+,-", }, {"+,-.", "npbs", "altn", "snt_", "-snt", "mnra", "mtnp", "nimt", "mnps", "nmtg", "pmna", "nmtx", "xpim", "nleg", "xems", "npgr", "-lip", "-lms", "mnai", "-ima", "gmns", "dm+,", "imgp", "imp+", "mi+,", "imt+", "im+,", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "pmgi", "iram", "m_iu", "iet\0", "6e-i", "e\0i_", "e\0ig", "e\0gi", "ei\0p", "e\0ia", "ei\0a", "eia0", "eais", "e\03a", "e\0+,", "e-i+", "e36a", "-ei+", "e+,-", "ea\0+", "-3e\0", "-312", "-egi", "e+,-", "+,-.", "i+,-", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"\0+,-", "iaop", "-alf", "a2ei", "a2ei", "iar\0", "6\0ia", "i\03a", "6\0ae", "a\0ei", "\0ead", "a\0_e", "adi+", "e-ad", "3eri", "ae+,", "3p\0+", "ior+", "i+,-", "ik+,", "i+,-", "or+,", "a+,-", "r+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "8fdm", "ctrp", "eld2", "\0e_c", "\0p_e", "\0tm-", "\0t-b", "\0-te", "\0t-6", "\0tm1", "t\0-_", "-\06e", "-\0ta", "8tdm", "-8e2", "m8ey", "8aem", "t\0+,", "\0+,-", "t+,-", "\0+,-", "y+,-", "y+,-", "+,-.", "+,-.", "\0+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "m+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", }, {"+,-.", "u4ae", "stnp", "2t\0n", "\0-np", "\0pt.", "-\0pu", "s\0pn", "\0-md", "\0s-_", "\0-sf", "\0p-_", "\0lps", "\0_sc", "\0-rR", "\0-tp", "\0-p+", "\0p_l", "\01_t", "ps\0+", "\0+,-", "+,-.", "p\0+,", "\0+,-", "n\0+,", "\0+,-", "+,-.", "+,-.", "+,-.", "-+,.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", },{"pslm", "is\0b", "cmdi", "\0ice", "i\04b", "e-_\0", "ei\0c", "eaim", "e\0d+", "eo+,", "oe+,", "eo\0+", "oef+", "eaio", "eos+", "ei+,", "e+,-", "e+,-", "e+,-", "+,-.", "e+,-", "e+,-", "e+,-", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "+,-.", "\0+,-", }, };

unsigned int rand(unsigned int max) {
    unsigned int buf[1];
    read(3, &buf, sizeof(unsigned int));
    return buf[0] % max;
}

// Generate a new random name with markov chain
void new_name() {
    char c = '\0';
    int n = 0;

    while (n < 15) {
        if (c == '\0')
            c = 79 + 43;
        
        const char *key = chain[c-43][n];
        char next = key[rand(4)];

        if (next == '\0')
            break;

        name[n] = next;
        c = next;
        n += 1;
    }

    name[n] = '\0';
}

int ends_with(char * a, char *b) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);

    if (blen > alen)
        return 0;

    return strncmp(a + alen - blen, b, blen) == 0;
}

int main(int argc, char **argv) {
    if (ends_with(argv[0], "invincible")) {

        // Setup memfd to hold our binary
        int rand = open("/dev/urandom", O_RDONLY);  // fd will always be 3
        new_name();

        int mem = memfd_create(name, 0); // fd will always be 4

        // Find path to our binary
        pid_t pid = getpid();
        char path[128];
        sprintf(path, "/proc/%d/exe", pid);

        // Open and copy to memfd
        int exe = open(path, O_RDONLY);

        char buf[1024];
        for (;;) {
            size_t n = read(exe, buf, 1024);
            if (n == 0)
                break;

            char * loc = buf;
            while (n > 0) {
                size_t w = write(mem, loc, n);
                loc += w;
                n -= w;
            }
        }
    } else {
        // Set our name in the other ways that the system can see it
        prctl(PR_SET_NAME, (unsigned long) argv[0], 0, 0, 0);
        pthread_setname_np(pthread_self(), argv[0]);

        new_name();

        // Do something nefarious (optional)
        usleep(1000 * 300);
    }
    
    // Fork and let the parent die so we are an orphan
    if (fork() != 0)
        return 0;

    // detach from tty and pgroup
    setsid();

    // Execve into memfd
    //
    // File descriptors are preserved, so we can do this forever :)
    const char * const av[] = {name, NULL};
    const char * const ep[] = {NULL};
    int i = fexecve(4, (char * const *) av, (char * const *) ep);
    
    printf("fexec returned %d, errno=%d\n", i, errno);
}
