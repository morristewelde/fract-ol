/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 03:57:09 by mtewelde          #+#    #+#             */
/*   Updated: 2024/10/28 18:33:33 by mtewelde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map_s(double old_n, double new_mn, double new_mx, double old_mx)
{
	return (((new_mx - new_mn) * old_n / (old_mx)) + new_mn);
}
