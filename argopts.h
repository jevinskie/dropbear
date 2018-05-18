#ifndef DROPBEAR_ARGOPTS_H_
#define DROPBEAR_ARGOPTS_H_

typedef struct argopts {
	const char *argv0;
	const char *argv1;
	const char *bin_path;
	const char *bin_dir;
} argopts;

extern argopts arg_opts;

void slurp_args(int argc, const char **argv);

#endif /* DROPBEAR_ARGOPTS_H_ */
