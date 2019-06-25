#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if(argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }
  else if(argc >= 2) {
    char *searchterm = argv[1]; 

   

    FILE *stream;
    size_t currentArgv = 0;

    for(; currentArgv < argc; currentArgv++) {
      char **output = calloc(0, sizeof(char *));
      size_t size = 0;

      char *text = calloc(1, 1);
      char buffer[10];

      if(argc == 2) {
        stream = stdin;
      }
      else {
        currentArgv = 2;
        stream = fopen(argv[currentArgv], "r");
        if(stream == NULL) {
          printf("wgrep: cannot open file\n");
          return 1;
        }
      }

      while(fgets(buffer, sizeof(buffer), stream)) {
        text = realloc(text, strlen(text)+strlen(buffer)+1);

        strcat(text, buffer);

        if(buffer[strlen(buffer)-1] == '\n') {
          if(strstr(text, searchterm) != NULL) {
            output = realloc(output, (size+1)*sizeof(char *));
            output[size] = malloc(strlen(text)+1);
            strcpy(output[size], text);
            size++;
          }
          text[0] = '\0';
        }
      }

      for(size_t i = 0; i < size; i++) {
        printf("%s", output[i]);
        free(output[i]);
      }

      if(argc == 2) {
        return 0;
      }
      else {
        fclose(stream);
      }

      free(output);
      free(text);
    }
  }

  return 0;
}
