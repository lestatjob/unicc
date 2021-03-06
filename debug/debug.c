#ifdef __NO_DEBUG
#define printf(x...)
#define print_reg_type()
#define print_fun()
#define print_var()
#define __assert(a,b,c)
#define __assert2(a,b,c,d)
#else
#include "printf.c"
//----------------------------------------------------------------------
 void print_var() {
    int i=0;

    printf("regs var:\n");

    while (var_$l>i) {
        printf("i=%d \t| $ =%l \t\t| $t =%s\t| $f =%l \t |",i,(long)var_$[i],type_$t[var_$t[i]],(long)var_$f[i]);
        printf("$n =%s\t| ",var_$n[i]);
        printf("\n");
        i++;
        }
    return;
    }
//----------------------------------------------------------------------
int print_reg_type(void) {
    int i=0;
    printf("regs type:\n");
    while (type_$l>i) {
        printf("i = %d | t=%s | z=%l\n",i,type_$t[i],(long)type_$z);
        i++;
        }
    return 1;
    }
//----------------------------------------------------------------------
void __assert(char *file, int line, char *failedexpr){
	printf("assertion \"%s\" failed: file \"%s\", line %d\n",failedexpr, file, line);
	//exit(1);
}
//----------------------------------------------------------------------
void __assert2(char *file, int line, char *fun, char *failedexpr){
	printf("assertion \"%s\" failed: file \"%s\", line %d, function \"%s\"\n",failedexpr, file, line, fun);
  //exit(1);
}
//----------------------------------------------------------------------
void print_fstat(struct stat_f *fin){
printf("st_dev=%l\n",fin->st_dev);
printf("st_ino=%l\n",fin->st_ino);
printf("st_mode=%l\n",fin->st_mode);
printf("st_nlink=%l\n",fin->st_nlink);
printf("st_uid=%l\n",fin->st_uid);
printf("st_gid=%l\n",fin->st_gid);
printf("st_rdev=%l\n",fin->st_rdev);
printf("st_size=%l\n",fin->st_size);
printf("st_atime=%l\n",fin->st_atime);
printf("st_mtime=%l\n",fin->st_mtime);
printf("st_ctime=%l\n",fin->st_ctime);
return;
				}
						  
#endif
