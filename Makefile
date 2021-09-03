CC=c99
CFLAGS=-Wall -Wextra
PREFIX=/usr

indexer:
	$(CC) indexer.c -o indexer $(CFLAGS)
clean:
	rm indexer
install: indexer
	cp indexer $(PREFIX)/bin/indexer
	cp indexer.1 $(PREFIX)/share/man/man1/indexer.1
uninstall:
	rm $(PREFIX)/bin/indexer
	rm $(PREFIX)/share/man/man1/indexer.1
