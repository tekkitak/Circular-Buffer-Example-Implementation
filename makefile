MKDIR = mkdir
CLEANUP = rm -f
TARGET_EXT = exe

PATHU = unity/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

SRCT = $(wildcard $(PATHT)*.c)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -DUnityTest_

RESULTS = $(patsubst $(PATHT)UnityTest_%.c,$(PATHR)UnityTest_%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(BUILD_PATHS) $(RESULTS)
	@printf "IGNORES\n"
	@printf "$(IGNORE)\n\n"
	@printf "FAILURES\n"
	@printf "$(FAIL)\n\n"
	@printf "PASSED\n"
	@printf "$(PASSED)\n\n"

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXT)
	-./$< > $@ 2>&1

$(PATHB)UnityTest_%.$(TARGET_EXT): $(PATHO)UnityTest_%.o $(PATHO)%.o $(PATHU)unity.o #$(PATHD)UnityTest_%.d
	$(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXT)
	$(CLEANUP) $(PATHR)*.txt