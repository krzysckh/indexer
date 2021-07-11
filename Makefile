instd=/usr/bin/
mand=/usr/share/man/man1/

CC=cc

indexer:
	$(CC) -Wall indexer.c -o indexer

clean:
	rm indexer

install: indexer
	cp indexer $(instd)
	cp indexer.1 $(mand)

uninstall:
	rm $(instd)indexer
	rm $(mand)indexer.1
