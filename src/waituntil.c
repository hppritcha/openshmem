/* For license: see LICENSE file at top-level */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include "shmemu.h"
#include "shmemc.h"
#include "shmem/defs.h"

#ifdef ENABLE_PSHMEM
#pragma weak shmem_short_wait_until = pshmem_short_wait_until
#define shmem_short_wait_until pshmem_short_wait_until
#pragma weak shmem_int_wait_until = pshmem_int_wait_until
#define shmem_int_wait_until pshmem_int_wait_until
#pragma weak shmem_long_wait_until = pshmem_long_wait_until
#define shmem_long_wait_until pshmem_long_wait_until
#pragma weak shmem_longlong_wait_until = pshmem_longlong_wait_until
#define shmem_longlong_wait_until pshmem_longlong_wait_until
#pragma weak shmem_ushort_wait_until = pshmem_ushort_wait_until
#define shmem_ushort_wait_until pshmem_ushort_wait_until
#pragma weak shmem_uint_wait_until = pshmem_uint_wait_until
#define shmem_uint_wait_until pshmem_uint_wait_until
#pragma weak shmem_ulong_wait_until = pshmem_ulong_wait_until
#define shmem_ulong_wait_until pshmem_ulong_wait_until
#pragma weak shmem_ulonglong_wait_until = pshmem_ulonglong_wait_until
#define shmem_ulonglong_wait_until pshmem_ulonglong_wait_until
#pragma weak shmem_int32_wait_until = pshmem_int32_wait_until
#define shmem_int32_wait_until pshmem_int32_wait_until
#pragma weak shmem_int64_wait_until = pshmem_int64_wait_until
#define shmem_int64_wait_until pshmem_int64_wait_until
#pragma weak shmem_uint32_wait_until = pshmem_uint32_wait_until
#define shmem_uint32_wait_until pshmem_uint32_wait_until
#pragma weak shmem_uint64_wait_until = pshmem_uint64_wait_until
#define shmem_uint64_wait_until pshmem_uint64_wait_until
#pragma weak shmem_size_wait_until = pshmem_size_wait_until
#define shmem_size_wait_until pshmem_size_wait_until
#pragma weak shmem_ptrdiff_wait_until = pshmem_ptrdiff_wait_until
#define shmem_ptrdiff_wait_until pshmem_ptrdiff_wait_until
#endif /* ENABLE_PSHMEM */

/**
 * wait_until with operator dispatchers, type-parameterized.
 */
#define SHMEM_TYPE_WAIT_UNTIL(_opname, _type, _size)                    \
    void                                                                \
    shmem_##_opname##_wait_until(_type *ivar,                           \
                                 shmem_cmp_t cmp,                       \
                                 _type cmp_value)                       \
    {                                                                   \
        switch (cmp) {                                                  \
        case SHMEM_CMP_EQ:                                              \
            shmemc_wait_eq_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        case SHMEM_CMP_NE:                                              \
            shmemc_wait_ne_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        case SHMEM_CMP_GT:                                              \
            shmemc_wait_gt_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        case SHMEM_CMP_LE:                                              \
            shmemc_wait_le_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        case SHMEM_CMP_LT:                                              \
            shmemc_wait_lt_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        case SHMEM_CMP_GE:                                              \
            shmemc_wait_ge_until##_size((int##_size##_t *) ivar,        \
                                        cmp_value);                     \
            break;                                                      \
        default:                                                        \
            logger(LOG_FATAL,                                           \
                   "unknown operator (code %d) in \"%s\"",              \
                   cmp,                                                 \
                   __func__                                             \
                   );                                                   \
            return;                                                     \
            /* NOT REACHED */                                           \
            break;                                                      \
        }                                                               \
    }

