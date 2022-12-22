

#include "../includes/minishell.h"

void	sig_handler(int signal)
{
	char	*path;

	(void)signal;
	path = getcwd(0, 0);
	if (signal == SIGINT)
	{
		// kill(-1, SIGQUIT);
		ft_printf("\n%s\n", path);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	free(path);
}