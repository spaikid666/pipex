/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:40:51 by asalguer          #+#    #+#             */
/*   Updated: 2025/05/16 13:40:51 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (ft_free_matrix(paths), path);
		free(path);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}

static void	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_free_matrix(cmd);
		perror("The command wasn't found");
		return (exit(127));
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_free_matrix(cmd);
		perror("Error executing the command");
		return (exit(127));
	}
}

void	ft_execute_cmd(char *argv, char**envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!envp || !cmd[0])
		return (ft_free_matrix(cmd), \
		perror("The command is invalid"), exit(127));
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (execve(cmd[0], cmd, envp) == -1)
				return (ft_free_matrix(cmd), \
				perror("Error executing the command"), exit(127));
		}
		else
			return (ft_free_matrix(cmd), \
			perror("The command wasn't found"), exit(127));
	}
	else
		execute_cmd(cmd, envp);
}
