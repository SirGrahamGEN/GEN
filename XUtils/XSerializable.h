/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializable.h
* 
* @class      XSERIALIZABLE
* @brief      eXtended Utils Serializable class
* @ingroup    XUTILS
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

#ifndef _XSERIALIZABLE_H_
#define _XSERIALIZABLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XString.h"
#include "XBuffer.h"
#include "XVariant.h"
#include "XVector.h"

#ifdef XSERIALIZABLE_JSON_ACTIVE
#include "XFileJSON.h"
#endif

#include "XSerializationMethod.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XSERIALIZABLE
{
  public:

                                   XSERIALIZABLE        ();
    virtual                       ~XSERIALIZABLE        ();

    #ifdef XSERIALIZABLE_BINARY_ACTIVE
    static XSERIALIZATIONMETHOD*   CreateInstance       (XBUFFER& databinary); 
    #endif

    #ifdef XSERIALIZABLE_JSON_ACTIVE
    static XSERIALIZATIONMETHOD*   CreateInstance       (XFILEJSON& fileJSON);    
    #endif

    template<class T>
    bool                           Primitive_Add        (T var, XCHAR* name)
                                   {                               
                                     return serializationmethod->Add(var, name);                                 
                                   }

    template<class T>
    bool                           Primitive_Extract    (T var, XCHAR* name)
                                   {
                                     return serializationmethod->Extract(var, name);                               
                                   }

    template<class T>
    bool                           Class_Add            (T* var, XCHAR* name)
                                   {                                        
                                     if(!dynamic_cast<XSERIALIZABLE*>(var))
                                       {
                                         return false;
                                       }

                                     if(!var)
                                       {
                                         return false;
                                       }
                                
                                     serializationmethod->AddStruct(name, true);

                                     var->SetSerializationMethod(serializationmethod);
                                     bool status = var->Serialize();            
                                     
                                     serializationmethod->AddStruct(name, false);

                                     return status;
                                   }

    template<class T>
    bool                           Class_Extract        (T* var, XCHAR* name)
                                   {
                                     if(!var)
                                       {
                                         return false;
                                       }

                                     if(!dynamic_cast<XSERIALIZABLE*>(var))
                                       {
                                         return false;
                                       }
                                                                 
                                     var->SetSerializationMethod(serializationmethod);
                                     bool status = var->Deserialize(); 
                                                             
                                     return status;
                                   }                              
  
    template<class T>
    bool                           XVector_Add          (XVECTOR<T*>* var, XCHAR* name)
                                   { 
                                     if(!dynamic_cast<XSERIALIZABLE*>(var->Get(0)))  
                                       {
                                         return false;
                                       }
                                       
                                     serializationmethod->AddArray(var->GetSize(), name, true);                                                                               
                                     
                                     for(XDWORD c=0; c<var->GetSize(); c++)
                                       {
                                         T* element = var->Get(c);
                                         if(element)
                                           {
                                             element->SetSerializationMethod(serializationmethod);
                                             element->Serialize();               
                                           }                                       
                                       }

                                      serializationmethod->AddArray(var->GetSize(), name, false); 

                                     return true;                               
                                   }

    template<class T>
    bool                           XVector_Extract      (XVECTOR<T*>* var, XCHAR* name)
                                   {
                                     if(!dynamic_cast<XSERIALIZABLE*>(var->Get(0)))  
                                       {
                                         return false;
                                       }                                   
                                     
                                     for(XDWORD c=0; c<var->GetSize(); c++)
                                       {
                                         T* element = var->Get(c);
                                         if(element)
                                           {
                                             element->SetSerializationMethod(serializationmethod);
                                             element->Deserialize();               
                                           }                                       
                                       } 

                                     return true;                           
                                   }  
                                   
    template<class T>
    bool                           XVectorClass_Add          (XVECTOR<T*>* var, XCHAR* name, XCHAR* nameclass)
                                   { 
                                     if(!dynamic_cast<XSERIALIZABLE*>(var->Get(0)))  
                                       {
                                         return false;
                                       }
                                       
                                     serializationmethod->AddArray(var->GetSize(), name, true);                                                                               
                                     
                                     for(XDWORD c=0; c<var->GetSize(); c++)
                                       {
                                         T* element = var->Get(c);
                                         if(element)
                                           {
                                            element->SetSerializationMethod(serializationmethod);
                                            Class_Add<T>(element, nameclass);
                                           }                                       
                                       }

                                      serializationmethod->AddArray(var->GetSize(), name, false); 

                                     return true;                               
                                   }

    template<class T>
    bool                           XVectorClass_Extract      (XVECTOR<T*>* var, XCHAR* name, XCHAR* nameclass)
                                   {
                                     if(!dynamic_cast<XSERIALIZABLE*>(var->Get(0)))  
                                       {
                                         return false;
                                       }                                   
                                     
                                     for(XDWORD c=0; c<var->GetSize(); c++)
                                       {
                                         T* element = var->Get(c);
                                         if(element)
                                           {
                                             element->SetSerializationMethod(serializationmethod);
                                             Class_Extract<T>(element, nameclass);
                                           }                                       
                                       } 

                                     return true;                           
                                   }                             

    XSERIALIZATIONMETHOD*          GetSerializationMethod     ();
    void                           SetSerializationMethod     (XSERIALIZATIONMETHOD* serializationmethod);

    bool                           DoSerialize                ();    
    bool                           DoDeserialize              ();   

    bool                           DoSerialize                (XSERIALIZATIONMETHOD* serializationmethod);    
    bool                           DoDeserialize              (XSERIALIZATIONMETHOD* serializationmethod);   

    virtual bool                   Update                     ();

    virtual bool                   Serialize                  ();    
    virtual bool                   Deserialize                ();  
    
  private:

    void                           Clean                      ();   

    XSERIALIZATIONMETHOD*          serializationmethod; 
       
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

