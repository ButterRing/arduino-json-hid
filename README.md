# arduino-json-hid
After transferring the keyboard input or mouse input JSON script to the Arduino board,
the Arduino board commands the keyboard input or mouse input to the computer.

enable ATmega32u4 or SAMD micro based boards.


## Example
An example from a computer perspective.

### Serial Write

#### Template JSON
``` json
{
  "key": "random key",
  "delay": 200,
  "commands": [
    {
      "method": "method name",
      "params": {
        "delay": 100
      }
    }
  ]
}
```
| type | json key | description |
| ---:| --- | --- |
| string | key | Key to verify returned data |
| int | delay | The overall delay of "commands" |
| array | commands | HID commands |
| string | commands.method | HID command type |
| object | commands.params | HID command params |
| int | commands.params.delay | HID command delay, global delay override |

#### "method" mouse.move
``` json
{
  "method": "mouse.move",
  "params": {
    "x": 20,
    "y": 20,
    "wheel": 0
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| int | x | Relative x-axis movement of the current mouse position |
| int | y | Relative y-axis movement of the current mouse position |
| int | wheel | Mouse wheel |

#### "method" mouse.click
``` json
{
  "method": "mouse.click",
  "params": {
    "button": "LEFT"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | button | [Mouse Modifiers](.#Mouse-Modifires) |

#### "method" mouse.press
``` json
{
  "method": "mouse.press",
  "params": {
    "button": "LEFT"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | button | [Mouse Modifiers](.#Mouse-Modifires) |

#### "method" mouse.release
``` json
{
  "method": "mouse.release",
  "params": {
    "button": "LEFT"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | button | [Mouse Modifiers](.#Mouse-Modifires) |

#### "method" keyboard.write
``` json
{
  "method": "keyboard.write",
  "params": {
    "key": "A"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | key | char \| int \| hex \| oct \| [Keyboard Modifiers](.#Keyboard-Modifires) |

#### "method" keyboard.press
``` json
{
  "method": "keyboard.press",
  "params": {
    "key": "A"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | key | char \| int \| hex \| oct \| [Keyboard Modifiers](.#Keyboard-Modifires) |

#### "method" keyboard.release
``` json
{
  "method": "keyboard.release",
  "params": {
    "key": "A"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | key | char \| int \| hex \| oct \| [Keyboard Modifiers](.#Keyboard-Modifires) |

#### "method" keyboard.releaseAll
``` json
{
  "method": "keyboard.releaseAll",
  "params": {}
}
```

#### "method" keyboard.print
``` json
{
  "method": "keyboard.print",
  "params": {
    "string": "This is keyboard print"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | string | keyboard print text |

#### "method" keyboard.println
``` json
{
  "method": "keyboard.println",
  "params": {
    "string": "This is keyboard println"
  }
}
```
| type | json key | description |
| ---:| --- | --- |
| string | string | keyboard print text |


## Mouse Modifires
| value | description |
| --- | ---|
| LEFT | mouse left button |
| RIGHT | mouse right button |
| MIDDLE | mouse wheel button |


## Keyboard Modifires
| value | description |
| --- | --- |
| LEFT_CTRL | left ctrl key |
| LEFT_SHIFT | left shift key |
| LEFT_ALT | left alt key |
| LEFT_GUI | left command(OSX) \| win(Windows) \| GUI(Linux) key |
| RIGHT_CTRL | right ctrl key |
| RIGHT_SHIFT | right shift key |
| RIGHT_ALT | right alt key |
| RIGHT_GUI | right command(OSX) \| win(Windows) \| GUI(Linux) key |
| UP_ARROW | up arrow key |
| DOWN_ARROW | down arrow key |
| LEFT_ARROW | left arrow key |
| RIGHT_ARROW | right arrow key |
| BACKSPACE | backspace key |
| TAB | tab key |
| RETURN | enter key |
| ESC | esc key |
| INSERT | insert key |
| DELETE | delete key |
| PAGE_UP | page up key |
| PAGE_DOWN | page down key |
| HOME | home key |
| END | end key |
| CAPS_LOCK | caps lock key |
| F1 | f1 key |
| F2 | f2 key |
| F3 | f3 key |
| F4 | f4 key |
| F5 | f5 key |
| F6 | f6 key |
| F7 | f7 key |
| F8 | f8 key |
| F9 | f9 key |
| F10 | f10 key |
| F11 | f11 key |
| F12 | f12 key |
