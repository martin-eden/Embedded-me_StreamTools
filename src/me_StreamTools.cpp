// Streams implementation

/*
  Author: Martin Eden
  Last mod.: 2026-04-11
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

using namespace me_StreamTools;

// ( [Adapter] Input stream from reader
void TReaderInputStream::Init(
  TFixedOperation UnitReader
)
{
  this->ReadUnit = UnitReader;
}

TBool TReaderInputStream::Read(
  TUnit * Unit
)
{
  return this->ReadUnit((TAddress) Unit);
}
// )

// ( [Adapter] Output stream from writer
void TWriterOutputStream::Init(
  TFixedOperation UnitWriter
)
{
  this->WriteUnit = UnitWriter;
}

TBool TWriterOutputStream::Write(
  TUnit Unit
)
{
  return this->WriteUnit((TAddress) &Unit);
}
// )

/*
  [Copy] Save small input stream to large output stream

  Fails when output stream becomes full.
*/
TBool me_StreamTools::SaveStreamTo(
  IInputStream * InputStream,
  IOutputStream * OutputStream
)
{
  TUnit Unit;

  while (InputStream->Read(&Unit))
  {
    if (!OutputStream->Write(Unit))
      return false;
  }

  return true;
}

/*
  [Copy] Load small output stream from large input stream

  Fails when input stream becomes empty.

  Note that we're using Rereadable input stream to put back
  last unit read in case of success.
*/
TBool me_StreamTools::LoadStreamFrom(
  IOutputStream * OutputStream,
  TRereadableInputStream * InputStream
)
{
  TUnit Unit;

  do
  {
    if (!InputStream->Read(&Unit))
      return false;

  } while (OutputStream->Write(Unit));

  InputStream->Unread();

  return true;
}

/*
  [Compare] Compare streams
*/
TBool me_StreamTools::StreamsAreEqual(
  IInputStream * A_Stream,
  IInputStream * B_Stream
)
{
  TBool A_Stream_Done;
  TBool B_Stream_Done;
  TUnit A_Unit;
  TUnit B_Unit;

  while (true)
  {
    A_Stream_Done = !A_Stream->Read(&A_Unit);
    B_Stream_Done = !B_Stream->Read(&B_Unit);

    if (A_Stream_Done || B_Stream_Done)
      break;

    if (A_Unit != B_Unit)
      return false;
  }

  return (A_Stream_Done && B_Stream_Done);
}

/*
  2025 # # #
  2025-10-12
*/
