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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "ANDROIDJNIObject.h"

#include "ANDROIDJNI.h"

#include <stdarg.h>

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDJNIOBJECT::ANDROIDJNIOBJECT(XSTRING classname, XSTRING constructorsignature, ...)
* @brief      Constructor of class
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  classname : 
* @param[in]  constructorsignature : 
* @param[in]  ... : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDJNIOBJECT::ANDROIDJNIOBJECT(XSTRING classname, XSTRING constructorsignature, ...)

{
  JNIEnv*   JEnv = ANDROIDJNI::GetJNIEnv();
  char*     cstr = NULL;
  
  classname.CreateOEM(cstr);

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
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDJNIOBJECT::~ANDROIDJNIOBJECT()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDJNIMETHOD ANDROIDJNIOBJECT::GetClassMethod(XSTRING method, XSTRING signature)
* @brief      Get class method
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
* @brief      Get J string
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  str : 
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
* @fn         void ANDROIDJNIOBJECT::CallMethod<void>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method<void>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
void ANDROIDJNIOBJECT::CallMethod<void>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  JEnv->CallVoidMethodV(jniobject, method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool ANDROIDJNIOBJECT::CallMethod<bool>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method<bool>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
bool ANDROIDJNIOBJECT::CallMethod<bool>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  bool RetVal = JEnv->CallBooleanMethodV(jniobject, method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int ANDROIDJNIOBJECT::CallMethod<int>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method<int>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
int ANDROIDJNIOBJECT::CallMethod<int>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  int RetVal = JEnv->CallIntMethodV(jniobject, method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         jobject ANDROIDJNIOBJECT::CallMethod<jobject>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method<jobject>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* @return     jobject : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
jobject ANDROIDJNIOBJECT::CallMethod<jobject>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  jobject val = JEnv->CallObjectMethodV(jniobject, method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  jobject RetVal = JEnv->NewGlobalRef(val);

  JEnv->DeleteLocalRef(val);

  return RetVal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         long long ANDROIDJNIOBJECT::CallMethod<long long>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method<long long>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* @return     long : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
template<>
long long ANDROIDJNIOBJECT::CallMethod<long long>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  long long RetVal = JEnv->CallLongMethodV(jniobject, method.method, Params);
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  return RetVal;
}


template<>
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING ANDROIDJNIOBJECT::CallMethod<XSTRING>(ANDROIDJNIMETHOD method, ...)
* @brief      Call method< XSTRING>
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  method : 
* @param[in]  ... : 
* 
* @return     XSTRING : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING ANDROIDJNIOBJECT::CallMethod<XSTRING>(ANDROIDJNIMETHOD method, ...)
{
  JNIEnv* JEnv = ANDROIDJNI::GetJNIEnv();

  va_list Params;

  va_start(Params, method);
  jstring RetVal = static_cast<jstring>(JEnv->CallObjectMethodV(jniobject, method.method, Params));
  va_end(Params);

  ANDROIDJNI::CheckJavaException();

  const char * UTFString = JEnv->GetStringUTFChars(RetVal, NULL);
  XSTRING Result(UTFString);

  JEnv->ReleaseStringUTFChars(RetVal, UTFString);

  return Result;
}


#pragma endregion
