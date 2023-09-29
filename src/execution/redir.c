/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:49:12 by snocita           #+#    #+#             */
/*   Updated: 2023/09/29 15:36:30 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	redir(t_gen *gen, t_token *token, int type)
{
	ft_close(gen->fdout);
	if (type == TRUNC)
		gen->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		gen->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (gen->fdout == -1)
	{
		ft_putstr_fd("\033[0;32mMinishelly$\033[0m : ", STDERR_FILENO);
		ft_putstr_fd(token->str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		gen->ret = 1;
		gen->no_exec = 1;
		return ;
	}
	dup2(gen->fdout, STDOUT_FILENO);
}

void	input(t_gen *gen, t_token *token)
{
	ft_close(gen->fdin);
	gen->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (gen->fdin == -1)
	{
		ft_putstr_fd("Minishelly: ", STDERR_FILENO);
		ft_putstr_fd(token->str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		gen->ret = GENERALERROR;
		gen->no_exec = 1;
		return ;
	}
	dup2(gen->fdin, STDIN_FILENO);
}

int	cmdpipe(t_gen *gen)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		gen->pipin = pipefd[0];
		gen->pid = -1;
		gen->parent = 0;
		gen->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		gen->pipout = pipefd[1];
		gen->pid = pid;
		gen->last = 0;
		return (1);
	}
}

void	exec_cmd(t_gen *gen, t_token *token)
{
	char	**cmd_array;

	if (gen->responsibility == 0)
		return ;
	cmd_array = cmd_tab(token);
	if (cmd_array && cmd_array[0] && ft_strcmp(cmd_array[0], "exit") == 0
		&& has_pipe(token) == 0)
		program_exit(gen, cmd_array);
	else if (is_builtin(gen))
		gen->ret = do_builtin(gen);
	else if (cmd_array)
		gen->ret = exec_bin(cmd_array, gen->env, gen);
	free(cmd_array);
	ft_close(gen->pipin);
	ft_close(gen->pipout);
	gen->pipin = -1;
	gen->pipout = -1;
	gen->responsibility = 0;
}

void	redirection_handler(t_gen *gen, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(gen, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(gen, token, APPEND);
	else if (is_type(prev, INPUT))
		input(gen, token);
	else if (is_type(prev, HEREDOC))
		here_doc(gen, token);
	else if (is_type(prev, PIPE))
		pipe = cmdpipe(gen);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redirection_handler(gen, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && gen->no_exec == 0)
		exec_cmd(gen, token);
}
