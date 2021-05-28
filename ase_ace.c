#include <stdlib.h>
#include <stdio.h>

// Global constant
#define MAXINP      256     // maximum number of input units
#define ASE_ETA0    10.0    // ASE default learning rate
#define ASE_DECAY0  0.85    // ASE default eligibility
#define ACE_ETA0    0.5     // ACE default learning rate
#define ACE_DECAY0  0.4     // ACE default trace
#define GAMMA0      0.95    // default prediction discount

//Global variables
static float 	ws[MAXINP];		// ASE weights
static float 	wc[MAXINP];		// ACE weights

static int		x[MAXINP];		// input vector
static float    eligi[MAXINP];	// ASE eligibility vector
static float	trace[MAXINP];	// ACE trace vector

static float	ase_eta;	// ASE learning rate (alfa)
static float	ase_decay;	// ASE eligibility decay (delta)
static float	ace_eta;	// ACE learning rate (beta)
static float	ace_decay;	// ACE trace decay (lambda)
static float 	discount;	// ACE prediction discount (gamma)

static int		ninputs;	// # of input units
static int		r;			// primary reinforcement
static int		y;			// ASE output
static float	p;			// ACE output

// Auxiliary functions
float frand(float xmin, float xmax)
{
float range;
	range = (xmax -xmin);
	return xmin + range*rand()/(float)RAND_MAX;
}

int sign(float y)
{
	if (y > 0) return 1;
	return -1;
}

//Basic functions
void init_net(int ni)
{
int i;

	ninputs = ni;
	for (i=0; i<ni; i++)
		ws[i] = wc[i] = 0.0;
	ase_eta = ASE_ETA0;
	ace_eta = ACE_ETA0;
	ase_decay = ASE_DECAY0;
	ace_decay = ACE_DECAY0;
	discount = GAMMA0;
}

int ase_output(int x)
{
float net;
int y, temp;

	net = ws[x] + frand(-0.7, 0.7);
	temp = sign(ws[x]);
	y = sign(net);
	//printf("y = %d, temp = %d\n", y, temp);
	return y;
}

float ace_output(int x)
{
	return wc[x];
}

void update_weights(int r) //dobbiamo passargli il secondary reinforce
{
int i;

	for (i=0; i<ninputs; i++){
		ws[i] += r * ase_eta * eligi[i];
		wc[i] += r * ace_eta * trace[i];
	}
}

void update_eligibilities_traces(int x, int y){
	eligi[x] += (1.0 - ase_decay) * y;
	trace[x] += (1.0 - ace_decay);
}

void decay_eligibilities_traces()
{
int i;

	for(i=0; i<ninputs; i++){
		eligi[i] = ase_decay * eligi[i];
		trace[i] = ace_decay * trace[i];
	}
}

void clear_eligibilities_traces()
{
int i;

	for (i=0; i<ninputs; i++)
		eligi[i] = trace[i] = 0.0;
}

float secondary_reinforce(int r)
{
static float oldp;
float sr;

	sr = r + discount*p - oldp;
	oldp = p;
	return sr;
}