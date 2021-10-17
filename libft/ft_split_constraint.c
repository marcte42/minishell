#include "../includes/minishell.h"

static void	ft_free(int i, char **result)
{
	int	j;

	j = 0;
	while (j < i)
		free(result[j++]);
	free(result);
}

static int	ft_size_malloc(char *s, char c, int (*constraint)(char *s, char *c))
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && !constraint(s, &s[i]))
			count++;
		i++;
	}
	return (count + 1);
}

static char	*ft_line(char *s, char c, int (*constraint)(char *s, char *c))
{
	char	*line;
	int		i;

	i = 0;
	while (s[i] && (s[i] != c || constraint(s, &s[i])))
		i++;
	if (!(line = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && (s[i] != c || constraint(s, &s[i])))
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char    **ft_split_constraint(char *s, char c, int (*constraint)(char *s, char *c))
{
	char	**result;
	int		i;
    int     j;

	if (!(result = (char **)malloc(sizeof(char *) *
	(ft_size_malloc((char *)s, c, constraint) + 1))))
		return (NULL);
	i = 0;
    j = 0;
	while (s[j])
	{
		while (s[j] == c && !constraint(s, &s[j]) && *s)
			j++;
		if (s[j] && (s[j] != c || constraint(s, &s[j])))
		{
			if ((result[i++] = ft_line(&s[j], c, constraint)) == NULL)
			{
				ft_free(i - 1, result);
				return (NULL);
			}
			while (s[j] && (s[j] != c || constraint(s, &s[j])))
            {
				j++;
            }
		}
	}
	result[i] = 0;
	return (result);
}