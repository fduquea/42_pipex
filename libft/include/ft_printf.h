/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:56:43 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/02 11:18:01 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		param_detector(va_list args, char c);
int		param_string(char *string);
int		param_pointer(unsigned long long ptr);
int		param_decimal(int proof);
int		param_unsdecimal(unsigned int num);
int		param_hex(unsigned int num, char c);
int		param_char(char character);
int		hex_len(unsigned int num);
void	ft_print_hex(unsigned int num, const char c);

#endif // FT_PRINTF_H