// Flesh for streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-09-05
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
  class TReaderInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      TBool Read(TUnit * Unit) override;

    protected:
      TFixedOperation ReadUnit;
  };

  // [Adapter] Output stream == Writer
  class TWriterOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    protected:
      TFixedOperation WriteUnit;
  };

  // [Adapter] Input stream = Address segment + Getter
  class TAddrsegInputStream : public IInputStream
  {
    public:
      TBool Init(
        TAddressSegment AddrSeg,
        TOperation UnitGetter
      );

      TBool Read(TUnit * Unit) override;

    private:
      TAddrsegIterator Rator;
      TOperation GetUnit;
  };

  // [Adapter] Output stream = Address segment + Setter
  class TAddrsegOutputStream : public IOutputStream
  {
    public:
      TBool Init(
        TAddressSegment AddrSeg,
        TOperation UnitSetter
      );

      TBool Write(TUnit Unit) override;

    private:
      TAddrsegIterator Rator;
      TOperation SetUnit;
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
