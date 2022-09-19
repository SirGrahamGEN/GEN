/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XASN1.h
* 
* @class      XASN1
* @brief      eXtended ANS.1 format buffer  (Abstract Syntax Notation One, defined in X.208)
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

#ifndef _XASN1_H_
#define _XASN1_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "XFileJSON.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum XASN1_TAG
{		
	XASN1_TAG_CONTEXT_SPECIFIC				=    0	,	// ASN.1 CONTEXT SPECIFIC
	XASN1_TAG_BOOLEAN 								=    1	,	// ASN.1 BOOLEAN
	XASN1_TAG_INTEGER 								=    2	,	// ASN.1 INTEGER
	XASN1_TAG_BIT_STRING							=    3	,	// ASN.1 BIT STRING
	XASN1_TAG_OCTET_STRING						=    4	,	// ASN.1 OCTET STRING	
	XASN1_TAG_TAG_NULL								=    5	,	// ASN.1 NULL
	XASN1_TAG_OBJECT_IDENTIFIER			  =    6	,	// ASN.1 OBJECT IDENTIFIER
	XASN1_TAG_OBJECT_DESCRIPTOR			  =    7	,	// ASN.1 Object Descriptor	
	XASN1_TAG_EXTERNAL								=    8	,	// ASN.1 EXTERNAL REFERENCE	
	XASN1_TAG_REAL										=    9	,	// ASN.1 REAL INTEGER
	XASN1_TAG_ENUMERATED							=   10	,	// ASN.1 ENUMERATED VALUE	
	XASN1_TAG_EMBEDDED_PDV						=   11	, // ASN.1 EMBEDDED PDV
	XASN1_TAG_UTF8_STRING						  =   12	,	// ASN.1 UTF-8 String
	XASN1_TAG_RELATIVE_OID					  = 	13  , // ASN.1 RELATIVE-OID
	XASN1_TAG_SEQUENCE								=   16  ,	// ASN.1 Sequence
	XASN1_TAG_SET 										=   17	,	// ASN.1 Set
	XASN1_TAG_NUMERIC_STRING					=   18	,	// ASN.1 Numeric string
	XASN1_TAG_PRINTABLE_STRING 			  =   19	,	// ASN.1 Printable string
	XASN1_TAG_T61_STRING							=   20  ,	// ASN.1 TeletexString, T61 string
	XASN1_TAG_VIDEOTEXT_STRING 			  =   21	,	// ASN.1 Videotext string
	XASN1_TAG_IA5_STRING							=   22	,	// ASN.1 IA5 string
	XASN1_TAG_UTC_TIME 							  =   23	,	// ASN.1 UTC time
	XASN1_TAG_GENERALIZED_TIME 			  =   24	,	// ASN.1 Generalized time
	XASN1_TAG_GRAPHIC_STRING					=   25	,	// ASN.1 Graphic string
	XASN1_TAG_VISIBLE_STRING					=   26	,	// ASN.1 Visible string
	XASN1_TAG_GENERAL_STRING					=   27	,	// ASN.1 General string
	XASN1_TAG_UNIVERSAL_STRING				=   28	,	// ASN.1 Universal string
	XASN1_TAG_CHARACTER_STRING				=   29	, // ASN.1 CHARACTER STRING
	XASN1_TAG_BMP_STRING  						=   30 		// ASN.1 BMP string
};


enum XASN1_TAGFLAG
{	
	XASN1_TAGFLAG_UNIVERSAL						= 0x00	,	// ASN.1 Universal class
	XASN1_TAGFLAG_CONSTRUCTED					= 0x20	,	// ASN.1 Constructed flag
	XASN1_TAGFLAG_APPLICATION					= 0x40	,	// ASN.1 Application class
	XASN1_TAGFLAG_CONTEXT_SPECIFIC    = 0x80	,	// ASN.1 Context specific class
	XASN1_TAGFLAG_PRIVATE             = 0xc0		// ASN.1 Private class
};


#define XASN1_TAG_PRIMITIVEMASK							0x1F 


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class CIPHERKEYSFILEPEM_TYPECERTIFICATE;

class XASN1
{
  public:
                    XASN1										();
    virtual        ~XASN1										();

		bool						GetTagName		   				(XBYTE tag, XSTRING& tagname);
		XDWORD					GetLenght								(XBYTE *buffer, int buf_len, XDWORD *octets);

		bool						Decode									(XBUFFER& data, XFILEJSON& decodejson);			

  private:

		bool						Decode									(XBYTE* buffer, XDWORD size, XDWORD& position, XFILEJSON& decodejson);

    void            Clean										();
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

