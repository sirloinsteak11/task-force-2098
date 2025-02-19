CC     = gcc
CFLAGS = -Wall -Wextra

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:%.c=%.o)
EXE  = game

DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)_debug
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCFLAGS = -g -O0 -DDEBUG -fsanitize=address -fsanitize=undefined

RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake clean_release clean_debug prep_debug prep_release

# Default build
default: prep_release release

all: prep release debug

#
# Debug rules
#
debug: prep_debug $(DBGEXE) clean_savefile

$(DBGEXE): $(DBGOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#
# Release rules
#
release: prep_release $(RELEXE) clean_savefile

$(RELEXE): $(RELOBJS)
	$(CC) $(CFLAGS) $(RELCFLAGS) -o $(RELEXE) $^

$(RELDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

#
# Other rules
#
prep: savefile
	@mkdir -p $(DBGDIR)/src $(RELDIR)/src

prep_release: savefile
	@mkdir -p $(RELDIR)/src

prep_debug: savefile
	@mkdir -p $(DBGDIR)/src

savefile:
	touch savefile

clean_savefile: savefile
	rm -f savefile

remake: clean all

clean:
	rm -rf $(RELDIR) $(DBGDIR)

clean_release:
	rm -rf $(RELDIR)

clean_debug:
	rm -rf $(DBGDIR)

run_debug: prep_debug debug
	$(DBGDIR)/$(EXE)_debug $(ARGS)

run_release: prep_release release
	$(RELDIR)/$(EXE) $(ARGS)