//https://github.com/chneukirchen/musl-chris2/tree/master/src ---explore this link, he uses interesting methods
//http://mirror.fsf.org/pmon2000/3.x/src/lib/libc/
//http://lord-n.narod.ru/download/books/walla/programming/Spr_po_C/main.htm - частично взять описание функций
//http://www.codenet.ru/progr/cpp/spr/ - частично взять описание функций
//http://www.delorie.com/djgpp/malloc/
//http://ermak.cs.nstu.ru/cprog/html/091.htm

/*
typedef struct {
enum {UNKNOWN,INT,CHAR,LONG,DOUBLE,FLOAT,POINTER} key;
union{int i; char c; long l; double d; float f; void* p; } value;
}var;

 
 
void print_element(var* e)
{
    switch(e->key)
    {   
        case INT:
            printf("%d\n",(int)e->value.i);
            break;
        case POINTER:
            printf("%s\n",(char*)e->value.p);
            break;
    }   
}

  var e1;
  var e2; 
  
    e1.key = INT;
    e1.value.i = 10; 
 
    e2.key = POINTER;
    e2.value.p = "test";
 
    print_element(&e1);
    print_element(&e2);
*/

