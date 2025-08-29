// Address segments as streams implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-28
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>

using namespace me_StreamTools;

// ( [Adapter] Input stream == Address segment + Reader

/*
  Setup
*/
TBool TAddrsegInputStream::Init(
  TAddressSegment AddrSeg,
  TOperation UnitReader
)
{
  if (!Rator.Init(AddrSeg))
    return false;

  this->ReadUnit = UnitReader;

  return true;
}

/*
  Read byte wrapper
*/
TBool TAddrsegInputStream::Read(
  TUnit * Unit
)
{
  TAddress ReadAddr;
  TAddress UnitAddr = (TAddress) Unit;

  if (!Rator.GetNextAddr(&ReadAddr))
    return false;

  if (!ReadUnit(UnitAddr, ReadAddr))
    return false;

  return true;
}

// )

// ( [Adapter] Output stream == Address segment + Writer

/*
  Setup
*/
TBool TAddrsegOutputStream::Init(
  TAddressSegment AddrSeg,
  TOperation UnitWriter
)
{
  if (!Rator.Init(AddrSeg))
    return false;

  this->WriteUnit = UnitWriter;

  return true;
}

/*
  Write byte wrapper
*/
TBool TAddrsegOutputStream::Write(
  TUnit Unit
)
{
  TAddress WriteAddr;
  TAddress UnitAddr = (TAddress) &Unit;

  if (!Rator.GetNextAddr(&WriteAddr))
    return false;

  if (!WriteUnit(UnitAddr, WriteAddr))
    return false;

  return true;
}

// )

/*
  2025-08-25
*/
