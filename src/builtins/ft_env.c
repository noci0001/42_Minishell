/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:22 by snocita           #+#    #+#             */
/*   Updated: 2023/07/24 20:25:05 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_key_value(t_env	*env)
{
	env->key = ft_strdup(env->value);
	env->value = ft_strdup(env->value);
}

int	obtain_envp(t_gen *gen, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (free_env_list(gen->env));
		new->value = ft_strdup_for_envp(env->value, 1);
		new->key = ft_strdup_for_envp(env->value, 0);
		new->prev = env;
		if (env)
			env->next = new;
		else
			gen->env = new;
		env = new;
		i++;
	}
	if (env)
		env->next = NULL;
	return (SUCCESS);
}

char	*env_to_str_func(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!(env))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i++] = lst->value[j++];
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->key, 1);
		if (env->key != NULL)
			ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
	}
	return (1);
}
