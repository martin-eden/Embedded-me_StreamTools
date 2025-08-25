// Streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-24
*/

#include <me_Streams.h>

#include <me_BaseTypes.h>

using namespace me_Streams;

//

void TInputStream::Init(
  TFixedOperation UnitReader
)
{
  this->ReadUnit = UnitReader;
}

TBool TInputStream::Read(
  TUnit * Unit
)
{
  return this->ReadUnit((TAddress) Unit);
}

//

void TOutputStream::Init(
  TFixedOperation UnitWriter
)
{
  this->WriteUnit = UnitWriter;
}

TBool TOutputStream::Write(
  TUnit Unit
)
{
  return this->WriteUnit((TAddress) &Unit);
}

//

/*
  2025-08-24
*/
