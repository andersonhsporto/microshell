#ifndef MICROSHELL_H
# define MICROSHELL_H

# define MAXCOM 1000 // max number of letters to be supported
# define MAXLIST 100 // max number of commands to be supported

# include	<stdio.h>
# include	<string.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/types.h>
# include	<sys/wait.h>
# include	<readline/readline.h>
# include	<readline/history.h>

typedef struct s_shell
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;
	char	inputString[MAXCOM];
	char	*parsedArgs[MAXLIST];
	char	*parsedArgsPiped[MAXLIST];
	int		execFlag;
}	t_shell;

void	exec_args_piped(char **parsed, char **parsedpipe, t_shell *shell);
void	openhelp(void);
int		ownCmdHandler(char	**parsed);
void	parseSpace(char *str, char **parsed);
int		processString(char *str, char **parsed, char **parsedpipe);

void	execargs(char **parsed);

int		takeinput(char *str);

#endif
