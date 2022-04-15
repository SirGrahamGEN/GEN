/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFileWAV.h
*
* @class      SNDFILEWAV
* @brief      Sound File WAV format class
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

#ifndef _SNDFILEWAV_H_
#define _SNDFILEWAV_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XFile.h"
#include "XPath.h"

#include "SNDFileBase.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFILERIFF;
class XFILERIFF_LIST;

typedef struct 
{
  XWORD                     audio_format;
  XWORD                     num_channels;
  XDWORD                    sample_rate;            
  XDWORD                    byte_rate;
  XWORD                     block_align;
  XWORD                     bits_per_sample;

} SNDFILEWAV_FORMAT;



class SNDFILEWAV : public SNDFILEBASE
{
  public:    
                            SNDFILEWAV                      ();                             
    virtual                ~SNDFILEWAV                      ();
 
    bool                    Open                            (XCHAR* path, XCHAR* ID);    
    bool                    ReadData                        (XBYTE* data, XDWORD& sizeread, bool& isfinished); 
    
    XDWORD                  GetDataSize                     (); 
    XDWORD                  GetReadSize                     (); 
    
    bool                    Close                           ();
    
    SNDFILEWAV_FORMAT*      GetFormat                       ();

    using                   SNDFILEBASE::Open;        
    using                   SNDFILEBASE::ReadData;        
    
  private:

    void                    Clean                           ();    

    XFILERIFF*              fileRIFF;
    XFILERIFF_LIST*         format_list;
    XFILERIFF_LIST*         data_list;

    SNDFILEWAV_FORMAT       format;  

    XQWORD                  dataoffsetinfile;  
    XDWORD                  datasizeinfile;
    XDWORD                  datasizeread; 

};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



