// Streams interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-26
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_Streams
{
  // Input stream concept
  class IInputStream
  {
    public:
      virtual TBool Read(TUnit * Unit) = 0;
  };

  // Output stream concept
  class IOutputStream
  {
    public:
      virtual TBool Write(TUnit Unit) = 0;
  };

  // Input stream, requires reader
  class TInputStream : public IInputStream
  {
    public:
      void Init(TFixedOperation UnitReader);

      TBool Read(TUnit * Unit) override;

    protected:
      TFixedOperation ReadUnit;
  };

  // Output stream, requires writer
  class TOutputStream : public IOutputStream
  {
    public:
      void Init(TFixedOperation UnitWriter);

      TBool Write(TUnit Unit) override;

    protected:
      TFixedOperation WriteUnit;
  };

  // Copy stream
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
