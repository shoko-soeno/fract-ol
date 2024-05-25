#include "./minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define KEY_ESC 53
#define WIDTH 800
#define HEIGHT 600

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_vars {
    void    *mlx;
    void    *win;
	int     pos_x;
	int     pos_y;
	int		radius;
    t_data  img;
}               t_vars;

/*****************************************************************************/

// /* 色の各成分（透明度 t、赤 r、緑 g、青 b）を受け取り、それらを単一の整数にエンコード
// 関数内部では、バイト配列にこれらの値を順序付けて格納し、その配列を整数型として解釈して返す
// ここでの格納順序は b, g, r, t  これはメモリにおけるエンディアン（バイトの順序）に依存する*/
// int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
// {
// 	return (*(int *)(unsigned char [4]){b, g, r, t});
// }

// int	get_t(int trgb)
// {
// 	return ((trgb >> 24) & 0xFF);
// }

// int	get_r(int trgb)
// {
// 	return ((trgb >> 16) & 0xFF);
// }

// int	get_g(int trgb)
// {
// 	return ((trgb >> 8) & 0xFF);
// }

// int	get_b(int trgb)
// {
// 	return (trgb & 0xFF);
// }

// int	add_shade(double distance, int color)
// {
// 	if (distance < 0) distance = 0;
// 	if (distance > 1) distance = 1;

// 	//extract each color component
// 	int r = (color >> 16) & 0xFF;
// 	int g = (color >> 8) & 0xFF;
// 	int b = color & 0xFF;

// 	//calculate the new color components
// 	r = (int)(r * (1 - distance));
// 	g = (int)(g * (1 - distance));
// 	b = (int)(b * (1 - distance));

// 	//reassemble color
// 	return (color & 0xFF000000) | (r << 16) | (g << 8) | b;
// }

// int get_opposite(int color) {
// 	// Extract each color component
// 	int r = (color >> 16) & 0xFF;
// 	int g = (color >> 8) & 0xFF;
// 	int b = color & 0xFF;

// 	// Invert each color component
// 	r = 255 - r;
// 	g = 255 - g;
// 	b = 255 - b;

