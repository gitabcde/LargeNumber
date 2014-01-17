
#ifdef APPLE
#pragma error("define APPLE")
#endif
#include <iostream>
#include "CXPrimitiveType.h"
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#elif defined(unix)
#include <pthread.h>
#endif


int CX_CreateLargeNumber(char** result,int bits)
{
	int ret_bits=bits+(8-bits%8)*(bits%8!=false);
	*result=new char[ret_bits];
	memset(*result,0,ret_bits);
	return 0;
}

int CX_SetAllValueOne(char* num,int size)
{
	CX_UINT64 mytest=(-1);
	int times=size/sizeof(CX_UINT64);
	for(int n=0;n<times;n++)
	{
		*(CX_UINT64*)num=mytest;
	}
	int left=size%sizeof(CX_UINT64);
	for(int n=0;n<left;n++)
	{
		*num=(unsigned char)((1<<8)-1);
	}
	return 0;
}

int CX_SetAllValueZero(char* num,int size)
{
	CX_UINT64 mytest=0;
	int times=size/(sizeof(CX_UINT64)*8);
	for(int n=0;n<times;n++)
	{
		*(CX_UINT64*)num=mytest;
	}
	int left=size%(sizeof(CX_UINT64)*8);
	for(int n=0;n<left;n++)
	{
		*num=(unsigned char)(0);
	}
	return 0;
}
int CX_SetBitValueOne(char* number,int bits)
{
	int num_index=(bits-1)/8;
	number[num_index]|=(((unsigned char)1<<(bits-1)%8));

	return 0;
}
int CX_SetBitValueZero(char* number,int bits)
{
	int num_index=(bits-1)/8;
	number[num_index]&=(~(((unsigned char)1<<(bits-1)%8)));
	return 0;
}
int CX_AddOne(char* number,int bits)
{
	if(bits>0)
	{
		CX_UINT32 tmp=(CX_UINT32)*number;
		tmp+=1;
		*number=tmp;
		if(tmp>255)
		{
			CX_AddOne(number+8,bits-8);
		}
	}
	return 0;

}

int CX_IsAllOne(char* num,int size)
{
	CX_UINT64 mytest=-1;
	int times=size/(sizeof(CX_UINT64)*8);
	for(int n=0;n<times;n++)
	{
		if(mytest!=(*(CX_UINT64*)num))
			return -1;
		num+=sizeof(CX_UINT64);

	}
	int left=size%(sizeof(CX_UINT64)*8);
	for(int n=0;n<left;n++)
	{
		if(*num!=(unsigned char)((1<<8)-1))
			return -1;
	}
	return 0;
}
struct mythreadstruct
{
	int id;
	int begin;
	int end;
};

CX_INT32 __stdcall mythread(void* p)
{
	mythreadstruct* mthd=(mythreadstruct*)p;
	CX_UINT64 test1,test2,test3,testnum,test=1;
	testnum=(test<<mthd->begin);
	while(testnum<(test<<mthd->end))
	{
		test2=(testnum*30)%1234;
		test3=(testnum*test2)%456;
		test1=test2+test3;
		testnum++;
	}

	return 0;
}
int main(int argc, char* argv[])
{
	int *numbers,ncount=0;
	char* large_count;
	CX_CreateLargeNumber(&large_count,123);
	CX_SetAllValueZero(large_count,123);
	unsigned int *mytestint=(unsigned int*)large_count;
	std::cout<<"isallone is "<<CX_IsAllOne(large_count,64)<<std::endl;
	/*
	while(CX_IsAllOne(large_count,64)!=0)
	{

	}
	*/
/*

	mythreadstruct mytestttt;
	mytestttt.id=1;
	mytestttt.begin=0;
	mytestttt.end=10;
	DWORD hd1;
	HANDLE myhd1,myhd2,myhd3,myhd4;
	myhd1=(HANDLE)CreateThread(NULL,NULL,mythread,&mytestttt,NULL,&hd1);

	mytestttt.id=2;
	mytestttt.begin=10;
	mytestttt.end=25;
	DWORD hd2;
	myhd2=(HANDLE)CreateThread(NULL,NULL,mythread,&mytestttt,NULL,&hd2);

	mytestttt.id=3;
	mytestttt.begin=25;
	mytestttt.end=40;
	DWORD hd3;
	myhd3=(HANDLE)CreateThread(NULL,NULL,mythread,&mytestttt,NULL,&hd3);

	mytestttt.id=4;
	mytestttt.begin=40;
	mytestttt.end=60;
	DWORD hd4;
	myhd4=(HANDLE)CreateThread(NULL,NULL,mythread,&mytestttt,NULL,&hd4);
	
	WaitForSingleObject(myhd1,INFINITE);
	WaitForSingleObject(myhd2,INFINITE);
	WaitForSingleObject(myhd3,INFINITE);
	WaitForSingleObject(myhd4,INFINITE);
*/
	return 0;
}

