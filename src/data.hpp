#ifndef DATA_H_
#define DATA_H_

namespace data {
enum Wave { Sine, Rect, Tri };
enum Selection { Normal, Fast, Range };
enum Mod { Off, On, SettingSelection, SettingWave };

struct State {
  long freq = 1000;
  Wave wave = Wave::Rect;
  Selection selection = Selection::Normal;
  Mod mod = Mod::Off;
};

enum Click { None, Short, Long };
struct InputEvent {
  Click click;
  long rotation;
};

typedef void (*OnClickCallback)(data::Click);
typedef void (*OnRotateCallback)(long);

typedef void (*InputEventHandler)(InputEvent);

} // namespace data

#endif // DATA_H_
