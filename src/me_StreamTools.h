// Flesh for streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-10-14
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

namespace me_StreamTools
{
  // [Emitter] .Read() --> 0
  class TZeroesInputStream : public TInputStream
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

    private:
      TFixedOperation ReadUnit;
  };

  // [Adapter] Output stream == Writer
  class TWriterOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    private:
      TFixedOperation WriteUnit;
  };

  // [Internal] Address segment iterator base class
  class TAddrsegStream
  {
    public:
      TBool Init(TAddressSegment AddrSeg);

      TAddressSegment GetProcessedSegment();

    protected:
      TAddrsegIterator Rator;

    private:
      TAddressSegment OrigAddrSeg;
  };

  // [Adapter] Input stream = Address segment + Getter
  class TAddrsegInputStream : public IInputStream, public TAddrsegStream
  {
    public:
      TBool Init(TAddressSegment AddrSeg, TOperation UnitGetter);

      TBool Read(TUnit * Unit) override;

    private:
      TOperation GetUnit;
  };

  // [Adapter] Output stream = Address segment + Setter
  class TAddrsegOutputStream : public IOutputStream, public TAddrsegStream
  {
    public:
      TBool Init(TAddressSegment AddrSeg, TOperation UnitSetter);

      TBool Write(TUnit Unit) override;

    private:
      TOperation SetUnit;
  };

  // [Copy] Input --> Output, fails when output is full
  TBool CopyStreamTo(
    TInputStream * InputStream,
    IOutputStream * OutputStream
  );

  // [Copy] Input --> Output, fails when input is empty
  TBool LoadStreamFrom(
    IOutputStream * OutputStream,
    TInputStream * InputStream
  );

  // [Compare] A == B ?
  TBool StreamsAreEqual(
    IInputStream * A_Stream,
    IInputStream * B_Stream
  );
}

/*
  2025 # # # # # #
  2025-10-12 [+] LoadStreamFrom()
  2025-10-14
*/
