# Design

*RadioBrowser* can be dissected into few components related to
the area of functionality. These would be representation i.e.,
GUI, stream playback, localization and user configuration
storage.

## Graphical user interface (states)
*RadioBrowser* uses *nana* to build GUI and follows *MVC*
pattern in order to connect representation, data and logic
without introducing tight coupling. There is a class
for each specific window state that contains all the
widgets that are part of the state.

More on states in [*`States`*](states.md).

## Event handling
MVC is implemented through self rolled *Observer* pattern
(check `Observer.hpp` and `Subject.hpp` to see how it is implemented).

More on event handling in [*`Event handling`*](events.md).

## Stream playback
`bass` library is responsible for both stream receiving
through `http` then decoding it and finally outputting
it to sound device.

More on stream playback in [*`Stream playback`*](stream.md).

## Localization
Localization is supported by `nana` library directly. It uses
`po` files which is format specific for translations. There
are some wrappers imlemented around this system for ease of
use.

More on localization in [*`Localization`*](localization.md).

## Configuration storage
User configuration is done with config.ini 

More on stream configuration in [*`Configuration`*](configuration.md).