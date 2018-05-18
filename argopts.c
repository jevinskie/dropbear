#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "argopts.h"
#include "default_options.h"

argopts arg_opts;

void dump_arg_opts(void) {
	printf("argv0: '%s'\n", arg_opts.argv0);
	printf("argv1: '%s'\n", arg_opts.argv1);
	printf("bin_path: '%s'\n", arg_opts.bin_path);
	printf("bin_dir: '%s'\n", arg_opts.bin_dir);
	printf("pid_path: '%s'\n", arg_opts.pid_path);
	printf("dss_priv_host_key_path: '%s'\n", arg_opts.dss_priv_host_key_path);
	printf("rsa_priv_host_key_path: '%s'\n", arg_opts.rsa_priv_host_key_path);
	printf("ecdsa_priv_host_key_path: '%s'\n", arg_opts.ecdsa_priv_host_key_path);
}

void slurp_args(int argc, const char **argv) {

	printf("slurp_args before:\n");
	dump_arg_opts();

	if (!strlen(arg_opts.argv0)) {
		strcpy(arg_opts.argv0, argv[0]);
		if (argc > 1) {
			strcpy(arg_opts.argv1, argv[1]);
		}
		realpath(argv[0], arg_opts.bin_path);
		strcpy(arg_opts.bin_dir, arg_opts.bin_path);
		char *bin_dir_last_slash = strrchr(arg_opts.bin_dir, '/');
		assert(bin_dir_last_slash != &arg_opts.bin_dir[0]);
		*bin_dir_last_slash = '\0';
		snprintf(arg_opts.pid_path, sizeof(arg_opts.pid_path), "%s/%s", arg_opts.bin_dir, DROPBEAR_PIDFILE_BASE);
		snprintf(arg_opts.dss_priv_host_key_path, sizeof(arg_opts.dss_priv_host_key_path), "%s/%s", arg_opts.bin_dir, DSS_PRIV_FILENAME_BASE);
		snprintf(arg_opts.rsa_priv_host_key_path, sizeof(arg_opts.rsa_priv_host_key_path), "%s/%s", arg_opts.bin_dir, RSA_PRIV_FILENAME_BASE);
		snprintf(arg_opts.ecdsa_priv_host_key_path, sizeof(arg_opts.ecdsa_priv_host_key_path), "%s/%s", arg_opts.bin_dir, ECDSA_PRIV_FILENAME_BASE);

	}

	printf("slurp_args after:\n");
	dump_arg_opts();

	return;
}
