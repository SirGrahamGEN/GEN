/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFileBase.h
*
* @class      SNDFILEBASE
* @brief      Sound File Base class
* @ingroup    SOUND
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _SNDFILEBASE_H_
#define _SNDFILEBASE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XFile.h"
#include "XPath.h"
#include "XString.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class SNDFILEBASE 
{
  public:

                                    SNDFILEBASE                           ();    
    virtual                        ~SNDFILEBASE                           ();
    
    XSTRING*                        GetID                                 ();
    
    XWORD                           GetChannels                           ();
    XDWORD                          GetNSamples                           ();
    XDWORD                          GetSampleRate                         ();    
    float                           GetDuration                           ();

    virtual bool                    Open                                  (XCHAR* path , XCHAR* ID);   
    bool                            Open                                  (XPATH& xpath , XCHAR* ID);   
    
    virtual bool                    ReadData                              (XBYTE* data, XDWORD& sizeread, bool& isfinished);
    bool                            ReadData                              (XBUFFER& data, bool& isfinished);   

    virtual XDWORD                  GetDataSize                           (); 
    virtual XDWORD                  GetReadSize                           (); 

    virtual bool                    Close                                 ();
    
  protected:
      
    XSTRING                         ID;
    
    XWORD                           channels;
    XDWORD                          nsamples;
    XDWORD                          samplerate;
    float                           duration;   

    
  private:

    void                            Clean                                 ();                                 
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


