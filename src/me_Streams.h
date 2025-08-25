// Streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-25
*/

#pragma once

#include <me_BaseTypes.h>

#include <me_MemorySegment.h>

namespace me_Streams
{
  class IInputStream
  {
    public:
      virtual TBool Read(TUnit * Unit);
  };

  class TInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      virtual TBool Read(TUnit * Unit);

    protected:
      TFixedOperation ReadUnit;
  };

  class TOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      virtual TBool Write(TUnit Unit);

    protected:
      TFixedOperation WriteUnit;
  };

  namespace Freetown
  {
    TBool CopyTo(
      TOutputStream * OutputStream,
      TInputStream * InputStream
    );
  }
}

/*
  2025-08-24
  2025-08-25
*/
