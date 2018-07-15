AC_INIT(roll, 2.4.0, matteo@corti.li)
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_FILES(Makefile)
AC_CONFIG_HEADERS(config.h)

AC_PROG_CC
AM_PROG_LEX
AC_PROG_YACC
AC_ISC_POSIX
AM_PROG_CC_C_O

AC_STDC_HEADERS
AC_HAVE_HEADERS(stdio.h getopt.h errno.h string.h strings.h sys/types.h unistd.h limits.h)

AC_CHECK_FUNCS(atol)
AC_CHECK_FUNCS(srandomdev)
AC_CHECK_FUNCS(getpid)
AC_CHECK_FUNCS(qsort)

AC_CHECK_LIB(m, ceil,,[AC_MSG_ERROR([libm not found])])

dnl this macro is used to get the arguments supplied
dnl to the configure script (./configure --enable-debug)
AC_MSG_CHECKING(whether to enable debugging)
debug_default="no"
AC_ARG_ENABLE(debug, [  --enable-debug=[no/yes] turn on debugging [default=no]],, enable_debug=$debug_default)
case "${enable_debug}" in
  yes) CFLAGS="$CFLAGS -g -DDEBUG"; AC_MSG_RESULT(yes) ;;
  no)  AC_MSG_RESULT(no);;
  *) AC_MSG_ERROR(bad value ${enable_debug} for --enable-debug) ;;
esac

AC_SUBST(PACKAGE_DATE, `date "+%Y-%m-%d"`)

AC_OUTPUT(roll.1 VERSION roll.spec)
