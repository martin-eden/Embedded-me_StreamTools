// Flesh for streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-28
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

namespace me_StreamTools
{
  // [Emitter] .Read() --> 0
  class TZeroesInputStream : public IInputStream
  {
    public:
      TBool Read(TUnit * Unit) override;
  };

  // [Adapter] Input stream == Reader
  class TInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      TBool Read(TUnit * Unit) override;

    protected:
      TFixedOperation ReadUnit;
  };

  // [Adapter] Output stream == Writer
  class TOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    protected:
      TFixedOperation WriteUnit;
  };

  // [Copy] Input --> Output
  TBool CopyStreamTo(
    IInputStream * InputStream,
    IOutputStream * OutputStream
  );

  // [Compare] A == B ?
  TBool StreamsAreEqual(
    IInputStream * A_Stream,
    IInputStream * B_Stream
  );
}

/*
  2025-08-24
  2025-08-25
  2025-08-26
  2025-08-28
*/
