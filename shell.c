#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void count_chars(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp){ printf("File not found!\n"); return; }
    int c, count=0;
    while((c=fgetc(fp)) != EOF) count++;
    fclose(fp);
    printf("Characters: %d\n", count);
}

void count_words(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp){ printf("File not found!\n"); return; }
    int c, count=0, inword=0;
    while((c=fgetc(fp)) != EOF){
        if(isspace(c)) inword=0;
        else if(!inword){ inword=1; count++; }
    }
    fclose(fp);
    printf("Words: %d\n", count);
}

void count_lines(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp){ printf("File not found!\n"); return; }
    int c, count=0;
    while((c=fgetc(fp)) != EOF) if(c=='\n') count++;
    fclose(fp);
    printf("Lines: %d\n", count);
}

int main() {
    char input[100], *arg[5];

    while(1) {
        printf("myshell$ ");
        if(!fgets(input, sizeof(input), stdin)) break;

        int i=0;
        arg[i] = strtok(input, " \t\n");
        if(!arg[i]) continue;
        while((arg[++i] = strtok(NULL, " \t\n")));

        if(!strcmp(arg[0], "exit")) break;
        else if(!strcmp(arg[0], "count") && arg[1] && arg[2]){
            if(arg[1][0]=='c') count_chars(arg[2]);
            else if(arg[1][0]=='w') count_words(arg[2]);
            else if(arg[1][0]=='l') count_lines(arg[2]);
            else printf("Unknown count option!\n");
        }
        else {
            if(fork()==0){
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
