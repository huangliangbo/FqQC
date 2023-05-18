#include <zlib.h>  
#include <stdio.h>  
#include "kseq.h"  

// reference: http://lh3lh3.users.sourceforge.net/parsefastq.shtml

// Liangbo Huang 2022-05-24

// STEP 1: declare the type of file handler and the read() function  
KSEQ_INIT(gzFile, gzread)  
  
int main(int argc, char *argv[])
{  
    gzFile fp;  
    kseq_t *seq;  
    int l;  
    if (argc == 1) {  
        fprintf(stderr, "Usage: %s <in.fq|fq.gz>\n", argv[0]);  
        return 1;  
    }
    long int tot_read = 0, tot_base = 0, q20_base = 0, q30_base = 0, gc_cnt = 0;
    fp = gzopen(argv[1], "r"); // STEP 2: open the file handler  
    seq = kseq_init(fp); // STEP 3: initialize seq  
    while ((l = kseq_read(seq)) >= 0) { // STEP 4: read sequence
        ++tot_read, tot_base += seq->seq.l;
        // printf("name: %s\n", seq->name.s);
        // if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
        // printf("seq: %s\n", seq->seq.s);
        // if (seq->qual.l) printf("qual: %s\n", seq->qual.s);
        for (int i = 0; i < seq->seq.l; i++) {
            if (seq->seq.s[i] == 'C' || seq->seq.s[i] == 'G') {
                ++gc_cnt;
            }
            // printf("%c ", seq->qual.s[i]);
            // printf("%d ", seq->qual.s[i]);
            if (seq->qual.s[i] - 33 >= 30) {
                ++q30_base, ++q20_base;
            } else if (seq->qual.s[i] - 33 >= 20) {
                ++q20_base;
            }
        }
    }
    printf("Num reads: %ld\n", tot_read);
    printf("Num bases: %ld\n", tot_base);
    printf("q20 bases: %ld\n", q20_base);
    printf("q30 bases: %ld\n", q30_base);
    printf("q20 %%: %.3f\n", q20_base/(float)tot_base * 100);
    printf("q30 %%: %.3f\n", q30_base/(float)tot_base * 100);
    printf("GC %%: %.2f\n", gc_cnt/(float)tot_base * 100);

    kseq_destroy(seq); // STEP 5: destroy seq  
    gzclose(fp); // STEP 6: close the file handler  
    return 0;  
}  
