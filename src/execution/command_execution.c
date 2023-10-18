/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:05:01 by snocita           #+#    #+#             */
/*   Updated: 2023/08/01 17:39:08 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("Minishelly: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = COMMANDNOTFOUND;
	else
		ret = CANNOTEXECUTE;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	magic_box(char *path, char **args, t_env *env, t_gen *gen)
{
	char	**env_array;
	char	*ptr;
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		ptr = env_to_str_func(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab(env_array);
		free_token(gen->start);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret > 256)
		ret = 1;
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while (1)
	{
		item = readdir(folder);
		if (item == NULL)
			break ;
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

// int	exec_bin(char **args, t_env *env, t_gen *gen)
// {
// 	int		i;
// 	char	**bin;
// 	char	*path;
// 	int		ret;

// 	i = 0;
// 	ret = CANNOTEXECUTE;
// 	if (navigate_until_path(env) != SUCCESS)
// 		return (ret);
// 	printf("PATH IS->%s\n", env->value);
// 	if (env == NULL || env->next == NULL)
// 		return (magic_box(args[0], args, env, gen));
// 	bin = ft_split(env->value, ':');
// 	if (allocate_bin(bin, env, args) == GENERALERROR)
// 		return (GENERALERROR);
// 	i = 1;
// 	printf("BIN is : %s\n", bin[0]);
// 	path = check_dir(bin[0] + 5, args[0]);
// 	while (args[0] && bin[i] && path == NULL)
// 		path = check_dir(bin[i++], args[0]);
// 	ret = execute_depending_on_path(path, args, env, gen);
// 	free_tab(bin);
// 	ft_memdel(path);
// 	return (ret);
// }

int	exec_bin(char **args, t_env *env, t_gen *gen)
{
	int		ret;
	int		found;

	found = GENERALERROR;
	ret = CANNOTEXECUTE;
	while (env && env->value)
	{
		if (is_match(env) != GENERALERROR)
		{
			found = SUCCESS;
			break ;
		}
		env = env->next;
	}
	if (found != SUCCESS)
		return (ret);
	ret = continue_execution(env, args, gen);
	return (ret);
}
