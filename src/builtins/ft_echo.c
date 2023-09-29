/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:21:01 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 14:40:32 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	loop_through_tokens(t_token *token, int *print_new_line)
{
	while (token->str != NULL && token->type == ARG)
	{
		if (token->str[0] == '-' && token->str[1] == 'n')
		{
			if (!token->next)
				break ;
			token = token->next;
			print_new_line = 0;
		}
		ft_putstr_fd(token->str, 1);
		if (token->next != NULL)
		{
			ft_putchar_fd(' ', 1);
			token = token->next;
		}
		else
		{
			if (print_new_line != 0)
				ft_putchar_fd('\n', 1);
			return (1);
		}
	}
	return (1);
}

int	ft_echo(t_token *token, t_gen *gen, t_env *env)
{
	int	print_new_line;

	(void)env;
	print_new_line = 1;
	if ((!gen->start->next))
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if (token->str[0] == '$' && token->str[1] == '?')
		return (1);
	loop_through_tokens(token->next, &print_new_line);
	return (1);
}
