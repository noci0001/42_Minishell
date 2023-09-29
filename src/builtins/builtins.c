/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:01:23 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 16:37:32 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(t_gen	*gen)
{
	if (is_exact_match(gen->start->str, "cd"))
		return (1);
	if (is_exact_match(gen->start->str, "clear"))
		return (1);
	if (is_exact_match(gen->start->str, "echo"))
		return (1);
	else if (is_exact_match(gen->start->str, "pwd"))
		return (1);
	else if (is_exact_match(gen->start->str, "export"))
		return (1);
	else if (is_exact_match(gen->start->str, "unset"))
		return (1);
	else if (is_exact_match(gen->start->str, "env"))
		return (1);
	else
		return (SUCCESS);
}

int	do_builtin(t_gen	*gen)
{
	if (is_exact_match(gen->start->str, "cd"))
		return (ft_cd(gen, gen->env) * 0);
	if (is_exact_match(gen->start->str, "clear"))
		return (ft_clear());
	if (is_exact_match(gen->start->str, "echo"))
		return (ft_echo(gen->start, gen, gen->env) * 0);
	else if (is_exact_match(gen->start->str, "pwd"))
		return (ft_pwd(gen->env) * 0);
	else if (is_exact_match(gen->start->str, "export"))
		return (ft_export(gen, gen->env) * 0);
	else if (is_exact_match(gen->start->str, "unset"))
		return (ft_unset(gen, gen->env) * 0);
	else if (is_exact_match(gen->start->str, "env"))
		return (ft_env(gen->env) * 0);
	else
		return (GENERALERROR);
}

int	ft_clear(void)
{
	int	i;

	i = 0;
	while (i < 50)
	{
		write(1, "\n", 1);
		i++;
	}
	return (1);
}
