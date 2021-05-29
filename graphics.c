#include <allegro.h>
#include <math.h>
#include <stdio.h>

// Nota: 1 cm = 2 pixel
#define XWIN	1400	// windows width
#define YWIN	260		// windows height
#define XBIT	1300	// bitmap width	
#define YBIT	180		// bitmap height
#define BLK		0		// black color
#define WHITE	15		// white color
#define RED		12		// red color
#define GREEN	10		// green color
#define BLUE	9		// blue color
#define CYAN	11		// cyan color
#define GREY	8		// grey color
#define CARTH	40		// cart height [px]
#define CARTL	100		// cart width [px]
#define CARTB	160		// cart bottom y coordinate in the bitmap [px]
#define CARTU	120		// cart top y coordinate in the bitmap [px]
#define OFFSET	650		// offset to map 0m of real world in the centre of the bitmap [px]
#define RADIUS	10		// wheel radius [px]
#define WHEELH	170		// wheel center y choord [px]
#define DIST	30		// x dist from cart center to wheel center [px]
#define LENGTH	100		// pole length [px]

// Global variables used in cart.c
extern int view;		// to know when display the cart evolution
extern int stop;		// to know when to stop 

// Structure used to describe the cart state
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
