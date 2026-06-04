CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -O2
DEBUGFLAGS := -std=c23 -Wall -Wextra -g -O0

SRCDIR := src
TESTDIR := tests
BUILDDIR := build

# Source files (recursive)
SOURCES := $(sort $(shell find $(SRCDIR) -type f -name '*.c'))
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
LIB_SOURCES := $(filter-out $(SRCDIR)/main.c,$(SOURCES))
LIB_OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(LIB_SOURCES))

# Test files (recursive)
TEST_SOURCES := $(sort $(shell find $(TESTDIR) -type f -name '*.c' 2>/dev/null))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/tests/%.o,$(TEST_SOURCES))

# Output
TARGET := $(BUILDDIR)/aoc
TEST_TARGET := $(BUILDDIR)/tests_runner

.PHONY: all clean rebuild test debug

all: $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

test: $(TEST_TARGET)

$(BUILDDIR)/tests/%.o: $(TESTDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(LIB_OBJECTS) $(TEST_OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(LIB_OBJECTS) $(TEST_OBJECTS) -o $@
	./$@

debug: CFLAGS = $(DEBUGFLAGS)
debug: clean $(TARGET)

clean:
	rm -rf $(BUILDDIR)

rebuild: clean all
