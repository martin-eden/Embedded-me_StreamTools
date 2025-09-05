// Address segments as streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-05
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

/*
  Setup
*/
TBool TAddrsegInputStream::Init(
  TAddressSegment AddrSeg,
  TOperation UnitGetter
)
{
  if (!TAddrsegStream::Init(AddrSeg))
    return false;

  this->GetUnit = UnitGetter;

  return true;
}

/*
  Read
*/
TBool TAddrsegInputStream::Read(
  TUnit * Unit
)
{
  TAddress Addr;

  if (!Rator.GetNextAddr(&Addr))
    return false;

  if (!GetUnit((TAddress) Unit, Addr))
    return false;

  return true;
}

// )

// ( [Adapter] Output stream == Address segment + Setter

/*
  Setup
*/
TBool TAddrsegOutputStream::Init(
  TAddressSegment AddrSeg,
  TOperation UnitSetter
)
{
  if (!TAddrsegStream::Init(AddrSeg))
    return false;

  this->SetUnit = UnitSetter;

  return true;
}

/*
  Write
*/
TBool TAddrsegOutputStream::Write(
  TUnit Unit
)
{
  TAddress Addr;

  if (!TAddrsegStream::Rator.GetNextAddr(&Addr))
    return false;

  if (!SetUnit((TAddress) &Unit, Addr))
    return false;

  return true;
}

// )

/*
  2025-08-25
  2025-09-05
*/
