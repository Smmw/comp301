/*
 * This program will translate existing written works into a language
 * understandable by future generations. Input and output data are
 * compressed using gzip. The program itself makes use of threading
 * to leverage multiple CPUs commonly available.
 *
 * Dan Collins 2014
 * COMP301 - 14B
 * 1183446
 */

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

/* Maximum number of bytes to read from file */
#define BUF_SIZE 2048

/* Print program usage instructions */
void usage(char *name) {
  printf("Translator Usage\n");
  printf("%s input.gz output.gz\n", name);
}

/* Translate len characters in buf
 * a,A -> 4
 * e,E -> 3
 * i,I -> 1
 * o,O -> 0
 * s,S -> 5
 */
/* O(n) */
void translate(char *buf, int len) {
  int i;

  /* In place translation */
  for (i = 0; i < len; i++) {
    if (buf[i] == 'a' || buf[i] == 'A')
      buf[i] = '4';

    if (buf[i] == 'e' || buf[i] == 'E')
      buf[i] = '3';

    if (buf[i] == 'i' || buf[i] == 'I')
      buf[i] = '1';

    if (buf[i] == 'o' || buf[i] == 'O')
      buf[i] = '0';

    if (buf[i] == 's' || buf[i] == 'S')
      buf[i] = '5';
  }
}

int main(int argc, char **argv) {
  gzFile input, output;
  int len;
  char in_buf[BUF_SIZE];

  /* Test input arguments */
  if (argc != 3) {
    fprintf(stderr, "Invalid input arguments\n");
    usage(argv[0]);
    return -1;
  }

  /* Open input file */
  input = gzopen(argv[1], "rb");
  if (input == NULL) {
    fprintf(stderr, "Unable to open %s.\n", argv[1]);
    return -1;
  }

  /* Open output file */
  output = gzopen(argv[2], "wb");
  if (output == NULL) {
    fprintf(stderr, "Unable to open %s.\n", argv[2]);
    return -1;
  }

  /* Read all the bytes from the input file in chunks */
  while ((len = gzread(input, in_buf, BUF_SIZE)) > 0) {
    /* Translate the chunk */
    translate(in_buf, len);
    /* Write the translated data to the compressed output file */
    gzwrite(output, in_buf, len);
  }

  /* Close the files */
  gzclose(input);
  gzclose(output);

  return 0;
}
