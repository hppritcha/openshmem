/* For license: see LICENSE file at top-level */

#ifndef _SHMEMC_GLOBALEXIT_H
#define _SHMEMC_GLOBALEXIT_H 1

void shmemc_globalexit_init(void);
void shmemc_globalexit_finalize(void);

void shmemc_trigger_globalexit(int status);

#endif /* ! _SHMEMC_GLOBALEXIT_H */
