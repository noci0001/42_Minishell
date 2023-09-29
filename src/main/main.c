/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:12:10 by snocita           #+#    #+#             */
/*   Updated: 2023/08/03 16:04:16 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_input_and_history(t_gen	*gen)
{
	if (gen->input == NULL)
	{
		printf("Exit\n");
		exit(0);
	}
	if (gen->input && strlen(gen->input) > 0)
		add_history(gen->input);
}

void	signal_handler_ctrl_c(int signal)
{
	signal = 2;
	if (signal)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	turn_off_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &term);
	}
}

int	main(int ac, char **av, char **env)
{
	t_gen	gen;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_ctrl_c);
	gen.in = dup(STDIN_FILENO);
	gen.out = dup(STDOUT_FILENO);
	gen.exit = 0;
	gen.ret = 0;
	gen.no_exec = 0;
	reset_fds(&gen, ac, av);
	env_init(&gen, env, ac, av);
	increase_shlvl(gen.env);
	while (gen.exit == 0)
	{
		sig_init();
		gen.input = readline("\033[0;32mMinishelly$\033[0m ");
		check_input_and_history(&gen);
		parse(gen.input, &gen);
		if (gen.start != NULL && check_line(&gen, gen.start))
			execution(&gen);
		free_token(gen.start);
	}
	free_env(gen.env);
	return (gen.ret);
}
