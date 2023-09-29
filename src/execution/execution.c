/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:34:34 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 15:41:19 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_fds(t_gen	*gen)
{
	reset_std(gen);
	close_fds(gen);
	reset_fds(gen, 0, NULL);
}

void	execution(t_gen *gen)
{
	t_token	*token;
	int		status;

	token = next_run(gen->start, NOSKIP);
	if (is_types(gen->start, "TAI") != 0)
		token = gen->start->next;
	while (gen->exit == 0 && token)
	{
		gen->responsibility = 1;
		gen->parent = 1;
		gen->last = 1;
		redirection_handler(gen, token);
		handle_fds(gen);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (gen->last == 0)
			gen->ret = status;
		if (gen->parent == 0)
		{
			free_token(gen->start);
			exit(gen->ret);
		}
		gen->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	return (cmd_tab_continue(tab, token, start));
}

char	**cmd_tab_continue(char **tab, t_token *token, t_token *start)
{
	int	i;

	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}
