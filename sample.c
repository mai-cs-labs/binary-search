#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
	MAX_BUFFER_SIZE = 1024,
};

static const char DELIMITERS[] = " \r\t\n";

int main(void)
{
	bool running = true;

	fputs("VSDB command line interface\n"
	      "Type \"help\" for usage hints\n", stdout);

	char* line = NULL;
	size_t length = 0;

	while (running) {
		fputs("vsdb> ", stdout);
		// NOTE: getline allocates memory itself if line is NULL
		ssize_t read = getline(&line, &length, stdin);

		if (read == EOF) {
			fputc('\n', stdout);
			break;
		}

		// NOTE: ptr stores pointer to first word.
		//       First call to strtok_r will initialize ptr.
		char* ptr = NULL;
		char* action = strtok_r(line, DELIMITERS, &ptr);

		if (strncmp(action, "help", 4) == 0) {
			fputs("create\t\tinitialize empty database in memory\n"
			      "help\t\tprint this help message\n"
			      "save <path>\tsave database to path\n"
			      "quit\t\tstop interpreting input and exit program\n", stdout);
		}
		else if (strncmp(action, "create", 6) == 0) {
			fputs("New database initialized\n", stdout);
		}
		else if (strncmp(action, "save", 4) == 0) {
			// NOTE: Subsequent calls to strtok_r do not need line anymore, just ptr
			char* name = strtok_r(NULL, DELIMITERS, &ptr);
			if (name != NULL)
				fprintf(stdout, "Saved databased to %s\n", name);
			else
				fputs("Usage: save <path>\n", stdout);
		}
		else if (strncmp(action, "quit", 4) == 0) {
			running = false;
		}

		free(line); // NOTE: getline-allocated memory must be freed manually
		line = NULL; // NOTE: Reset pointer for getline to allocate memory again
	}

	if (line != NULL)
		free(line);
}
