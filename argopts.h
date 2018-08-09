#ifndef DROPBEAR_ARGOPTS_H_
#define DROPBEAR_ARGOPTS_H_

#include <limits.h>

typedef struct argopts {
	char argv0[PATH_MAX];
	char argv1[PATH_MAX];
	char bin_path[PATH_MAX];
	char bin_dir[PATH_MAX];
	char bin_name[PATH_MAX];
	char pid_path[PATH_MAX];
	char dss_priv_host_key_path[PATH_MAX];
	char rsa_priv_host_key_path[PATH_MAX];
	char ecdsa_priv_host_key_path[PATH_MAX];
} argopts;

extern argopts arg_opts;

void slurp_args(int argc, char **argv);

#endif /* DROPBEAR_ARGOPTS_H_ */
