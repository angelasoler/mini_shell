

#include "../includes/minishell.h"

void	sig_handler(int signal)
{
	char	*path;

	path = getcwd(0, 0);
	// if (signal == SIGINT)
	// {
		ft_printf("\n%s\n", path);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("\n --- %d ----\n", signal);
	// }
	// else if (signal == SIGMINE)
	// 	exit(0);
	// free(path);
}