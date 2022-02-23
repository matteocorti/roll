AC_INIT([roll],[2.6.1],[matteo@corti.li])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_FILES(Makefile)
AC_CONFIG_HEADERS(config.h)
AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_PROG_CC
AC_PROG_LEX([noyywrap])
AC_PROG_YACC
AM_PROG_CC_C_O

AC_CHECK_HEADERS(stdio.h getopt.h errno.h string.h strings.h sys/types.h unistd.h limits.h)

AC_CHECK_FUNCS(atol)
AC_CHECK_FUNCS(srandomdev)
AC_CHECK_FUNCS(srandom)
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

# bash complete
AC_ARG_WITH([bash-completion-dir],
    AS_HELP_STRING([--with-bash-completion-dir[=PATH]],
        [Install the bash auto-completion script in this directory. @<:@default=yes@:>@]),
    [],
    [with_bash_completion_dir=yes])

if test "x$with_bash_completion_dir" = "xyes"; then
    PKG_CHECK_MODULES([BASH_COMPLETION], [bash-completion >= 2.0],
        [BASH_COMPLETION_DIR="`pkg-config --variable=completionsdir bash-completion`"],
        [BASH_COMPLETION_DIR="$datadir/bash-completion/completions"])
else
    BASH_COMPLETION_DIR="$with_bash_completion_dir"
fi

AC_SUBST([BASH_COMPLETION_DIR])
AM_CONDITIONAL([ENABLE_BASH_COMPLETION],[test "x$with_bash_completion_dir" != "xno"])

AC_CONFIG_FILES([roll.1 VERSION roll.spec])
AC_OUTPUT
