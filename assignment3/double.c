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
#include <string.h>
#include <zlib.h>
#include <pthread.h>

/* Maximum number of bytes to read from file */
#define BUF_SIZE 2048

/* Threads will r/w from opposite buffers */
char in_buf_a[BUF_SIZE], in_buf_b[BUF_SIZE];
int in_len_a, in_len_b;
pthread_mutex_t in_mutex_a, in_mutex_b;

/* This will be set when the input file is EOF */
int eof;

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

void *translate_thread(void *args) {
  gzFile output = (gzFile)args;

  /* While the input thread is running, and there is data in the
   * buffers to translate... */
  while ((eof == 0) || (in_len_a > 0) || (in_len_b > 0)) {
    /* Wait until there is data in this buffer */
    if (in_len_a > 0) {
      pthread_mutex_lock(&in_mutex_a);

      /* We have the mutex, so translate the buffer safely */
      translate(in_buf_a, in_len_a);

      /* Write the translated data to the compressed output file */
      gzwrite(output, in_buf_a, in_len_a);

      /* This will tell the input thread this buffer is now empty */
      in_len_a = 0;
      pthread_mutex_unlock(&in_mutex_a);
    }
    
    /* Wait for the buffer to have data */
    if (in_len_b > 0) {
      pthread_mutex_lock(&in_mutex_b);

      /* Translate safely, as we have the mutex */
      translate(in_buf_b, in_len_b);

      /* Write the translated data to the compressed output file */
      gzwrite(output, in_buf_b, in_len_b);

      /* This will tell the input thread this buffer is now empty */
      in_len_b = 0;
      pthread_mutex_unlock(&in_mutex_b);
    }
  }

  /* No more data to translate, so we're done */
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  gzFile input, output;
  pthread_t trans, write;
  pthread_attr_t attr;
  int ret, len;
  char *ibuf; /* Will point to an input buffer */

  /* Test input arguments */
  if (argc != 3) {
    fprintf(stderr, "Invalid input arguments\n");
    usage(argv[0]);
    return -1;
  }

  /* Reset buffers */
  in_len_a = 0; in_len_b = 0;

  /* Clear EOF flag */
  eof = 0;

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

  /* Create the mutexes */
  pthread_mutex_init(&in_mutex_a, NULL);
  pthread_mutex_init(&in_mutex_b, NULL);

  /* Configure attributes for the threads */
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 2 * 1000 * 1000); /* 2MB */
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* Create and start the translation and output thread */
  ret = pthread_create(&trans, NULL, translate_thread, NULL);
  if (ret != 0) {
    fprintf(stderr, "Failed to create translate thread: %d\n", ret);
    return -1;
  }

  /* Read data in chunks to alternating input buffers.
   * The data will get used by the translate thread */
  while (!gzeof(input)) {
    pthread_mutex_lock(&in_mutex_a);
    if (in_len_a == 0) {
      len = gzread(input, in_buf_a, BUF_SIZE);
      in_len_a = len;
    }
    pthread_mutex_unlock(&in_mutex_a);
    
    pthread_mutex_lock(&in_mutex_b);
    if (in_len_b == 0) {
      len = gzread(input, in_buf_b, BUF_SIZE);
      in_len_b = len;
    }
    pthread_mutex_unlock(&in_mutex_b);
  }

  /* Notify other threads that EOF has occured */
  eof = 1;

  /* Block until all threads are done */
  pthread_join(trans, NULL);

  /* Clear the mutexes */
  pthread_mutex_destroy(&in_mutex_a);
  pthread_mutex_destroy(&in_mutex_b);

  /* Clear the attribute memory */
  pthread_attr_destroy(&attr);

  /* Close the files */
  gzclose(input);
  gzclose(output);

  return 0;
}
