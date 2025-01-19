/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLanguage_ISO_639_3.cpp
* 
* @class      XLANGUAGE_ISO_639_3
* @brief      eXtended Utils Language ISO 639-3 class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XLanguage_ISO_639_3.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


XLANGUAGE_ISO_639_3_ENTRY  iso_639_3_entry[] = {   {  XLANGUAGE_ISO_639_3_CODE_ENG,  __L("eng")   ,  __L("en")   ,  __L("English")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SPA,  __L("spa")   ,  __L("es")   ,  __L("Spanish")               , __L("Castilian")          , __L("")                       },   

                                                   //#ifndef MICROCONTROLLER
                                                   {  XLANGUAGE_ISO_639_3_CODE_AAR,  __L("aar")   ,  __L("aa")   ,  __L("Afar")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ABK,  __L("abk")   ,  __L("ab")   ,  __L("Abkhazian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AFR,  __L("afr")   ,  __L("af")   ,  __L("Afrikaans")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AKA,  __L("aka")   ,  __L("ak")   ,  __L("Akan")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ALB,  __L("alb")   ,  __L("sq")   ,  __L("Albanian")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AMH,  __L("amh")   ,  __L("am")   ,  __L("Amharic")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ARA,  __L("ara")   ,  __L("ar")   ,  __L("Arabic")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ARG,  __L("arg")   ,  __L("an")   ,  __L("Aragonese")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ARM,  __L("ARM")   ,  __L("hy")   ,  __L("Armenia")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ASM,  __L("asm")   ,  __L("as")   ,  __L("Assamese")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AVA,  __L("ava")   ,  __L("av")   ,  __L("Avaric")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AVE,  __L("ave")   ,  __L("ae")   ,  __L("Avestan")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AYM,  __L("aym")   ,  __L("ay")   ,  __L("Aymara")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_AZE,  __L("aze")   ,  __L("az")   ,  __L("Azerbaijani")           , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BAK,  __L("bak")   ,  __L("ba")   ,  __L("Bashkir")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BAM,  __L("bam")   ,  __L("bm")   ,  __L("Bambara")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BAQ,  __L("baq")   ,  __L("eu")   ,  __L("Basque")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BEL,  __L("bel")   ,  __L("be")   ,  __L("Belarusian")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BEN,  __L("ben")   ,  __L("bn")   ,  __L("Bengali")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BIH,  __L("bih")   ,  __L("bh")   ,  __L("Bihari languages")      , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BIS,  __L("bis")   ,  __L("bi")   ,  __L("Bislama")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BOS,  __L("bos")   ,  __L("bs")   ,  __L("Bosnian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BRE,  __L("bre")   ,  __L("br")   ,  __L("Breton")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BUL,  __L("bul")   ,  __L("bg")   ,  __L("Bulgarian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_BUR,  __L("bur")   ,  __L("my")   ,  __L("Burmese")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CAT,  __L("cat")   ,  __L("ca")   ,  __L("Catalan")               , __L("Valencian")          , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CHA,  __L("cha")   ,  __L("ch")   ,  __L("Chamorro")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CHE,  __L("che")   ,  __L("ce")   ,  __L("Chechen")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CHI,  __L("chi")   ,  __L("zh")   ,  __L("Chinese")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CHU,  __L("chu")   ,  __L("cu")   ,  __L("Church Slavic")         , __L("Old Slavonic")       , __L("Church Slavonic")        },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CHV,  __L("chv")   ,  __L("cv")   ,  __L("Chuvash")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_COR,  __L("cor")   ,  __L("kw")   ,  __L("Cornish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_COS,  __L("cos")   ,  __L("co")   ,  __L("Corsican")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CRE,  __L("cre")   ,  __L("cr")   ,  __L("Cree")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_CZE,  __L("cze")   ,  __L("cs")   ,  __L("Czech")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_DAN,  __L("dan")   ,  __L("da")   ,  __L("Danish")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_DIV,  __L("div")   ,  __L("dv")   ,  __L("Divehi")                , __L("Dhivehi")            , __L("Maldivian")              },
                                                   {  XLANGUAGE_ISO_639_3_CODE_DUT,  __L("dut")   ,  __L("nl")   ,  __L("Dutch")                 , __L("Flemish")            , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_DZO,  __L("dzo")   ,  __L("dz")   ,  __L("Dzongkha")              , __L("")                   , __L("")                       },                                                   
                                                   {  XLANGUAGE_ISO_639_3_CODE_EPO,  __L("epo")   ,  __L("eo")   ,  __L("Esperanto")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_EST,  __L("est")   ,  __L("et")   ,  __L("Estonian")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_EWE,  __L("ewe")   ,  __L("ee")   ,  __L("Ewe")                   , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FAO,  __L("fao")   ,  __L("fo")   ,  __L("Faroese")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FIJ,  __L("fij")   ,  __L("fj")   ,  __L("Fijian")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FIN,  __L("fin")   ,  __L("fi")   ,  __L("Finnish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FRE,  __L("fre")   ,  __L("fr")   ,  __L("French")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FRY,  __L("fry")   ,  __L("fy")   ,  __L("Western Frisian")       , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_FUL,  __L("ful")   ,  __L("ff")   ,  __L("Fulah")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GEO,  __L("geo")   ,  __L("ka")   ,  __L("Georgian")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GER,  __L("ger")   ,  __L("de")   ,  __L("German")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GLA,  __L("gla")   ,  __L("gd")   ,  __L("Gaelic")                ,  __L("Scottish Gaelic")   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GLE,  __L("gle")   ,  __L("ga")   ,  __L("Irish")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GLG,  __L("glg")   ,  __L("gl")   ,  __L("Galician")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GLV,  __L("glv")   ,  __L("gv")   ,  __L("Manx")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GRE,  __L("gre")   ,  __L("el")   ,  __L("Greek Modern (1453-)")  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GRN,  __L("grn")   ,  __L("gn")   ,  __L("Guarani")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_GUJ,  __L("guj")   ,  __L("gu")   ,  __L("Gujarati")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HAT,  __L("hat")   ,  __L("ht")   ,  __L("Haitian")               ,  __L("Haitian Creole")    , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HAU,  __L("hau")   ,  __L("ha")   ,  __L("Hausa")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HEB,  __L("heb")   ,  __L("he")   ,  __L("Hebrew")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HER,  __L("her")   ,  __L("hz")   ,  __L("Herero")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HIN,  __L("hin")   ,  __L("hi")   ,  __L("Hindi")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HMO,  __L("hmo")   ,  __L("ho")   ,  __L("Hiri Motu")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HRV,  __L("hrv")   ,  __L("hr")   ,  __L("Croatian")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_HUN,  __L("hun")   ,  __L("hu")   ,  __L("Hungarian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_IBO,  __L("ibo")   ,  __L("ig")   ,  __L("Igbo")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ICE,  __L("ice")   ,  __L("is")   ,  __L("Icelandic")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_IDO,  __L("ido")   ,  __L("io")   ,  __L("Ido")                   , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_III,  __L("iii")   ,  __L("ii")   ,  __L("Sichuan Yi")            ,  __L("Nuosu")             , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_IKU,  __L("iku")   ,  __L("iu")   ,  __L("Inuktitut")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ILE,  __L("ile")   ,  __L("ie")   ,  __L("Interlingue")           ,  __L("Occidental")        , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_INA,  __L("ina")   ,  __L("ia")   ,  __L("Interlingua")           , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_IND,  __L("ind")   ,  __L("id")   ,  __L("Indonesian")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_IPK,  __L("ipk")   ,  __L("ik")   ,  __L("Inupiaq")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ITA,  __L("ita")   ,  __L("it")   ,  __L("Italian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_JAV,  __L("jav")   ,  __L("jv")   ,  __L("Javanese")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_JPN,  __L("jpn")   ,  __L("ja")   ,  __L("Japanese")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KAL,  __L("kal")   ,  __L("kl")   ,  __L("Kalaallisut")           ,  __L("Greenlandic")       , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KAN,  __L("kan")   ,  __L("kn")   ,  __L("Kannada")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KAS,  __L("kas")   ,  __L("ks")   ,  __L("Kashmiri")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KAU,  __L("kau")   ,  __L("kr")   ,  __L("Kanuri")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KAZ,  __L("kaz")   ,  __L("kk")   ,  __L("Kazakh")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KHM,  __L("khm")   ,  __L("km")   ,  __L("Central Khmer")         , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KIK,  __L("kik")   ,  __L("ki")   ,  __L("Kikuyu")                ,  __L("Gikuyu")            , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KIN,  __L("kin")   ,  __L("rw")   ,  __L("Kinyarwanda")           , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KIR,  __L("kir")   ,  __L("ky")   ,  __L("Kirghiz")               ,  __L("Kyrgyz")            , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KOM,  __L("kom")   ,  __L("kv")   ,  __L("Komi")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KON,  __L("kon")   ,  __L("kg")   ,  __L("Kongo")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KOR,  __L("kor")   ,  __L("ko")   ,  __L("Korean")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KUA,  __L("kua")   ,  __L("kj")   ,  __L("Kuanyama")              ,  __L("Kwanyama")          , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_KUR,  __L("kur")   ,  __L("ku")   ,  __L("Kurdish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LAO,  __L("lao")   ,  __L("lo")   ,  __L("Lao")                   , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LAT,  __L("lat")   ,  __L("la")   ,  __L("Latin")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LAV,  __L("lav")   ,  __L("lv")   ,  __L("Latvian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LIM,  __L("lim")   ,  __L("li")   ,  __L("Limburgan")             ,  __L("Limburger")         , __L("Limburgish")             },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LIN,  __L("lin")   ,  __L("ln")   ,  __L("Lingala")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LIT,  __L("lit")   ,  __L("lt")   ,  __L("Lithuanian")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LTZ,  __L("ltz")   ,  __L("lb")   ,  __L("Luxembourgish")         ,  __L("Letzeburgesch")     , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LUB,  __L("lub")   ,  __L("lu")   ,  __L("Luba-Katanga")          , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_LUG,  __L("lug")   ,  __L("lg")   ,  __L("Ganda")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAC,  __L("mac")   ,  __L("mk")   ,  __L("Macedonian")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAH,  __L("mah")   ,  __L("mh")   ,  __L("Marshallese")           , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAL,  __L("mal")   ,  __L("ml")   ,  __L("Malayalam")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAO,  __L("mao")   ,  __L("mi")   ,  __L("Maori")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAR,  __L("mar")   ,  __L("mr")   ,  __L("Marathi")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MAY,  __L("may")   ,  __L("ms")   ,  __L("Malay")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MLG,  __L("mlg")   ,  __L("mg")   ,  __L("Malagasy")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MLT,  __L("mlt")   ,  __L("mt")   ,  __L("Maltese")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_MON,  __L("mon")   ,  __L("mn")   ,  __L("Mongolian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NAU,  __L("nau")   ,  __L("na")   ,  __L("Nauru")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NAV,  __L("nav")   ,  __L("nv")   ,  __L("Navajo")                , __L("Navaho")             , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NBL,  __L("nbl")   ,  __L("nr")   ,  __L("Ndebele South")         , __L("South Ndebele")      , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NDE,  __L("nde")   ,  __L("nd")   ,  __L("Ndebele North")         , __L("North Ndebele")      , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NDO,  __L("ndo")   ,  __L("ng")   ,  __L("Ndonga")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NEP,  __L("nep")   ,  __L("ne")   ,  __L("Nepali")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NNO,  __L("nno")   ,  __L("nn")   ,  __L("Norwegian Nynorsk")     , __L("Nynorsk Norwegian")  , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NOB,  __L("nob")   ,  __L("nb")   ,  __L("Bokm_l Norwegian")     , __L("Norwegian Bokm_l")  , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NOR,  __L("nor")   ,  __L("no")   ,  __L("Norwegian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_NYA,  __L("nya")   ,  __L("ny")   ,  __L("Chichewa")              , __L("Chewa")              ,  __L("Nyanja")                },
                                                   {  XLANGUAGE_ISO_639_3_CODE_OCI,  __L("oci")   ,  __L("oc")   ,  __L("Occitan (post 1500)")   , __L("Proven_al")         , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_OJI,  __L("oji")   ,  __L("oj")   ,  __L("Ojibwa")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ORI,  __L("ori")   ,  __L("or")   ,  __L("Oriya")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ORM,  __L("orm")   ,  __L("om")   ,  __L("Oromo")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_OSS,  __L("oss")   ,  __L("os")   ,  __L("Ossetian")              , __L("Ossetic")            , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_PAN,  __L("pan")   ,  __L("pa")   ,  __L("Panjabi")               , __L("Punjabi")            , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_PER,  __L("per")   ,  __L("fa")   ,  __L("Persian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_PLI,  __L("pli")   ,  __L("pi")   ,  __L("Pali")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_POL,  __L("pol")   ,  __L("pl")   ,  __L("Polish")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_POR,  __L("por")   ,  __L("pt")   ,  __L("Portuguese")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_PUS,  __L("pus")   ,  __L("ps")   ,  __L("Pushto")                , __L("Pashto")             , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_QUE,  __L("que")   ,  __L("qu")   ,  __L("Quechua")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ROH,  __L("roh")   ,  __L("rm")   ,  __L("Romansh")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_RUM,  __L("rum")   ,  __L("ro")   ,  __L("Romanian")              , __L("Moldavian")          , __L("Moldovan")               },
                                                   {  XLANGUAGE_ISO_639_3_CODE_RUN,  __L("run")   ,  __L("rn")   ,  __L("Rundi")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_RUS,  __L("rus")   ,  __L("ru")   ,  __L("Russian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SAG,  __L("sag")   ,  __L("sg")   ,  __L("Sango")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SAN,  __L("san")   ,  __L("sa")   ,  __L("Sanskrit")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SIN,  __L("sin")   ,  __L("si")   ,  __L("Sinhala")               , __L("Sinhalese")          , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SLO,  __L("slo")   ,  __L("sk")   ,  __L("Slovak")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SLV,  __L("slv")   ,  __L("sl")   ,  __L("Slovenian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SME,  __L("sme")   ,  __L("se")   ,  __L("Northern Sami")         , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SMO,  __L("smo")   ,  __L("sm")   ,  __L("Samoan")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SNA,  __L("sna")   ,  __L("sn")   ,  __L("Shona")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SND,  __L("snd")   ,  __L("sd")   ,  __L("Sindhi")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SOM,  __L("som")   ,  __L("so")   ,  __L("Somali")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SOT,  __L("sot")   ,  __L("st")   ,  __L("Sotho Southern")        , __L("")                   , __L("")                       },                                                   
                                                   {  XLANGUAGE_ISO_639_3_CODE_SRD,  __L("srd")   ,  __L("sc")   ,  __L("Sardinian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SRP,  __L("srp")   ,  __L("sr")   ,  __L("Serbian")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SSW,  __L("ssw")   ,  __L("ss")   ,  __L("Swati")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SUN,  __L("sun")   ,  __L("su")   ,  __L("Sundanese")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SWA,  __L("swa")   ,  __L("sw")   ,  __L("Swahili")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_SWE,  __L("swe")   ,  __L("sv")   ,  __L("Swedish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TAH,  __L("tah")   ,  __L("ty")   ,  __L("Tahitian")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TAM,  __L("tam")   ,  __L("ta")   ,  __L("Tamil")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TAT,  __L("tat")   ,  __L("tt")   ,  __L("Tatar")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TEL,  __L("tel")   ,  __L("te")   ,  __L("Telugu")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TGK,  __L("tgk")   ,  __L("tg")   ,  __L("Tajik")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TGL,  __L("tgl")   ,  __L("tl")   ,  __L("Tagalog")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_THA,  __L("tha")   ,  __L("th")   ,  __L("Thai")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TIB,  __L("tib")   ,  __L("bo")   ,  __L("Tibetan")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TIR,  __L("tir")   ,  __L("ti")   ,  __L("Tigrinya")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TON,  __L("ton")   ,  __L("to")   ,  __L("Tonga (Tonga Islands)") , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TSN,  __L("tsn")   ,  __L("tn")   ,  __L("Tswana")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TSO,  __L("tso")   ,  __L("ts")   ,  __L("Tsonga")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TUK,  __L("tuk")   ,  __L("tk")   ,  __L("Turkmen")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TUR,  __L("tur")   ,  __L("tr")   ,  __L("Turkish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_TWI,  __L("twi")   ,  __L("tw")   ,  __L("Twi")                   , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_UIG,  __L("uig")   ,  __L("ug")   ,  __L("Uighur")                , __L("Uyghur")             , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_UKR,  __L("ukr")   ,  __L("uk")   ,  __L("Ukrainian")             , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_URD,  __L("urd")   ,  __L("ur")   ,  __L("Urdu")                  , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_UZB,  __L("uzb")   ,  __L("uz")   ,  __L("Uzbek")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_VEN,  __L("ven")   ,  __L("ve")   ,  __L("Venda")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_VIE,  __L("vie")   ,  __L("vi")   ,  __L("Vietnamese")            , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_VOL,  __L("vol")   ,  __L("vo")   ,  __L("Volap_k")              , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_WEL,  __L("wel")   ,  __L("cy")   ,  __L("Welsh")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_WLN,  __L("wln")   ,  __L("wa")   ,  __L("Walloon")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_WOL,  __L("wol")   ,  __L("wo")   ,  __L("Wolof")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_XHO,  __L("xho")   ,  __L("xh")   ,  __L("Xhosa")                 , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_YID,  __L("yid")   ,  __L("yi")   ,  __L("Yiddish")               , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_YOR,  __L("yor")   ,  __L("yo")   ,  __L("Yoruba")                , __L("")                   , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ZHA,  __L("zha")   ,  __L("za")   ,  __L("Zhuang")                , __L("Chuang")             , __L("")                       },
                                                   {  XLANGUAGE_ISO_639_3_CODE_ZUL,  __L("zul")   ,  __L("zu")   ,  __L("Zulu")                  , __L("")                   , __L("")                       }
                                                   //#endif
                                               };

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLANGUAGE_ISO_639_3::XLANGUAGE_ISO_639_3()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLANGUAGE_ISO_639_3::XLANGUAGE_ISO_639_3()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLANGUAGE_ISO_639_3::~XLANGUAGE_ISO_639_3()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLANGUAGE_ISO_639_3::~XLANGUAGE_ISO_639_3()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLANGUAGE_ISO_639_3::Code_GetByCodeAlpha3(XCHAR* codealpha3)
* @brief      Code get by code alpha3
* @ingroup    XUTILS
*
* @param[in]  codealpha3 :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XLANGUAGE_ISO_639_3::Code_GetByCodeAlpha3(XCHAR* codealpha3)
{
  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _codealpha3 = iso_639_3_entry[c].codealpha3;

      if(!_codealpha3.Compare(codealpha3)) return iso_639_3_entry[c].code;
    }

  return XLANGUAGE_ISO_639_3_CODE_INVALID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLANGUAGE_ISO_639_3::Code_GetByCodeAlpha2(XCHAR* codealpha2)
* @brief      Code get by code alpha2
* @ingroup    XUTILS
*
* @param[in]  codealpha2 :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XLANGUAGE_ISO_639_3::Code_GetByCodeAlpha2(XCHAR* codealpha2)
{
  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _codealpha2 = iso_639_3_entry[c].codealpha2;

      if(!_codealpha2.Compare(codealpha2)) return iso_639_3_entry[c].code;
    }

  return XLANGUAGE_ISO_639_3_CODE_INVALID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLANGUAGE_ISO_639_3::Code_GetByEnglishName(XCHAR* englishname)
* @brief      Code get by english name
* @ingroup    XUTILS
*
* @param[in]  englishname :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XLANGUAGE_ISO_639_3::Code_GetByEnglishName(XCHAR* englishname)
{
  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _englishname = iso_639_3_entry[c].englishname;

      if(!_englishname.Compare(englishname)) return iso_639_3_entry[c].code;
    }

  return XLANGUAGE_ISO_639_3_CODE_INVALID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLANGUAGE_ISO_639_3::Code_GetByAlias(XCHAR* alias)
* @brief      Code get by alias
* @ingroup    XUTILS
*
* @param[in]  alias :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XLANGUAGE_ISO_639_3::Code_GetByAlias(XCHAR* alias)
{
  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _aliasname;

      _aliasname = iso_639_3_entry[c].alias1name;
      if(!_aliasname.Compare(alias)) return iso_639_3_entry[c].code;

      _aliasname = iso_639_3_entry[c].alias2name;
      if(!_aliasname.Compare(alias)) return iso_639_3_entry[c].code;
    }

  return XLANGUAGE_ISO_639_3_CODE_INVALID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByCode(XDWORD code, XSTRING& codealpha3)
* @brief      Code alpha3 get by code
* @ingroup    XUTILS
*
* @param[in]  code :
* @param[in]  codealpha3 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByCode(XDWORD code, XSTRING& codealpha3)
{
  codealpha3.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      if(iso_639_3_entry[c].code == code)
        {
          codealpha3 = iso_639_3_entry[c].codealpha3;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByCodeAlpha2(XCHAR* codealpha2, XSTRING& codealpha3)
* @brief      Code alpha3 get by code alpha2
* @ingroup    XUTILS
*
* @param[in]  codealpha2 :
* @param[in]  codealpha3 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByCodeAlpha2(XCHAR* codealpha2, XSTRING& codealpha3)
{
  codealpha3.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _codealpha2 = iso_639_3_entry[c].codealpha2;

      if(!_codealpha2.Compare(codealpha2))
        {
          codealpha3 = iso_639_3_entry[c].codealpha3;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByEnglishName(XCHAR* englishname, XSTRING& codealpha3)
* @brief      Code alpha3 get by english name
* @ingroup    XUTILS
*
* @param[in]  englishname :
* @param[in]  codealpha3 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByEnglishName(XCHAR* englishname, XSTRING& codealpha3)
{
  codealpha3.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _englishname = iso_639_3_entry[c].englishname;

      if(!_englishname.Compare(englishname))
        {
          codealpha3 = iso_639_3_entry[c].codealpha3;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByAlias(XCHAR* alias, XSTRING& codealpha3)
* @brief      Code alpha3 get by alias
* @ingroup    XUTILS
*
* @param[in]  alias :
* @param[in]  codealpha3 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::CodeAlpha3_GetByAlias(XCHAR* alias, XSTRING& codealpha3)
{
  codealpha3.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _aliasname;

      _aliasname = iso_639_3_entry[c].alias1name;
      if(!_aliasname.Compare(alias))
        {
          codealpha3 = iso_639_3_entry[c].codealpha3;
          return true;
        }

      _aliasname = iso_639_3_entry[c].alias2name;
      if(!_aliasname.Compare(alias))
        {
          codealpha3 = iso_639_3_entry[c].codealpha3;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::EnglishName_GetByCode(XDWORD code, XSTRING& englishname)
* @brief      English name get by code
* @ingroup    XUTILS
*
* @param[in]  code :
* @param[in]  englishname :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::EnglishName_GetByCode(XDWORD code, XSTRING& englishname)
{
  englishname.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      if(iso_639_3_entry[c].code == code)
        {
          englishname = iso_639_3_entry[c].englishname;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::EnglishName_GetByCodeAlpha3(XCHAR* codealpha2, XSTRING& englishname)
* @brief      English name get by code alpha3
* @ingroup    XUTILS
*
* @param[in]  codealpha2 :
* @param[in]  englishname :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::EnglishName_GetByCodeAlpha3(XCHAR* codealpha3, XSTRING& englishname)
{
  englishname.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _codealpha3 = iso_639_3_entry[c].codealpha3;

      if(!_codealpha3.Compare(codealpha3))
        {
          englishname = iso_639_3_entry[c].englishname;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::EnglishName_GetByCodeAlpha2(XCHAR* codealpha2, XSTRING& englishname)
* @brief      English name get by code alpha2
* @ingroup    XUTILS
*
* @param[in]  codealpha2 :
* @param[in]  englishname :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::EnglishName_GetByCodeAlpha2(XCHAR* codealpha2, XSTRING& englishname)
{
  englishname.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _codealpha2 = iso_639_3_entry[c].codealpha2;

      if(!_codealpha2.Compare(codealpha2))
        {
          englishname = iso_639_3_entry[c].englishname;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLANGUAGE_ISO_639_3::EnglishName_GetByAlias(XCHAR* alias, XSTRING& englishname)
* @brief      English name get by alias
* @ingroup    XUTILS
*
* @param[in]  alias :
* @param[in]  englishname :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLANGUAGE_ISO_639_3::EnglishName_GetByAlias(XCHAR* alias, XSTRING& englishname)
{
  englishname.Empty();

  for(XDWORD c=0; c<XLANGUAGE_ISO_639_3_NENTRYS; c++)
    {
      XSTRING _aliasname;

      _aliasname = iso_639_3_entry[c].alias1name;
      if(!_aliasname.Compare(alias))
        {
          englishname = iso_639_3_entry[c].englishname;
          return true;
        }

      _aliasname = iso_639_3_entry[c].alias2name;
      if(!_aliasname.Compare(alias))
        {
          englishname = iso_639_3_entry[c].englishname;
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLANGUAGE_ISO_639_3::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLANGUAGE_ISO_639_3::Clean()
{

}


#pragma endregion

