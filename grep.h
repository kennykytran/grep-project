#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <curses.h>
#include <string.h>
#include <regex.h>


/* make BLKSIZE and LBSIZE 512 for smaller machines */
const int BLKSIZE = 4096;  
const int NBLK = 2047;  
const int FNSIZE = 128;  
const int LBSIZE = 4096;
const int ESIZE = 256; 
const int GBSIZE = 256;  
const int NBRA = 5;  
const int KSIZE = 9;  
const int CBRA = 1;
const int CCHR = 2;  
const int CDOT = 4;  
const int CCL = 6;  
const int NCCL = 8;  
const int CDOL = 10;
const int CEOF = 11;  
const int CKET = 12;  
const int CBACK = 14;  
const int CCIRC = 15;  
const int STAR = 01;
const int READ = 0;  
const int WRITE = 1;
char	Q[]	= "", T[]	= "TMP";
char	savedfile[FNSIZE], genbuf[LBSIZE], file[FNSIZE], linebuf[LBSIZE], rhsbuf[LBSIZE/2], expbuf[ESIZE+4];
unsigned int	*addr1, *addr2, *dot, *dol, *zero;
long	count;
char	*nextip, *linebp, *globp, *tfname, *loc1, *loc2;
char	ibuff[BLKSIZE], obuff[BLKSIZE], WRERR[]	= "WRITE ERROR", *braslist[NBRA], *braelist[NBRA], tmpXXXXX[50] = "/tmp/eXXXXX";
int	iblock	= -1,	oblock	= -1, ichanged, nleft, names[26],anymarks, nbra, subnewa, subolda, fchange, wrapp, bpagesize = 20,col, listn, listf, oflag, vflag	= 1;
int	ninbuf, io, pflag, tfile	= -1, tline, given, peekc, lastc;
unsigned nlall = 128;

void quit(int);
char *getblock(unsigned int atl, int iof);
char *getline_(unsigned int tl);
void add(int i);
int advance(char *lp, char *ep);
int backref(int i, char *lp);
void blkio(int b, char *buf, int (*iofcn)(int, char*, int));
int cclass(char *set, int c, int af);
void commands(void);
void compile(int eof);
int compsub(void);
void error(char *s);
int execute(unsigned int *addr);
void exfile(void);
void filename(int comm);
int getfile(void);
int getnum(void);
int gettty(void);
int gety(void);
void global(int k);
void init(void);
unsigned int *address(void);
void newline(void);
void nonzero(void);
void onhup(int n);
void onintr(int n);
void print(void);
void putchr(int ac);
void putd(void);
void putfile(void);
int putline(void);
void setwide(void);
void setnoaddr(void);
void squeeze(int i);
long	lseek(int, long, int);
int	open(char *, int);
int	creat(char *, int);
int	read(int, char*, int);
int	write(int, char*, int);
int	close(int);
int	unlink(char *);
char	*mkdtemp(char *);
void cerror_();
int star_(char *, char *, char *);

void readfile(char*);
void search( char*); 
void search_file(char*, char*);
