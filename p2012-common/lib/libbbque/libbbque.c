#define LOG_TAG "LIBBBQUE"

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <ctype.h>
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <netinet/in.h>
#include   <android/log.h>
#include	  <errno.h>
#include   "libbbque.h"
#include 		<jni.h>
 
#define MAXLENGTH 8
#define SERVER_PORT 1313

//static jobject activity_global_obj = NULL;
static jclass activity_global_class = NULL;
static JavaVM *global_jvm = NULL;
static JNIEnv *global_env = NULL;

int send_message_to_bbqued (char* cmd, int* nest) {
	char* command = cmd;
	int sockfd;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int i = 0, len;
	char buf[MAXLENGTH] = "", c;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, "Socket opening failed!");
		return -1;
	}
	//Connection
	if (connect(sockfd, (struct sockaddr *) &server, sizeof server) == -1)
	{
		__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, "Socket connection failed!");
		return -1;
	}
	//Receiving ack from the server
	if (recv(sockfd, buf, 2, 0) <= 0)
	{
		__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, "Connection to bbqued interrupted!");
		return -1;
	}
	len = strlen(command);
	//Sending command to the server
	if (send(sockfd, command, len, 0) == -1)
	{
		__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, "Error while sending message to bbqued!");
		return -1;
	}
	//Receiving response from the server
	if (recv(sockfd, buf, len, 0) > 0)
		*nest = atoi(buf);
	else
	{
		__android_log_write(ANDROID_LOG_ERROR, LOG_TAG, "Connection to bbqued interrupted");
		return -1;
	}
	close(sockfd);
	return 0;
}

extern int get_core_availability() {
	int core_number = -1;
	if (send_message_to_bbqued("core", &core_number) >= 0)
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Called get_core_availability()");
	return core_number;
}

extern int ask_more_core() {
	int core_number;
	if (send_message_to_bbqued("more", &core_number) >= 0)
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Called ask_more_core()");
	return core_number;
}

extern int ask_less_core() {
	int core_number;
	if (send_message_to_bbqued("less", &core_number) >= 0)
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Called ask_less_core()");
	return core_number;
}

extern int free_core() {
	int core_number;
	if (send_message_to_bbqued("free", &core_number) >= 0)
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Called free_core()");
	return core_number;
}

extern int send_message_to_app(JNIEnv *env, jclass clazz) {
	__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "Called send_message_to_app()");
	if(*env != NULL && clazz != NULL)
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "env and clazz exist!");
	else
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "env and clazz DOES NOT exist!");
	
	jmethodID mid = (*env)->GetMethodID(env, clazz, "appCallback", "()V");
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback method not found");
	(*env)->CallStaticVoidMethod(env, clazz, mid);
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...method called back!");
	
	return 0;
/*	
	// get global ref for the object and keep it
	//activity_global_obj = (*env)->NewGlobalRef(env, obj);
	
	// get global ref for the JVM and keep it
	(*env)->GetJavaVM(env, &global_jvm);
	if (global_jvm == NULL)
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "global_jvm NULL, not retrieved from *env");
	else
		__android_log_write(ANDROID_LOG_INFO, LOG_TAG, "global_jvm correctly retrieved from *env");
		
	global_env = env;

	// get object concerned
	//jclass localRef_class = (*env)->GetObjectClass(env, activity_global_obj);
	//if (localRef_class == 0)
	//printf("NATIVE : error, unable to have local ref\n");

	//get an absolute ref on the object, the local one is lost at the end of the function call
	activity_global_class = (*env)->NewGlobalRef(env, clazz);
	if (activity_global_class == 0)
	printf("NATIVE : error, unable to have global ref\n");

	// get the method
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "ready to getMethodID");
	jmethodID mid = (*env)->GetMethodID(env, clazz, "activityCallback", "()V");
	if (mid == 0) {
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback method not found");
		return 1;
	}
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback succeeded");
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...calling back method");
		(*env)->CallStaticVoidMethod(env, clazz, mid);
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...method called back!");
	
	return 0; */
}

/*void activityCallback(char* message) {
  JNIEnv *jenv;
	jmethodID mid;
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "into activityCallback method");
	//activityStop = callback;
	if (global_jvm != NULL) {
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "global_jvm NOT NULL");
		// the Java thread and the C one are not the same so re find the good JNIEnv
		//if (!(*global_jvm)->AttachCurrentThread(global_jvm, (void **)&jenv, NULL)) {
		if (!(*global_jvm)->GetEnv(global_jvm, (void **)&jenv, JNI_VERSION_1_2)) {
			// get the method
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "ready to getMethodID");
			mid = (*jenv)->GetMethodID(jenv, activity_global_class, "activityCallback", "(Ljava/lang/String;)I");
			if (mid == 0) {
				__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback method not found");
				return;
			} 
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback succeeded");
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...calling back method");
				(*jenv)->CallStaticVoidMethod(jenv, activity_global_class, mid, message);
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...method called back!");
		}
	}
	else {
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "global_jvm is NULL. Using old env");
			if (global_env == NULL)
				__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "global_env is NULL. Going to crash...");
			// get the method
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "ready to getMethodID");
			mid = (*global_env)->GetMethodID(global_env, activity_global_class, "activityCallback", "(Ljava/lang/String;)I");
				__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback succeeded");
			if (mid == 0) {
				__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "getMethodID activityCallback method not found");
				return;
			}
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...calling back methos");
				(*jenv)->CallStaticVoidMethod(global_env, activity_global_class, mid, message);
			__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, "...method called back!");
	}
return;
}*/
