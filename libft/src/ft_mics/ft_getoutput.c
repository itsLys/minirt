/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getoutput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 10:49:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 11:04:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

#define CHILD_PROC 0
char	*ft_getoutput(char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	char	*output;
	int		bytes_read;

	if (pipe(pipefd) == ERROR)
		return NULL;
	pid = fork();
	if (pid == CHILD_PROC)
	{
		dup2(pipefd[STDOUT_FILENO], STDOUT_FILENO);
		ft_execvpe(argv[0], argv, envp);
	}
	output = malloc(PIPE_BUF + 1);
	if (output == NULL)
		return NULL;
	bytes_read = read(pipefd[STDIN_FILENO], output, PIPE_BUF);
	if (bytes_read == ERROR)
		return free(output), NULL;
	output[bytes_read] = 0;
	return (output);
}
