/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:47:37 by snocita           #+#    #+#             */
/*   Updated: 2023/08/03 15:02:06 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd("\n\033[0;32mMinishelly$\033[0m ", STDERR_FILENO);
		g_sig.exit_status = 0;
	}
	else
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putendl_fd(nbr, STDERR_FILENO);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	ft_memdel(nbr);
}

// check for open quotes
int	check_for_open_quotes(t_gen *gen, char **line)
{
	if (quotes(*line, 2147483647))
	{
		printf("\033[0;32mMinishelly$\033[0m: syntax error with open quotes\n");
		ft_memdel(*line);
		gen->ret = MISUSEOFBUILTINS;
		gen->start = NULL;
		return (1);
	}
	return (0);
}

// - Checking for open quotes
// - Tokanization of head
void	parse(char *line, t_gen *gen)
{
	t_token	*token;

	signal(SIGQUIT, &sig_quit);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_int);
	signal(SIGINT, &signal_handler_ctrl_c);
	if (g_sig.sigint == 1)
		gen->ret = g_sig.exit_status;
	if (check_for_open_quotes(gen, &line))
		return ;
	line = space_line(line);
	gen->start = get_tokens(line);
	ft_memdel(line);
	squish_args(gen);
	token = gen->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		check_expansion(gen, token);
		token = token->next;
	}
}
