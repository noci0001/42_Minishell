/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:37:58 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 14:43:38 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		start = start->next;
		if (start->prev->str)
			free(start->prev->str);
		ft_memdel(start->prev);
	}
	if (start)
	{
		free(start->str);
		ft_memdel(start);
	}
}

int	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		ft_strdel(&temp->value);
		ft_strdel(&temp->key);
		ft_strdel(&temp->value);
		free(temp);
	}
	return (1);
}

int	free_env_list2(t_env *env)
{
	t_env	*temp;

	if (env)
	{
		temp = env;
		ft_strdel(&temp->value);
		ft_strdel(&temp->key);
		free(temp);
	}
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

void	free_head(t_gen	*gen)
{
	t_env	*temp;

	temp = gen->env;
	free(temp->key);
	free(temp->value);
	free(temp);
	return ;
}
