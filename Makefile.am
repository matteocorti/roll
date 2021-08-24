BUILT_SOURCES= parser.h
AM_YFLAGS = -d

bin_PROGRAMS = roll
roll_CFLAGS  = -Wall $(AM_CLFAGS)
roll_SOURCES = roll.c parser.y scanner.l roll.h

man_MANS = roll.1

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/tap-driver.sh
TESTS=tests/*test
AUTOMAKE_OPTIONS = serial-tests


EXTRA_DIST = $(man_MANS) roll.spec COPYRIGHT $(TESTS)

README: README.md
	pandoc -f markdown -t plain $< -o $@
