/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:59:02 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/11 15:36:18 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static t_env *create_env_var(const char *name, const char *value);
// static void add_env_var(t_table *table, const char *name, const char *value);
// static int export_bad_id(char *id);
// static int str_check(char *str1, char *str2);
// static int	valid_id(char *str);
// static int	char_check(char *str, char c);
// static int print_export(t_table *table);
// static void find_exported(t_table *table, char *var_name);


// int cmd_export(t_arg *arg, t_table *table)
// {
//     int exit_status;
// 	//t_env *temp;
//     int i;

// 	exit_status = EXIT_SUCCESS;
// 	i = 0;
//     if (arg->argc == 1)
// 	{
// 		return print_export(table);
// 	}
// 	//printf("je suis avant le while de cmd_export\n");
// 	//printf("argc =%d\n", arg->argc);
//     while (i < arg->argc)
//     {
// 		//printf("CCCCC\n");
//         if (!valid_id(arg->argv[i]))
// 		{
// 			//printf("je suis dans le if de cmd_export\n");
//             exit_status = export_bad_id(arg->argv[i]);
// 		}
		
//         else if (char_check(arg->argv[i], '='))
//         {
// 			//printf("je suis dans le else if de cmd_export\n");
//             char *name = arg->argv[i];
//             char *value = ft_strchr(name, '=');
//             if (value)
//             {
// 				//printf("je suis dans le if de value\n");
//                 *value = '\0'; // Sépare le nom et la valeur
//                 value++; // Pointe vers la valeur
// 				//printf("name =%s\n", name);
// 				//printf("value =%s\n", value);
//                 add_env_var(table, name, value);
//                 //printf("je suis apres add_env_var\n");
//                 find_exported(table, name);
//             }
// 			else
// 				exit_status = export_bad_id(arg->argv[i]);
//         }
//         else
// 		{
// 			//printf("OUPS\n");
// 			find_exported(table, arg->argv[i]);
// 		}
// 		//printf("valid_id =%d\n", valid_id(arg->argv[i]));
// 		//printf("char_check =%d\n", char_check(arg->argv[i], '='));
//         i += 1;
//     }
//     return (exit_status);
// }

// static t_env *create_env_var(const char *name, const char *value)
// {
// 	t_env *new_var;

//     new_var = malloc(sizeof(t_env));
//     if (new_var == NULL)
//     {
//         perror("Erreur d'allocation de mémoire");
//         exit(EXIT_FAILURE);
//     }
//     new_var->var_name = ft_strdup(name);
//     new_var->var_value = ft_strdup(value);
//     new_var->exported = 1;
//     new_var->next = NULL;
//     return (new_var);
// }

// static void add_env_var(t_table *table, const char *name, const char *value)
// {
// 	t_env *new_var;

//     new_var = create_env_var(name, value);
//     new_var->next = table->env->next;
//     table->env->next = new_var;
// }

// static int export_bad_id(char *id)
// {
//     fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", id);
//     return EXIT_FAILURE;
// }

// static int str_check(char *str1, char *str2)
// {
//     if (!str1 || !str2)
//         return (0);
//     while (*str1 && *str2)
//     {
//         if (*str1 != *str2)
//             return (0);
//         str1++;
//         str2++;
//     }
//     return (*str1 == '\0' && *str2 == '\0');
// }

// static int	valid_id(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	if (str_check(str, "="))
// 		return (0);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
// 			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
// 			return (0);
// 		i += 1;
// 	}
// 	return (1);
// }

// static int	char_check(char *str, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (1);
// 		i += 1;
// 	}
// 	return (0);
// }

// static int print_export(t_table *table)
// {
// 	t_env *tmp;

//     tmp = table->env;
//     while (tmp != NULL)
//     {
//         if (tmp->exported)
//             printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->var_value);
//         tmp = tmp->next;
//     }
//     return (EXIT_SUCCESS);
// }

// static void find_exported(t_table *table, char *var_name)
// {
//     t_env *tmp;

//     tmp = table->env->next;
// 	//printf("je suis apres tmp = table->env \n");
//     while (tmp != NULL)
//     {
// 		//printf("je suis avant le if \n");
// 		//printf("var_name :%s\n tmp->var_name: %s\n", var_name, tmp->var_name);
//         if (ft_strcmp(var_name, tmp->var_name) == 0)
//         {
//             tmp->exported = 1;
//             break;
//         }
// 		//printf("var_name :%s\n tmp->var_name: %s\n", var_name, tmp->var_name);
//         tmp = tmp->next;
//     }
// // }
