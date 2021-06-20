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
indexer \[--css\] \[-T\] \[--help\] files 
```
e.g.
```
indexer --css style.css -T html \*.txt > index.html
```
## arguments
```
--css file.css	-	add css stylesheet when using -T html

-T md / html	-	specify output format

--help		-	show help
```
