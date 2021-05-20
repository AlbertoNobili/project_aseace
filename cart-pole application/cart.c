// Physical constants
#define LEFT_LIMIT	-3.0	// position of left block [m]
#define RIGHT_LIMIT	3.0		// position of right block [m]
#define THETA_LIMIT	0.2		// 0.2 rad = 11.5 deg
#define CART_MASS	1.0		// mass of the cart [kg]
#define POLE_MASS	0.1		// mass of the pole [kg]
#define POLE_LEN	0.5		// length of the pole [m]
#define FORCE		10		// force level [N]
#define GRAVITY		9.8		// [m/s^2]

// simulation constants
#define MAXDUR		4000000L	// max duration
#define MAXFAIL		1000000L	// max # of failures
#define NBOXES		162			// # of state boxes

// Cart structure
typedef struct{
	float pos;
	float speed;
	float theta;
	float omega;
} state;
static state s;

//Auxiliary functions
void set_state(float x, float v, float t, float w)
{
	s.pos = x;
	s.speed = v;
	s.theta = t;
	s.omega = w;
}

int out_limits()
{
	if ((s.pos > RIGHT_LIMIT) || (s.pos < LEFT_LIMIT) || 
		(fabs(s.theta) > THETA_LIMIT))	return 1;
	return 0;
}

// Update state
int update_state(float force)
{
	float ct, st, dt;		// sin, cos, integration step
	float x_acc, t_acc;		// linear & angular acceleration

		ct = cos(s.theta);
		st = sin(s.theta);
		t_acc = ((CART_MASS + POLE_MASS)*GRAVITY*st - 
					(FORCE+POLE_MASS*POLE_LEN*s.omega*s.omega*st)*ct)/
					(4/3*(CART_MASS+POLE_MASS)*POLE_LEN-POLE_MASS*POLE_LEN*ct*ct);
		x_acc = (FORCE + POLE_MASS*POLE_LEN*(s.omega*s.omega*st-t_acc*ct))/(POLE_MASS+CART_MASS);
		dt = 0.01;			// integration step of 10 ms
		s.pos   += s.speed*dt;
		s.speed += x_acc*dt;
		s.theta += s.omega*dt;
		s.omega += t_acc*dt;
		return out_limits();
}

// Decode state
#define XL	0.8
#define VL	0.5
#define T1	0.01745
#define T6	0.10472
#define W50	0.87266

// first option
int decode_state()
{
int box;

	if (s.pos < -XL)		box = 0;
	else if (s.pos < XL)	box = 1;
	else 					box = 2;

	if (s.speed < -VL)		;
	else if (s.speed < VL)	box +=3;
	else					box += 6;	

	if (s.theta < -T6)		;
	else if (s.theta <-T1)	box += 9;
	else if (s.theta < 0)	box += 18;
	else if (s.theta < T1)	box += 27;
	else if (s.theta < T6)	box += 36;
	else 					box += 45;

	if (s.omega < -W50)		;
	else if (s.omega < W50)	box += 54;
	else					box += 108;

	return box;
}

// second option