
	// MYVCDLL.cpp : Defines the entry point for the DLL application.
	//

#include "stdafx.h"
#include "../java/firstJNI.h"
#include <jni.h> //can copy or give full path
#include <math.h>
#include <WTypes.h>

	BOOL APIENTRY DllMain( HANDLE hModule, 
	DWORD  ul_reason_for_call, 
	LPVOID lpReserved
	)
{
	return TRUE;
}

extern "C" __declspec(dllexport) int getMemorySize();
//And your function definition should look like this: 
extern "C" __declspec(dllexport) int getMemorySize()
{     //do something 

	MEMORYSTATUS memoryStatus;  
	int MB=1024*1024 ;
	double memSize;  
	memoryStatus.dwLength=sizeof(MEMORYSTATUS);  

	GlobalMemoryStatus(&memoryStatus);  

	__int64 size= memoryStatus.dwTotalPhys;  

	memSize=(double)size/MB;  

	printf("\nTotal Memory %.0lf MB",ceil(memSize));

	return 0;
}

JNIEXPORT void JNICALL 
	Java_firstJNI_displayHelloWorld(JNIEnv *env, jobject obj) 
{
	printf("Hello world! This is using VC++ DLL\n");

}

JNIEXPORT void JNICALL 
	Java_firstJNI_displayOther(JNIEnv *env, jobject obj) 
{

	printf("Hello world! This is using VC++ DLL Other Function \n");
	getMemorySize();

}

JNIEXPORT jstring JNICALL
	Java_firstJNI_getLine(JNIEnv *env, jobject obj, jstring enter)
{

	char buf[128];
	const char *str = env->GetStringUTFChars(enter, 0);
	printf("\n%s", str);
	env->ReleaseStringUTFChars(enter, str);
	scanf("%s", buf);
	return env->NewStringUTF(buf);

}
