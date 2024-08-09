/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:24:05 by rmei              #+#    #+#             */
/*   Updated: 2024/08/09 20:14:49 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// - X11 screen
# define W_WIDTH 1280
# define W_HEIGHT 720

// - X11 image
# define I_WIDTH 1024
# define I_HEIGHT 576
# define IX_POS 0.10
# define IY_POS 0.10

// - Render details
# define BG_COLOR "0x800000"
# define PXL_WHITE "0xFFFFFF"

// - X11 events
# define ON_DESTROY 17
# define MLX_MASK 0

// - X11 key codes
# define X11LINUX_ESC 65307
# define X11MACOS_ESC 53

// - Boolean values
# define TRUE 1
# define FALSE 0

#endif
