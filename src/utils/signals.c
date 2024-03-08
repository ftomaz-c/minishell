#include "../../includes/minishell.h"

void	sig_handler(int	sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigaction()
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler =	SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}