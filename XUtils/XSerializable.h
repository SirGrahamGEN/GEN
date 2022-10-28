/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializable.h
* 
* @class      XSERIALIZABLE
* @brief      eXtended Serializable base class
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

//#include "nameof.hpp"

#include "XBase.h"
#include "XString.h"
#include "XBuffer.h"
#include "XVector.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSERIALIZATIONMETHOD
{
  public:
                                   XSERIALIZATIONMETHOD ();
    virtual                       ~XSERIALIZATIONMETHOD ();

    virtual bool                   Add                  (bool var)        = 0; 
    virtual bool                   Add                  (char var)        = 0;  
    virtual bool                   Add                  (int var)         = 0;  
    virtual bool                   Add                  (float var)       = 0;  
    virtual bool                   Add                  (double var)      = 0; 
    virtual bool                   Add                  (long var)        = 0; 
    virtual bool                   Add                  (long long var)   = 0;  

    virtual bool                   Add                  (XBYTE var)       = 0;  
    virtual bool                   Add                  (XWORD var)       = 0;  
    virtual bool                   Add                  (XDWORD var)      = 0; 
    virtual bool                   Add                  (XQWORD var)      = 0; 
    
    virtual bool                   Add                  (XSTRING& var)    = 0;       
    virtual bool                   Add                  (XBUFFER& var)    = 0;


    virtual bool                   Extract              (bool var)        = 0; 
    virtual bool                   Extract              (char var)        = 0;  
    virtual bool                   Extract              (int var)         = 0;  
    virtual bool                   Extract              (float var)       = 0;  
    virtual bool                   Extract              (double var)      = 0; 
    virtual bool                   Extract              (long var)        = 0; 
    virtual bool                   Extract              (long long var)   = 0;  

    virtual bool                   Extract              (XBYTE var)       = 0;  
    virtual bool                   Extract              (XWORD var)       = 0;  
    virtual bool                   Extract              (XDWORD var)      = 0; 
    virtual bool                   Extract              (XQWORD var)      = 0; 
    
    virtual bool                   Extract              (XSTRING& var)    = 0;       
    virtual bool                   Extract              (XBUFFER& var)    = 0;
    
  private:

    void                           Clean                ();   
};


class XSERIALIZABLE
{
  public:

                                   XSERIALIZABLE        ();
    virtual                       ~XSERIALIZABLE        ();

    static XSERIALIZATIONMETHOD*   CreateBinary         (XBUFFER& databinary);    

    template<class T>
    bool                           Primitive_Add        (T var, XCHAR* name)
                                   {                               
                                     serialization->Add(var);
                                 
                                     return true;
                                   }

    template<class T>
    bool                           Primitive_Extract    (T var, XCHAR* name)
                                   {
                                     serialization->Extract(var);
                               
                                     return true; 
                                   }

    template<class T>
    bool                           Class_Add            (T* var, XCHAR* name)
                                   {                                        
                                     if(!dynamic_cast<XSERIALIZABLE*>(var))
                                       {
                                         return false;
                                       }

                                     if(var)
                                       {
                                         return false;
                                       }
                                
                                     var->SetSerialization(serialization);
                                     return var->Serialize();                                 
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
                            
                                     var->SetSerialization(serialization);
                                     return var->Deserialize();                                 
                                   }                              
  
    template<class T>
    bool                           XVector_Add          (XVECTOR<T*>* var, XCHAR* name)
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
                                             element->SetSerialization(serialization);
                                             element->Serialize();               
                                           }                                       
                                       }

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
                                             element->SetSerialization(serialization);
                                             element->Deserialize();               
                                           }                                       
                                       } 

                                     return true;                           
                                   }                             

    XSERIALIZATIONMETHOD*          GetSerialization     ();
    void                           SetSerialization     (XSERIALIZATIONMETHOD* serialization);

    bool                           InitSerialize        (XSERIALIZATIONMETHOD* serialization);    
    bool                           InitDeserialize      (XSERIALIZATIONMETHOD* serialization);   

    virtual bool                   Serialize            ();    
    virtual bool                   Deserialize          ();  
    

  protected:

    bool                           Serialize            (XSERIALIZATIONMETHOD* serialization);    
    bool                           Deserialize          (XSERIALIZATIONMETHOD* serialization);   

  private:

    void                           Clean                ();   

    XSERIALIZATIONMETHOD*          serialization; 
       
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

