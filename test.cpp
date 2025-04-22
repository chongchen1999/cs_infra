/*
 * textutil - a text file processing utility
 *
 * This program performs various text processing operations on files
 * including counting words/lines/chars, finding patterns, and basic
 * transformations.
 *
 * Written in the style of Dennis Ritchie
 */

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /* maximum line length */
#define MAXWORD 100  /* maximum word length */
#define MAXPAT 100   /* maximum pattern length */
#define MAXFILES 100 /* maximum number of files */
#define HASHSIZE 101 /* size of hash table */

struct nlist {          /* basic hash table entry */
    char *name;         /* defined name */
    int count;          /* count of occurrences */
    struct nlist *next; /* next entry in chain */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* function prototypes */
void count(FILE *fp, char *fname);
void find(FILE *fp, char *fname, char *pattern);
void replace(FILE *fp, FILE *out, char *old, char *new);
void printlines(FILE *fp, int start, int end);
void tolower_file(FILE *fp, FILE *out);
void toupper_file(FILE *fp, FILE *out);
void unique(FILE *fp, FILE *out);
void sort_lines(FILE *fp, FILE *out);
int getword(FILE *fp, char *word, int lim);
void wordfreq(FILE *fp);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name);
void freehash(void);
void printusage(void);

/* global variables */
char line[MAXLINE]; /* current input line */
int lineno;         /* current line number */

int main(int argc, char *argv[]) {
    int c;
    int cflag = 0;     /* count */
    int fflag = 0;     /* find */
    int rflag = 0;     /* replace */
    int lflag = 0;     /* lines */
    int wflag = 0;     /* word frequency */
    int sflag = 0;     /* sort */
    int uflag = 0;     /* unique */
    int lowerflag = 0; /* convert to lowercase */
    int upperflag = 0; /* convert to uppercase */

    char *pattern = NULL;
    char *replace_old = NULL;
    char *replace_new = NULL;
    int start_line = 0;
    int end_line = 0;

    int nfiles = 0;
    char *filenames[MAXFILES];
    FILE *fp;
    FILE *outfp = stdout;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'c':
                    cflag = 1;
                    break;
                case 'f':
                    fflag = 1;
                    if (--argc <= 0) goto argerror;
                    pattern = *++argv;
                    break;
                case 'r':
                    rflag = 1;
                    if (--argc <= 0) goto argerror;
                    replace_old = *++argv;
                    if (--argc <= 0) goto argerror;
                    replace_new = *++argv;
                    break;
                case 'l':
                    lflag = 1;
                    if (--argc <= 0) goto argerror;
                    start_line = atoi(*++argv);
                    if (--argc <= 0) goto argerror;
                    end_line = atoi(*++argv);
                    break;
                case 'w':
                    wflag = 1;
                    break;
                case 's':
                    sflag = 1;
                    break;
                case 'u':
                    uflag = 1;
                    break;
                case 'L':
                    lowerflag = 1;
                    break;
                case 'U':
                    upperflag = 1;
                    break;
                case 'o':
                    if (--argc <= 0) goto argerror;
                    outfp = fopen(*++argv, "w");
                    if (outfp == NULL) {
                        fprintf(stderr, "cannot open output file %s\n", *argv);
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "textutil: illegal option %c\n", c);
                    printusage();
                    exit(1);
            }
        }
    }

    if (argc == 0) {
        if (cflag)
            count(stdin, "stdin");
        else if (fflag)
            find(stdin, "stdin", pattern);
        else if (rflag)
            replace(stdin, outfp, replace_old, replace_new);
        else if (lflag)
            printlines(stdin, start_line, end_line);
        else if (wflag)
            wordfreq(stdin);
        else if (lowerflag)
            tolower_file(stdin, outfp);
        else if (upperflag)
            toupper_file(stdin, outfp);
        else if (uflag)
            unique(stdin, outfp);
        else if (sflag)
            sort_lines(stdin, outfp);
        else {
            printusage();
            exit(1);
        }
    }

    while (argc-- > 0) {
        if ((fp = fopen(*argv, "r")) == NULL) {
            fprintf(stderr, "textutil: can't open %s\n", *argv);
            exit(1);
        }
        if (cflag)
            count(fp, *argv);
        else if (fflag)
            find(fp, *argv, pattern);
        else if (rflag)
            replace(fp, outfp, replace_old, replace_new);
        else if (lflag)
            printlines(fp, start_line, end_line);
        else if (wflag)
            wordfreq(fp);
        else if (lowerflag)
            tolower_file(fp, outfp);
        else if (upperflag)
            toupper_file(fp, outfp);
        else if (uflag)
            unique(fp, outfp);
        else if (sflag)
            sort_lines(fp, outfp);
        fclose(fp);
        argv++;
    }

    if (outfp != stdout) fclose(outfp);

    return 0;

argerror:
    fprintf(stderr, "textutil: option requires an argument -- %c\n", c);
    printusage();
    exit(1);
}

