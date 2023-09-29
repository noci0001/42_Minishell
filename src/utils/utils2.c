/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:39:39 by snocita           #+#    #+#             */
/*   Updated: 2023/08/03 15:29:13 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_gen *gen)
{
	dup2(gen->in, STDIN_FILENO);
	dup2(gen->out, STDOUT_FILENO);
}

void	close_fds(t_gen *gen)
{
	ft_close(gen->fdin);
	ft_close(gen->fdout);
	ft_close(gen->pipin);
	ft_close(gen->pipout);
}

int	unexpected_token_message(t_token	*token, t_gen	*gen, int version)
{
	if (version == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `\n", 2);
		if (token->next)
			ft_putstr_fd(token->next->str, 2);
		else
			return (0);
		ft_putendl_fd("'", 2);
		gen->ret = 258;
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `\n", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd("'", 2);
		gen->ret = 258;
	}
	return (0);
}

void	program_exit(t_gen *gen, char **cmd_array)
{
	gen->exit = 1;
	ft_putstr_fd("exit ", STDERR_FILENO);
	if (cmd_array[1] && cmd_array[2])
	{
		gen->ret = 1;
		ft_putendl_fd("\033[0;32mMinishelly\033[0m: exit: \
			too many arguments", STDERR_FILENO);
	}
	else if (cmd_array[1] && ft_strisnum(cmd_array[1]) == 0)
	{
		gen->ret = 255;
		ft_putstr_fd("\033[0;32mMinishelly\033[0m: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd_array[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (cmd_array[1])
		gen->ret = ft_atoi(cmd_array[1]);
	else
		gen->ret = 0;
}