// 	// Reassemble the color
// 	return (color & 0xFF000000) | (r << 16) | (g << 8) | b;
// }

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	close_window(t_vars *vars) {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	exit(0);  // プログラムを終了させる
// }

// int	key_hook(int keycode, t_vars *vars)
// {
// 	(void)*vars;
// 	if (keycode == KEY_ESC) {
// 		return close_window(vars);
// 	}
// 	printf("Keycode %d received in key_hook!\n", keycode);
// 	return (0);
// }

// int	main(void)
// {
// 	// void	*mlx;
// 	// void	*mlx_win;
// 	// t_data	img;
// 	t_vars	vars;

// 	vars.mlx = mlx_init(); //mlxの初期化
// 	if (vars.mlx == 0)
// 		return (1);

// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!"); //windowの作成
// 	if (vars.win == 0){
// 		printf("failed to create window");
// 		return (1);
// 	}

// 	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080); // 画像の作成
// 	if (vars.img.img == NULL) {
// 		printf("Failed to create image\n");
// 		return (1);
// 	}

// 	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
// 								&vars.img.endian);
// 	my_mlx_pixel_put(&vars.img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);

// 	int blue_color = 0x0000FF;

// 	int rect_width = 300;
//     int rect_height = 200;
//     int start_x = 100; // x coordinate of the top-left corner
//     int start_y = 100; // y coordinate of the top-left corner

// 	for (int y = start_y; y < start_y + rect_height; y++) {
//         for (int x = start_x; x < start_x + rect_width; x++) {
//             mlx_pixel_put(vars.mlx, vars.win, x, y, blue_color);
//         }
//     }
// 	mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_loop(vars.mlx);
// }

/*****************************************************************************/
// typedef struct  s_vars {
//     void    *mlx;
//     void    *win;
//     int     pos_x;
//     int     pos_y;
// }               t_vars;

// int render_next_frame(void *param) {
//     t_vars *vars = param;

//     // Clear the window (by drawing a black rectangle over it)
//     mlx_clear_window(vars->mlx, vars->win);

//     // Draw a circle at the current position
//     mlx_string_put(vars->mlx, vars->win, vars->pos_x, vars->pos_y, 0xFFFFFF, "O");

//     return 0;
// }

// int key_hook(int keycode, t_vars *vars) {
//     printf("Keycode: %d\n", keycode);
//     switch (keycode) {
//         case 13:  // W
//             vars->pos_y -= 10;
//             break;
//         case 0:   // A
//             vars->pos_x -= 10;
//             break;
//         case 1:   // S
//             vars->pos_y += 10;
//             break;
//         case 2:   // D
//             vars->pos_x += 10;
//             break;
//         default:
//             break;
//     }
//     return 0;
// }

// int main(void) {
//     t_vars vars;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniLibX Circle Movement");
//     vars.pos_x = WIDTH / 2;
//     vars.pos_y = HEIGHT / 2;

//     mlx_key_hook(vars.win, key_hook, &vars);
//     mlx_loop_hook(vars.mlx, render_next_frame, &vars);
//     mlx_loop(vars.mlx);

//     return 0;
// }
/*****************************************************************************/

/* Bresenham 第1オクタントの1/8円は、円の中心から右上方向に45度の範囲
この範囲内ではx座標のほうが常にy座標以上か等しいから */
void	draw_circle(t_vars *vars, int x0, int y0, int radius, int color) {
    int x = radius; //xの初期値が半径
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) //xがyよりも大きいか等しい間=第1オクタントの1/8円が描かれるまで
	{ //現在の(x,y) に基づいて8つの対称点を描画します。
        mlx_pixel_put(vars->mlx, vars->win, x + x0, y + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, y + x0, x + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, -x + x0, y + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, -y + x0, x + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, -x + x0, -y + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, -y + x0, -x + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, x + x0, -y + y0, color);
        mlx_pixel_put(vars->mlx, vars->win, y + x0, -x + y0, color);
        y++; //yを1増やします（垂直方向に移動）

        if (radiusError < 0) //誤差の更新: radiusErrorが0未満の場合はyを1増やす
		{
            radiusError += 2 * y + 1;
        } else { //それ以外の場合はxを1減らし、radiusErrorも更新する
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void draw_circle_sqrt(t_vars *vars, int x0, int y0, int radius, int color) {
    for (int x = -radius; x <= radius; x++) {
        int height = (int)sqrt(radius * radius - x * x);
		// 内部の塗りつぶしは行わない。
        // for (int y = -height; y <= height; y++) {
        //     mlx_pixel_put(vars->mlx, vars->win, x + x0, y + y0, color);
        // }
		mlx_pixel_put(vars->mlx, vars->win, x + x0, height + y0, color);  // 上の円周
        mlx_pixel_put(vars->mlx, vars->win, x + x0, -height + y0, color); // 下の円周
    }
}

int render_next_frame(void *param) {
    t_vars *vars = param;

    mlx_clear_window(vars->mlx, vars->win);
    draw_circle(vars, vars->pos_x - 100, vars->pos_y,  vars->radius, 0xFFFFFF);  // 半径を50に設定
	draw_circle_sqrt(vars, vars->pos_x + 100, vars->pos_y, vars->radius, 0xFFFFFF);  // 右側にsqrtを使った円
    return 0;
}

int key_hook(int keycode, t_vars *vars) {
    switch (keycode) {
        case 13: // W
            vars->pos_y -= 10;
            break;
        case 0: // A
            vars->pos_x -= 10;
            break;
        case 1: // S
            vars->pos_y += 10;
            break;
        case 2: // D
            vars->pos_x += 10;
            break;
        case 7: // キー 'x'
            vars->radius += 10;
            break;
        case 6: // キー 'z'
            vars->radius = (vars->radius > 5) ? vars->radius - 10 : 10;
            break;
    }
    return 0;
}

int main(void) {
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniLibX Circle Movement");
    vars.pos_x = WIDTH / 2;
    vars.pos_y = HEIGHT / 2;
	vars.radius = 100;

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop_hook(vars.mlx, render_next_frame, &vars);
    mlx_loop(vars.mlx);

    return 0;
}
