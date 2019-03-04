#include <jni.h>
#include <assert.h>
#include <stdio.h>

#include "hook_read.h"
#include "vector.h"


/*
 * Ϊĳһ����ע�᱾�ط���
 * */
static int registerNativeMethods(JNIEnv* env,const char* className,
		JNINativeMethod* gMethods,int numMethods)
{
	jclass clazz;
	clazz = (*env)->FindClass(env,className);
	if (clazz == NULL)
	{
		return JNI_FALSE;
	}

	if ((*env)->RegisterNatives(env,clazz,gMethods,numMethods) < 0){
		return JNI_FALSE;
	}

	return JNI_TRUE;
}

/**
* ������Ӧ��
*/
static const char* hookreadClassName = "com/yusakul/nativehook/HookRead";
static JNINativeMethod hookreadMethods[] = {
		{"init", "()V", hook_read_bind},//��ʼ��
		{"uninit", "()V", hook_read_unbind},//���
		{"purArray", "([B)V", put_array},//���
		{"deleteArray", "()V", delete_array},//���
};

/*
* Ϊ������ע�᱾�ط���
*/
static int registerNatives(JNIEnv* env) {
	int ret;
	//
    ret =  registerNativeMethods(env, hookreadClassName, hookreadMethods,
            sizeof(hookreadMethods) / sizeof(hookreadMethods[0]));

    return ret;
}

/*
* System.loadLibrary("lib")ʱ����
* ����ɹ�����JNI�汾, ʧ�ܷ���-1
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
	 JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {//ע��
        return -1;
    }
    //�ɹ�
    result = JNI_VERSION_1_6;

    return result;
}
