.PHONY: build run clean

filename = dbtest
dbname = db.sqlite3

ifeq ($(OS),Windows_NT)
	separator = \\
	delete = del
	execext = .exe
endif

separator ?= /
delete ?= rm
execext ?= 

build: $(filename)$(execext)

$(filename)$(execext):
	@gcc -o $(filename)$(execext) \
		-lsqlite3 \
		$(filename).c

run: build
	@.$(separator)$(filename)

clean: $(filename)$(execext)
	@rm .$(separator)dbtest$(execext) $(dbname)
