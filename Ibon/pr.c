/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:43:32 by iboiraza          #+#    #+#             */
/*   Updated: 2025/01/22 19:43:35 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **argv)
{
	char	**pos;

	if (argv == NULL)
		return ;
	pos = argv;
	while (*pos != NULL)
		free(*(pos++));
	free(argv);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

static int	ft_count_splits(char const *s, char c)
{
	int	count;
	int	first_letter;

	count = 0;
	first_letter = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (first_letter == 0)
			{
				count++;
				first_letter = 1;
			}
		}
		else
			first_letter = 0;
		s++;
	}
	return (count);
}

static int	ft_sub_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	**ft_free_mem(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i--]);
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		splits;
	int		i;
	int		len;
	char	**result;

	splits = ft_count_splits(s, c);
	result = (char **)malloc((splits + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < splits)
	{
		while (*s == c)
			s++;
		len = ft_sub_len(s, c);
		result[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!result[i])
			return (ft_free_mem(result, i));
		ft_strlcpy(result[i], s, len + 1);
		s = s + len;
		i++;
	}
	result[splits] = NULL;
	return (result);
}

void	pwd(int argc)
{
	char	*pwd;

    if (argc > 1)
    {
        printf("pwd: too many arguments\n");
        return ;
    }
	pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
}
// void	ls(char *path, char *av)
// {
// 	 //readdir(dirp);
// 	 execv(path, &av);
// }

void	cd(char *av)
{
	char	*path;
	char	*pwd;

	pwd = NULL;
	//printf("av: %s\n", av);
	path = av;
	//pwd = getcwd(NULL, 0);
	//printf("%s\n", pwd);
	if(chdir(path) == -1)
{
    	perror("chdir");
		return ;
    /* return error of some sort, don't continue */
}
	else
		pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	//ls(path, av);
}

void	echo(char **av, int flag)
{	
	int i;

	i = 1;
	if (flag == 2)
		i = 2;
	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && ft_strlen(av[i]) == 2)
		i++;
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			printf(" ");
	}
	if (flag == 1)
		printf("\n");
}

void    ft_print_user(void)
{
  	char    *pwd;
	char    *username;

    pwd = getcwd(NULL, 0);
	username = getenv("USER");
    printf("\033[37;44m%s\033[0m", username);
    printf("\033[32m %s\033[0m\n", pwd);

  return ;
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i == n - 1)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strlen (char *s)
{
	int	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

int	export_action(int argc, char **argv, int flag)
{
    char	var_name[128];
    int		var_value[128];
	int		i;

	flag = 0;
	i = 0;
	if (argc == 0)
		printf("h\n");
	if (ft_strncmp(argv[0], "export", 7) == 0)
	{
		while (argv[1][i++] != '=')
			var_name[i] = argv[1][i];
		i++;
		while (argv[1][i++])
			var_value[i] = argv[1][i];
		printf ("%s=%ls\n", var_name, var_value);
	}
	else
		flag = 1;
	return (flag);
}

int	fork_actions(int argc, char **argv, int flag)
{
	pid_t	pid;
	char	*path;

	if (ft_strncmp(argv[0], "ls", 2) == 0 && ft_strlen(argv[0]) == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			path = "/usr/bin/ls";
			execv(path, &argv[0]);
			exit(0);
		}
		wait(NULL);
	}
	else if (argc >= 1 && ft_strncmp(argv[0], "env", 3) == 0 && ft_strlen (argv[0]) == 3)
	{
		pid = fork();
		if (pid == 0)
		{
			path = "/usr/bin/env";
			execv(path, &argv[0]);
			exit(0);
		}
		wait(NULL);
	}
	else
		flag = 1;
	return (flag);
}

int	other_actions(int argc, char **argv, int flag)
{
	flag = 0;
	if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && ft_strlen(argv[0]) == 2)
 		cd(argv[1]);
	else if (argc > 1 && ft_strncmp(argv[0], "echo", 4) == 0 && ft_strlen(argv[0]) == 4
		&& ft_strncmp(argv[1], "-n", 2) == 0 && ft_strlen(argv[1]) == 2)
		echo(argv, 2);
	else if (argc >= 1 && ft_strncmp(argv[0], "echo", 4) == 0 && ft_strlen(argv[0]) == 4)
		echo(argv, 1);
	else if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && ft_strlen(argv[0]) == 2)
 		cd(argv[2]);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0 && ft_strlen(argv[0]) == 3)
 		pwd(argc);
	else
		flag = 1;
	return (flag);
}

void    init_shell(int argc, char **argv)
{
	int		flag;

	flag = 0;
	flag += fork_actions(argc, argv, flag);
//	printf("%d\n", flag);
	flag += other_actions(argc, argv, flag);
	flag += export_action(argc, argv, flag);
	if (flag == 3)
        printf("Command not found: %s\n", argv[0]);
    return ;
}

void    enter(char *line)
{
    char    **commands;
    int     splits;
    
    //add_history(line);
    commands = ft_split (line, ' ');
    splits = ft_count_splits (line, ' ');
    init_shell(splits, commands);
    free_split(commands);
}

int exist(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line [i] != '\0')
        return (1);
        i++;
    }
    return (0);
}
/*int main (int argc, char **argv, char **envp)*/
int main (void)
{
	char	*line;
//    char    **commands;
//    int     splits;

	while (1)
	{
        ft_print_user();
		line = readline(" > ");
        if (exist(line) == 0)
            write(1, "\0", 1);
        /*if (!line)
			break;*/
        if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
		{
			free(line);
			break;
		}
        if (exist(line))
            enter (line);
/*      if (exist(line))
        {
            commands = ft_split (line, ' ');
            splits = ft_count_splits (line, ' ');
            init_shell(splits, commands);
            free_split(commands);
        }*/
        free (line);
	}
    printf("\033[31mFin.\033[0m\n");
	return (0);
}
