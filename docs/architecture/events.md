# Event handling
Event handling i.e., responding to user input is done
through `Observer` pattern. Each `State` directly inherits
from `Subject` which enables them to attach observers to
themselves. Thus each `State` can notify of something happening
like *play* button being pushed. Observers can react on events
that they are monitoring. Such observers can be user stations
database or application configuration reader writer.

`Subject` and `Observer` classes look as follows.
```c++
class Observer {
   public:
    virtual ~Observer() = default;
    virtual void on_notify(const radiostream::Event e,
                           const std::any& data) = 0;
};

class Subject {
   public:
    void attach(std::shared_ptr<Observer> observer);
    void notify(const std::any& data, radiostream::Event e);
};
```