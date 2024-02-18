/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       ANDROIDJNIObject.cpp
* 
* @class      ANDROIDJNIOBJECT
* @brief      ANDROID JNI Object class 
* @ingroup    PLATFORM_ANDROID
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "ANDROIDJNIObject.h"

#include "ANDROIDJNI.h"

#include <stdarg.h>

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDJNIOBJECT::ANDROIDJNIOBJECT(XSTRING ClassName, XSTRING constructorsignature, ...)
* @brief      Constructor
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  XSTRING : 
* @param[in]   XSTRING constructorsignature : 
* @param[in]   ... : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDJNIOBJECT::ANDROIDJNIOBJECT(XSTRING ClassName, XSTRING constructorsignature, ...)
{
  JNIEnv*   JEnv = ANDROIDJNI::GetJNIEnv();
  char*     cstr = NULL;
  
  ClassName.CreateOEM(cstr);

  jniclass = ANDROIDJNI::FindJNIClass(cstr);  
  delete cstr;

  constructorsignature.CreateOEM(cstr);

  jmethodID constructor = JEnv->GetMethodID(jniclass, "<init>", cstr);
  delete cstr;


  va_list params;

  va_start(params, constructorsignature);
  jobject object = JEnv->NewObjectV(jniclass, constructor, params);
  va_end(params);

  ANDROIDJNI::CheckJavaException();

  jniobject = JEnv->NewGlobalRef(object);
  JEnv->DeleteLocalRef(object);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDJNIOBJECT::~ANDROIDJNIOBJECT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDJNIOBJECT::~ANDROIDJNIOBJECT()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDJNIMETHOD ANDROIDJNIOBJECT::GetClassMethod(XSTRING method, XSTRING signature)
* @brief      GetClassMethod
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  signature : 
* 
* @return     ANDROIDJNIMETHOD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDJNIMETHOD ANDROIDJNIOBJECT::GetClassMethod(XSTRING method, XSTRING signature)
{
  ANDROIDJNIMETHOD m;

  m.name      = method;
  m.signature = signature;

  JNIEnv* env = ANDROIDJNI::GetJNIEnv();

  char* cmethod;
  char* csignature;

  method.CreateOEM(cmethod);
  signature.CreateOEM(csignature);

  m.method = env->GetMethodID(jniclass, cmethod, csignature);

  delete cmethod;
  delete csignature;

  return m;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         jstring ANDROIDJNIOBJECT::GetJString(const XSTRING& str)
* @brief      GetJString
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  XSTRING& str : 
* 
* @return     jstring : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
jstring ANDROIDJNIOBJECT::GetJString(const XSTRING& str)
{
  jstring r;

  char* cstr;
  str.CreateOEM(cstr);

  JNIEnv* env = ANDROIDJNI::GetJNIEnv();

  r = env->NewStringUTF(cstr);

  delete cstr;

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDJNIOBJECT::CallMethod<void>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<void>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
void ANDROIDJNIOBJECT::CallMethod<void>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  JEnv->CallVoidMethodV(jniobject, Method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool ANDROIDJNIOBJECT::CallMethod<bool>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<bool>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
bool ANDROIDJNIOBJECT::CallMethod<bool>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  bool RetVal = JEnv->CallBooleanMethodV(jniobject, Method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int ANDROIDJNIOBJECT::CallMethod<int>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<int>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
int ANDROIDJNIOBJECT::CallMethod<int>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  int RetVal = JEnv->CallIntMethodV(jniobject, Method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         jobject ANDROIDJNIOBJECT::CallMethod<jobject>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<jobject>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     jobject : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
jobject ANDROIDJNIOBJECT::CallMethod<jobject>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  jobject val = JEnv->CallObjectMethodV(jniobject, Method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  jobject RetVal = JEnv->NewGlobalRef(val);

  JEnv->DeleteLocalRef(val);

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         long long ANDROIDJNIOBJECT::CallMethod<long long>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<long long>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     long : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
long long ANDROIDJNIOBJECT::CallMethod<long long>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  long long RetVal = JEnv->CallLongMethodV(jniobject, Method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING ANDROIDJNIOBJECT::CallMethod<XSTRING>(ANDROIDJNIMETHOD Method, ...)
* @brief      CallMethod<XSTRING>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  Method : 
* @param[in]  ... : 
* 
* @return     XSTRING : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
XSTRING ANDROIDJNIOBJECT::CallMethod<XSTRING>(ANDROIDJNIMETHOD Method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, Method);
  jstring RetVal = static_cast<jstring>(JEnv->CallObjectMethodV(jniobject, Method.method, Params));
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  const char * UTFString = JEnv->GetStringUTFChars(RetVal, NULL);
  XSTRING Result(UTFString);

  JEnv->ReleaseStringUTFChars(RetVal, UTFString);

  return Result;
}


#pragma endregion