/**-------------------------------------------------------------------------------------------------------------------
*
* @file       ID_IBAN.cpp
*
* @class      ID_IBAN
* @brief      IDentification (ID) IBAN Number (International Bank Account Number)
* @ingroup    IDENTIFICATION
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

#include "ID_IBAN.h"

#include "XBuffer.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         ID_IBAN::ID_IBAN()
* @brief      Constructor
* @ingroup    IDENTIFICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
ID_IBAN::ID_IBAN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         ID_IBAN::~ID_IBAN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    IDENTIFICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
ID_IBAN::~ID_IBAN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* ID_IBAN::Get()
* @brief      Get
* @ingroup    IDENTIFICATION
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* ID_IBAN::Get()
{
  return &IBANstr;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool ID_IBAN::Set(XCHAR* IBAN)
* @brief      Set
* @ingroup    IDENTIFICATION
*
* @param[in]  IBAN :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool ID_IBAN::Set(XCHAR* IBAN)
{
  bool status = false;

  IBANstr = IBAN;

  IBANstr.DeleteCharacter(__C(' '));
  IBANstr.DeleteCharacter(__C('-'));
  IBANstr.DeleteCharacter(__C('_'));
  IBANstr.ToUpperCase();

  IBANstr.Copy(0, 2, IDcountry);

  status = IsValidSizeCountry(IDcountry.Get(), IBANstr.GetSize());
  if (status)
  {
    if (!IDcountry.Compare(__L("ES"), true))
    {
      if (!Spain_ValidateControlDigit(IBANstr))
      {
        return false;
      }
    }

    XSTRING IBANtempo;
    XSTRING IBANtempo2;
    XSTRING tempo;

    size = IBANstr.GetSize();

    IBANtempo = IBANstr.Get();

    IBANtempo.Copy(0, 4, tempo);
    IBANtempo.DeleteCharacters(0, 4);
    IBANtempo.Add(tempo);

    for (int c = 0; c < IBANtempo.GetSize(); c++)
    {
      if (!IBANtempo.Character_IsNumber(IBANtempo.Get()[c], false))
      {
        XCHAR code1 = (IBANtempo.Get()[c] - 55) / 10 + '0';
        XCHAR code2 = (IBANtempo.Get()[c] - 55) % 10 + '0';

        IBANtempo2 += code1;
        IBANtempo2 += code2;
      }
      else
      {
        IBANtempo2 += IBANtempo.Get()[c];
      }
    }

    if (Mod97(IBANtempo2) != 1)
    {
      IBANstr.Empty();

      return false;
    }

    return true;

  }
  else
  {
    IDcountry.Empty();
  }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* ID_IBAN::GetCountry()
* @brief      GetCountry
* @ingroup    IDENTIFICATION
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* ID_IBAN::GetCountry()
{
  return &country;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool ID_IBAN::IsValidSizeCountry(XCHAR* countrystr, int size)
* @brief      IsValidSizeCountry
* @ingroup    IDENTIFICATION
*
* @param[in]  countrystr :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool ID_IBAN::IsValidSizeCountry(XCHAR* countrystr, int size)
{
  typedef struct
  {
    XCHAR* IDcontry;
    int       size;
    XCHAR* contry;

  } CONTRYLIST;


  CONTRYLIST  countrylist[] = { { __L("DE"), 22, __L("Germany")                },
                                  { __L("AD"), 24, __L("Andorra")                },
                                  { __L("SA"), 24, __L("Saudi Arabia")           },
                                  { __L("AT"), 20, __L("Austria")                },
                                  { __L("BH"), 22, __L("Bahrain")                },
                                  { __L("BE"), 16, __L("Belgium")                },
                                  { __L("BA"), 20, __L("Bosnia-Herzegovina")     },
                                  { __L("BG"), 22, __L("Bulgaria")               },
                                  { __L("QA"), 29, __L("Qatar")                  },
                                  { __L("CY"), 28, __L("Cyprus")                 },
                                  { __L("CR"), 22, __L("Costa Rica")             },
                                  { __L("HR"), 21, __L("Croatia")                },
                                  { __L("DK"), 18, __L("Denmark")                },
                                  { __L("AE"), 23, __L("United Arab Emirates")   },
                                  { __L("SK"), 24, __L("Slovakia")               },
                                  { __L("SI"), 19, __L("Slovenia")               },
                                  { __L("ES"), 24, __L("Spain")                  },
                                  { __L("EE"), 20, __L("Estonia")                },
                                  { __L("FI"), 18, __L("Finland")                },
                                  { __L("FR"), 27, __L("France")                 },
                                  { __L("GE"), 22, __L("Georgia")                },
                                  { __L("GI"), 23, __L("Gibraltar")              },
                                  { __L("GB"), 22, __L("Great Britain")          },
                                  { __L("GR"), 27, __L("Greece")                 },
                                  { __L("GL"), 18, __L("Greenland")              },
                                  { __L("GB"), 22, __L("Guernsey")               },
                                  { __L("HU"), 28, __L("Hungary")                },
                                  { __L("IE"), 22, __L("Ireland")                },
                                  { __L("GB"), 22, __L("Isle of Man")            },
                                  { __L("IM"), 22, __L("Isle of Man")            },
                                  { __L("IS"), 26, __L("Iceland")                },
                                  { __L("FO"), 18, __L("Faroe Islands")          },
                                  { __L("IT"), 27, __L("Italy")                  },
                                  { __L("GB"), 22, __L("Jersey")                 },
                                  { __L("JO"), 30, __L("Jordan")                 },
                                  { __L("KZ"), 20, __L("Kazakhstan")             },
                                  { __L("KW"), 30, __L("Kuwait")                 },
                                  { __L("LV"), 21, __L("Latvia")                 },
                                  { __L("LB"), 28, __L("Lebanon")                },
                                  { __L("LI"), 21, __L("Liechtenstein")          },
                                  { __L("LT"), 20, __L("Lithuania")              },
                                  { __L("LU"), 20, __L("Luxembourg")             },
                                  { __L("MK"), 19, __L("Macedonia")              },
                                  { __L("MT"), 31, __L("Malta")                  },
                                  { __L("MD"), 24, __L("Moldova")                },
                                  { __L("MC"), 27, __L("Monaco")                 },
                                  { __L("ME"), 22, __L("Montenegro")             },
                                  { __L("NO"), 15, __L("Norway")                 },
                                  { __L("NL"), 18, __L("Netherlands")            },
                                  { __L("PS"), 29, __L("Palestine")              },
                                  { __L("PL"), 28, __L("Poland")                 },
                                  { __L("PT"), 25, __L("Portugal")               },
                                  { __L("CZ"), 24, __L("Czech Republic")         },
                                  { __L("RO"), 24, __L("Romania")                },
                                  { __L("SM"), 27, __L("San Marino")             },
                                  { __L("SE"), 24, __L("Sweden")                 },
                                  { __L("CH"), 21, __L("Switzerland")            },
                                  { __L("TN"), 24, __L("Tunisia")                },
                                  { __L("TR"), 26, __L("Turkiye")                }
  };
  XSTRING     cs;

  cs = countrystr;

  for (XDWORD c = 0; c < sizeof(countrylist) / sizeof(CONTRYLIST); c++)
  {
    CONTRYLIST* countryitem = &countrylist[c];
    if (countryitem)
    {
      if (!cs.Compare(countryitem->IDcontry, false))
      {
        if (countryitem->size == size)
        {
          country = countryitem->contry;

          return true;
        }
      }
    }
  }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int ID_IBAN::Mod97(XSTRING& IBANstr)
* @brief      Mod97
* @ingroup    IDENTIFICATION
*
* @param[in]  IBANstr :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int ID_IBAN::Mod97(XSTRING& IBANstr)
{
  XBUFFER     xbuffer;
  const char* iban = NULL;
  int         size = 0;
  char* temp;
  int         mod = 0;
  int         i;

  IBANstr.ConvertToASCII(xbuffer);

  iban = (char*)xbuffer.Get();
  size = (int)strlen(iban);

  temp = new char[size + 5];

  if (!temp)
  {
    return 0;
  }

  strcpy(temp, iban);

  for (i = 0; i < strlen(temp); i++)
  {
    if (temp[i] >= 'A' && temp[i] <= 'Z')
    {
      mod = ((mod * 10) + (temp[i] - 'A' + 10)) % 97;
    }
    else
    {
      if (temp[i] >= 'a' && temp[i] <= 'z')
      {
        mod = ((mod * 10) + (temp[i] - 'a' + 10)) % 97;
      }
      else
      {
        mod = ((mod * 10) + (temp[i] - '0')) % 97;
      }
    }
  }

  delete[] temp;

  return mod;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int ID_IBAN::Spain_CalculeControlDigit(XSTRING& IBANstr)
* @brief      Spain_CalculeControlDigit
* @ingroup    IDENTIFICATION
*
* @param[in]  IBANstr :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int ID_IBAN::Spain_CalculeControlDigit(XSTRING& IBANstr)
{
  int firstdigit = 0;
  int seconddigit = 0;
  int rest = 0;
  int bankID[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int accountnumber[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  bankID[0] = (IBANstr.Get()[4] - 48) * 4;
  bankID[1] = (IBANstr.Get()[5] - 48) * 8;
  bankID[2] = (IBANstr.Get()[6] - 48) * 5;
  bankID[3] = (IBANstr.Get()[7] - 48) * 10;

  bankID[4] = (IBANstr.Get()[8] - 48) * 9;
  bankID[5] = (IBANstr.Get()[9] - 48) * 7;
  bankID[6] = (IBANstr.Get()[10] - 48) * 3;
  bankID[7] = (IBANstr.Get()[11] - 48) * 6;

  for (int c = 0; c < 8; c++)
  {
    firstdigit += bankID[c];
  }

  rest = (firstdigit % 11);

  firstdigit = (11 - rest);

  switch (firstdigit)
  {
  case 10: firstdigit = 1;
  case 11: firstdigit = 0;
  }


  accountnumber[0] = (IBANstr.Get()[14] - 48) * 1;
  accountnumber[1] = (IBANstr.Get()[15] - 48) * 2;
  accountnumber[2] = (IBANstr.Get()[16] - 48) * 4;
  accountnumber[3] = (IBANstr.Get()[17] - 48) * 8;
  accountnumber[4] = (IBANstr.Get()[18] - 48) * 5;
  accountnumber[5] = (IBANstr.Get()[19] - 48) * 10;
  accountnumber[6] = (IBANstr.Get()[20] - 48) * 9;
  accountnumber[7] = (IBANstr.Get()[21] - 48) * 7;
  accountnumber[8] = (IBANstr.Get()[22] - 48) * 3;
  accountnumber[9] = (IBANstr.Get()[23] - 48) * 6;

  for (int c = 0; c < 10; c++)
  {
    seconddigit += accountnumber[c];
  }


  rest = (seconddigit % 11);

  seconddigit = (11 - rest);

  switch (seconddigit)
  {
  case 10: seconddigit = 1;
  case 11: seconddigit = 0;
  }

  return (firstdigit * 10) + (seconddigit);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool ID_IBAN::Spain_ValidateControlDigit(XSTRING& IBANstr)
* @brief      Spain_ValidateControlDigit
* @ingroup    IDENTIFICATION
*
* @param[in]  IBANstr :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool ID_IBAN::Spain_ValidateControlDigit(XSTRING& IBANstr)
{
  if (IBANstr.GetSize() != 24)
  {
    return false;
  }

  XSTRING DCstring;
  XSTRING DCstring2;
  int     DC = 0;

  DC = Spain_CalculeControlDigit(IBANstr);
  DCstring.Format(__L("%02d"), DC);

  DCstring2.Add(IBANstr.Get()[12]);
  DCstring2.Add(IBANstr.Get()[13]);

  if (!DCstring.Compare(DCstring2.Get(), true))
  {
    return true;
  }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void ID_IBAN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    IDENTIFICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
void ID_IBAN::Clean()
{
  IBANstr.Empty();
  country.Empty();
  size = 0;
}



#pragma endregion


