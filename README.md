# Huffman Archiver

This project contains an archiver that uses the Huffman algorithm.

## Command line arguments:

```bash
-c
	compressing mode

-u
	decompressing mode

-f <FILE>, --file <FILE>
	input file

-o <FILE>, --output <FILE>
	output file
```

## Output

#### Compressing mode output:

	<decompressed data size>
	<compressed data size>
	<header size>

#### Decompressing mode output:

	<compressed data size>
	<decompressed data size>
	<header size>

## Examples

#### Compressing example:

```bash
./archiver -c -f data -o compressedData
18074
11845
518
```

#### Decompressing example:

```bash
./archiver -u -f compressedData -o data
11845
18074
518
```
