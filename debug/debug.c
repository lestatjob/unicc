//#include <stdio.h>
///---------------------------------------------------------------------
///Отладка
///---------------------------------------------------------------------

void print_fun(void) {
    int i=0;
    print("regs fun:\n");
    while(i<fun_$l) {
print(itos(i));
print("\t| $=");
print(ltos((long)fun_$[i]));
print("\t|$n= ");
print(fun_$n[i]);
print(" | \t$o=");
print(type_$t[fun_$o[i]]);
print(" |\t $p=");
print(ltos((long)fun_$p[i]));
print("|\t $a=");
print(ltos((long)fun_$a[i]));
print("|\t $i:");
    int n=0;
    while(fun_$i[i][n]!=0){
print(ltos((long)n));
print("(");
print((char*)fun_$i[i][n]);
print("),");
n++;}    
        i++;
        print("\n");
        }
        
    }
//----------------------------------------------------------------------
 void print_var() {
    int i=0;

    print("regs var:\n");

    while (var_$l>i) {
print("i=");        
print(itos(i));
print(" \t| $ =");
print(ltos((long)var_$[i]));
print("\t| $t =");
print((char*)type_$t[var_$t[i]]);
print("\t| $f =");
print(ltos((long)var_$f[i]));
print(" \t | $n =");
print((char*)var_$n[i]);
print("\t|\n");
	i++;
        }
    return;
    }
//----------------------------------------------------------------------
int print_reg_type(void) {
    int i=0;
    print("regs type:\n");
    while (type_$l>i) {
print("i = ");
print(itos((int)i));
print(" | t=");
print((char*)type_$t[i]);
print(" | z=");
print(ltos((long)type_$z));
print("\n");
        i++;
        }
    return 1;
    }
//----------------------------------------------------------------------

