/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:54 by snocita           #+#    #+#             */
/*   Updated: 2023/08/01 17:36:16 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_for_path(t_env	*env)
{
	int		path_found;
	t_env	*reference;

	path_found = 0;
	reference = env;
	while (env && env->key)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			path_found = 1;
			printf("%s\n", env->value);
		}
		env = env->next;
	}
	if (path_found != 0)
	{
		env = reference;
		while (env && env->key && ft_strncmp(env->key, "PATH", 4) != 0)
			env = env->next;
		printf("%s\n", env->value);
	}
	else
		printf(NOPATH);
	return (path_found);
}

int	allocate_bin(char **bin, t_env	*env, char **args)
{
	(void)env;
	if (!args[0] && !bin[0])
		return (GENERALERROR);
	else
		return (SUCCESS);
}

int	navigate_until_path(t_env	*env)
{
	int	found;

	found = GENERALERROR;
	while (env && env->value)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			found = SUCCESS;
			break ;
		}
		env = env->next;
	}
	if (found == GENERALERROR)
		return (GENERALERROR);
	else
		return (SUCCESS);
}

int	execute_depending_on_path(char	*path, char **args, t_env *env, t_gen *gen)
{
	int	ret;

	if (path != NULL)
		ret = magic_box(path, args, env, gen);
	else
		ret = magic_box(args[0], args, env, gen);
	return (ret);
}
