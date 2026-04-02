// Address segment as stream implementation

/*
  Author: Martin Eden
  Last mod.: 2026-04-02
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_AddrsegTools.h>

using namespace me_StreamTools;

// ( [Internal] Base for address segment iterator stream
TBool TAddrsegStream::Init(
  TAddressSegment AddrSeg,
  TMethod Operation
)
{
  if (!Rator.Init(AddrSeg))
    return false;

  this->AddrSeg = AddrSeg;
  this->Operation = Operation;

  return true;
}

TAddressSegment TAddrsegStream::GetProcessedSegment()
{
  TAddressSegment Result;

  Result = AddrSeg;

  if (!Rator.IsDone())
    me_AddrsegTools::ChopRightAt(&Result, Rator.GetAddr());

  return Result;
}
// )

// ( [Adapter] Input stream
TBool TAddrsegInputStream::Read(
  TUnit * Unit
)
{
  TAddress Addr;

  if (!TAddrsegStream::Rator.GetNextAddr(&Addr))
    return false;

  TAddrsegStream::Operation((TAddress) Unit, Addr);

  return true;
}
// )

// ( [Adapter] Output stream
TBool TAddrsegOutputStream::Write(
  TUnit Unit
)
{
  TAddress Addr;

  if (!TAddrsegStream::Rator.GetNextAddr(&Addr))
    return false;

  TAddrsegStream::Operation((TAddress) &Unit, Addr);

  return true;
}
// )

/*
  2025-08-25
  2025-09-05
  2026-03-31
  2026-04-02
*/
