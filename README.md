A simple tool to calculate of number of raw reads, number of total, Q20, Q30 and GC content for FASTQ file.

wget https://raw.githubusercontent.com/lh3/bioawk/master/kseq.h
gcc -o FqQC_gc FqQC_gc.c -lz -std=c99

```shell
time ./FqQC_gc S1_L001_R1_001.fastq.gz
```
Num reads: 1470426
Num bases: 220563900
q20 bases: 215670500
q30 bases: 207905093
q20 %: 97.781
q30 %: 94.261
GC %: 45.48
