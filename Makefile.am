#  -*- Mode: makefile; indent-tabs-mode: t -*-

CLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory
AUTOMAKE_OPTIONS = color-tests parallel-tests

GCC_COLORS ?= 'ooh, shiny!'
export GCC_COLORS

SUBDIRS = .

AM_CFLAGS = \
	-pipe \
	-Wall \
	-Wextra \
	-Wundef \
	-Wformat=2 -Wformat-security -Wformat-nonliteral \
	-Wlogical-op \
	-Wmissing-include-dirs \
	-Wold-style-definition \
	-Wpointer-arith \
	-Winit-self \
	-Wdeclaration-after-statement \
	-Wfloat-equal \
	-Wsuggest-attribute=noreturn \
	-Werror=missing-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=missing-declarations \
	-Werror=return-type \
	-Werror=shadow \
	-Wstrict-prototypes \
	-Wredundant-decls \
	-Wmissing-noreturn \
	-Wshadow \
	-Wendif-labels \
	-Wstrict-aliasing=2 \
	-Wwrite-strings \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-Wno-unused-result \
	-Wno-format-signedness \
	-Werror=overflow \
	-Wdate-time \
	-Wnested-externs \
	-ffast-math \
	-fno-common \
	-fdiagnostics-show-option \
	-fno-strict-aliasing \
	-fvisibility=hidden \
	-fstack-protector \
	-fstack-protector-strong \
	-fPIE \
	--param=ssp-buffer-size=4 \
	-D_GNU_SOURCE

bin_PROGRAMS = cpsquashfs

cpsquashfs_SOURCES = cpsquashfs.c
cpsquashfs_CFLAGS = $(AM_CFLAGS)

