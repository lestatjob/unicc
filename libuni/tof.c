#ifndef no_tof
float _unic_tof(uni* x){
	uni id=get_var_id(x);
	float out=0;
	char* buff;
if(id!=-1){
char* type=get_var_type(x);
if(sch_count(type,'*')>0 && scmp(type,"char")==1){
	buff=(void*)*x; out=stof((void*)buff);
}else{out=*(double*)(x);}
		   }
return out;
	}
#define tof(x) (_unic_tof((uni*)&x))
#endif
