#include "minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_received_signal = 130;
}

void	ft_init_signal(void)
{
	struct sigaction	act_sa;


}
