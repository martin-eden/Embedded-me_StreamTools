// [me_Streams] echo test

/*
  Author: Martin Eden
  Last mod.: 2025-08-25
*/

#include <me_Streams.h>

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
  me_Streams::TInputStream InputStream;
  me_Streams::TOutputStream OutputStream;

  InputStream.Init(Op_WaitByte);
  OutputStream.Init(me_Uart::Op_PutByte);

  me_Streams::Freetown::CopyTo(&OutputStream, &InputStream);
}

void setup()
{
  Console.Init();

  Console.Print("[me_Streams] infinite test. Echo");
  EchoTest_Inf();
  Console.Print("Done (lol)");
}

void loop()
{
}

/*
  2025-08-24
*/
