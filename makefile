TYPE		:= development

TARGET      := performance-service

PTHREAD 	:= -l pthread
MATH 		:= -lm

OPENSSL		:= -l ssl -l crypto

CERVER		:= -l cerver
CERVER_INC	:= -I /usr/local/include/cerver

DEVELOPMENT	:= -D PERCEPTHOR_DEBUG

DEFINES		:= -D _GNU_SOURCE

CC          := gcc

GCCVGTEQ8 	:= $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 8)

SRCDIR      := src
INCDIR      := include
BUILDDIR    := objs
TARGETDIR   := bin

SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

# common flags
# -Wconversion
COMMON		:= -march=native \
				-Wall -Wno-unknown-pragmas \
				-Wfloat-equal -Wdouble-promotion -Wint-to-pointer-cast -Wwrite-strings \
				-Wtype-limits -Wsign-compare -Wmissing-field-initializers \
				-Wuninitialized -Wmaybe-uninitialized -Wempty-body \
				-Wunused-but-set-parameter -Wunused-result \
				-Wformat -Wformat-nonliteral -Wformat-security -Wformat-overflow -Wformat-signedness -Wformat-truncation

# main
CFLAGS      := $(DEFINES)

ifeq ($(TYPE), development)
	CFLAGS += -g -fasynchronous-unwind-tables $(DEVELOPMENT)
else ifeq ($(TYPE), test)
	CFLAGS += -g -fasynchronous-unwind-tables -D_FORTIFY_SOURCE=2 -fstack-protector -O2 $(DEVELOPMENT)
else
	CFLAGS += -D_FORTIFY_SOURCE=2 -O2
endif

CFLAGS += -std=c11 -Wpedantic -pedantic-errors
# check for compiler version
ifeq "$(GCCVGTEQ8)" "1"
	CFLAGS += -Wcast-function-type
else
	CFLAGS += -Wbad-function-cast
endif

CFLAGS += $(COMMON)

LIB         := -L /usr/local/lib $(PTHREAD) $(MATH) $(OPENSSL) $(CERVER)
INC         := -I $(INCDIR) -I /usr/local/include $(CERVER_INC)
INCDEP      := -I $(INCDIR)

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(TARGET)

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR) 
	@$(RM) -rf $(TARGETDIR)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

# link
$(TARGET): $(OBJECTS)
	$(CC) $^ $(LIB) -o $(TARGETDIR)/$(TARGET)

# compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

.PHONY: all clean
