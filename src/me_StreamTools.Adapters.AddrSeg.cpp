// Address segments as streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-05
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>

using namespace me_StreamTools;

// ( [Adapter] Input stream == Address segment + Getter

/*
  Setup
*/
TBool TAddrsegInputStream::Init(
  TAddressSegment AddrSeg,
  TOperation UnitGetter
)
{
  if (!Rator.Init(AddrSeg))
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
  if (!Rator.Init(AddrSeg))
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

  if (!Rator.GetNextAddr(&Addr))
    return false;

  if (!SetUnit((TAddress) &Unit, Addr))
    return false;

  return true;
}

/*
  Get write address
*/
TAddress TAddrsegOutputStream::GetWriteAddr()
{
  return Rator.GetAddr();
}

/*
  Check that iteration is complete
*/
TBool TAddrsegOutputStream::IsFull()
{
  return Rator.IsDone();
}

// )

/*
  2025-08-25
*/
