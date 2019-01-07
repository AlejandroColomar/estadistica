#!/usr/bin/make -f
VERSION		= 3
PATCHLEVEL	= ~a6
SUBLEVEL	=
EXTRAVERSION	=
NAME		=

export	VERSION
export	PATCHLEVEL
export	SUBLEVEL

################################################################################
# *AUTHOR*

# EMAIL		"1903716@gmail.com"
# FULL NAME	"Alejandro Colomar Andrés"

################################################################################
# *DOCUMENTATION*
# To see a list of typical targets execute "make help"
# More info can be located in ./README.txt
# Comments in this file are targeted only to the developer, do not
# expect to learn how to build mine-sweeper reading this file.

################################################################################
# Beautify output
# ---------------------------------------------------------------------------
# Prefix commands with $(Q) - that's useful
# for commands that shall be hidden in non-verbose mode.
#
#	$(Q)some command here
#
# If BUILD_VERBOSE equals 0 then the above command will be hidden.
# If BUILD_VERBOSE equals 1 then the above command is displayed.
#
# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands

ifeq ("$(origin V)","command line")
  BUILD_VERBOSE = $(V)
endif
ifndef BUILD_VERBOSE
  BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE), 1)
  Q =
else
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(findstring s,$(filter-out --%,$(MAKEFLAGS))),)
  Q = @
endif

export	Q
export	BUILD_VERBOSE

################################################################################
# Do not print "Entering directory ...",
# but we want to display it when entering to the output directory
# so that IDEs/editors are able to understand relative filenames.
MAKEFLAGS += --no-print-directory

################################################################################
export	OS = linux
export	TST = false
export	DBG = false

################################################################################
PROGRAMVERSION	= $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
export	PROGRAMVERSION

################################################################################
# Make variables (CC, etc...)
  CC		= gcc
  AS		= as
  AR		= ar
  LD		= ld

export	CC
export	AS
export	AR
export	LD

################################################################################
# cflags
CFLAGS_STD	= -std=c11
CFLAGS_STD     += -Wpedantic

CFLAGS_OPT	= -O3
CFLAGS_OPT     += -march=native

CFLAGS_W	= -Wall
CFLAGS_W       += -Wextra
CFLAGS_W       += -Wstrict-prototypes
CFLAGS_W       += -Werror
#CFLAGS_W       += -Wno-error=unused-function
#CFLAGS_W       += -Wno-error=unused-parameter

CFLAGS_PKG	= `pkg-config --cflags ncurses`

CFLAGS_D	= -D PROG_VERSION=\"$(PROGRAMVERSION)\"
CFLAGS_D       += -D INSTALL_SHARE_DIR=\"$(INSTALL_SHARE_DIR)\"
CFLAGS_D       += -D SHARE_DIR=\"$(SHARE_DIR)\"
CFLAGS_D       += -D INSTALL_VAR_DIR=\"$(INSTALL_VAR_DIR)\"
CFLAGS_D       += -D VAR_DIR=\"$(VAR_DIR)\"

CFLAGS		= $(CFLAGS_STD)
CFLAGS         += $(CFLAGS_OPT)
CFLAGS         += $(CFLAGS_W)
CFLAGS         += $(CFLAGS_PKG)
CFLAGS         += $(CFLAGS_D)

export	CFLAGS

################################################################################
# libs
LIBS_STD	= -l m

LIBS_PKG	= `pkg-config --libs ncurses`

LIBS		= $(LIBS_STD)
ifeq ($(OS), win)
    LIBS       += -static
endif
LIBS           += $(LIBS_PKG)

export	LIBS

################################################################################
# directories

MAIN_DIR	= $(CURDIR)

LIBALX_DIR	= $(CURDIR)/libalx/
MODULES_DIR	= $(CURDIR)/modules/
TMP_DIR		= $(CURDIR)/tmp/
BIN_DIR		= $(CURDIR)/bin/

export	MAIN_DIR
export	LIBALX_DIR
export	MODULES_DIR

# FIXME: Set local or not local when building a package
INSTALL_BIN_DIR		= /usr/local/bin/
#INSTALL_BIN_DIR	= /usr/bin/
INSTALL_SHARE_DIR	= /usr/local/share/
#INSTALL_SHARE_DIR	= /usr/share/
SHARE_DIR		= estadistica/
INSTALL_VAR_DIR		= /var/local/
#INSTALL_VAR_DIR	= /var/lib/
VAR_DIR			= estadistica/

