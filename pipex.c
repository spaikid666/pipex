/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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
	{
		perror("Error, couldn't open input file");
		return (exit(1));
	}
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error in setting file descriptor in the child");
		return (exit(1));
	}
	close(fd[0]);
	if (argv[2] == NULL || argv[2][0] == '\0')
	{
		perror("Error, the command is invalid");
		return (exit(1));
	}
	ft_execute_cmd(argv[2], envp);
}

static void	parent_process(int *fd, char **argv, char **envp)
{
	int	fd_out;
	int	status;

	waitpid(-1, &status, 0);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		perror("Error, couldn't open output file");
		return (exit(1));
	}
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error in setting the file descriptor in the parent");
		return (exit(1));
	}
	close(fd[1]);
	ft_execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (perror(INVALID_ARGS), -1);
	if (pipe(fd) == -1)
	{
		perror("The pipe creation failed");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error forking the process");
		return (-1);
	}
	if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
	return (0);
}
