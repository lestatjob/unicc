
/*! ~ Системные функции, обращение на уровне ядра ~ !*/
///------------------------------------------------------------
//http://blog.rchapman.org/post/36801038863/linux-system-call-table-for-x86-64
//http://numactl.sourcearchive.com/documentation/0.9/syscall_8c-source.html!!!
///------------------------------------------------------------
#ifdef __x86_64__
#include "sys/stdarg.h"
#endif

#ifdef __i386__
typedef void* va_list;
#define __va_argsiz(t) (((sizeof(t) + sizeof(uni) - 1) / sizeof(uni)) * sizeof(uni))
#define va_start(ap, pN) ((ap) = ((va_list) (&pN) + __va_argsiz(&pN)))
#define va_end(ap)	(ap=(void*)0)
#define va_arg(ap, t) (((ap) = (ap) + __va_argsiz(t)), *((t*)(void*)((ap) - __va_argsiz(t))))
#endif
///------------------------------------------------------------
uni* __arg(void* p,...){
int i=0;
uni buff[MAX_ARG];
va_list arg;
va_start(arg,p);
while(p){buff[i++]=(uni)p; p=va_arg(arg,typeof(p));}
va_end(arg);
uni* out=(uni*)buff;
	return out;
	}

///------------------------------------------------------------
#ifdef __i386__
asm(
"__syscall:\n" 
"pushl %ebp\n" 
"pushl %edi\n" 
"pushl %esi\n" 
"pushl %ebx\n"
"mov  (0+5)*4(%esp),%eax\n"
"mov  (1+5)*4(%esp),%ebx\n"
"mov  (2+5)*4(%esp),%ecx\n"
"mov  (3+5)*4(%esp),%edx\n"
"mov  (4+5)*4(%esp),%esi\n"
"mov  (5+5)*4(%esp),%edi\n"
"mov  (6+5)*4(%esp),%ebp\n"
"int $0x80\n"
"popl %ebx\n"
"popl %esi\n" 
"popl %edi\n" 
"popl %ebp\n" 
"ret"
);
#endif
///------------------------------------------------------------
#ifdef __x86_64__
asm("__syscall:\n" "movq %rdi,%rax\n" "movq %rsi,%rdi\n" "movq %rdx,%rsi\n"
"movq %rcx,%rdx\n" "movq %r8,%r10\n" "movq %r9,%r8\n" "movq 8(%rsp),%r9\n"
"syscall\n" "ret\n" );
#endif
///------------------------------------------------------------
long __syscall(long ns, long a, long b, long c, long d, long e, long f);
///------------------------------------------------------------
long __sysrun(long ns, ...){
	va_list atr;
	long  a,b,c,d,e,f;
	va_start(atr, ns);
	a=va_arg(atr, long);
	b=va_arg(atr, long);
	c=va_arg(atr, long);
	d=va_arg(atr, long);
	e=va_arg(atr, long);
	f=va_arg(atr, long);
	va_end(atr);
	return (long)(__syscall(ns,a,b,c,d,e,f));
}
///------------------------------------------------------------
#define __syscall0(n) __sysrun(n)
#define __syscall1(n,a) __sysrun(n,(long)(a))
#define __syscall2(n,a,b) __sysrun(n,(long)(a),(long)(b))
#define __syscall3(n,a,b,c) __sysrun(n,(long)(a),(long)(b),(long)(c))
#define __syscall4(n,a,b,c,d) __sysrun(n,(long)(a),(long)(b),(long)(c),(long)(d))
#define __syscall5(n,a,b,c,d,e) __sysrun(n,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define __syscall6(n,a,b,c,d,e,f) __sysrun(n,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e),(long)(f))
///------------------------------------------------------------
struct stat_f{
  long st_dev;
  long st_ino;
  long st_mode;
  long st_nlink;
  long st_uid;
  long st_gid;
  long st_rdev;
  long st_size;
  long st_atime;
  long st_mtime;
  long st_ctime;
};
///------------------------------------------------------------
uni open(char * filename, uni flags, uni mode) {return __syscall3(__NR_open,filename,flags,mode);}
void close(uni fd) {__syscall1(__NR_close,fd);}
uni stat(char * filename, struct stat_f *buf) {return __syscall2(__NR_stat,filename,buf);}
uni fstat(int fd, struct stat_f *buf) {return __syscall2(__NR_fstat,fd,buf);}
uni lstat(char * filename, struct stat_f *buf) {return __syscall2(__NR_lstat,filename,buf);}

