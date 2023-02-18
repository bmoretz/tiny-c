#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const size_t BSIZE = 256;

int main(int argc, char *argv[]) {

  const char filename[] = "../data/pithy_large.txt";
  FILE *fp;
  char buffer[BSIZE];
  char *r, *entry;
  int items, offset;
  char **list_entries;

  list_entries = (char **)malloc(sizeof(char *) * 100);

  if (list_entries == NULL) {
    fprintf(stderr, "Unable to allocate memory for list entries.");
    exit(1);
  }

  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    exit(1);
  }

  while (!feof(fp)) {

    if (items % 100 == 0) {
      list_entries =
          (char **)realloc(list_entries, sizeof(char *) * (items + 100));
    }

    if (list_entries == NULL) {
        fprintf(stderr, "Unable to allocate memory for additional entries.");
        exit(1);
    }

    r = fgets(buffer, BSIZE, fp);

    size_t buff_len = strlen(buffer) + 1;

    entry = (char *)malloc(sizeof(char) * buff_len);

    if (entry == NULL) {
      fprintf(stderr, "Unable to allocate memory for entry.");
      exit(1);
    }

    strcpy(entry, buffer);

    *(list_entries + items) = entry;

    items++;

    if (r == NULL) {
      break;
    }
  }

  fclose(fp);

  srand( (unsigned) time(NULL));
  offset = rand() % (items-1);

  printf("%s", *(list_entries+offset));

  return (0);
}