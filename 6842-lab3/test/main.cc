#include "utilities.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

void prompt()
{
    cout << "\033[1;31mmyshell> ";
    cout << "\033[1;36m";
}

void handle_sigint(int sig)
{
    cout << endl;
    cout << "  --------------------------------------------------------------" << endl;
    cout << "ctrl-c signal is ignored" << endl;
    cout << "  --------------------------------------------------------------" << endl;
    cout << endl;
}

int main()
{
    signal(SIGINT, handle_sigint);

    int defaultout = dup(1);

    while (true)
    {
        dup2(defaultout, 1);
        close(defaultout);

        prompt();

        Command currentCommand;

        currentCommand.defaultin = dup(0);
        currentCommand.defaultout = dup(1);
        currentCommand.defaulterr = dup(2);
        currentCommand.defaultlog = "log.txt";

        tokenize(currentCommand);

        classifyCommand(currentCommand);
        modifyCommand(currentCommand);

        if (currentCommand.commandType == "single")
        {
            if (currentCommand.simpleCommands[0].command == "cd")
                changeDirectory(currentCommand);

            else
                forkProcces(currentCommand);
        }
        if (currentCommand.commandType == "pipe")
        {
            forkProcessPipe(currentCommand);
        }
    }
    return 0;
}
