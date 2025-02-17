CC     = gcc
CFLAGS = -Wall -Werror -Wextra

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

.PHONY: all clean debug prep release remake clean_release clean_debug

# Default build
default: prep release

all: prep release debug

#
# Debug rules
#
debug: prep $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#
# Release rules
#
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CC) $(CFLAGS) $(RELCFLAGS) -o $(RELEXE) $^

$(RELDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR)/src $(RELDIR)/src

remake: clean all

clean:
	rm -rf $(RELDIR) $(DBGDIR)

clean_release:
	rm -rf $(RELDIR)

clean_debug:
	rm -rf $(DBGDIR)