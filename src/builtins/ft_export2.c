/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:37:19 by snocita           #+#    #+#             */
/*   Updated: 2023/08/01 15:42:14 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_for_arg_absence_or_head(t_gen	*gen, t_env	*envp)
{
	char	*key;

	key = NULL;
	if (is_arg_absent(gen, envp, EXPORT) == 1)
		return (1);
	if (ft_strchr(gen->start->next->str, '=') == NULL)
		return (0);
	key = ft_strdup_for_envp(gen->start->next->str, 0);
	if (look_for_head_for_export(key, envp) == 1)
	{
		free(envp->value);
		envp->value = ft_strdup_for_envp(gen->start->next->str, 1);
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

void	continue_export(t_env *envp, t_gen *gen, char *key)
{
	if (envp->next == NULL)
		free_and_add_node(key, envp, gen);
	else
		free_and_replace_value(envp, gen, key);
}

void	free_and_add_node(char	*key, t_env *envp, t_gen *gen)
{
	free(key);
	add_node_to_envp(envp, gen);
}

void	free_and_replace_value(t_env *envp, t_gen *gen, char *key)
{
	free(envp->value);
	envp->value = ft_strdup_for_envp(gen->start->next->str, 1);
	free(key);
}
