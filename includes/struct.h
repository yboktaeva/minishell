/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/11 15:28:09 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TRUE 1
# define FAULSE 0
# define SUCCES ((void *)1)

typedef enum s_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PIPE
}		t_type;

typedef struct s_token /*lexer part*/
{
	t_type	type;
	char	*value;
}		t_token;

typedef struct	s_env /*dup ENVP in linked list*/
{
	char			*var_name;
	char			*var_value;
	char			*str;
	int				exported;
	struct s_env	*next;
}		t_env;

typedef struct s_redir /*struct for redirections IN, OUT, HEREDOC, APPEND*/
{
	t_type			type;
	char			*file_name;
	struct s_redir	*next;
}		t_redir;

typedef struct s_one_cmd /*node of one cmd*/
{
	char				*str;
	struct s_one_cmd	*next;
}		t_one_cmd;

typedef struct s_parse_list/*parsing linked list*/
{
	t_one_cmd	*one_cmd;
	t_redir		*input;
	t_redir		*output;
	struct s_parse_list	*next;
}		t_parse_list;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
}			t_arg;

typedef struct s_table
{
	t_env			*env;
	t_arg			*arg;
	char			**cmds;
	char			*path;
	char			*pwd;
	char			*old_pwd;
	t_parse_list	*parse_list;
	int				n_tokens;
	int				cmd_count;
	int				exit_status;
	pid_t			pid;
}			t_table;


#endif