#include <stdio.h>
#include <time.h>

int moon_phase(int year, int month, int day);

const char * phases[8] = {
    "waxing crescent", "at first quarter",
    "waxing gibbous", "full", "waning gibbous",
    "at last quarter", "waning crescent", "new"
};

int main(int argc, char *argv[]) {
  time_t now;

  time(&now);
  tm *clock = localtime(&now);

  int mp = moon_phase(clock->tm_year, clock->tm_mon, clock->tm_mday);

  printf("The moon is %s\n", phases[mp]);

  return(0);
}

int moon_phase(int year, int month, int day) {
  int d, g, e;

  d = day;

  if (month == 2) {
    d += 31;
  } else if (month > 2) {
    d += 59 + (month - 3) * 30.6 + 0.5;
  }

  g = (year - 1900) % 19;
  e = (11 * g + 29) % 30;

  if (e == 25 || e == 24) {
    ++e;
  }

  int f = (e + d) * 6.5;

  return (f % 177) / 22 & 7;
}