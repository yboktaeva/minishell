/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/21 17:04:46 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/struct.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    
    char *prompt;

    prompt = readline("minishell$");
    return (0);
}