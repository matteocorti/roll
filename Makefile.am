BUILT_SOURCES= parser.h
VERSION=2.6.0
AM_YFLAGS = -d

bin_PROGRAMS = roll
roll_CFLAGS  = -Wall $(AM_CLFAGS)
roll_SOURCES = roll.c parser.y scanner.l roll.h

man_MANS = roll.1

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/tap-driver.sh
TESTS=tests/*test
AUTOMAKE_OPTIONS = serial-tests


EXTRA_DIST = $(man_MANS) roll.spec COPYRIGHT $(TESTS) tests/test_functions.sh

README: README.md
	if uname -a | grep -qi alpine ; then  pandoc -f markdown -t plain $< -o $@ ; else cp README.md README; fi

rpm: dist
	mkdir -p rpmroot/SOURCES rpmroot/BUILD
	cp roll-$(VERSION).tar.gz rpmroot/SOURCES
	rpmbuild --define "_topdir `pwd`/rpmroot" -ba roll.spec

if ENABLE_BASH_COMPLETION
bashcompletiondir = $(BASH_COMPLETION_DIR)
dist_bashcompletion_DATA = roll.completion
endif
