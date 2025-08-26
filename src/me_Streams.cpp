// Streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-26
*/

#include <me_Streams.h>

#include <me_BaseTypes.h>

using namespace me_Streams;

/*
  Zeroes input stream

  Used by [me_MemorySegment] to fill unused memory.
*/
TBool TZeroesInputStream::Read(
  TUnit * Unit
)
{
  *Unit = (TUnit) 0;

  return true;
}

// ( Input stream

/*
  Setup input stream

  Requires reader function.
*/
void TInputStream::Init(
  TFixedOperation UnitReader
)
{
  this->ReadUnit = UnitReader;
}

/*
  Read unit
*/
TBool TInputStream::Read(
  TUnit * Unit
)
{
  return this->ReadUnit((TAddress) Unit);
}

// )

// ( Output stream

/*
  Setup output stream

  Requires write function.
*/
void TOutputStream::Init(
  TFixedOperation UnitWriter
)
{
  this->WriteUnit = UnitWriter;
}

/*
  Write unit
*/
TBool TOutputStream::Write(
  TUnit Unit
)
{
  return this->WriteUnit((TAddress) &Unit);
}

// )

/*
  Copy stream
*/
TBool me_Streams::CopyStreamTo(
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
  Compare streams
*/
TBool me_Streams::StreamsAreEqual(
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
  2025-08-24
  2025-08-25
  2025-08-26
*/
