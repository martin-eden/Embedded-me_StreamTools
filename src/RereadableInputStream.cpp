// Re-readable input stream implementation

/*
  Author: Martin Eden
  Last mod.: 2025-10-14
*/

/*
  Our streams are working with units

  When copying from larger to smaller stream one unit is
  read but not written. It will be lost for next use of
  input stream if we won't save it.

  This class wraps input stream with method to
  put one unit back.

  Of course it's just emulation. Nothing can be write to
  input stream. When class instance dies, cached unit
  dies with it.
*/

#include <me_StreamTools.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

using namespace me_StreamTools;

/*
  Init
*/
void TRereadableInputStream::Init(
  IInputStream * BaseInputStream
)
{
  InputStream = BaseInputStream;
  HasUnitRead = false;
  UseUnitRead = false;
}

/*
  Read

  Returns stored unit if previous call was Unread().
  Else does read from input stream, stores and returns unit.
*/
TBool TRereadableInputStream::Read(
  TUnit * Unit
)
{
  if (UseUnitRead)
  {
    *Unit = UnitRead;
    HasUnitRead = false;

    UseUnitRead = false;

    return true;
  }

  if (InputStream->Read(&UnitRead))
  {
    *Unit = UnitRead;
    HasUnitRead = true;

    return true;
  }

  return false;
}

/*
  Unread

  Return last read unit for next Read().
*/
TBool TRereadableInputStream::Unread()
{
  if (!HasUnitRead)
    return false;

  UseUnitRead = true;

  return true;
}

// ( Freetown

/*
  [Copy] Load small output stream from large input stream

  Fails when input stream is empty.
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

// )

/*
  2025-08-31
  2025-09-01
  2025-10-14
*/
