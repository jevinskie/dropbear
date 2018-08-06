#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "argopts.h"
#include "options.h"

argopts arg_opts;

#if defined(DEBUG_TRACE) && !defined(DBMULTI_sftpserver)
void dump_arg_opts(void) {
    fprintf(stderr, "\targ_opts->argv0: '%s'\n", arg_opts.argv0);
    fprintf(stderr, "\targ_opts->argv1: '%s'\n", arg_opts.argv1);
    fprintf(stderr, "\targ_opts->bin_path: '%s'\n", arg_opts.bin_path);
    fprintf(stderr, "\targ_opts->bin_dir: '%s'\n", arg_opts.bin_dir);
    fprintf(stderr, "\targ_opts->pid_path: '%s'\n", arg_opts.pid_path);
    fprintf(stderr, "\targ_opts->dss_priv_host_key_path: '%s'\n", arg_opts.dss_priv_host_key_path);
    fprintf(stderr, "\targ_opts->rsa_priv_host_key_path: '%s'\n", arg_opts.rsa_priv_host_key_path);
    fprintf(stderr, "\targ_opts->ecdsa_priv_host_key_path: '%s'\n", arg_opts.ecdsa_priv_host_key_path);
}
#endif

void slurp_args(int argc, char **argv) {

#if defined(DEBUG_TRACE) && !defined(DBMULTI_sftpserver)
    fprintf(stderr, "arg_opts before slurp_args():\n");
    dump_arg_opts();
#endif

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

#if defined(DEBUG_TRACE) && !defined(DBMULTI_sftpserver)
    fprintf(stderr, "arg_opts before slurp_args():\n");
    dump_arg_opts();
#endif

    return;
}
