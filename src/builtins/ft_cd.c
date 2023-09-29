/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:06:38 by snocita           #+#    #+#             */
/*   Updated: 2023/08/02 17:20:50 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	navigate_backward(t_env	*env)
{
	char	*cwd;
	size_t	cwd_len;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	cwd_len = ft_strlen(cwd);
	while (cwd[cwd_len] != '/')
		cwd_len--;
	new_cwd = ft_substr(cwd, 0, cwd_len);
	if (chdir(new_cwd) == 0)
		update_pwd(env);
	free(new_cwd);
	free(cwd);
	return (1);
}

int	navigate_forward(t_env	*env, char	*arg)
{
	char	*cwd;
	size_t	cwd_len;
	char	*new_cwd;
	char	*with_slash;

	cwd = getcwd(NULL, 0);
	cwd_len = ft_strlen(cwd);
	with_slash = ft_strjoin("/", arg);
	new_cwd = ft_strjoin(cwd, with_slash);
	if (chdir(new_cwd) == 0)
		update_pwd(env);
	else
		printf("");
	free(with_slash);
	free(new_cwd);
	free(cwd);
	return (1);
}

int	navigate_home(t_env	*env, int is_tilde, t_gen	*gen)
{
	char	*home;
	char	*cwd;

	home = ft_get_env(env, "HOME");
	cwd = getcwd(NULL, 0);
	if (chdir(home) == 0)
		update_pwd(env);
	if (is_tilde == 1)
	{
		if (ft_strlen(gen->start->next->str) < 2)
			navigate_home(env, 0, gen);
		else
			go_places(gen->start->next->str + 2, env);
	}
	update_oldpwd(env, cwd);
	free(cwd);
	return (1);
}

int	go_places(char	*arg, t_env	*env)
{
	int		i;
	char	**splitted_path;
	char	*cwd_before_move;

	cwd_before_move = getcwd(NULL, 0);
	splitted_path = ft_split(arg, '/');
	i = 0;
	while (splitted_path[i] != NULL)
	{
		if (is_exact_match(splitted_path[i], "..") == 1)
			navigate_backward(env);
		else
			navigate_forward(env, splitted_path[i]);
		i++;
	}
	update_oldpwd(env, cwd_before_move);
	free_double_arr(splitted_path);
	free(cwd_before_move);
	return (1);
}

int	ft_cd(t_gen	*gen, t_env	*env)
{
	char	*arg;

	if (is_arg_absent(gen, env, 0) == 1)
		return (navigate_home(env, 0, NULL));
	arg = ft_strdup(gen->start->next->str);
	if (arg[0] == '~')
	{
		free(arg);
		return (navigate_home(env, 1, gen));
	}
	if (arg[0] == '-' && arg[1] == '\0')
	{
		go_to_path(env);
		free(arg);
		return (1);
	}
	go_places(arg, env);
	free(arg);
	return (1);
}
