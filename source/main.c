#include "microshell.h"

int	main(void)
{
	t_shell	*shell;

	shell->execFlag = 0;
	init_shell();
    while (1)
	{
        // print shell line
        printdir();
        // take input
        if (takeinput(shell->inputString))
            continue ;
        // process
        shell->execFlag = processString(shell->inputString,
        shell->parsedArgs, shell->parsedArgsPiped);
        // execflag returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
        // 2 if it is including a pipe.
        // execute
        if (shell->execFlag == 1)
            execargs(shell->parsedArgs);
        if (shell->execFlag == 2)
            exec_args_piped(shell->parsedArgs, shell->parsedArgsPiped, &shell);
    }
    return 0;
}
