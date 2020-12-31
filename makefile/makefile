P = car
SRCS := main.c car.c
OBJS = $(subst .c,.o,$(SRCS))
DEPS= $(subst .c,.d,$(SRCS))
LDLIBS = 
CC = c99
CFLAGS = -g -Wall -O3
CPPFLAGS = 
TARGET_ARCH = 

# Report content of SRCS
# $(info $$SRCS is [${SRCS}])

# Report content of OBJS
# $(info $$OBJS is [${OBJS}])

# Report content of DEPS
# $(info $$DEPS is [${DEPS}])

# Build using implicit rule:
$(P): $(OBJS)

# Include depencency rules (*.d) in the build:
include $(DEPS)

# Build dependency files:
# Ref: GNU make manual - Automatic Prerequisites 
# https://www.gnu.org/software/make/manual/html_node/automatic-prerequisites.html
# This step converts the output of cc -MM main.c:
# main.o : main.c defs.h
# to:
# main.c main.d : main.c defs.h 
# set -e causes the shell to exit immediately if the $(CC) command fails.
# $@ is the target filename (*.d)
# $< is the filename of the first prerequisite (*.c)
# $@.$$$$ is a temp file like main.d.4253.  This will contain something like:
# main.o : main.c defs.h
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) $(P) 

