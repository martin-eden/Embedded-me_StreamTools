// Streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-26
*/

#include <me_Streams.h>

#include <me_BaseTypes.h>

using namespace me_Streams;

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
  2025-08-24
  2025-08-25
  2025-08-26
*/
