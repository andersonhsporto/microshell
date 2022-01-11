/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:48:14 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/01/10 22:45:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

// Function to take input
int	takeinput(char *str)
{
	char	*buf;

	buf = readline("\nmicroshell >>> ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
	{
		return (1);
	}
}

// Function to print Current Directory.
void	printdir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}
