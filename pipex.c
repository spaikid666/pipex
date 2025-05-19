/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+	      +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:13:03 by asalguer          #+#    #+#             */
/*   Updated: 2025/05/16 14:13:03 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		return (perror("Error opening input file"), close(fd[1]), exit(1));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (perror("Error duplicating fd_in to stdin"), close(fd[1]),
			close(fd_in), exit(1));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (perror("Error duplicating fd[1] to stdout"), close(fd[1]),
			exit(1));
	close(fd[1]);
	close(fd_in);
	if (argv[2] == NULL || argv[2][0] == '\0')
	{
		write(2, "Error, the command is invalid.\n", 32);
		return (exit(1));
	}
	ft_execute_cmd(argv[2], envp);
}

static void	handle_dup2_error(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("Error duplicating file descriptor");
		close(old_fd);
		exit(1);
	}
}

static void	parent_process(int *fd, char **argv, char **envp)
{
	int	fd_out;
	int	status;

	waitpid(-1, &status, 0);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		perror("Error opening output file");
		close(fd[0]);
		exit(1);
	}
	handle_dup2_error(fd[0], STDIN_FILENO);
	handle_dup2_error(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd_out);
	if (!argv[3] || !argv[3][0])
	{
		write(2, "Error, the command is invalid.\n", 32);
		exit(1);
	}
	ft_execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (write(2, INVALID_ARGS, 50), -1);
	if (pipe(fd) == -1)
		return (perror("The pipe creation failed"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Error forking the process"), close(fd[0]), close(fd[1]),
			-1);
	if (pid == 0)
	{
		close(fd[0]);
		child_process(fd, argv, envp);
	}
	else
	{
		close(fd[1]);
		parent_process(fd, argv, envp);
	}
	return (0);
}