SHMEM_TYPE_WAIT_UNTIL(short, short, 16)
SHMEM_TYPE_WAIT_UNTIL(int, int, 32)
SHMEM_TYPE_WAIT_UNTIL(long, long, 64)
SHMEM_TYPE_WAIT_UNTIL(longlong, long long, 64)
SHMEM_TYPE_WAIT_UNTIL(ushort, unsigned short, 16)
SHMEM_TYPE_WAIT_UNTIL(uint, unsigned int, 32)
SHMEM_TYPE_WAIT_UNTIL(ulong, unsigned long, 64)
SHMEM_TYPE_WAIT_UNTIL(ulonglong, unsigned long long, 64)
SHMEM_TYPE_WAIT_UNTIL(int32, int32_t, 32)
SHMEM_TYPE_WAIT_UNTIL(int64, int64_t, 64)
SHMEM_TYPE_WAIT_UNTIL(uint32, uint32_t, 32)
SHMEM_TYPE_WAIT_UNTIL(uint64, uint64_t, 64)
SHMEM_TYPE_WAIT_UNTIL(size, size_t, 64)
SHMEM_TYPE_WAIT_UNTIL(ptrdiff, ptrdiff_t, 64)

#ifdef ENABLE_PSHMEM
#pragma weak shmem_short_wait = pshmem_short_wait
#define shmem_short_wait pshmem_short_wait
#pragma weak shmem_int_wait = pshmem_int_wait
#define shmem_int_wait pshmem_int_wait
#pragma weak shmem_long_wait = pshmem_long_wait
#define shmem_long_wait pshmem_long_wait
#pragma weak shmem_longlong_wait = pshmem_longlong_wait
#define shmem_longlong_wait pshmem_longlong_wait
#pragma weak shmem_ushort_wait = pshmem_ushort_wait
#define shmem_ushort_wait pshmem_ushort_wait
#pragma weak shmem_uint_wait = pshmem_uint_wait
#define shmem_uint_wait pshmem_uint_wait
#pragma weak shmem_ulong_wait = pshmem_ulong_wait
#define shmem_ulong_wait pshmem_ulong_wait
#pragma weak shmem_ulonglong_wait = pshmem_ulonglong_wait
#define shmem_ulonglong_wait pshmem_ulonglong_wait
#pragma weak shmem_int32_wait = pshmem_int32_wait
#define shmem_int32_wait pshmem_int32_wait
#pragma weak shmem_int64_wait = pshmem_int64_wait
#define shmem_int64_wait pshmem_int64_wait
#pragma weak shmem_uint32_wait = pshmem_uint32_wait
#define shmem_uint32_wait pshmem_uint32_wait
#pragma weak shmem_uint64_wait = pshmem_uint64_wait
#define shmem_uint64_wait pshmem_uint64_wait
#pragma weak shmem_size_wait = pshmem_size_wait
#define shmem_size_wait pshmem_size_wait
#pragma weak shmem_ptrdiff_wait = pshmem_ptrdiff_wait
#define shmem_ptrdiff_wait pshmem_ptrdiff_wait
#endif /* ENABLE_PSHMEM */

/**
 * deprecated @ 1.4
 *
 * wait is just wait_until with inequality/change test
 */

#define SHMEM_TYPE_WAIT(_name, _type, _size)                            \
    void                                                                \
    shmem_##_name##_wait(_type *ivar, _type cmp_value)                  \
    {                                                                   \
        deprecate(__func__);                                            \
        shmemc_wait_ne_until##_size((int##_size##_t *) ivar, cmp_value); \
    }


SHMEM_TYPE_WAIT(short, short, 16)
SHMEM_TYPE_WAIT(int, int, 32)
SHMEM_TYPE_WAIT(long, long, 64)
SHMEM_TYPE_WAIT(longlong, long long, 64)
SHMEM_TYPE_WAIT(ushort, unsigned short, 16)
SHMEM_TYPE_WAIT(uint, unsigned int, 32)
SHMEM_TYPE_WAIT(ulong, unsigned long, 64)
SHMEM_TYPE_WAIT(ulonglong, unsigned long long, 64)
SHMEM_TYPE_WAIT(int32, int32_t, 32)
SHMEM_TYPE_WAIT(int64, int64_t, 64)
SHMEM_TYPE_WAIT(uint32, uint32_t, 32)
SHMEM_TYPE_WAIT(uint64, uint64_t, 64)
SHMEM_TYPE_WAIT(size, size_t, 64)
SHMEM_TYPE_WAIT(ptrdiff, ptrdiff_t, 64)
