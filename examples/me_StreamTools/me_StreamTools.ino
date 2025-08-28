// [me_Streams] echo test

/*
  Author: Martin Eden
  Last mod.: 2025-08-28
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Uart.h>

// TFixedOperation wrapper for me_Uart::WaitByte
TBool Op_WaitByte(
  TAddress Data
)
{
  me_Uart::WaitByte((TUint_1 *) Data);

  return true;
}

/*
  Echo - copy input to output
*/
void EchoTest_Inf()
{
  /*
    Here we're initializing input stream with "wait byte from UART"
    operation. Then we're setting output stream to "output to UART".
    And then we're copying input stream to output stream.
  */

  me_StreamTools::TInputStream InputStream;
  me_Uart::TOutputStream OutputStream;

  InputStream.Init(Op_WaitByte);

  me_StreamTools::CopyStreamTo(&InputStream, &OutputStream);
}

void setup()
{
  Console.Init();

  Console.Print("[me_Streams] Infinite echo test");
  EchoTest_Inf();
  Console.Print("Done (lol)");
}

void loop()
{
}

/*
  2025-08-24
*/
