OBJS = src/main.o \
       src/match.o \
       src/ref.o \
       src/render.o \
       src/intset.o \
       src/strutil.o \
       data/data.o
CFLAGS += -Wall -Isrc/ -o3
LDLIBS += -lreadline

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin

biblia: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

src/main.o: src/main.c src/config.h src/data.h src/match.h src/ref.h src/render.h src/strutil.h

src/match.o: src/match.h src/match.c src/config.h src/data.h src/ref.h

src/ref.o: src/ref.h src/ref.c src/intset.h src/data.h

src/render.o: src/render.h src/render.c src/config.h src/data.h src/match.h src/ref.h

src/insetset.o: src/intset.h src/insetset.c

src/strutil.o: src/strutil.h src/strutil.c

data/data.o: src/data.h data/data.c

data/data.c: data/ave-maria.tsv data/generate.awk src/data.h
	awk -f data/generate.awk $< > $@

.PHONY: clean install uninstall
clean:
	rm -rf $(OBJS) biblia

install:
	install biblia $(bindir)/biblia

uninstall:
	rm -rf $(bindir)/biblia
