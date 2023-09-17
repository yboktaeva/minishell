/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/17 22:12:53 by yuliaboktae      ###   ########.fr       */
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

extern int	g_status;

typedef enum e_sig_state
{
    SIG_DEFAULT = 1,
    SIG_HEREDOC,
    SIG_CHILD,
    SIG_PARENT
}    t_sig_state;

typedef enum e_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PIPE
}		t_type;

typedef enum e_num_cmd
{
	ONE_CMD,
	MULTI_CMD
}			t_num_cmd;

typedef struct s_token
{
	t_type	type;
	char	*value;
}		t_token;

typedef struct	s_env
{
	int				exported;
	char			*var_name;
	char			*var_value;
	char			*str;
	struct s_env	*next;
}		t_env;

typedef struct s_one_cmd
{
	char				*str;
	struct s_one_cmd	*next;
}		t_one_cmd;

typedef struct s_redir
{
	t_type			type;
	char			*file_name;
	struct s_redir	*next;
}		t_redir;

typedef struct s_here_doc
{
	int	read;
	struct s_here_doc *next;
}		t_here_doc;

typedef struct s_parse_list
{
	t_one_cmd	*one_cmd;
	t_redir		*input;
	t_redir		*output;
	struct s_parse_list	*next;
}		t_parse_list;

typedef struct s_arg
{
	int		n_args;
	char	**argv;
	char	**envp;
}			t_arg;

typedef struct s_table
{
	t_env			*env;
	t_arg			*arg;
	t_token			*tokens;
	t_parse_list	*parse_list;
	t_here_doc		*here_doc;
	int				n_tokens;
	int				cmd_count;
	pid_t			pid;
}			t_table;

#endif