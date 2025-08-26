// Streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-26
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_Streams
{
  // [Core] Input stream concept
  class IInputStream
  {
    public:
      virtual TBool Read(TUnit * Unit) = 0;
  };

  // [Core] Output stream concept
  class IOutputStream
  {
    public:
      virtual TBool Write(TUnit Unit) = 0;
  };

  // [Handy] Infinite input stream of zeroes
  class TZeroesInputStream : public IInputStream
  {
    public:
      TBool Read(TUnit * Unit) override;
  };

  // [Handy] Input stream, requires reader
  class TInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      TBool Read(TUnit * Unit) override;

    protected:
      TFixedOperation ReadUnit;
  };

  // [Handy] Output stream, requires writer
  class TOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    protected:
      TFixedOperation WriteUnit;
  };

  // [Handy] Copy stream
  TBool CopyStreamTo(
    IInputStream * InputStream,
    IOutputStream * OutputStream
  );
}

/*
  2025-08-24
  2025-08-25
  2025-08-26
*/
