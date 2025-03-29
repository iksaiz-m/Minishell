/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:04:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/03/29 20:13:18 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lstsort(t_prompt *lst, int swapped)
{
    t_prompt *current;
	char *temp;
    t_prompt *last;

	last = NULL;
    if (lst == NULL)
        return;  // Si la lista está vacía, no hace nada
    while (swapped) // Sigue iterando mientras haya intercambios
	{
        swapped = 0;
        current = lst;
        // Compara los nodos consecutivos
        while (current->next != last)
		{
            if (strcmp(current->envp, current->next->envp) > 0) // Si el valor del nodo actual es mayor que el siguiente, los intercambiamos
			{
                temp = current->envp; // Intercambiar los valores de los nodos
                current->envp = current->next->envp;
                current->next->envp = temp;
                swapped = 1;  // Se ha hecho un intercambio
            }
            current = current->next;
        }
        last = current;  // Último nodo ya está ordenado
    }
}

t_prompt	*ft_lstlast(t_prompt *lst)
{
	t_prompt	*last;
	t_prompt	*first;
	int		i;
	int		t;

	i = 0;
	first = lst;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	t = i - 1;
	while (t > 0)
	{
		t--;
		first = first->next;
	}
	last = first;
	return (last);
}

void	ft_lstadd_back(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temporal;

	temporal = ft_lstlast(*lst);
	if (!temporal)
		*lst = new;
	else
		temporal->next = new;
}

void	asign_env_value(char *argv, t_prompt **data)
{
	t_prompt	*tmp;
	t_prompt	*var;
	char		**var_name;

	tmp = *data;
	var_name = ft_split(argv, '=');
	while (tmp)
	{
		if (ft_strncmp(var_name[0], tmp->envp, ft_strlen(var_name[0])) == 0 // Comparamos el valor de la variable de entorno con argv
			&& tmp->envp[ft_strlen(var_name[0])] == '=') 
		{
			tmp->envp = strdup(argv);
			free(var_name);
			return ;
		}
		tmp = tmp->next;
	}
	var = malloc(sizeof(t_prompt));
	if (!var)
		return ;
	var->envp = strdup(argv); // Si no existe una variable con ese nombre, se crea una nueva y se asigna el valor de argv
	var->next = NULL;
	free(var_name);
	ft_lstadd_back(data, var); //Se añade la nueva variable al final de la lista de variables.
	return ;
}

void	export(char **argv, t_prompt *data)
{
	t_prompt	*tmp;
	t_prompt	*var;
	int			i;

	i = 1;
	if (!argv[1])
	{
		ft_lstsort(data, 1);
		printaddata(data);
		return ;
	}
	while(argv[i])
	{
		asign_env_value(argv[i], &data);
		i++;
	}
	var = NULL;
	tmp = data;
}

void	remove_env(char *argv, t_prompt **data)
{
	t_prompt	*tmp;
	t_prompt	*var;

	var = NULL;
	tmp = *data;
	while (tmp)
	{
		// Comparamos el valor de la variable de entorno con argv
		if (ft_strncmp(argv, tmp->envp, ft_strlen(argv)) == 0
			&& tmp->envp[ft_strlen(argv)] == '=')
		{
			// Si estamos eliminando el primer nodo (cabeza de lista)
			if (var == NULL)
				*data = tmp->next;
			else
				var->next = tmp->next;
			// Liberamos el espacio de memoria de la variable de entorno y el nodo
			free(tmp->envp);
			free(tmp);
			return;  // Terminamos la función después de eliminar el nodo
		}
		// Continuamos recorriendo la lista
		var = tmp;
		tmp = tmp->next;
	}
}

void	unset(char **argv, t_prompt **data)
{
	int	i;
	t_prompt *unset;

	unset = *data;
	i = 1;
	while (argv[i])
	{
		remove_env(argv[i], &unset);
		i++;
	}
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
	free(pwd);
}

void	cd(int argc, char *av)
{
	char	*path;

	if (argc == 1)
		path = getenv("HOME");
	else
		path = av;
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
}

void	echo(char **av, int flag)
{
	int	i;

	i = 1;
	if (flag == 2)
		i = 2;
	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && !av[i][2])
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

//  Para la comprobacion del -n o cosas asi en vez de usar ft_strlen comprobar que no haya siguiente
//	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && !av[i][3])