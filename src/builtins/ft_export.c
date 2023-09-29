/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/08/01 15:41:09 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	add_node_to_envp(t_env *envp, t_gen	*gen)
{
	t_env	*last_node;
	t_env	*next_node;

	last_node = envp;
	next_node = malloc(sizeof(t_env));
	if (!next_node)
		return (1);
	next_node->value = ft_strdup_for_envp(gen->start->next->str, 1);
	next_node->key = ft_strdup_for_envp(gen->start->next->str, 0);
	next_node->prev = last_node;
	next_node->next = NULL;
	last_node->next = next_node;
	return (1);
}

int	ft_export(t_gen *gen, t_env *envp)
{
	char	*key;

	if (check_for_arg_absence_or_head(gen, envp) == 1)
		return (1);
	key = ft_strdup_for_envp(gen->start->next->str, 0);
	while (envp && envp->next != NULL)
	{
		if (is_exact_match(key, envp->next->key) == 1)
			break ;
		if (envp->next)
			envp = envp->next;
	}
	if (envp->next)
		envp = envp->next;
	if (is_exact_match(key, envp->key) == 1)
	{
		free(envp->value);
		envp->value = ft_strdup_for_envp(gen->start->next->str, 1);
		free(key);
		return (1);
	}
	continue_export(envp, gen, key);
	return (1);
}

int	check_for_tail(t_gen	*gen, t_env	*tail)
{
	t_env	*prev;

	if (is_exact_match(gen->start->next->str, tail->next->key) == 1)
	{
		prev = tail;
		prev->next = NULL;
		return (1);
	}
	return (0);
}
