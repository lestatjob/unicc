
#include "unic.c"
#include "debug.c"

///todo
///1. написать выгрузку методов по объекту родителю
///2. написать наследование и замену методов (Полиморфизм)
///3. написать ассоциатор (прогроматор) типов данных
///4. написать очистку и выгрузку переменных
///5. написать очистку и выгрузку типов данных
///6. написать инкапсуляцию методов										
///7. написать ассoциатор имен методов 									(написано)
///8. написать очистку и выгрузку методов

 
//----------------------------------------------------------------------
int main(int argc, char **argv) {
	set_fun(main,int,main,2);
	char* t=var(t,char*,main);
	char** r=var(r,char**,main);
	int i=var(i,int,main);
i=0;
printf("test 123\n");
/*
while(i<9999){
r[i]=var(r[i],char*,main);
i++;}
i=0;
while(i<9999){
r[i]=val(r[i],tos(i));
pub(r[i]);
pub("\n");
//delete(r[i]);

	i++;}

   print_var();*/
///----------------------------------------------------------------------
//char* a="test";
//printf("a=%s\n",a);
//free(a);
/*
int te(uni p,...){printf("\n-test-\n");return 0;}
func ast=(func)te;
ast(0);
ast=clear_fun(ast);
ast(0);
char* testarr=var(testarr,char*,main);
testarr=clear_var(testarr);

//unset_fun("newClass");
*/
/*
   print_fun();
    
    print_var();
print_reg_type();
*/
    return 0;
    }
