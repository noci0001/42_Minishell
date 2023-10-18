/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:51:10 by snocita           #+#    #+#             */
/*   Updated: 2023/07/27 13:39:10 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	absent_or_not(t_gen	*gen, t_env	*env)
{
	char	*value_before_equal;

	if (is_arg_absent(gen, env, UNSET) == 1)
	{
		ft_putendl_fd("unset: wrong unsettable argument", 1);
		return (1);
	}
	else
	{
		value_before_equal = ft_strdup(gen->start->next->str);
		if (value_before_equal != NULL)
		{
			free(value_before_equal);
			return (0);
		}
	}
	return (1);
}

int	look_for_head(t_gen	*node, t_env *env)
{
	if (ft_strchr(node->start->next->str, '=') != NULL)
		return (0);
	if (is_exact_match(node->start->next->str, env->key) == 1)
		return (1);
	return (0);
}

void	remove_middle_man_found_inbetween(t_env	*env)
{
	t_env	*prev;
	t_env	*next;
	t_env	*curr;

	next = NULL;
	curr = NULL;
	prev = env;
	env = env->next;
	curr = env;
	if (env->next)
		env = env->next;
	next = env;
	prev->next = next;
	next->prev = prev;
	free(curr->key);
	free(curr->value);
	free(curr);
}

void	remove_middle_man(t_env	*env)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = NULL;
	prev = env;
	if (env->next)
		env = env->next;
	curr = env;
	free_env(curr);
	prev->next = NULL;
}
