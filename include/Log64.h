/**
   USE OF THIS SOFTWARE IS GOVERNED BY THE TERMS AND CONDITIONS
   OF THE LICENSE STATEMENT AND LIMITED WARRANTY FURNISHED WITH
   THE PRODUCT.
   <p/>
   IN PARTICULAR, YOU WILL INDEMNIFY AND HOLD ITS AUTHOR, ITS
   RELATED ENTITIES AND ITS SUPPLIERS, HARMLESS FROM AND AGAINST ANY
   CLAIMS OR LIABILITIES ARISING OUT OF THE USE, REPRODUCTION, OR
   DISTRIBUTION OF YOUR PROGRAMS, INCLUDING ANY CLAIMS OR LIABILITIES
   ARISING OUT OF OR RESULTING FROM THE USE, MODIFICATION, OR
   DISTRIBUTION OF PROGRAMS OR FILES CREATED FROM, BASED ON, AND/OR
   DERIVED FROM THIS SOURCE CODE FILE.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SERIAL and/or EPROM LOG LIRARY

// if you want to see the log you need to put in the beggining of your code the following
//
// #define LOG64_ENABLED
// #define EEPROM_LOG64_ENABLED
//
// for realease you just comments the #define out and everything related to logging
// will be omitted from your code and will not consume any memory
//
// IMPORTANT !!!!
//
// the two #define need to be BEFORE the : #include <Log64.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOG64 MACROS

#ifndef _LOG64_DEF_
#define _LOG64_DEF_

#include <Arduino.h>

#if defined (LOG64_ENABLED)

inline void LOG64_SPACE_IMPL();
inline void LOG64_SET_IMPL(int8_t i);
inline void LOG64_SET_IMPL(int16_t i);
inline void LOG64_SET_IMPL(int32_t i);
inline void LOG64_SET_IMPL(int64_t i);
inline void LOG64_SET_IMPL(uint8_t i);
inline void LOG64_SET_IMPL(uint16_t i);
inline void LOG64_SET_IMPL(uint32_t i);
inline void LOG64_SET_IMPL(uint64_t i);
inline void LOG64_SET_IMPL(char c);
inline void LOG64_SET_IMPL(String s);
inline void LOG64_SET_IMPL(float f);
inline void LOG64_SET_IMPL(double d);
inline void LOG64_NEW_LINE_IMPL();

#define LOG64_SET(P) LOG64_SET_IMPL(P)
#define LOG64_NEW_LINE LOG64_NEW_LINE_IMPL();
#define LOG64_SPACE LOG64_SPACE_IMPL()

#else

#define LOG64_SET(P)
#define LOG64_NEW_LINE
#define LOG64_SPACE

#endif

// EEPROM LOG64
#if defined (EEPROM_LOG64_ENABLED)

#include <EEPROM.h>

inline void LOG64_EEPROM_SET_IMPL(String s);
inline void LOG64_EEPROM_READ_IMPL();

#define LOG64_EEPROM_SET(P) LOG64_EEPROM_SET_IMPL(P)
#define LOG64_EEPROM_READ LOG64_EEPROM_READ_IMPL()

#else

#define LOG64_EEPROM_SET(P)
#define LOG64_EEPROM_READ

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION

#define EEPROM_LOG64_Size_Address 200
#define EEPROM_LOG64_Start_Address ( EEPROM_LOG64_Size_Address + 2 )
#define EEPROM_LOG64_MAX_MSG 512

#if defined (EEPROM_LOG64_ENABLED)
uint16_t EEPROM_LOG64_ADDR_PTR;
char EEPROM_LOG64_BUFFER[EEPROM_LOG64_MAX_MSG];
#endif

inline void LOG64_INIT()
{
#if defined (LOG64_ENABLED)
  Serial.begin(115200);
  LOG64_SET("Initialized: SERIAL_LOG64");
  LOG64_NEW_LINE;
#endif

#if defined (EEPROM_LOG64_ENABLED)
  LOG64_EEPROM_READ;

  EEPROM_LOG64_ADDR_PTR = EEPROM_LOG64_Start_Address;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LOG64
#if defined (LOG64_ENABLED)

inline void LOG64_PRINT_TIMESTAMP() {
  Serial.print('[');
  Serial.print(millis());
  Serial.print(']');
  LOG64_SPACE;
}

inline void LOG64_SPACE_IMPL()
{
  Serial.print(" ");
}

inline void LOG64_SET_IMPL(int8_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(int16_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(int32_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(uint8_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(uint16_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(uint32_t i)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(i);
  LOG64_SPACE;
}


inline void LOG64_SET_IMPL(char c)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(c);
  LOG64_SPACE;
}


inline void LOG64_SET_IMPL(String s)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(s);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(float f)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(f);
  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(double d)
{
  LOG64_PRINT_TIMESTAMP();
  Serial.print(d);
  LOG64_SPACE;
}

inline void LOG64_NEW_LINE_IMPL()
{
  Serial.println(" ");
}

inline void LOG64_SET_IMPL(uint64_t n)
{
  LOG64_PRINT_TIMESTAMP();
  unsigned char buf[16 * sizeof(long)];

  if (n == 0)
  {
    Serial.print((char)'0');
    LOG64_SPACE;
    return;
  }

  for (uint16_t i = 0; n > 0; i++)
  {
    buf[i] = n % 10;
    n /= 10;
  }

  for (uint16_t i = 0; i > 0; i--)
  {
    Serial.print((char) (buf[i - 1] < 10 ? ('0' + buf[i - 1]) : ('A' + buf[i - 1] - 10)));
  }

  LOG64_SPACE;
}

inline void LOG64_SET_IMPL(int64_t n)
{
  LOG64_PRINT_TIMESTAMP();
  unsigned char buf[16 * sizeof(long)]; ;

  if (n == 0)
  {
    Serial.print((char)'0');
    LOG64_SPACE;
    return;
  }

  if (n < 0)
  {
    Serial.print((char)'-');
    n = n * (-1);
  }

  for (uint16_t i = 0; n > 0; i++)
  {
    buf[i] = n % 10;
    n /= 10;
  }

  for (uint16_t i = 0; i > 0; i--)
  {
    Serial.print((char) (buf[i - 1] < 10 ? ('0' + buf[i - 1]) : ('A' + buf[i - 1] - 10)));
  }

  LOG64_SPACE;
}


#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EEPROM

#if defined (EEPROM_LOG64_ENABLED)

inline void LOG64_EEPROM_SET_IMPL(String s)
{
  LOG64_SET(s);
  LOG64_NEW_LINE;

  if ((EEPROM_LOG64_ADDR_PTR + s.length()) <= EEPROM.length())
  {
    uint16_t size = s.length();
    EEPROM.put(EEPROM_LOG64_ADDR_PTR, size);
    EEPROM_LOG64_ADDR_PTR += 2;

    for (uint16_t i = 0; i < size; i++)
    {
      EEPROM.write(EEPROM_LOG64_ADDR_PTR + i, s[i]);
    }
    EEPROM_LOG64_ADDR_PTR += size;

    EEPROM.put(EEPROM_LOG64_Size_Address, (EEPROM_LOG64_ADDR_PTR - EEPROM_LOG64_Start_Address));
  }
}

inline void LOG64_EEPROM_READ_IMPL()
{
  LOG64_SET("------ EEPROM LOG START ------");
  LOG64_NEW_LINE;

  uint16_t EEPROM_LOG64_Size;
  EEPROM.get(EEPROM_LOG64_Size_Address, EEPROM_LOG64_Size);

  LOG64_SET("EPROM LOG64 SIZE : ");
  LOG64_SET(EEPROM_LOG64_Size);
  LOG64_NEW_LINE;

  EEPROM_LOG64_Size += EEPROM_LOG64_Start_Address;

  for (volatile uint16_t i = EEPROM_LOG64_Start_Address; i < EEPROM_LOG64_Size;)
  {
    uint16_t size = 0;
    EEPROM.get(i, size);

    i += 2;

    for (uint16_t j = 0; j < size; j++)
    {
      EEPROM.get(i + j, EEPROM_LOG64_BUFFER[j]);
    }

    i += size;

    EEPROM_LOG64_BUFFER[size] = '\0';
    LOG64_SET(EEPROM_LOG64_BUFFER);
    LOG64_NEW_LINE;
  }
  LOG64_SET("------ EEPROM LOG END ------");
  LOG64_NEW_LINE;
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _LOG64_DEF_
