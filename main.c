#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
typedef unsigned int u32;
typedef unsigned long u64;
u64 max(u64 v1 , u64 v2){
	return v1>v2?v1:v2;
}
u64 min(u64 v1 , u64 v2){
	return v1>v2?v2:v1;
}
void* Push(char* val , u32 sizeofstr ,u64 pos,  u64& dataSize , u64& usedData , char* data){
	
	if(usedData+sizeofstr>= dataSize){
		u64 newDataSize = dataSize+max(0x1000,usedData+sizeofstr);
		char* newdata = (char*)malloc(newDataSize);
		memcpy(newdata, data, dataSize);
		free(data);
		data=newdata;
		dataSize=newDataSize; 
	}
	if(pos>=dataSize){
		u64 newDataSize = dataSize+max(0x1000,usedData+sizeofstr);
		char* newdata = (char*)malloc(dataSize+max(0x1000,pos));
		memcpy(newdata, data, dataSize);
		free(data);
		data=newdata;
		dataSize=newDataSize;
	}
	for(u32 i = usedData+sizeofstr; i>pos+sizeofstr; i--){
		data[i-1] = data[i-sizeofstr-1];
	}
	
	for(u32 i = 0 ; i < sizeofstr ; i++){
		data[i+pos]=val[i];
	}
	usedData+=sizeofstr;
	return data;
}
unsigned long GetFileSize(FILE* fl){
	if(fl==NULL){
		printf("err in file\n");
		return -1;
	}
	long prev=ftell(fl);
	if(fseek(fl, 0L, SEEK_END)==-1){
		printf("files to fseek");
		return -1;
	}
	unsigned long fileSize = ftell(fl);
	fseek(fl, prev, SEEK_SET);
	return fileSize;

}
void* readFile(const char* fileName , unsigned long & sizeOUT){
	FILE* file = fopen(fileName, "r");
	if(file==NULL){
		printf("err in opening file\n");
		return NULL;
	}
	unsigned long fileSz = GetFileSize(file);
	sizeOUT=fileSz;
	
	if(fileSz!=-1){
		char* data = (char*)malloc(fileSz);
		fread(data, fileSz, 1, file);
		
		
		fclose(file);
		return data;
	}

	fclose(file);
	return NULL;
}

void WriteConstCharHaderFile(const char* haderName, char* matrixName , char* data , u64 sizeofData){
	FILE* hader = fopen(haderName, "w");
	if(!hader){
		printf("Erorr in writing hader file");
		return;
	}
	for(u32 i = 0 ; i < strlen(matrixName); i++){
		switch (matrixName[i]) {
			case '.':
				matrixName[i]='_';
				break;
			case '"':
				matrixName[i]='_';
				break;
			case  '\'':
				matrixName[i]='_';
				break;
			case '@':
				matrixName[i]='/';
				break;
			case '%':
				matrixName[i]='_';
				break;
			default:
				break;
		};
		
	}
	if( matrixName[0] <='9' && matrixName[0] >='0'){
		matrixName[0]='_';
	}
	
	

	fprintf(hader, "const char* %s = \n",matrixName);
	fwrite(data, 1, sizeofData-1,hader);
	//fwrite(const void *__restrict ptr, size_t size, size_t n, FILE *__restrict s)
	fprintf(hader, ";");
	fclose(hader);
	return;
}

void WriteMatrixHaderFile(const char* haderName, char* matrixName , char* data , u64 sizeofData){
	FILE* hader = fopen(haderName, "w");
	if(!hader){
		printf("Erorr in writing hader file");
		return;
	}
	for(u32 i = 0 ; i < strlen(matrixName); i++){
		switch (matrixName[i]) {
			case '.':
				matrixName[i]='_';
				break;
			case '"':
				matrixName[i]='_';
				break;
			case  '\'':
				matrixName[i]='_';
				break;
			case '@':
				matrixName[i]='/';
				break;
			case '%':
				matrixName[i]='_';
				break;
			default:
				break;
		};
		
	}
	if( matrixName[0] <='9' && matrixName[0] >='0'){
		matrixName[0]='_';
	}
	
	

	fprintf(hader, "const char %s[]{ \n\t",matrixName);
	
	for(u64 i = 0 ; i < sizeofData ; i++){
		if(!(i%10)){
			fprintf(hader, "\n\t");
		}
		fprintf(hader, "%d , ",(u32)data[i]);
		
	}
	//fwrite(const void *__restrict ptr, size_t size, size_t n, FILE *__restrict s)
	fprintf(hader, "};");
	fclose(hader);
	return;
}
int main(int argc, char** arg){
	printf("*** File2.H ***\n");
	if(argc>=2) 
	{	
		u32 arglng = strlen(arg[1]);
		if( (arglng==2 & !memcmp(arg[1], "-h", 2)) || 
		    (arglng==6 & !memcmp(arg[1], "--help", 6))
		  ){
			printf("Welcome to File2.H\nthis programe is under the MIT Licence\ncheckout the github : https://github.com/chamseddine2009-06/File2.H\n");
			printf("===> [arg1 fileName] [arg2 2haderName] [arg3 StringName]\n-m at the end if you want to save it as matrix not as a string\n");
			return 0;
		}
	}

	if(argc<=3){
		printf("wrong argmentes struct, type -h for help\n");
		return 1;
	}
	bool matrixmode = false;
	if(strlen(arg[argc-1])==2 && !memcmp(arg[argc-1] ,"-m", 2)){
		printf("\nYou are in matrix mod, all the data in your file will save a matrix not a string.\n");
		matrixmode = true;
	}
	
	u64 dataSize=0;
	char* data = (char*)readFile(arg[1], dataSize);
	u64 usedData = dataSize;
	printf("file %s size %d \n",arg[1],dataSize);
	if(!matrixmode){
		for(u64 i = dataSize ; i > 0 ; i--){
			if(data[i-1] == '\n'){
				data = (char*)Push("\t\"", 2, i, dataSize, usedData, data);
				data = (char*)Push("\\n\"", 3, i-1, dataSize, usedData, data);

			}
			if(data[i-1]=='"' ){
				if(i>2 && data[i-2]=='\\' && data[i-3]!='\\'){
					continue;
				}
				data = (char*)Push("\\", 1, i-1, dataSize, usedData, data);
			}
		}
		if(data[usedData-1]=='"'){
			data[usedData-1]='\0';
		}
	
		data=(char*)Push("\t\"", 2, 0, dataSize, usedData, data);
		printf("Data size %d\n" , dataSize);
		
		WriteConstCharHaderFile(arg[2],arg[3], data, usedData);
	}else {
		WriteMatrixHaderFile(arg[2], arg[3], data, dataSize);
	}
	
	return 0;

}
