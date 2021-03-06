/* For license: see LICENSE file at top-level */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include "state.h"
#include "shmemu.h"
#include "shmemc.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/time.h>
#include <assert.h>
#include <ctype.h>

#define TRACE_MSG_BUF_SIZE 256

static FILE *log_stream = NULL;
static bool logging = false;
static char *host = NULL;

typedef struct shmemu_log_table {
    shmemu_log_t level;
    char *name;
} shmemu_log_table_t;

#define LOG_LEVEL_EMIT(_level) { LOG_##_level, #_level }

static shmemu_log_table_t table[] =
    {
        LOG_LEVEL_EMIT(FATAL),
        LOG_LEVEL_EMIT(INIT),
        LOG_LEVEL_EMIT(FINALIZE),
        LOG_LEVEL_EMIT(MEMORY),
        LOG_LEVEL_EMIT(HEAP),
        LOG_LEVEL_EMIT(WORKER),
        LOG_LEVEL_EMIT(INFO),
        LOG_LEVEL_EMIT(REDUCTION),
        LOG_LEVEL_EMIT(BARRIER),
        LOG_LEVEL_EMIT(DEPRECATE),
        LOG_LEVEL_EMIT(LOCK),
        LOG_LEVEL_EMIT(UNKNOWN)
    };

static char *
level_to_name(shmemu_log_t level)
{
    shmemu_log_table_t *tp = table;

    while (tp->level != LOG_UNKNOWN) {
        if (level == tp->level) {
            return tp->name;
            /* NOT REACHED */
        }
        tp += 1;
    }

    return "UNKNOWN";
}

static shmemu_log_t
name_to_level(const char *name)
{
    shmemu_log_table_t *tp = table;

    while (tp->level != LOG_UNKNOWN) {
        if (strncmp(name, tp->name, strlen(tp->name)) == 0) {
            return tp->level;
            /* NOT REACHED */
        }
        tp += 1;
    }

    return LOG_UNKNOWN;
}

/*
 * for private use before up and running
 */
static void
fatal(const char *fmt, ...)
{
        va_list ap;

        va_start(ap, fmt);
        {
            fprintf(stderr, "FATAL: ");
            vfprintf(stderr, fmt, ap);
            fprintf(stderr, "\n");
            fflush(stderr);
        }
        va_end(ap);

        exit(EXIT_FAILURE);
}

void
shmemu_logger_init(void)
{
    /* enable if: "y[es]", "on" or positive number */
    if (proc.env.debug) {

        host = shmemu_gethostname();
        assert(host != NULL);

        /* TODO "%" modifiers for extra info */
        if (proc.env.debug_file != NULL) {
            log_stream = fopen(proc.env.debug_file, "a");
            if (log_stream == NULL) {
                fatal("can't open debug log file \"%s\"",
                      proc.env.debug_file);
                /* NOT REACHED */
            }
        }
        else {
            log_stream = stderr;
        }
    }
}

void
shmemu_logger_finalize(void)
{
    if (! proc.env.debug) {
        return;
    }

    if (log_stream != NULL) {
        fclose(log_stream);
    }
}

void
shmemu_logger(shmemu_log_t level, const char *fmt, ...)
{
    if (logging) {
        char *tmp1;
        char *tmp2;
        va_list ap;

        tmp1 = (char *) malloc(TRACE_MSG_BUF_SIZE * sizeof(*tmp1));
        assert(tmp1 != NULL);
        tmp2 = (char *) malloc(TRACE_MSG_BUF_SIZE * sizeof(*tmp2));
        assert(tmp2 != NULL);

        snprintf(tmp1, TRACE_MSG_BUF_SIZE,
                 "[%s:%d:%d:%6.6f] %10s: ",
                 host,
                 proc.rank,
                 (int) getpid(),
                 shmemu_timer(),
                 level_to_name(level)
                 );

        va_start(ap, fmt);
        vsnprintf(tmp2, TRACE_MSG_BUF_SIZE, fmt, ap);
        va_end(ap);

        strncat(tmp1, tmp2, strlen(tmp2));
        strncat(tmp1, "\n", 1);

        fputs(tmp1, log_stream);
        /* make sure this all goes out in 1 burst */
        fflush(log_stream);

        free(tmp2);
        free(tmp1);

        if (level == LOG_FATAL) {
            exit(1);            /* maybe not just exit... */
        }
    }
}
