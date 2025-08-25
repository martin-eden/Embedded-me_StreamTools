//

/*
*/

#include <me_Streams.h>

#include <me_BaseTypes.h>

using namespace me_Streams;

TBool Freetown::CopyTo(
  TOutputStream * OutputStream,
  TInputStream * InputStream
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
  2025-08-25
*/
