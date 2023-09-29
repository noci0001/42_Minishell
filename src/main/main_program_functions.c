/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:16:02 by snocita           #+#    #+#             */
/*   Updated: 2023/07/28 17:55:30 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	reset_fds(t_gen *gen, int ac, char **av)
{
	(void)ac;
	(void)av;
	gen->fdin = -1;
	gen->fdout = -1;
	gen->pipin = -1;
	gen->pipout = -1;
	gen->pid = -1;
}

int	check_ac_and_av(t_gen *gen, int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		gen->ret = GENERALERROR;
		gen->exit = 1;
		return (GENERALERROR);
	}
	return (0);
}

void	free_env_in_between(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
	free(env->value);
	free(env->key);
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
	free(env->value);
	free(env->key);
	free(env);
}

// void	register_key_values(t_env	*new, char **envp, int i)
// {
// 	new->key = ft_strdup_for_envp(envp[i], GET_KEY);
// 	new->value = ft_strdup_for_envp(envp[i], GET_VALUE);
// 	if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
// 	{
// 		free(new->value);
// 		get_home_path(envp, new);
// 	}
// }

// void	register_key_values(t_env	*new, char **envp, int i)
// {
// 	new->key = ft_strdup_for_envp(envp[i], GET_KEY);
// 	new->value = ft_strdup_for_envp(envp[i], GET_VALUE);
// }

int	env_init(t_gen *gen, char **envp, int ac, char **av)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (check_ac_and_av(gen, ac, av) == GENERALERROR)
		return (GENERALERROR);
	env->key = ft_strdup_for_envp(envp[0], GET_KEY);
	env->value = ft_strdup_for_envp(envp[0], GET_VALUE);
	env->next = NULL;
	gen->env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!(new))
			return (1);
		new->key = ft_strdup_for_envp(envp[i], GET_KEY);
		new->value = ft_strdup_for_envp(envp[i], GET_VALUE);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
