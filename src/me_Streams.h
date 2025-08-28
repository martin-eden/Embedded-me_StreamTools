// Flesh for streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-28
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

namespace me_Streams
{
  // [Emitter] Input stream of zeroes
  class TZeroesInputStream : public IInputStream
  {
    public:
      TBool Read(TUnit * Unit) override;
  };

  // [Adapter] Input stream from reader
  class TInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      TBool Read(TUnit * Unit) override;

    protected:
      TFixedOperation ReadUnit;
  };

  // [Adapter] Output stream from writer
  class TOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    protected:
      TFixedOperation WriteUnit;
  };

  // [Copy] Copy stream
  TBool CopyStreamTo(
    IInputStream * InputStream,
    IOutputStream * OutputStream
  );

  // [Compare] Data equality check
  TBool StreamsAreEqual(
    IInputStream * A_Stream,
    IInputStream * B_Stream
  );
}

/*
  2025-08-24
  2025-08-25
  2025-08-26
*/
