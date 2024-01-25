/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:25:49 by amalangi          #+#    #+#             */
/*   Updated: 2024/01/24 20:53:30 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	g_bitcontrol;

int	verify_process_id(int pid)
{
	if (!pid)
	{
		ft_printf("Invalid process id: %d\n", pid);
		exit(1);
	}
	if (kill(pid, 0) < 0)
	{
		ft_printf("Error with process id: %d, cannot send signal\n", pid);
		exit(1);
	}
	return (pid);
}

void	diplay_character(char c, pid_t pid)
{
	int			bit;

	bit = 7;
	while (bit >= 0)
	{
		verify_process_id(pid);
		g_bitcontrol = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_bitcontrol != 1)
			usleep(600);
		bit--;
	}
}

void	diplay_string(char *str, pid_t pid)
{
	int	index;

	index = 0;
	while (str[index])
	{
		diplay_character(str[index], pid);
		index++;
	}
	diplay_character(0, pid);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_bitcontrol = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("Message received successfully!\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	process_id;

	if (argc != 3)
	{
		ft_printf("Error: Arguments is missing !");
		exit(1);
	}
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	process_id = ft_atoi(argv[1]);
	verify_process_id(ft_atoi(argv[1]));
	diplay_string(argv[2], process_id);
	while (1)
		sleep(1);
	return (0);
}
