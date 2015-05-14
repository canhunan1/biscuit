#pragma once

#include <littypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define         RED     "\x1b[31;1m"
#define         GREEN   "\x1b[32;1m"
#define         BLUE    "\x1b[34;1m"
#define         RESET   "\x1b[0m"

#define EPERM		1
#define ENOENT		2
#define EBADF		9
#define ECHILD		10
#define ENOMEM		12
#define EFAULT		14
#define EEXIST		17
#define ENOTDIR		20
#define EISDIR		21
#define EINVAL		22
#define ENAMETOOLONG	36
#define ENOSYS		38

#define SIGKILL		9

#define MAP_FAILED	((void *) -1)

#define MAP_PRIVATE	0x2
#define MAP_ANON        0x20
#define MAP_ANONYMOUS   MAP_ANON

#define PROT_NONE	0x0
#define PROT_READ	0x1
#define PROT_WRITE	0x2
#define PROT_EXEC	0x4

#define WAIT_ANY	(-1)
#define WAIT_MYPGRP	0

#define FORK_PROCESS	0x1
#define FORK_THREAD	0x2

#define MAXBUF        4096

/*
 * system calls
 */
struct __attribute__((packed)) stat {
	ulong	st_dev;
	ulong	st_ino;
	ulong	st_mode;
	ulong	st_size;
};

struct __attribute__((packed)) tfork_t {
	void *tf_tcb;
	void *tf_tid;
	void *tf_stack;
};

#define S_ISDIR(mode)	(mode == 2)
#define S_ISREG(mode)	(mode == 1)

int close(int);
int chdir(char *);
void exit(int);
int execv(const char *, char * const[]);
long fake_sys(long);
int fork(void);
int fstat(int, struct stat *);
int getpid(void);
int kill(int, int);
int link(const char *, const char *);
int mkdir(const char *, long);
void *mmap(void *, size_t, int, int, int, long);
int munmap(void *, size_t);
int open(const char *, int, int);
#define    O_RDONLY          0
#define    O_WRONLY          1
#define    O_RDWR            2
#define    O_CREAT         0x40
#define    O_EXCL          0x80
#define    O_TRUNC         0x200
#define    O_DIRECTORY     0x10000

#define    S_IRWXU        0700
int pause(void);
int pipe(int *);
long read(int, void*, size_t);
int unlink(const char *);
int wait(int *);
int wait4(int, int *, int, void *);
long write(int, void*, size_t);

/*
 * thread stuff
 */
void tfork_done(long);
int tfork_thread(struct tfork_t *, long (*fn)(void *), void *);
void threxit(long);
int thrwait(int, int *);

typedef struct {
	int tid;
	void *stack;
} pthread_t;

typedef struct {
} pthread_attr_t;

int pthread_create(pthread_t *, pthread_attr_t *, void* (*)(void *), void *);
int pthread_join(pthread_t, void **);

/*
 * libc
 */
typedef struct {
	int fd;
} FILE;
extern FILE  *stdin, *stdout, *stderr;

struct timeval {
	time_t tv_sec;
	time_t tv_usec;
};

struct timezone {
};

int atoi(const char *);
ulong atoul(const char *);
void err(int, const char *, ...)
    __attribute__((format(printf, 2, 3)));
void errx(int, const char *, ...)
    __attribute__((format(printf, 2, 3)));
int fprintf(FILE *, const char *, ...)
    __attribute__((format(printf, 2, 3)));
int gettimeofday(struct timeval *tv, struct timezone *tz);
void *memset(void *, int, size_t);
int printf(char *, ...)
    __attribute__((format(printf, 1, 2)));
ulong rdtsc(void);
char *readline(char *);
int snprintf(char *, size_t, const char *,...)
    __attribute__((format(printf, 3, 4)));
char *strncpy(char *, const char *, size_t);
size_t strlen(char *);
int strncmp(const char *, const char *, size_t);
char *strstr(const char *, const char *);
int vfprintf(FILE *, const char *, va_list)
    __attribute__((format(printf, 2, 0)));
int vprintf(const char *, va_list)
    __attribute__((format(printf, 1, 0)));

void *malloc(size_t);
void free(void *);

extern char __progname[64];

#ifdef __cplusplus
}	// extern "C"
#endif
