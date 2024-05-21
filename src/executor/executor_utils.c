/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/21 20:54:00 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Creates a basic environment for the shell.
 * 
 * This function creates a basic environment for the shell containing
 * only the PATH variable.
 * 
 * @return A pointer to the array of environment variables.
 */
char	**basic_env(void)
{
	char	**b_env;

	b_env = calloc (sizeof(char *), 3);
	b_env[0] = ft_strdup("PATH=/bin:/usr/bin");
	b_env[1] = ft_strdup("_=/bin/env");
	return (b_env);
}

void	nint_mode(t_tools *tools)
{
	if (tools->nint_mode && !tools->exit)
	{
		ft_putstr_fd("minishell: line ", STDERR_FILENO);
		ft_putnbr_fd(tools->line_count, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

/**
 * @brief Handles execution errors by printing error messages
 * and updating the global status.
 * 
 * This function handles execution errors by printing the
 * corresponding error message,
 * updating the global status, and freeing any allocated memory.
 * 
 * @param tools A pointer to the tools structure.
 * @param err The error code.
 * @param str The string representing the command or file causing the error.
 * @param value A pointer to the value to be freed, if applicable.
 * @return None.
 */
void	exec_err(t_tools *tools, int err, char *str, char *value)
{
	nint_mode(tools);
	if (err == 1)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_status = 127;
	}
	else if (err == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_status = 127;
	}
	else if (err == 8)
		g_status = 0;
	else if (err == 13)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_status = 130;
	}
	if (value)
		free(value);
}

/**
 * @brief Waits for a child process to change state and 
 * updates the global status.
 * 
 * This function waits for the child process with the specified 
 * PID to change state.
 * It updates the global_status variable with the exit status
 *  of the child process if it exited normally.
 * 
 * @param pid    Process ID of the child process to wait for.
 * @param status Pointer to an integer to store the exit 
 * status of the child process.
 */
void	wait_status(t_tools *tools, int pid, int *status, int here_doc)
{
	int	i;
	int	sig;

	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
			g_status = 130;
		else if (sig == SIGQUIT)
			g_status = 131;
	}
	else if (WIFEXITED(*status))
		g_status = WEXITSTATUS(*status);
	if (here_doc)
	{
		if (g_status == 130)
			free_and_exit(tools, g_status);
		dup2(tools->parser->fd[0], STDIN_FILENO);
		close(tools->parser->fd[0]);
	}
	else
	{
		i = 3;
		while (i < 1024)
			close(i++);
		if (g_status == 130)
			write(1, "\n", 1);
		else if (g_status == 131)
			write(1, "Quit (core dumped)\n", 19);
	}
}
