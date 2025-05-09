#ifndef PIPEX_H

# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define ERROR_MSG "Expected: ./pipex <infile> <cmd> <cmd> <outfile>\n"

void	ft_execute_cmd(char *argv, char **envp);
char	*ft_find_path(char *cmd, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *lil, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);


#endif