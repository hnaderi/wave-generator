#ifndef DATA_H_
#define DATA_H_

namespace data {
enum class Wave { Sine, Rect, Tri };
enum class Selection { Normal, Fast, Range };
enum class Mod { Off, On, Setting };

struct State {
  long freq = 1000;
  Wave wave = Wave::Rect;
  Selection selection = Selection::Normal;
  Mod mod = Mod::Off;
};

enum class Click { None, Short, Long };
struct InputEvent {
  Click click;
  long rotation;
};

typedef void (*OnClickCallback)(data::Click);
typedef void (*OnRotateCallback)(long);

typedef void (*InputEventHandler)(InputEvent);

} // namespace data

#endif // DATA_H_
