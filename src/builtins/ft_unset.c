/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:01:07 by snocita           #+#    #+#             */
/*   Updated: 2023/07/28 17:23:10 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	look_for_head_for_export(char *key, t_env *env)
{
	if (is_exact_match(key, env->key) == 1)
		return (1);
	return (0);
}

void	go_to_corresponding_node(t_gen	*node, t_env *env)
{
	while (is_exact_match(node->start->next->str, env->next->key) != 1)
	{
		if (env->next)
			env = env->next;
		else
			return ;
	}
	return ;
}

int	is_at_tail(t_gen *gen, t_env *env)
{
	t_env	*reference;

	env = env->next;
	reference = env;
	while (env->next != NULL)
		env = env->next;
	if (is_exact_match(gen->start->next->str, env->key) == 1)
	{
		env = reference;
		return (1);
	}
	env = reference;
	return (0);
}

int	check_tail_and_body(t_gen	*gen, t_env	*env)
{
	if (is_at_tail(gen, env) == 1)
	{
		while (env->next->next != NULL)
			env = env->next;
		remove_middle_man(env);
		return (1);
	}
	else
	{
		if ((is_exact_match(gen->start->next->str, env->next->key) == 1)
			&& (env->next->next->key != NULL))
			remove_middle_man_found_inbetween(env);
		return (1);
	}
	return (0);
}

int	ft_unset(t_gen	*gen, t_env	*env)
{
	t_env	*head_ref;

	if (look_for_head(gen, env) == 1)
	{
		head_ref = env->next;
		free_head(gen);
		gen->env = head_ref;
		return (1);
	}
	else
	{
		while (env && env->next != NULL)
		{
			if (is_exact_match(gen->start->next->str, env->next->key) == 1)
				break ;
			if (env->next)
				env = env->next;
		}
		if (check_tail_and_body(gen, env) == 0)
			return (1);
	}
	return (1);
}
