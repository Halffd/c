#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_PARAMS 100

int parse_pipe(char* command, char** pipelines) {
    int n = 0;
    char* line = strdup(command); // Allocate memory and copy the command to line

    char* token = strtok(line, "|");
    while (token != NULL && n < MAX_COMMAND_PARAMS) {
        pipelines[n++] = token;
        token = strtok(NULL, "|");
    }

    free(line); // Free the dynamically allocated memory
    return n;
}

int parse(char* pipelines, char** params) {
    int n = 0;

    char* token = strtok(pipelines, " ");
    while (token != NULL && n < MAX_COMMAND_PARAMS) {
        params[n++] = token;
        token = strtok(NULL, " ");
    }

    return n;
}
int _p_main(void){
    pipes();
    return 0;
}
int pipes() {
    char command[] = "command1 | command2 | command3";
    char* pipelineCommands[MAX_COMMAND_PARAMS];
    int numPipelines = parse_pipe(command, pipelineCommands);

    for (int i = 0; i < numPipelines; i++) {
        char* params[MAX_COMMAND_PARAMS];
        int numParams = parse(pipelineCommands[i], params);

        printf("Pipeline %d:\n", i + 1);
        for (int j = 0; j < numParams; j++) {
            printf("Param %d: %s\n", j + 1, params[j]);
        }
        printf("\n");
    }

    return 0;
}