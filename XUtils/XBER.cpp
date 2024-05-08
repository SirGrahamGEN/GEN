/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XBER.cpp
* 
* @class      XBER
* @brief      eXtended Utils Basic Encoding Rules (BER) encoding class (https://en.wikipedia.org/wiki/X.690)
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBER.h"

#include "XTrace.h"
#include "XASN1.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XDWORD XBER::totalposition = 0;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBER::XBER()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XBER::XBER()
{
  Clean();

  data.Empty();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBER::~XBER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XBER::~XBER()
{
  Sequence_DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE XBER::GetTagType()
* @brief      GetTagType
* @ingroup    XUTILS
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBER::GetTagType()
{
  return (XBYTE)tagtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::GetTagTypeName(XSTRING& name)
* @brief      GetTagTypeName
* @ingroup    XUTILS
* 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::GetTagTypeName(XSTRING& name)
{
  name.Empty();

  switch(GetTagType())
    {
      case XBER_TAGTYPE_CONTEXT_SPECIFIC     : name = __L("CONTEXT_SPECIFIC");	          break;
      case XBER_TAGTYPE_BOOLEAN	             : name = __L("BOOLEAN");	  	                break;
      case XBER_TAGTYPE_INTEGER	             : name = __L("INTEGER");	  	                break;
      case XBER_TAGTYPE_BIT_STRING	         : name = __L("BIT STRING");	  	            break;
      case XBER_TAGTYPE_OCTET_STRING         : name = __L("OCTET STRING");	  	          break;
      case XBER_TAGTYPE_NULL                 : name = __L("NULL");	  	                  break;
      case XBER_TAGTYPE_OBJECT_IDENTIFIER    : name = __L("OBJECT IDENTIFIER");	  	      break;
      case XBER_TAGTYPE_OBJECT_DESCRIPTOR    : name = __L("Object Descriptor");	  	      break;
      case XBER_TAGTYPE_EXTERNAL             : name = __L("EXTERNAL");	  	              break;
      case XBER_TAGTYPE_REAL                 : name = __L("REAL (float)");	  	          break;
      case XBER_TAGTYPE_ENUMERATED           : name = __L("ENUMERATED");	  	            break;
      case XBER_TAGTYPE_EMBEDDED_PDV         : name = __L("EMBEDDED PDV");	  	          break;
      case XBER_TAGTYPE_UTF8STRING           : name = __L("UTF8String");	  	            break;
      case XBER_TAGTYPE_RELATIVE_OID         : name = __L("RELATIVE-OID");	  	          break;
      case XBER_TAGTYPE_TIME                 : name = __L("TIME");	  	                  break;
      case XBER_TAGTYPE_RESERVED             : name = __L("Reserved");	  		            break;
      case XBER_TAGTYPE_SEQUENCE             : name = __L("SEQUENCE");	                  break;
      case XBER_TAGTYPE_SET                  : name = __L("SET");	  	                    break;
      case XBER_TAGTYPE_NUMERICSTRING        : name = __L("NumericString");	  	          break;
      case XBER_TAGTYPE_PRINTABLESTRING      : name = __L("PrintableString");	  	        break;
      case XBER_TAGTYPE_T61STRING            : name = __L("T61String");	  	              break;
      case XBER_TAGTYPE_VIDEOTEXSTRING       : name = __L("VideotexString");	  	        break;
      case XBER_TAGTYPE_IA5STRING            : name = __L("IA5String");	  	              break;
      case XBER_TAGTYPE_UTCTIME              : name = __L("UTCTime");	  	                break;
      case XBER_TAGTYPE_GENERALIZEDTIME      : name = __L("GeneralizedTime");	  	        break;
      case XBER_TAGTYPE_GRAPHICSTRING        : name = __L("GraphicString");	  	          break;
      case XBER_TAGTYPE_VISIBLESTRING        : name = __L("VisibleString");	  	          break;
      case XBER_TAGTYPE_GENERALSTRING        : name = __L("GeneralString");	  	          break;
      case XBER_TAGTYPE_UNIVERSALSTRING      : name = __L("UniversalString");	  	        break;
      case XBER_TAGTYPE_CHARACTER_STRING     : name = __L("CHARACTER STRING");	  	      break;
      case XBER_TAGTYPE_BMPSTRING            : name = __L("BMPString");	  		            break;
      case XBER_TAGTYPE_DATE                 : name = __L("DATE");	  	                  break;
      case XBER_TAGTYPE_TIME_OF_DAY          : name = __L("TIME-OF-DAY");	  	            break;
      case XBER_TAGTYPE_DATE_TIME            : name = __L("DATE-TIME");	  	              break;
      case XBER_TAGTYPE_DURATION             : name = __L("DURATION");	  	              break;
      case XBER_TAGTYPE_OID_IRI              : name = __L("OID-IRI");	  	                break;
      case XBER_TAGTYPE_RELATIVE_OID_IRI     : name = __L("RELATIVE-OID-IRI");	  	      break;
    }

  return (!name.IsEmpty());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBER_TAGCLASS XBER::GetTagClass()
* @brief      GetTagClass
* @ingroup    XUTILS
* 
* @return     XBER_TAGCLASS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBER_TAGCLASS XBER::GetTagClass()
{
  return tagclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::IsConstructed()
* @brief      IsConstructed
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::IsConstructed()
{
  return isconstructed;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XBER::GetSizeHead()
* @brief      Get Size Head of BER
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBER::GetSizeHead()
{
  return sizehead;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBER::GetSize()
* @brief      Get size of BER
* @ingroup    XUTILS
*
* @return     XDWORD : size of BER
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBER::GetSize()
{
  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* XBER::GetData()
* @brief      Get data of BER
* @ingroup    XUTILS
*
* @return     XBUFFER* : buffer of data
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* XBER::GetData()
{
  return &data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* XBER::GetValue()
* @brief      GetValue
* @ingroup    XUTILS
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* XBER::GetValue()
{
  return &value;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::GetDump(XBUFFER& xbuffer, bool notheader)
* @brief      GetDump
* @ingroup    XUTILS
*
* @param[in]  xbuffer : 
* @param[in]  notheader : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XBER::GetDump(XBUFFER& xbuffer, bool notheader)
{
  if(!notheader)
    {
      xbuffer.Add((XBYTE)tagtype);

      XBUFFER sizedata;
      if(CodeSize(size, sizedata) && tagtype != XBER_TAGTYPE_NULL) xbuffer.Add(&sizedata);
    }

  if(data.GetSize()) xbuffer.Add(data.Get(), data.GetSize());

  for(XDWORD c=0;c<sequences.GetSize();c++)
    {
      XBER* xber = (XBER*)sequences.Get(c);
      if(xber) xber->GetDump(xbuffer);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::SetFromDump(XBUFFER& buffer)
* @brief      SetFromDump
* @ingroup    XUTILS
* 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetFromDump(XBUFFER& buffer)
{
  totalposition = 0;
  
  return SetFromDumpInternal(buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::SetTagType(XBYTE tagtype)
* @brief      SetTagType
* @ingroup    XUTILS
* 
* @param[in]  tagtype : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetTagType(XBYTE tagtype)
{
  this->tagtype = tagtype;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::SetSize(XDWORD size)
* @brief      SetSize
* @ingroup    XUTILS
*
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetSize(XDWORD size)
{
  this->size = size;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetNULL()
* @brief      Set BER to NULL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetNULL()
{
  data.Delete();

  data.Add((XBYTE)0);

  tagtype = XBER_TAGTYPE_NULL;
  size    = 0;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetINTEGER(XDWORD integer)
* @brief      Set Integet to BER
* @ingroup    XUTILS
*
* @param[in]  integer : integer to assign
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetINTEGER(XDWORD integer)
{ 
  data.Delete();

  XDWORD size = 0;

  if(integer&0xFF800000)
    {
      size = 4;
    }
   else
    {
      if(integer&0x00FF8000)
        {
          size = 3;
        }
       else
        {
          if(integer&0x0000FF80)
            {
              size = 2;
            }
           else
            {
              size = 1;
            }
        }
    }

  if(!size) return false;

  for(int c=(size-1);c>=0;c--)
    {
      XBYTE byte = (XBYTE)((c?(integer>>(c*8)):(integer))&0xFF);

      data.Add((XBYTE)byte);
    }

  tagtype = XBER_TAGTYPE_INTEGER;
  this->size = size;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetINTEGER(XBUFFER& xbufferdata)
* @brief      Set BER to integer
* @ingroup    XUTILS
*
* @param[in]  xbufferdata : buffer to assign
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetINTEGER(XBUFFER& xbufferdata)
{
  data.Delete();

  data.Add(xbufferdata);

  tagtype = XBER_TAGTYPE_INTEGER;
  size    = xbufferdata.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetBITSTRING(XBUFFER& xbuffer)
* @brief      Set Bit String to BER
* @ingroup    XUTILS
*
* @param[in]  xbuffer : buffer to assign
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetBITSTRING(XBUFFER& xbuffer)
{
  if(!xbuffer.GetSize()) return false;
  
  data.Delete();

  data.Add(xbuffer);

  tagtype = XBER_TAGTYPE_BIT_STRING;
  size    = xbuffer.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetBITSTRING(XBYTE* buffer, XDWORD size)
* @brief      Set Bit String to BER
* @ingroup    XUTILS
*
* @param[in]  buffer : pointer to buffer bytes
* @param[in]  size : size buffer
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetBITSTRING(XBYTE* buffer, XDWORD size)
{
  if(!buffer) return false;
  if(!size)   return false;
  
  data.Delete();

  data.Add(buffer, size);

  tagtype = XBER_TAGTYPE_BIT_STRING;
  this->size    = size;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetOCTETSTRING(XCHAR* string)
* @brief      Set Octet string to BER
* @ingroup    XUTILS
*
* @param[in]  string : string with octets
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetOCTETSTRING(XCHAR* string)
{
  if(!string)    return false;
  if(!string[0]) return false;
  
  data.Delete();

  XSTRING _string;

  _string = string;

  XBUFFER charstr;
  
  _string.ConvertToASCII(charstr);
 
  data.Add((XBYTE*)charstr.Get(), _string.GetSize());
  
  tagtype = XBER_TAGTYPE_OCTET_STRING;
  size    = _string.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetOCTETSTRING(XBUFFER& xbuffer)
* @brief      Set Octet string to BER
* @ingroup    XUTILS
*
* @param[in]  xbuffer : buffer with octets
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetOCTETSTRING(XBUFFER& xbuffer)
{
  if(!xbuffer.GetSize()) return false;
  
  data.Delete();

  data.Add(xbuffer);

  tagtype = XBER_TAGTYPE_OCTET_STRING;
  size    = xbuffer.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetOCTETSTRING(XBYTE* buffer, XDWORD size)
* @brief      Set Octet string to BER
* @ingroup    XUTILS
*
* @param[in]  buffer : pointer buffer with octets
* @param[in]  size : size of buffer
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetOCTETSTRING(XBYTE* buffer, XDWORD size)
{
  if(!buffer) return false;
  if(!size)   return false;
  
  data.Delete();

  data.Add(buffer, size);

  tagtype = XBER_TAGTYPE_OCTET_STRING;
  this->size    = size;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::SetOID(XCHAR* OIDstring)
* @brief      Set OID
* @ingroup    XUTILS
*
* @param[in]  OIDstring : OID to assign
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetOID(XCHAR* OIDstring)
{
  if(!OIDstring)    return false;
  if(!OIDstring[0]) return false;
  
  data.Delete();

  XSTRING       string;
  XVECTOR<int>  numbers;
  int           start = 0;
  int           end   = 0;

  string = OIDstring;

  while(1)
    {
      XSTRING numberstring;
      int     indexstring = string.Find(__L("."),true,start);

      if(indexstring != XSTRING_NOTFOUND)
        {
          end = indexstring;
          string.Copy(start,end,numberstring);
          numbers.Add(numberstring.ConvertToInt());
          start = end+1;
        }
       else
        {
          string.Copy(end+1,numberstring);
          numbers.Add(numberstring.ConvertToInt());

          break;
        }
    }

  if(!numbers.GetSize()) return false;

  //---------------------------------------------------
  // The firts 2 bytes are special
  //

  size_t _first = (size_t)(numbers.Get(0));
  int first = (int)_first;

  first *= (40);
  _first = (size_t)(numbers.Get(1));
  first += (int)(_first);

  data.Add((XBYTE)first);

  for(XDWORD c=2;c<numbers.GetSize();c++)
    {
      XBUFFER _data;

      size_t _number = (size_t)(numbers.Get(c));
      XDWORD number = (XDWORD)(_number);

      if(CodeBigNumber((XDWORD)(number),_data))
        {
          data.Add(_data.Get(),_data.GetSize());
        }
    }

  this->tagtype = XBER_TAGTYPE_OBJECT_IDENTIFIER;
  this->size    = data.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::Copy(XBER* newxber)
* @brief      Copy XBER from pointer *BER
* @ingroup    XUTILS
*
* @param[in]  newxber : pointer to new BER to assign
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::Copy(XBER* newxber)
{
  if(!newxber)       return false;
 
  newxber->tagtype  = tagtype;
  newxber->size     = size;
 
  newxber->data.Delete();
  newxber->data.Add(data.Get(),data.GetSize());

  for(XDWORD c=0;c<sequences.GetSize();c++)
    {
      XBER* xbertmp = (XBER*)sequences.Get(c);
      if(xbertmp)
        {
          XBER* newxberseq = new XBER();
          if(newxberseq)
            {
              if(xbertmp->Copy(newxberseq))  newxber->sequences.Add(newxberseq);
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::Sequence_AddTo(XBER& xber)
* @brief      Add BER to secuence
* @ingroup    XUTILS
*
* @param[in]  xber : XBER to add in secuence
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::Sequence_AddTo(XBER& xber)
{
  data.Delete();

  XBER* newxber = new XBER();
  if(!newxber) return false;

  if(!xber.Copy(newxber))
    {
      delete newxber;
      return false;
    }

  sequences.Add(newxber);

  tagtype = XBER_TAGTYPE_SEQUENCE;
  size    = 0;

  for(XDWORD c=0;c<sequences.GetSize();c++)
    {
      XBER* xber = (XBER*)sequences.Get(c);
      if(xber) size += xber->Sequence_GetSize();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XBER*>* XBER::Sequence_GetSequences()
* @brief      Sequence_GetSequences
* @ingroup    XUTILS
* 
* @return     XVECTOR<XBER*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XBER*>* XBER::Sequence_GetSequences()
{
  return &sequences;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::Sequence_AddCommandTo(XBYTE command, XBER& xber)
* @brief      Sequence_AddCommandTo
* @ingroup    XUTILS
*
* @param[in]  command : 
* @param[in]  xber : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XBER::Sequence_AddCommandTo(XBYTE command, XBER& xber)
{ 
  data.Delete();

  xber.GetDump(data, true);

  this->tagtype = command;
  this->size    = data.GetSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBER::Sequence_GetSize()
* @brief      Get Secuence size
* @ingroup    XUTILS
*
* @return     XDWORD : size secuence
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBER::Sequence_GetSize()
{
  XDWORD  sizeall = 0;

  // Size type
  if(tagtype != XBER_TAGTYPE_NULL) sizeall++;

  // Size of size;
  XBUFFER sizedata;

  CodeSize(size,sizedata);
  sizeall += sizedata.GetSize();

  sizeall += data.GetSize();

  for(XDWORD c=0;c<sequences.GetSize();c++)
    {
      XBER* xber = (XBER*)sequences.Get(c);
      if(xber) sizeall += xber->Sequence_GetSize();
    }

  return sizeall;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::Sequence_DeleteAll()
* @brief      Delete all secuence
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::Sequence_DeleteAll()
{
  if(sequences.IsEmpty()) return false;

  sequences.DeleteContents();

  sequences.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::SetFromDumpInternal(XBUFFER& buffer)
* @brief      SetFromDumpInternal
* @ingroup    XUTILS
* 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::SetFromDumpInternal(XBUFFER& buffer)
{
  static XASN1_OID_PROPERTY*  property  = NULL;
  static XBYTE                level     = 0;
  XSTRING                     line;
  
  if(buffer.IsEmpty()) return false;

  tagtype = (XBYTE)(buffer.Get()[0] & XBER_TAG_MASKTYPE); 

  if(!CalculeSize(buffer, size, sizehead)) return false;  
  
  tagclass = XBER_TAG_CLASS(buffer.Get()[0]);

  switch(tagclass)
    {
      case XBER_TAGCLASS_UNIVERSAL	      : break;

      case XBER_TAGCLASS_APPLICATION	    : break;

      case XBER_TAGCLASS_CONTEXT_SPECIFIC	: contextspecificvalue = tagtype;
                                            tagtype = XBER_TAGTYPE_CONTEXT_SPECIFIC;
                                            break;

      case XBER_TAGCLASS_PRIVATE          :	break;
    } 

  GetTagTypeName(nametagtype);
  
  isconstructed =  ((buffer.Get()[0] & XBER_TAG_MASKISCONSTRUCTED) == XBER_TAG_MASKISCONSTRUCTED)?true:false;

  data.Delete();
  data.Add(&buffer.Get()[sizehead], size);

  line.Format(__L("(%d, %d) %s"), totalposition, size, nametagtype.Get());  

  switch(tagtype)
   {   
     case XBER_TAGTYPE_CONTEXT_SPECIFIC    : line.AddFormat(__L(" (%d) "), contextspecificvalue);  
                                             break;

     case XBER_TAGTYPE_OBJECT_IDENTIFIER  : { XSTRING valuestr;
      
                                              ConvertToObjetIdentifier(data, value);
                                              value.ToString(valuestr);

                                              property = XASN1::GetOIDProperty(valuestr.Get());
                                              if(property)
                                                {
                                                  line.AddFormat(__L(": %s :"), property->description);  
                                                  
                                                  if(!property->isconstructed)
                                                    {
                                                      property = NULL;
                                                    }
                                                }
                                            }

                                            break;

     case XBER_TAGTYPE_BIT_STRING         : unusedbits = data.Get()[0];   
                                            data.Extract(NULL, 0, 1);                                            
                                            line.AddFormat(__L(" UnusedBits: %d "), unusedbits);                                                                           
                                            if(property)
                                              {
                                                isconstructed = property->isconstructed;
                                                if(isconstructed) totalposition++;
                                              }

                                            property = NULL;                                               
                                            break;

     case XBER_TAGTYPE_OCTET_STRING       : if(property)
                                              {
                                                isconstructed = property->isconstructed;  
                                              }

                                            property = NULL;                                            
                                            break;

                          default         : break;
   }

  if(isconstructed)  
    { 
      XBUFFER subdata;
      XBER*   sub_ber  = NULL; 
      XDWORD  position = 0;    

      XTRACE_PRINTTAB(level, line.Get(), NULL);  
      //XTRACE_PRINTDATABLOCKTAB(level, buffer.Get(), sizehead);
       
      level++;          

      totalposition += sizehead;           

      subdata.Delete();
      subdata.Add(data.Get(), data.GetSize());          
      
      while(subdata.GetSize())
        {                  
          sub_ber = new XBER();
          if(sub_ber) 
            {                           
              if(!sub_ber->SetFromDumpInternal(subdata))
                {
                  delete sub_ber;    
                  sub_ber = NULL;

                  return false;  
                }
               else
                {                
                  sequences.Add(sub_ber);
                    
                  int addsize = sub_ber->GetSizeHead() + sub_ber->GetSize();    
                  
                  position += addsize;                                                                                     
                  
                  subdata.Extract(NULL, 0, addsize);
                }            
                
            } else return false;
        }

      level--;
    } 
   else
    {
      switch(tagtype)
        {  
          case XBER_TAGTYPE_CONTEXT_SPECIFIC    : break;

          case XBER_TAGTYPE_BOOLEAN	            : ConvertToBoolean(data, value);
                                                  break;

          case XBER_TAGTYPE_INTEGER	            : ConvertToInteger(data, value);
                                                  break;

          case XBER_TAGTYPE_BIT_STRING	        : ConvertToBitString(data, value);                                                  
                                                  break;

          case XBER_TAGTYPE_OCTET_STRING        : ConvertToOctetString(data, value);
                                                  break;

          case XBER_TAGTYPE_NULL                : value.Set();
                                                  break;

          case XBER_TAGTYPE_OBJECT_IDENTIFIER   : ConvertToObjetIdentifier(data, value);                                                  
                                                  break;

          case XBER_TAGTYPE_OBJECT_DESCRIPTOR   : break;
          case XBER_TAGTYPE_EXTERNAL            : break;
          case XBER_TAGTYPE_REAL                : break;
          case XBER_TAGTYPE_ENUMERATED          : break;
          case XBER_TAGTYPE_EMBEDDED_PDV        : break;
          case XBER_TAGTYPE_UTF8STRING          : break;
          case XBER_TAGTYPE_RELATIVE_OID        : break;
          case XBER_TAGTYPE_TIME                : break;
          case XBER_TAGTYPE_RESERVED            : break;
          case XBER_TAGTYPE_SEQUENCE            : break;
          case XBER_TAGTYPE_SET                 : break;
          case XBER_TAGTYPE_NUMERICSTRING       : break;

          case XBER_TAGTYPE_PRINTABLESTRING     : ConvertToPrintableString(data, value);
                                                  break;

          case XBER_TAGTYPE_T61STRING           : break;
          case XBER_TAGTYPE_VIDEOTEXSTRING      : break;
          case XBER_TAGTYPE_IA5STRING           : break;

          case XBER_TAGTYPE_UTCTIME             : ConvertToUTCTime(data, value);
                                                  break;

          case XBER_TAGTYPE_GENERALIZEDTIME     : break;
          case XBER_TAGTYPE_GRAPHICSTRING       : break;
          case XBER_TAGTYPE_VISIBLESTRING       : break;
          case XBER_TAGTYPE_GENERALSTRING       : break;
          case XBER_TAGTYPE_UNIVERSALSTRING     : break;
          case XBER_TAGTYPE_CHARACTER_STRING    : break;
          case XBER_TAGTYPE_BMPSTRING           : break;
          case XBER_TAGTYPE_DATE                : break;
          case XBER_TAGTYPE_TIME_OF_DAY         : break;
          case XBER_TAGTYPE_DATE_TIME           : break;
          case XBER_TAGTYPE_DURATION            : break;
          case XBER_TAGTYPE_OID_IRI             : break;
          case XBER_TAGTYPE_RELATIVE_OID_IRI    : break;
        }            


      if(!value.IsNull())
        {
          XSTRING valuestr;

          value.ToString(valuestr);

          if(!valuestr.IsEmpty())
            {     
              line.AddFormat(__L(" '%s' "), valuestr.Get());  
            }         
        }

      XTRACE_PRINTTAB(level, line.Get(), NULL);        

      totalposition += sizehead + size;     
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToBoolean(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToBoolean
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToBoolean(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 
    
  string.Format(__L("%s"), data.Get()[0]?__L("True"):__L("False"));
  
  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToInteger(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToInteger
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToInteger(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 

  if(data.GetSize() <= 4)
    {
      XDWORD integerdec = 0;

      for(int c=0; c<data.GetSize(); c++)
        {
          integerdec |= data.Get()[c];
          if(c != data.GetSize() -1) integerdec <<= 8;
        }   

      string.Format(__L("%d"), integerdec);
    }
   else
    { 
      for(int c=0; c<data.GetSize(); c++)
        {
          string.AddFormat(__L("%02X"), data.Get()[c]);
        }
    }
  
  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToOctetString(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToOctetString
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToOctetString(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 

  for(int c=0; c<data.GetSize(); c++)
    {
      string.AddFormat(__L("%02X"), data.Get()[c]);
    }

  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToBitString(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToBitString
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToBitString(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 

  for(int c=0; c<data.GetSize(); c++)
    {
      string.AddFormat(__L("%02X"), data.Get()[c]);
    }

  variant = string;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToNULL(XVARIANT& variant)
* @brief      ConvertToNULL
* @ingroup    XUTILS
* 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToNULL(XVARIANT& variant)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToObjetIdentifier(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToObjetIdentifier
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToObjetIdentifier(XBUFFER& data, XVARIANT& variant)
{  
  XSTRING string;      
  int     length  = data.GetSize();
  XBYTE*  bits    = data.Get();
 
  if(length < 2 && !(length == 1 && bits[0] == 0))
    {
      return false; 
    }

  string.Format(__L("%d.%d"), (data.Get()[0]/40), (data.Get()[0]%40));
   
  size_t i = 0;
  while(i != length - 1)
    {
      XDWORD component = 0;

      while(i != length - 1)
        {
          ++i;
 
          if(component >> (32-7))
            {
              return false;      
            }
 
          component = (component << 7) + (bits[i] & 0x7F);
 
          if(!(bits[i] & 0x80))
            {
              break;
            }
        }

      string.AddFormat(__L(".%d"), component);

    }

  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToPrintableString(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToPrintableString
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToPrintableString(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 

  string.Add(data);

  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER::ConvertToUTCTime(XBUFFER& data, XVARIANT& variant)
* @brief      ConvertToUTCTime
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::ConvertToUTCTime(XBUFFER& data, XVARIANT& variant)
{
  XSTRING string; 

  string.Add(data);
  string.Add(__L("Z"));

  variant = string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XBER::CalculeSize(XBYTE& sizehead)
* @brief      CalculeSize
* @ingroup    XUTILS
* 
* @param[in]  sizehead : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::CalculeSize(XBUFFER& buffer, XDWORD& sizedataber, XBYTE& sizehead)
{  
  int mode = -1;
  
  if(buffer.IsEmpty()) return false;

  if(!(buffer.Get()[1] & 0x80))
    {
      if(!(buffer.Get()[1]))
        {
          if(tagtype == XBER_TAGTYPE_NULL)            
                 mode = 0;             
            else mode = 3;
            
        } else mode  = 0;

    } else mode = 2;  
    

  switch(mode)
    {
      case  0 : // Short mode              
                sizedataber = buffer.Get()[1];              
                sizehead    = 2;
                break;

      case  2 : // Long mode;
                { 
                  int sizeofsize = (buffer.Get()[1] & 0x7F);
                  sizehead       = 2 + sizeofsize;

                  if(sizeofsize > 4)  return false;
                  if(!sizeofsize)     return false;                    
                
                  memcpy((XBYTE*)&sizedataber, (XBYTE*)&buffer.Get()[2], sizeofsize);   
                  SWAPDWORD(sizedataber);

                  XBYTE bitsrotate = (32-(sizeofsize*8));
                  sizedataber >>= bitsrotate; 
                }
                break;

      case  3 : // Indefinite mode;                               
                sizehead    = 2;
                sizedataber = 0;
                /*
                for(XDWORD c=2; c<data.GetSize()-1; c++)
                  {
                    if(!data.Get()[c] && !data.Get()[c+1])  
                      {
                        sizedataber++;
                      }
                  }  
                */
                break;

      default : break;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::CodeBigNumber(XDWORD number, XBUFFER& data)
* @brief      Code Big number
* @ingroup    XUTILS
*
* @param[in]  number : number to code
* @param[in]  data : buffer big numer coded
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::CodeBigNumber(XDWORD number, XBUFFER& data)
{
  data.Delete();

  int value = number;
  int length = 0;

  if(value >= (268435456))
    { // 2 ^ 28
      length = 5;
    }
   else
    {
      if(value >= (2097152))
        { // 2 ^ 21
          length = 4;
        }
       else
        {
          if(value >= 16384)
            { // 2 ^ 14
              length = 3;
            }
           else
            {
              if(value >= 128)
                { // 2 ^ 7
                  length = 2;
                }
               else
                {
                  length = 1;
                }
            }
        }
    }


  int j = 0;
  for(j = length - 1; j >= 0; j--)
   {
     if(j)
      {
        int p = ((value >> (7 * j)) & 0x7F) | 0x80;
        data.Add((XBYTE)p);
      }
     else
      {
        int p = ((value >> (7 * j)) & 0x7F);
        data.Add((XBYTE)p);
      }
    }

  return true;
 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBER::CodeSize(XDWORD integer, XBUFFER& data)
* @brief      Get Code size
* @ingroup    XUTILS
*
* @param[in]  integer : integer to code
* @param[in]  data : buffer size coded
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER::CodeSize(XDWORD integer, XBUFFER& data)
{
  data.Delete();

  XBYTE size = 0;

  if(integer&0xFF800000)
    {
      size = 4;
    }
   else
    {
      if(integer&0x00FF8000)
        {
          size = 3;
        }
       else
        {
          if(integer&0x0000FF80)
            {
              size = 2;
            }
           else
            {
              size = 1;
            }
        }
    }

  if(!size) return false;

  if(size>1) data.Add((XBYTE)((size-1)|0x80));

  for(int c=(size-data.GetSize()-1);c>=0;c--)
    {
      XBYTE byte = (XBYTE)((c?(integer>>(c*8)):(integer))&0xFF);

      data.Add((XBYTE)byte);
    }

  return true;
 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBER::Clean()
{
  tagtype               = 0;  
  nametagtype.Empty();
  tagclass              = XBER_TAGCLASS_UNIVERSAL;

  sizehead              = 0;
  size                  = 0;

  data.Empty();

  isconstructed         = false;

  contextspecificvalue  = 0;
  unusedbits            = 0;

  value.Set();

  sequences.DeleteContents();
  sequences.DeleteAll();
}


#pragma endregion

