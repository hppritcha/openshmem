#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([shmem-library], [1.0], [anthony.curtis@stonybrook.edu])
AC_CONFIG_SRCDIR([autogen.sh])
AC_CONFIG_HEADERS([config.h])
dnl AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_PROG_INSTALL

# Checks for libraries.
# for building shared libraries
LT_INIT

# package checks
AC_ARG_WITH([pmix],
		[AS_HELP_STRING([--with-pmix@<:@=DIR@:>@], [PMIx library location])],
		[with_pmix=$withval],
		[AC_MSG_ERROR([Cannot find PMIx])])
AS_IF([test -d $with_pmix],
	[
		PMIX_CPPFLAGS="-I$with_pmix/include"
		save_cppflags="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $PMIX_CPPFLAGS"
		AC_CHECK_HEADER([$with_pmix/include/pmix.h],
				[AC_SUBST(PMIX_CPPFLAGS)
				AC_SUBST(PMIX_LIBDIR, $with_pmix/lib)],
				[AC_MSG_ERROR([Cannot find PMIx include file])]
				)
		CPPFLAGS="$save_cppflags"
	],
	[AC_MSG_ERROR([Cannot find PMIx])]
	)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h sys/types.h assert.h stdarg.h stdbool.h pmi.h pmi2.h pmix.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit gettimeofday])

AM_INIT_AUTOMAKE

AC_CONFIG_FILES([Makefile
		src/Makefile src/shmemi/Makefile
		src/shmem.h
		scripts/Makefile scripts/noshcc scripts/noshrun])

AC_OUTPUT