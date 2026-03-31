// Address segment as stream implementation

/*
  Author: Martin Eden
  Last mod.: 2026-03-31
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_AddrsegTools.h>

using namespace me_StreamTools;

// ( [Internal] Base for address segment iterator stream
TBool TAddrsegStream::Init(
  TAddressSegment AddrSeg
)
{
  if (!Rator.Init(AddrSeg))
    return false;

  this->OrigAddrSeg = AddrSeg;

  return true;
}

TAddressSegment TAddrsegStream::GetProcessedSegment()
{
  TAddressSegment Result;

  Result = OrigAddrSeg;

  if (!Rator.IsDone())
    me_AddrsegTools::ChopRightAt(&Result, Rator.GetAddr());

  return Result;
}
// )

// ( [Adapter] Input stream == Address segment + Getter
TBool TAddrsegInputStream::Init(
  TAddressSegment AddrSeg,
  TMethod UnitGetter
)
{
  if (!TAddrsegStream::Init(AddrSeg))
    return false;

  this->GetUnit = UnitGetter;

  return true;
}

TBool TAddrsegInputStream::Read(
  TUnit * Unit
)
{
  TAddress Addr;

  if (!TAddrsegStream::Rator.GetNextAddr(&Addr))
    return false;

  GetUnit((TAddress) Unit, Addr);

  return true;
}
// )

// ( [Adapter] Output stream == Address segment + Setter
TBool TAddrsegOutputStream::Init(
  TAddressSegment AddrSeg,
  TMethod UnitSetter
)
{
  if (!TAddrsegStream::Init(AddrSeg))
    return false;

  this->SetUnit = UnitSetter;

  return true;
}

TBool TAddrsegOutputStream::Write(
  TUnit Unit
)
{
  TAddress Addr;

  if (!TAddrsegStream::Rator.GetNextAddr(&Addr))
    return false;

  SetUnit((TAddress) &Unit, Addr);

  return true;
}
// )

/*
  2025-08-25
  2025-09-05
  2026-03-31
*/
