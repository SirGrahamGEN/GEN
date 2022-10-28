/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializableBinary.h
* 
* @class      XSERIALIZABLEBINARY
* @brief      eXtended Serializable binary class
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

#ifndef _XSERIALIZABLEBINARY_H_
#define _XSERIALIZABLEBINARY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XSerializable.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class XSERIALIZATIONMETHODBINARY : public XSERIALIZATIONMETHOD
{
  public:
                             XSERIALIZATIONMETHODBINARY     ();
    virtual                 ~XSERIALIZATIONMETHODBINARY     ();

    virtual bool             Add                            (bool var); 
    virtual bool             Add                            (char var);  
    virtual bool             Add                            (int var);  
    virtual bool             Add                            (float var);  
    virtual bool             Add                            (double var); 
    virtual bool             Add                            (long var); 
    virtual bool             Add                            (long long var); 
    
    virtual bool             Add                            (XBYTE var);  
    virtual bool             Add                            (XWORD var);  
    virtual bool             Add                            (XDWORD var); 
    virtual bool             Add                            (XQWORD var); 
    
    virtual bool             Add                            (XSTRING& var);       
    virtual bool             Add                            (XBUFFER& var);


    virtual bool             Extract                        (bool var); 
    virtual bool             Extract                        (char var);  
    virtual bool             Extract                        (int var);  
    virtual bool             Extract                        (float var);  
    virtual bool             Extract                        (double var); 
    virtual bool             Extract                        (long var); 
    virtual bool             Extract                        (long long var); 

    virtual bool             Extract                        (XBYTE var);  
    virtual bool             Extract                        (XWORD var);  
    virtual bool             Extract                        (XDWORD var); 
    virtual bool             Extract                        (XQWORD var); 
    
    virtual bool             Extract                        (XSTRING& var);       
    virtual bool             Extract                        (XBUFFER& var);

    XBUFFER*                 GetBufferData                  (); 
    void                     SetBufferData                  (XBUFFER* bufferdata); 

  private:

    void                     Clean                          ();   

    XBUFFER*                 bufferdata; 
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

