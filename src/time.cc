#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t now;

    time(&now);

    printf("The computer think it's %ld\n", now);
    printf("%s", ctime(&now));
}