export	INSTALL_DIR
export	INSTALL_SHARE_DIR
export	SHARE_DIR

################################################################################
# executables

BIN_NAME	= estadistica3

export	BIN_NAME

################################################################################
# target: dependencies
#	action

# That's the default target when none is given on the command line
PHONY := all
all: binary


PHONY += libalx
libalx:
	@echo	'	MAKE	libalx'
	$(Q)$(MAKE) base	-C $(LIBALX_DIR)
	$(Q)$(MAKE) io		-C $(LIBALX_DIR)
	$(Q)$(MAKE) curses	-C $(LIBALX_DIR)
	@echo

PHONY += modules
modules: libalx
	@echo	'	MAKE	modules'
	$(Q)$(MAKE) -C $(MODULES_DIR)
	@echo

PHONY += main
main: modules libalx
	@echo	'	MAKE	main'
	$(Q)$(MAKE) -C $(TMP_DIR)
	@echo

PHONY += binary
binary: main
	@echo	'	MAKE	bin'
	$(Q)$(MAKE) -C $(BIN_DIR)
	@echo

PHONY += install
install: uninstall
	@echo	"	Install:"
	@echo	"	MKDIR	$(INSTALL_BIN_DIR)/"
	$(Q)mkdir -p		$(DESTDIR)/$(INSTALL_BIN_DIR)/
	@echo	"	CP	$(BIN_NAME)"
	$(Q)cp			$(BIN_DIR)/$(BIN_NAME)	$(DESTDIR)/$(INSTALL_BIN_DIR)/
	@echo	"	MKDIR	$(INSTALL_SHARE_DIR)/$(SHARE_DIR)/"
	$(Q)mkdir -p		$(DESTDIR)/$(INSTALL_SHARE_DIR)/$(SHARE_DIR)/
	@echo	"	CP -r	share/*"
	$(Q)cp -r		./share/*		$(DESTDIR)/$(INSTALL_SHARE_DIR)/$(SHARE_DIR)/
	@echo	"	Done"
	@echo

PHONY += uninstall
uninstall:
	@echo	"	Uninstall:"
	@echo	'	RM	bin'
	$(Q)rm -f	$(DESTDIR)/$(INSTALL_BIN_DIR)/$(BIN_NAME)
	@echo	'	RM	share/*'
	$(Q)rm -f -r	$(DESTDIR)/$(INSTALL_SHARE_DIR)/$(SHARE_DIR)/
	@echo	"	Done"
	@echo

PHONY += clean
clean:
	@echo	'	CLEAN	modules'
	$(Q)$(MAKE) clean	-C $(MODULES_DIR)
	@echo	'	CLEAN	tmp'
	$(Q)$(MAKE) clean	-C $(TMP_DIR)
	@echo	'	CLEAN	bin'
	$(Q)$(MAKE) clean	-C $(BIN_DIR)
	@echo

PHONY += mrproper
mrproper: clean
	@echo	'	CLEAN	libalx'
	$(Q)$(MAKE) clean	-C $(LIBALX_DIR)
	@echo

PHONY += help
help:
	@echo  'Cleaning targets:'
	@echo  '  clean		  - Remove all generated files'
	@echo  '  mrproper	  - Remove all generated files (including libraries)'
	@echo  ''
	@echo  'Other generic targets:'
	@echo  '  all		  - Build all targets marked with [*]'
	@echo  '* libalx	  - Build the libalx library'
	@echo  '* modules	  - Build all modules'
	@echo  '* object	  - Build the main object'
	@echo  '* binary	  - Build the binary'
	@echo  '  install	  - Install the program into the filesystem'
	@echo  '  uninstall	  - Uninstall the program off the filesystem'
	@echo  ''
	@echo  '  make V=0|1 [targets] 0 => quiet build (default), 1 => verbose build'
	@echo  ''
	@echo  'Execute "make" or "make all" to build all targets marked with [*] '
	@echo  'For further info see the ./README file'

################################################################################
# Declare the contents of the .PHONY variable as phony.
.PHONY: $(PHONY)




################################################################################
######## End of file ###########################################################
################################################################################
