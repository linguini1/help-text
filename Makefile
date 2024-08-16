CC = gcc
OUT = help-text

SRCDIR = $(abspath ./src)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
HELPTEXT = $(SRCDIR)/helptext.txt
HELPTEXTINC = $(SRCDIR)/helptext.h

CFLAGS = -Wall -Wextra

all: $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(CC) $^ -o $(OUT)

help: all
	cat $(HELPTEXT) | ./$(OUT) > $(HELPTEXTINC)

clean:
	@rm $(OBJS)
	@rm $(OUT)
