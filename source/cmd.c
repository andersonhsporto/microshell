#include "microshell.h"

// Function where the piped system commands is executed
void	exec_args_piped(char **parsed, char **parsedpipe, t_shell *shell)
{
	if (pipe(shell->pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return ;
	}
	shell->p1 = fork();
	if (shell->p1 < 0)
	{
		printf("\nCould not fork");
		return ;
	}
	if (shell->p1 == 0)
	{
	    // Child 1 executing..
	    // It only needs to write at the write end
		close(shell->pipefd[0]);
		dup2(shell->pipefd[1], STDOUT_FILENO);
		close(shell->pipefd[1]);
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		// Parent executing
		shell->p2 = fork();
		if (shell->p2 < 0)
		{
			printf("\nCould not fork");
			return ;
		}
		// Child 2 executing..
		// It only needs to read at the read end
		if (shell->p2 == 0)
		{
			close(shell->pipefd[1]);
			dup2(shell->pipefd[0], STDIN_FILENO);
			close(shell->pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
}

void	openhelp(void)
{
	puts("\n***WELCOME TO MICROSHELL"
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");
	return ;
}

int	ownCmdHandler(char	**parsed)
{
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
	
    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openhelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    default:
        break ;
    }
    return (0);
}

void	parseSpace(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break ;
		if (strlen(parsed[i]) == 0)
			i--;
		i++;
	}
}

int	processString(char *str, char **parsed, char **parsedpipe)
{
	char	*strpiped[2];
	int		piped;

	piped = parsePipe(str, strpiped);
	if (piped)
	{
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	}
	else
	{
		parseSpace(str, parsed);
	}
	if (ownCmdHandler(parsed))
		return (0);
	else
		return (1 + piped);
}
