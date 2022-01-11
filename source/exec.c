/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:03:21 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/01/10 22:41:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

// Function where the system command is executed
void	execargs(char **parsed)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }
    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}
  