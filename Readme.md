## What

(2025-08)

Tools and adapters for streams.

Unlike some other authors, I'll try to minimize conceptual scope.

Stream is something that can only be read (or written). You can't
unwind back (no indexability by design).

UART (any communication channel) is good example of stream.


## Code

* [Interface][Interface]
* [Example][Example]
* [Implementation][Implementation]


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Interface]: src/me_StreamTools.h
[Example]: examples/me_StreamTools/me_StreamTools.ino
[Implementation]: src/

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
