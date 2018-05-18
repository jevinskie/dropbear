#include <stdlib.h>

#include "argopts.h"

argopts arg_opts;

void slurp_args(int argc, const char **argv) {
	if (!arg_opts.argv0) {
		arg_opts.argv0 = argv[0];
		if (argc > 1) {
			arg_opts.argv1 = argv[1];
		}
		arg_opts.bin_path = realpath(argv[0], NULL);
		arg_opts.bin_dir = dirname(arg_opts.bin_path);
	}
	return;
}
