/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2022/02/09 19:56:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_input(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (ft_iswhitespace(input[*i]) == 1)
		*i = *i + 1;
	if (input[*i] == '\0')
		return (0);
	size = size_to_char(input, *i, ";");
	if (size == -1)
		return (-1);
	if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
		return (-1);
	cpy_instruction(instruction, input, i, size);
	*inst = instnew(ft_strdup(instruction));
	free(instruction);
	if (input[*i] == ';')
		*i = *i + 1;
	return (1);
}

//"$'tt'" il ecrit tout ce qu'il y a entre double quote //done
//'$tt' '"$tt"'  '$"tt"' il ecrit tout ce qu'il y a entre simple quote //done
//$tt normal //done

//"'$tt'" "$tt" il remplace et il garde les autres char quote compris	
//$'tt' $"tt" il vire le dolar et ecrit le reste

int		trigger(char c, int state)
{
	int		ret;

	ret = state;
	if (c == '\"' && state == 0)
		ret = 1;
	else if (c == '\"' && state == 1)
		ret = 0;
	else if (c == '\'' && state == 0)
		ret = 2;
	else if (c == '\'' && state == 2)
		ret = 0;
	return (ret);
}

int		search_key(t_env *env, char *key, char **res)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->set == 1)
			{
				*res = env->value;
				return (1);
			}
			*res = NULL;
			return (0);
		}
		env = env->next;
	}
	*res = NULL;
	return (0);
}

char	*dollar_project(t_env *env, char *str, int *i, int state)
{
	char	*res;
	char	*key;

	if (state == 2 || (state == 1 && (str[(*i) + 1] == '\"' || str[(*i) + 1] == '\'')))
	{
		if (new_malloc((void *)&res, sizeof(char), 1 + 1) == 0)
			return (NULL); //error
		res[0] = '$';
		res[1] = '\0';
		*i = *i + 1;
		return (res);
	}
	*i = *i + 1;
	if (state == 0 && str[*i] && ft_ischar("\r\n\v\t\f \'\"", str[*i]) == 1)
	{
		if (new_malloc((void *)&res, sizeof(char), 1 + 1) == 0)
			return (NULL); //error
		res[0] = '\0';
		return (res);
	}
	if (cpy_size_to_char(&key, str, i, "\r\n\v\t\f \'\"") != 1)
		return (NULL); //error
	if (search_key(env, key, &res) == 0)
	{
		ft_putchar(str[*i]);
		if (new_malloc((void *)&res, sizeof(char), 1) == 0)
			return (NULL); //error
		res[0] = '\0';
		return (res);
	}
	return (res);
}

void	dollar_expand(t_cmd *cmd, t_env *env)
{
	int		i;
	int		state;
	int		d;
	int		save;
	char	*res;
	char	*tmp;
	char	*full_res;

	i = 0;
	state = 0;
	d = 0;
	full_res = malloc(sizeof(char) * (ft_strlen(cmd->args[1]) + 1));
	while (cmd->args[1][i])
	{
		if (cmd->args[1][i] == '\'' || cmd->args[1][i] == '\"')
		{
			state = trigger(cmd->args[1][i], state);
			full_res[d] = cmd->args[1][i];
			i++;
			d++;
		}
		if (cmd->args[1][i] == '$')
		{
			save = i;
			res = dollar_project(env, cmd->args[1], &i, state);
			full_res[d] = '\0';
			d = i - save + 1;
			tmp = ft_strjoin(full_res, res);
			if (tmp[0] == '\0')
				d = 0;
			free(res);
			free(full_res);
			full_res = malloc(sizeof(char) * (ft_strlen(cmd->args[1]) + ft_strlen(tmp) + 1));	
			ft_strncpy(full_res, tmp, ft_strlen(tmp) + 1);

		}
		else if (cmd->args[1][i])
		{
			full_res[d] = cmd->args[1][i];
			i++;
			d++;
		}
	}
	full_res[d] = '\0';
	free(cmd->args[1]);
	cmd->args[1] = full_res;
	full_res = NULL;
}

void	exec_line(t_inst *inst, char *input, int *i, t_env *env)
{
	while (input[*i])
	{
		if (cut_input(&inst, input, i) != 1)
			return ;
		if (cut_instruction(inst, env) != 1)
			return ;
		dollar_expand(inst->cmds, env);
		//builting_detection;
		//print_debug(inst); //delete
		if (inst->cmds->next == NULL)
		{
			if (inst->cmds->builtin > 0)
				simple_builtin(inst->cmds);
			else
				exec_lonely(inst->cmds);
			instclear(inst);
		}
		else
		{
			exec_pipe(inst->cmds);
			instclear(inst);
		}
	}
}

int	main(int argc, char **argv, char *const envp[])
{
	int		exec_ret;
	char	*input;
	int		i;
	t_inst	inst;
	t_env	*env;

	(void)argc;
	(void)argv;
	exec_ret = 0;
	create_env_lst(&env, envp);
	while (exec_ret == 0)
	{
		i = 0;
		input = readline("minishell$> ");
		add_history(input);
		exec_line(&inst, input, &i, env);
	}
	//rl_clear_history();
	return (0);
}