uni brk(void* brkv) {return __syscall1(__NR_brk,brkv);}
uni __exit(uni error_code){return __syscall1(__NR_exit,error_code); }
uni __exit(uni error_code) __attribute__ ((destructor));
#define exit __exit
uni getpid(void){return __syscall0(__NR_getpid);}
int fork(void){return __syscall0(__NR_fork);}
int vfork(void){return __syscall0(__NR_vfork);}
uni read(uni fd, char * buf, uni count) {return __syscall3(__NR_read,fd,buf,count);}
uni kill(uni pid, int sig){return __syscall2(__NR_kill,pid,sig);}
uni dup2(uni oldfd, uni newfd){return __syscall2(__NR_dup2,oldfd,newfd);}
uni alarm(int seconds){return __syscall1(__NR_alarm,seconds);}
uni pipe(int* filedes){return __syscall1(__NR_pipe,filedes);}
long time(long tloc){return __syscall1(__NR_time,tloc);}
int unlink(char* filename){return __syscall1(__NR_unlink,filename);}
uni nanosleep(uni rqtp, uni rmtp){return __syscall2(__NR_nanosleep,rqtp,rmtp);}
int readlink(char* path, char * buf, int bufsize){return __syscall3(__NR_readlink,path,buf,bufsize);}
int ioctl(unsigned int fd, unsigned int cmd, unsigned int arg){return __syscall3(__NR_ioctl,fd,cmd,arg);}
int execve(const char* filename, char * const argv[], char *const envp[]){return __syscall3(__NR_execve,filename,argv,envp);}
size write(int fd, void* buf, size count) {return __syscall3(__NR_write,fd,buf,count);}
int mprotect(void* start, size_t len, long prot) {return __syscall3(__NR_mprotect,start,len,prot);}
uni munmap(void *addr, uni len) {return __syscall2(__NR_munmap,addr,len);}
void *mmap(void *start, size_t len, int prot, int flags, int fd, long int off){
#ifdef __NR_mmap2
	return (void *)__syscall6(__NR_mmap2, start, len, prot, flags, fd, off>>16);
#else
	return (void *)__syscall6(__NR_mmap, start, len, prot, flags, fd, off);
#endif
}
///------------------------------------------------------------
void *sbrk(long inc){return (void *)__syscall1(__NR_brk, __syscall1(__NR_brk, 0)+inc);}
///------------------------------------------------------------
void *mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...){
	va_list ap;
	void *new_addr;
	
	va_start(ap, flags);
	new_addr = va_arg(ap, void *);
	va_end(ap);

	return (void *)__syscall5(__NR_mremap, old_addr, old_len, new_len, flags, new_addr);
}
///------------------------------------------------------------
int madvise(void *addr, size_t len, int advice){return __syscall3(__NR_madvise, addr, len, advice);}
///------------------------------------------------------------
uint64_t  __udivmoddi4(uint64_t num, uint64_t den, uint64_t * rem_p){
  uint64_t quot = 0, qbit = 1;
    if ( den == 0 ) {return 1/((unsigned)den);}
  while ( (int64_t)den >= 0 ) {den <<= 1; qbit <<= 1; }
 
  while ( qbit ) {
    if ( den <= num ) { num -= den; quot += qbit;}
     den >>= 1; qbit >>= 1;
				  }
   if ( rem_p ){*rem_p = num;}
   return quot;
																		}
