/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:24:05 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 14:39:59 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// - X11 screen
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// - X11 image
# define IMG_WIDTH 960
# define IMG_HEIGHT 540
# define IMG_W_POS_COEFF 0.15
# define IMG_H_POS_COEFF 0.15
# define STD_PXL_COLOR "0xFFFFFF"

// - X11 events
# define ON_DESTROY 17
# define MLX_MASK 0

// - X11 key codes
# define X11LINUX_ESC 65307
# define X11MACOS_ESC 53

// - Initial matrix byte-size
# define MATRIX_SIZE 512

#endif
