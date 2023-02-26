#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const size_t BSIZE = 256;
const size_t BUFF_INC = 100;

struct list_entries {
    size_t length;
    char ** entries;
};

void read_entries( const char filename[], struct list_entries * list_entries);
void print_random_entry( const struct list_entries * list_entries);
void free_list_entries( struct list_entries * list_entries);

int main(int argc, char *argv[]) {

  const char filename[] = "../data/pithy_large.txt";

  struct list_entries le;

  read_entries( filename, &le );
  print_random_entry(&le);
  free_list_entries(&le);

  return (0);
}

void read_entries(const char filename[], struct list_entries * le) {
    FILE * fp;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        exit(1);
    }

    char buffer[BSIZE];
    char *result, *entry;
    char **entries;

    entries = (char **) malloc( sizeof( char * ) * BUFF_INC);

    if (entries == NULL) {
        fprintf(stderr, "Unable to allocate initial entries memory: %ld", BUFF_INC);
        exit(1);
    }

    int length = 0;

    while( !feof(fp)) {

        if ( length > 0 && (length % BUFF_INC) == 0) {
            entries =
                    (char **) realloc(entries,
                                       sizeof(char *) * (length + BUFF_INC));
        }

        if (entries == NULL) {
            fprintf(stderr, "Unable to allocate memory for [%ld] additional entries:", BUFF_INC);
            exit(1);
        }

        result = fgets(buffer, BSIZE, fp);

        if (result == NULL) {
            break;
        }

        size_t buff_size = strlen(result);
        entry = (char *) malloc(strlen(result));

        if (entry == NULL) {
            fprintf(stderr, "Unable to allocate memory for buffer: [%ld] bytes", buff_size);
            exit(1);
        }

        strcpy(entry, buffer);

        entries[length] = entry;

        length++;
    }

    fclose(fp);

    le->length = length;
    le->entries = entries;
}

void print_random_entry(const struct list_entries * le) {
    srand( (unsigned) time(NULL));

    int offset = rand() % (le->length - 1);
    printf("%s", *(le->entries + offset));
}

void free_list_entries( struct list_entries * le) {
    for(int idx = 0; idx < le->length; ++idx ) {
        free(le->entries[idx] );
    }

    free(le->entries);
}
