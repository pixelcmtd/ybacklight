#define DEBUG 0
#include "config.h"
#include "ybacklight.c"
#define isnum(c) ((c) >= '0' && (c) <= '9')
#if DEBUG
#define debug(f, a) fprintf(stderr, f, a)
#else
#define debug(f, a)
#endif

int S = 0, w = 0, f = 0;
long long A, C, M;
void run(char cmd)
{
        debug("Cmd: %c; ", cmd);
        debug("Short: %d\n", *S);
        switch(cmd)
        {
                case 'c': printf("%lld", S ? C / SHORT_FACTOR : C); w = 1; break;
                case 'm': printf("%lld", S ? M / SHORT_FACTOR : M); w = 1; break;
                case 'S': S = 1; return;
                case 'i': C += S ? A * SHORT_FACTOR : A; f = 1; break;
                case 'd': C -= S ? A * SHORT_FACTOR : A; f = 1; break;
                case 's': C  = S ? A * SHORT_FACTOR : A; f = 1; break;
                default:  putchar(cmd); w = 1; break;
        }
        S = 0;
}

int main(int argc, char **argv)
{
        C = read_brightness(BRIGHTNESS);
        M = read_brightness(MAX_BRIGHTNESS);
        char numbuf[NUM_MAX], queued = '\0';
        memset(numbuf, 0, NUM_MAX);
        for(int i = 1; i < argc; i++)
        {
                char c, *cp = argv[i];
                while((c = *cp++))
                        if(isnum(c)) numbuf[strlen(numbuf)] = c;
                        else
                        {
                                if(*numbuf) A = strtoll(numbuf, 0, 10),
                                            memset(numbuf, 0, NUM_MAX);
                                if(queued) run(queued),
                                           queued = '\0';
                                if((c == 's' || c == 'd' || c == 'i')
                                                && isnum(*(cp + 1))) queued = c;
                                else run(c);
                        }
        }
        if(strlen(numbuf) && queued) A = strtoll(numbuf, 0, 10), run(queued);
        if(w) putchar('\n');
        if(f) write_brightness(BRIGHTNESS, C);
        return 0;
}
