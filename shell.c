#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>

// This function takes an array of strings, creates a fork and executes the command given by the string array
void execute(char** command)
{
    int pid = fork();
    if(!pid)
    {
        execvp(command[0], command);
        exit(0);
    }
    else if(pid < 0)
        return;
    wait(NULL);
    return;
}

// This function takes a command string and uses ' ' token to create an array of strings
void getCmdList(char* command, char* params[])
{
    command[strcspn(command, "\n")] = 0;
    int paramsLen = 0;
    char* token = strtok(command, " ");
    while(token != NULL) 
    {
        params[paramsLen] = token;
        token = strtok(NULL, " ") ;
        paramsLen++;
    }
    params[paramsLen] = NULL;
}


int main()
{
    char command[1000];
    while(1) 
    {
        printf("+ ");
        fgets(command, 1000, stdin);
        char* params[50];
        getCmdList(command, params);  
        int onlyWhiteSpaces = 1;
        for(int i = 0; command[i] != '\0'; i++) 
        {
            if(command[i] != ' ' && command[i] != '\n')
            {
                onlyWhiteSpaces = 0;
                break;
            }
        }
        if(!onlyWhiteSpaces)
        {
            if(!strcmp(params[0], "exit"))
                break;
            else
                execute(params);
        }        
    }
    return 0;
}