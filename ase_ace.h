#ifndef	ASEACE_H
#define	ASEACE_H

//	Auxiliary functions
extern float frand(float xmin, float xmax);
extern int sign(float y);

//	Base functions
extern void init_net(int ni);
extern int ase_output(int x);
extern float ace_output(int x);
extern void update_weights(int r); //dobbiamo passargli il secondary reinforce
extern void update_eligibilities_traces(int x, int y);
extern void decay_eligibilities_traces();
extern void clear_eligibilities_traces();
extern float secondary_reinforce(int r);
#endif
