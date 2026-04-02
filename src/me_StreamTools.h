// Flesh for streams interface

/*
  Author: Martin Eden
  Last mod.: 2026-04-02
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

  // [Internal] Stream = Segment + Operation
  class TAddrsegStream
  {
    public:
      TBool Init(TAddressSegment AddrSeg, TMethod Operation);

      TAddressSegment GetProcessedSegment();

    protected:
      TAddrsegIterator Rator;
      TMethod Operation;

    private:
      TAddressSegment AddrSeg;
  };

  /*
    Streams over address segment believe that their operation
    never fails when called with address from that segment.

    So Read() or Write() will fail only after end of segment.
  */

  // [Adapter] Input stream
  class TAddrsegInputStream : public IInputStream, public TAddrsegStream
  {
    public:
      TBool Read(TUnit * Unit) override;
  };

  // [Adapter] Output stream
  class TAddrsegOutputStream : public IOutputStream, public TAddrsegStream
  {
    public:
      TBool Write(TUnit Unit) override;
  };

  // [Extender] Re-readable input stream
  class TRereadableInputStream : public IInputStream
  {
    public:
      void Init(IInputStream * InputStream);
      TBool Read(TUnit * Unit) override;
      TBool Unread();

    private:
      IInputStream * InputStream;
      TBool HasUnitRead;
      TBool UseUnitRead;
      TUnit UnitRead;
  };

  // [Copy] Input --> Output, fails when output becomes full
  TBool SaveStreamTo(
    IInputStream * InputStream,
    IOutputStream * OutputStream
  );

  // [Copy] Input --> Output, fails when input becomes empty
  TBool LoadStreamFrom(
    IOutputStream * OutputStream,
    TRereadableInputStream * InputStream
  );

  // [Compare] A == B ?
  TBool StreamsAreEqual(
    IInputStream * A_Stream,
    IInputStream * B_Stream
  );
}

/*
  2025 # # # # # # # #
  2026-03-31
  2026-04-02
*/
