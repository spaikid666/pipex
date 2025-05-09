#include "pipex.h"

static void	ft_free_matrix(char **matrix, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static char	*ft_allocateword(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_fill(char const *s, char c, int nw, char **matrix)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < nw)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		matrix[j] = ft_allocateword(s, start, i);
		if (!matrix[j])
			return (ft_free_matrix(matrix, j), NULL);
		j++;
	}
	matrix[j] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		nw;
	int		i;

	i = 0;
	nw = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
			nw++;
		i++;
	}
	matrix = (char **)malloc((nw + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	return (ft_fill(s, c, nw, matrix));
}