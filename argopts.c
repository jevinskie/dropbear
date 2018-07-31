#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "argopts.h"
#include "options.h"
#include "dbutil.h"

argopts arg_opts;

#if DEBUG_TRACE
void dump_arg_opts(void) {
    TRACE(("\targ_opts->argv0: '%s'", arg_opts.argv0))
    TRACE(("\targ_opts->argv1: '%s'", arg_opts.argv1))
    TRACE(("\targ_opts->bin_path: '%s'", arg_opts.bin_path))
    TRACE(("\targ_opts->bin_dir: '%s'", arg_opts.bin_dir))
    TRACE(("\targ_opts->pid_path: '%s'", arg_opts.pid_path))
    TRACE(("\targ_opts->dss_priv_host_key_path: '%s'", arg_opts.dss_priv_host_key_path))
    TRACE(("\targ_opts->rsa_priv_host_key_path: '%s'", arg_opts.rsa_priv_host_key_path))
    TRACE(("\targ_opts->ecdsa_priv_host_key_path: '%s'", arg_opts.ecdsa_priv_host_key_path))
}
#endif

void slurp_args(int argc, const char **argv) {

#if DEBUG_TRACE
    for (int i = 0; i < argc; i++) {
        if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] == 'v') {
            debug_trace = 1;
        }
    }
#endif

#if DEBUG_TRACE
    TRACE(("arg_opts before slurp_args():"));
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

#if DEBUG_TRACE
    TRACE(("arg_opts before slurp_args():"));
    dump_arg_opts();
#endif

    return;
}