/* count: count lines, words, and characters in a file */
void count(FILE *fp, char *fname) {
    int c, nl, nw, nc;
    int inword;

    inword = 0;
    nl = nw = nc = 0;
    while ((c = getc(fp)) != EOF) {
        nc++;
        if (c == '\n') nl++;
        if (c == ' ' || c == '\n' || c == '\t')
            inword = 0;
        else if (inword == 0) {
            inword = 1;
            nw++;
        }
    }
    printf("%7d %7d %7d %s\n", nl, nw, nc, fname);
}

/* find: print lines containing a pattern */
void find(FILE *fp, char *fname, char *pattern) {
    lineno = 0;
    while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if (strstr(line, pattern) != NULL)
            printf("%s:%d: %s", fname, lineno, line);
    }
}

/* replace: replace occurrences of old with new */
void replace(FILE *fp, FILE *out, char *old, char *new) {
    char *p, *q;
    char temp[MAXLINE];
    int oldlen = strlen(old);

    while (fgets(line, MAXLINE, fp) != NULL) {
        p = line;
        while ((q = strstr(p, old)) != NULL) {
            *q = '\0';
            fprintf(out, "%s%s", p, new);
            p = q + oldlen;
        }
        fprintf(out, "%s", p);
    }
}

/* printlines: print lines from start to end */
void printlines(FILE *fp, int start, int end) {
    lineno = 0;
    while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if (lineno >= start && lineno <= end) printf("%d: %s", lineno, line);
        if (lineno > end) break;
    }
}

/* tolower_file: convert input to lowercase */
void tolower_file(FILE *fp, FILE *out) {
    int c;

    while ((c = getc(fp)) != EOF) putc(tolower(c), out);
}

/* toupper_file: convert input to uppercase */
void toupper_file(FILE *fp, FILE *out) {
    int c;

    while ((c = getc(fp)) != EOF) putc(toupper(c), out);
}

/* getword: get next word from input */
int getword(FILE *fp, char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getc(fp)))
        ;

    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getc(fp))) {
            ungetc(*w, fp);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* wordfreq: count frequency of each word */
void wordfreq(FILE *fp) {
    char word[MAXWORD];
    struct nlist *np;
    int c;

    while (getword(fp, word, MAXWORD) != EOF)
        if (isalpha(word[0])) {
            np = install(word);
            np->count++;
        }

    for (c = 0; c < HASHSIZE; c++)
        for (np = hashtab[c]; np != NULL; np = np->next)
            printf("%4d %s\n", np->count, np->name);

    freehash();
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0) return np;

    return NULL;
}

/* install: put (name, count) in hashtab */
struct nlist *install(char *name) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
        np->count = 0;
    }

    return np;
}

/* freehash: free all allocated hash entries */
void freehash(void) {
    int i;
    struct nlist *np, *next;

    for (i = 0; i < HASHSIZE; i++) {
        for (np = hashtab[i]; np != NULL; np = next) {
            next = np->next;
            free(np->name);
            free(np);
        }
        hashtab[i] = NULL;
    }
}

/* unique: print unique lines only */
void unique(FILE *fp, FILE *out) {
    char lastline[MAXLINE] = "";

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (strcmp(line, lastline) != 0) {
            fputs(line, out);
            strcpy(lastline, line);
        }
    }
}

/* sort_lines: basic in-memory line sort */
void sort_lines(FILE *fp, FILE *out) {
    char **lines = NULL;
    int nlines = 0;
    int capacity = 100;
    int i, j;
    char *temp;

    lines = (char **)malloc(capacity * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "textutil: out of memory\n");
        exit(1);
    }

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (nlines >= capacity) {
            capacity *= 2;
            lines = (char **)realloc(lines, capacity * sizeof(char *));
            if (lines == NULL) {
                fprintf(stderr, "textutil: out of memory\n");
                exit(1);
            }
        }

        lines[nlines] = strdup(line);
        if (lines[nlines] == NULL) {
            fprintf(stderr, "textutil: out of memory\n");
            exit(1);
        }
        nlines++;
    }

    /* simple bubble sort */
    for (i = 0; i < nlines - 1; i++) {
        for (j = 0; j < nlines - i - 1; j++) {
            if (strcmp(lines[j], lines[j + 1]) > 0) {
                temp = lines[j];
                lines[j] = lines[j + 1];
                lines[j + 1] = temp;
            }
        }
    }

    /* print sorted lines */
    for (i = 0; i < nlines; i++) {
        fputs(lines[i], out);
        free(lines[i]);
    }

    free(lines);
}

/* printusage: print usage information */
void printusage(void) {
    fprintf(stderr, "Usage: textutil -[cflwsuLU] [args] [files]\n");
    fprintf(stderr, "  -c           count lines, words, chars\n");
    fprintf(stderr, "  -f pattern   find pattern in files\n");
    fprintf(stderr, "  -r old new   replace old with new\n");
    fprintf(stderr, "  -l m n       print lines m through n\n");
    fprintf(stderr, "  -w           count word frequencies\n");
    fprintf(stderr, "  -s           sort lines\n");
    fprintf(stderr, "  -u           print unique lines only\n");
    fprintf(stderr, "  -L           convert to lowercase\n");
    fprintf(stderr, "  -U           convert to uppercase\n");
    fprintf(stderr, "  -o file      specify output file\n");
}