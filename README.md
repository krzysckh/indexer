# indexer - basic program to index files (for websites or anything)

## installation

```
git clone https://github.com/krzysckh/indexer
cd indexer
make
sudo make install
```

## synopsis

```
indexer [--css file.css] [-T md/html] [--dir-emoji] [--file-emoji] [-d] [-f] files 
```
e.g.
```
indexer --css style.css -T html *.txt > index.html
```
## arguments
```
--css file.css	-	add css stylesheet when using -T html

-T md / html	-	specify output format

--dir-emoji	-	sets string before a directory

--file-emoji	-	sets string before a file

--help		-	show help
```
