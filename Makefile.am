BUILT_SOURCES= parser.h
AM_YFLAGS = -d

bin_PROGRAMS = roll
roll_CFLAGS  = -Wall $(AM_CLFAGS)
roll_SOURCES = roll.c parser.y scanner.l roll.h

man_MANS = roll.1
EXTRA_DIST = $(man_MANS) roll.spec COPYRIGHT

README: README.md
	pandoc -f markdown -t plain $< -o $@

test:
	./roll 1 > /dev/null
