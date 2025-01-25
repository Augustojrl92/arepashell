#include "../../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	(void)shell;
}

int	is_numeric(const char *str)
{
	int i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	do_exit(t_token *token)
{
	int	exit_code;

	if (token->args[1])
	{
		if (!is_numeric(token->args[1]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(token->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_code = 255;
		}
		else if (token->args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		else
			exit_code = ft_atoi(token->args[1]);
	}
	else
		exit_code = g_signal_data;
	free_shell(token->shell);
	exit(exit_code);
}
