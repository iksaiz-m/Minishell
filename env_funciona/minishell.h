/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:25 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/17 20:46:57 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#define COLOR_AZUL "\033[34m"
#define GREEN "\033[32m"
#define MAGENTA "\033[1;35m"
#define RST "\033[0m"

typedef struct s_prompt
{
	va_list *cmds;
	// char **envp;
	char *envp;
	struct s_prompt *next;
	pid_t pid;
}		t_prompt;

typedef struct s_mini
{
	char **full_cmd;
	char **commands;
	char *full_path;
	int infile;
	int outfile;
	int	splits;
	t_prompt	*env;
}	t_mini;

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void printaddata(t_prompt *adddata);

//split.c
char	**ft_split(char const *s, char c);
void	free_split(char **argv);
int		ft_count_splits(char const *s, char c);
char	**ft_splitquotes(char const *s, char c, char s_quote, char d_quote);
size_t	ft_num_word(char const *s, char c, size_t i, size_t num_word);
char 	**split_env(char **envp);
char 	**unset_split(char **envp, int flag);

//builtins.c
void	echo(char **av, int flag);
void	pwd(int argc);
void	cd(int argc, char *av);
// char	**unset(char **argv, char **envp);
void	unset(char **argv, t_prompt **data);
void	unset(char **argv, t_prompt **data);

//init_shell.c
int		export_action(int argc, char **argv);
// int		fork_actions(int argc, char **argv, int flag, t_mini **data);
int		fork_actions(int argc, char **argv, int flag, t_prompt *env);

int		other_actions(int argc, char **argv, t_mini **data);
// int	init_shell(int argc, char **argv, char **envp, t_mini **data);
int	init_shell(int argc, char **argv, t_prompt *emv, t_mini **data);

//exit.c
int		ft_exit(t_mini *data);
//parse_imput.c
/* int		parsequotes(t_mini *data);*/
void	remove_quotes(char *imput, int i);
int		detectopenquotes(char *line);

//commands.c
void	not_builtin_command(t_mini **data);

#endif
