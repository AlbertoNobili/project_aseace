#include <allegro.h>
#include <math.h>
#include <stdio.h>
#include "kbfunc.h"

// Nota: 1 cm = 2 pixel
#define XWIN	1400
#define YWIN	260
#define XBIT	1300
#define YBIT	180
#define BLK		0
#define WHITE	15
#define RED		12
#define GREEN	10
#define BLUE	9
#define CYAN	11
#define GREY	8
#define CARTH	40
#define CARTL	100
#define CARTB	160
#define CARTU	120
#define OFFSET	650
#define RADIUS	10		//wheel radius [px]
#define WHEELH	170		//wheel center y choord [px]
#define DIST	30		//x dist from cart center to wheel center [px]
#define LENGTH	100		//pole length [px]

extern int view;
extern int stop;

typedef struct{
	float pos;
	float speed;
	float theta;
	float omega;
} state;


void display_cart(state s)
{
int x, xpole, ypole;
BITMAP* buf;

	x = s.pos*200+OFFSET; //centro del cart in coordinate pixel
	//usiamo la bitmap come buffer
	buf = create_bitmap(XBIT, YBIT);
	//cancelliamo il cart precedente
	clear_to_color(buf, BLK);
	//draw body
	rectfill(buf, x-CARTL/2-50, CARTU, x+CARTL/2, CARTB, CYAN);
	//draw wheels
	circlefill(buf, x+DIST, WHEELH, RADIUS, BLUE);
	circlefill(buf, x-DIST, WHEELH, RADIUS, BLUE);
	//draw pole
	xpole = x + sin(s.theta)*LENGTH;
	ypole = CARTU - cos(s.theta)*LENGTH;
	line(screen, x, CARTU, xpole, ypole, GREY);
	circlefill(screen, xpole, ypole, RADIUS, GREY);
	//ricopiamo la bitmap
	blit(buf, screen, 0, 0, 50, 20, buf->w, buf->h);

	return;
}

void update_info(long epoch, long maxd)
{
char s[50];
	sprintf(s, "Epoch = %ld; Max duration = %ld", epoch, maxd);
	textout_centre_ex(screen, font, s,XWIN/2, 10, WHITE, BLK);
}

void init_graphics()
{

	allegro_init();
	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
	clear_to_color(screen, BLK);
	install_keyboard();
	
	srand(time(NULL));

	//draw limits
	rectfill(screen, 0, 80, 50, 200, RED);
	rectfill(screen, XWIN-50, 80, XWIN, 200, RED);
	//draw bottom
	rectfill(screen, 0, 200, XWIN, YWIN, GREEN);

	return;
}

void terminate_graphics(){
	allegro_exit();
}

char get_scancode_nb ()
{
char c;

	if (keypressed()){
		c = readkey();
		printf("carattere premuto:%c\n", c);
		return c;
	}else 
		return 0;
}

void read_key()
{
char c;
	c = get_scancode_nb();
	if (c == 'v')
		view = (view==1)? 0:1;
	else if (c == 'q')
		stop = 1;
}
