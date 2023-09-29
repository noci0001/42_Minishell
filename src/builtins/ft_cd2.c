/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:01:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/28 18:26:18 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_oldpwd(t_env	*env, char	*old_cwd)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(old_cwd);
			return ;
		}
		env = env->next;
	}
}

int	update_pwd(t_env	*env)
{
	t_env	*node;
	char	cwdbuffer[1024];
	char	*cwd;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			node = env;
			free(node->value);
			cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
			cwd = ft_strjoin("PWD=", cwd);
			node->value = ft_strdup_for_envp(cwd, 1);
			free(cwd);
		}
		env = env->next;
	}
	return (1);
}

int	go_to_path(t_env *env)
{
	int		ret;
	char	*env_path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env_path = get_old_pwd(env);
	ret = chdir(env_path);
	free(cwd);
	return (ret);
}

char	*get_old_pwd(t_env	*env)
{
	while (env->next != NULL)
	{
		if (ft_strncmp(env->key, "OLDPWD", 6) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
