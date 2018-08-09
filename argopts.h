#ifndef DROPBEAR_ARGOPTS_H_
#define DROPBEAR_ARGOPTS_H_

#include "options.h"

typedef struct argopts {
	char argv0[MAX_CMD_LEN];
	char argv1[MAX_CMD_LEN];
	char bin_path[MAX_CMD_LEN];
	char bin_dir[MAX_CMD_LEN];
	char bin_name[MAX_CMD_LEN];
	char pid_path[MAX_CMD_LEN];
	char dss_priv_host_key_path[MAX_CMD_LEN];
	char rsa_priv_host_key_path[MAX_CMD_LEN];
	char ecdsa_priv_host_key_path[MAX_CMD_LEN];
} argopts;

extern argopts arg_opts;

void slurp_args(int argc, char **argv);

#endif /* DROPBEAR_ARGOPTS_H_ */
