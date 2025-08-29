// [me_StreamTools] test

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_Console.h>

#include <me_MemorySegment.h>
#include <me_WorkMemory.h>
#include <me_Uart.h>

// TFixedOperation for sending byte
TBool Op_SendByte(
  TAddress Data
)
{
  TUint_1 ByteValue;

  ByteValue = *(TUint_1 *) Data;

  me_Uart::SendByte(ByteValue);

  return true;
}

/*
  Copy data from memory to output stream
*/
void MemToStreamTest()
{
  TAddressSegment TestDataSeg =
    me_MemorySegment::FromAsciiz("TEST DATA\n");

  me_StreamTools::TAddrsegInputStream Input_MemStream;
  me_StreamTools::TWriterOutputStream Output_UartStream;

  Console.Print("( Memory -> UART stream test");

  Input_MemStream.Init(TestDataSeg, me_WorkMemory::Op_GetByte);
  Output_UartStream.Init(Op_SendByte);

  me_StreamTools::CopyStreamTo(&Input_MemStream, &Output_UartStream);

  Console.Print(")");
}

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

  me_StreamTools::TReaderInputStream InputStream;
  me_StreamTools::TWriterOutputStream OutputStream;

  Console.Print("( UART -> UART stream test. Infinite");

  InputStream.Init(Op_WaitByte);
  OutputStream.Init(Op_SendByte);

  me_StreamTools::CopyStreamTo(&InputStream, &OutputStream);

  Console.Print(")");
}

void setup()
{
  Console.Init();

  Console.Print("[me_StreamTools] Tests");
  MemToStreamTest();
  EchoTest_Inf();
  Console.Print("Done");
}

void loop()
{
}

/*
  2025-08-24
  2025-08-25
  2025-08-28
*/
