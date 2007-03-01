AC_INIT(roll, 1.0.2, matteo.corti@gmail.com)
AM_INIT_AUTOMAKE(roll, 1.0.2, matteo.corti@gmail.com)
AC_CONFIG_FILES(Makefile)
AC_CONFIG_HEADERS(config.h)

AC_PROG_CC
AM_PROG_LEX
AC_PROG_YACC
AC_ISC_POSIX

AC_STDC_HEADERS
AC_HAVE_HEADERS(stdio.h getopt.h errno.h string.h strings.h sys/types.h unistd.h)

AC_CHECK_FUNCS(srandomdev)
AC_CHECK_FUNCS(getpid)

dnl this macro is used to get the arguments supplied
dnl to the configure script (./configure --enable-debug)
AC_MSG_CHECKING(whether to enable debugging)
debug_default="no"
AC_ARG_ENABLE(debug, [  --enable-debug=[no/yes] turn on debugging [default=yes]],, enable_debug=$debug_default)
case "${enable_debug}" in
  yes) CFLAGS="$CFLAGS -g -DDEBUG"; AC_MSG_RESULT(yes) ;;
  no)  AC_MSG_RESULT(no);;
  *) AC_MSG_ERROR(bad value ${enable_debug} for --enable-debug) ;;
esac

AC_OUTPUT(roll.1 VERSION)