///------------------------------------------------------------
uint64_t __udivdi3(uint64_t num, uint64_t den){return __udivmoddi4(num, den, NULL);}
///------------------------------------------------------------
uint64_t __umoddi3(uint64_t num, uint64_t den){ uint64_t v;(void) __udivmoddi4(num, den, &v);return v;} 
///------------------------------------------------------------
int64_t __moddi3(int64_t num, int64_t den){
  int minus = 0; int64_t v; 
  if ( num < 0 ) { num = -num; minus = 1; }
  if ( den < 0 ) { den = -den; minus ^= 1;}
  (void) __udivmoddi4(num, den, (uint64_t *)&v);
   if ( minus ){ v = -v;}
   return v;
 } 
///------------------------------------------------------------
int64_t __divdi3(int64_t num, int64_t den){
  int minus = 0; int64_t v;
  if ( num < 0 ) {num = -num; minus = 1; }
   if ( den < 0 ) { den = -den; minus ^= 1;}
    v = __udivmoddi4(num, den, NULL);
   if ( minus ){ v = -v;}
    return v;
}
///------------------------------------------------------------
typedef struct mhope{
int a[MAX_MEMORY_VAR];
int z[MAX_MEMORY_VAR];
int i;
	}mhope;

static mhope hope;
///------------------------------------------------------------
inline void init_malloc(void){hope.i=0;return;}
void init_malloc(void)	__attribute__ ((constructor));
///------------------------------------------------------------
void hope_sort(){
int i=0,j=0,z=0,min=0,max=0,nom=hope.i+1;
int a=0;	
    for(i = 0 ; i < nom ; i++) { 
       for(j = 0 ; j < nom - i - 1 ; j++) {  
           if(hope.a[j] < hope.a[j+1]) {           
              a = hope.a[j]; 
              hope.a[j] = hope.a[j+1] ; 
              hope.a[j+1] = a; 
              
              z = hope.z[j]; 
              hope.z[j] = hope.z[j+1] ; 
              hope.z[j+1] = z;
           }
        }
    }
if(hope.i>0){hope.i--;}    	
	}
///------------------------------------------------------------
int getptrid(void *ptr){
int i=0,z=0,n=-1;
while(i<hope.i){
if(((int)ptr)==hope.a[i]){z=hope.z[i];n=i;break;}	
	i++;
	}
return n;		
	}
///------------------------------------------------------------
void dropptr(void* ptr){
int id=getptrid(ptr);
hope.a[id]=-1; 
hope.z[id]=-1;
hope_sort();
	}
///------------------------------------------------------------	
size_t libc_strlen(char* str);
size_t libc_count(void** v);


void free_ptr(void* ptr){
if (ptr == NULL){return;}
int id=getptrid(ptr);
if(id==-1){return;}
if(hope.z[id]>0){
if(munmap(ptr, hope.z[id]) == -1){write($O,"munmap failed!\n",15);}	
dropptr(ptr);
}
return;		 
	}

void free(void* ptr){
if (ptr == NULL){return;}
int id=getptrid(ptr),pco=libc_strlen((char*)ptr),sco=libc_count((void**)ptr);
if(id==-1){return;}
if(sco>0 && pco==0){
	void** bf=ptr;
	while(sco>0){sco--;if(libc_count((void**)bf[sco])>0){free(bf[sco]);}else{free_ptr(bf[sco]);}}
					}
free_ptr(ptr);

return;	
	}




	
	
	






//!---------------------------------------------------------------------
	
void *malloc(size_t __size){
if(__size<=0){__size=1;}
void *result=mmap(0, __size*sizeof(result) , PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);//+ sizeof(size_t)
if (result == MAP_FAILED){write($O,"mmap failed!\n",13);return NULL;}
hope.a[hope.i]=(int)result;
hope.z[hope.i]=__size*sizeof(result);
hope.i++;

return result;
}	
//!---------------------------------------------------------------------
void *libc_memcpy (void *dest, void *src, size_t n);

//!---------------------------------------------------------------------
void *realloc(void *ptr, size_t __size){
int i=0,z=0,id=getptrid(ptr);
        if (!ptr){return malloc(__size);}
        if (!__size) {free(ptr);return malloc(1);}
          void *newptr = malloc(__size);
        if (newptr) {
				 libc_memcpy(newptr, ptr, hope.z[id]);
                free(ptr);
        }else{write($O,"mmap failed!\n",13);return NULL;}
        return newptr;
}

