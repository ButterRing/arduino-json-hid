#include <Mouse.h>
#include <Keyboard.h>
#include <ArduinoJson.h>
#include <MemoryFree.h>

DynamicJsonBuffer jsonBuffer;

void setup()
{
  Serial.setTimeout(0);
  Serial.begin(9600);

  Mouse.begin();
  Keyboard.begin();
}

void loop()
{
  if (Serial.available())
  {
    unsigned long startTime = millis();

    String json = Serial.readString();
    JsonObject& root = jsonBuffer.parseObject(json);
    JsonObject& resultRoot = jsonBuffer.createObject();

    methodArrayHandler(root["commands"], root["delay"]);

    resultRoot["key"] = root["key"];
    resultRoot["ms"] = millis() - startTime;
    resultRoot["freeMemory"] = freeMemory();

    resultRoot.printTo(Serial);
    Serial.println();

    jsonBuffer.clear();
  }
}

// methodArray = [ ...MethodItem ];
void methodArrayHandler(JsonArray& methodArray, int rootDelayTime) {
  for ( int i = 0; i < methodArray.size(); i = i + 1 )
  {
    methodItemHandler(methodArray[i], rootDelayTime);
  }
}

// methodItem = { "method": string, "params": { "delay": int, ... } }
void methodItemHandler(JsonObject& methodItem, int rootDelayTime) {
  String method = methodItem["method"];
  JsonObject& params = methodItem["params"];

  //  Serial.print("method: ");
  //  Serial.println(method);

  if (method == "mouse.move") {
    mouseMove(params);
  } else if (method == "mouse.click") {
    mouseClick(params);
  } else if (method == "mouse.press") {
    mousePress(params);
  } else if (method == "mouse.release") {
    mouseRelease(params);
  } else if (method == "keyboard.write") {
    keyboardWrite(params);
  } else if (method == "keyboard.press") {
    keyboardPress(params);
  } else if (method == "keyboard.release") {
    keyboardRelease(params);
  } else if (method == "keyboard.releaseAll") {
    keyboardReleaseAll(params);
  } else if (method == "keyboard.print") {
    keyboardPrint(params);
  } else if (method == "keyboard.println") {
    keyboardPrintln(params);
  }


  int delayTime = params["delay"];
  if (delayTime) {
    //    Serial.print("delay: ");
    //    Serial.println(delayTime);

    delay(delayTime);
  } else if (rootDelayTime) {
    delay(rootDelayTime);
  }
}

/*
   MOUSE METHOD
*/

// MouseButton = "LEFT" | "RIGHT" | "MIDDLE"
char convertMouseButton(String& button) {
  if (button == "LEFT")
    return MOUSE_LEFT;
  if (button == "RIGHT")
    return MOUSE_RIGHT;
  if (button == "MIDDLE")
    return MOUSE_MIDDLE;
}


// { "method": "mouse.move", "params": {"x": int, "y": int, "wheel": int } }
void mouseMove(JsonObject& params) {
  int x = params["x"];
  int y = params["y"];
  int wheel = params["wheel"];

  //  Serial.print("x: ");
  //  Serial.println(x);
  //  Serial.print("y: ");
  //  Serial.println(y);
  //  Serial.print("wheel: ");
  //  Serial.println(wheel);

  Mouse.move(x, y, wheel);
}

// { "method": "mouse.click", "params": {"button": MouseButton } }
void mouseClick(JsonObject& params) {
  String button = params["button"];

  //  Serial.print("button: ");
  //  Serial.println(button);

  char mouseButton = convertMouseButton(button);

  Mouse.click(mouseButton);
}

// { "method": "mouse.press", "params": {"button": MouseButton } }
void mousePress(JsonObject& params) {
  String button = params["button"];

  //  Serial.print("button: ");
  //  Serial.println(button);

  char mouseButton = convertMouseButton(button);

  Mouse.press(mouseButton);
}

// { "method": "mouse.release", "params": {"button": MouseButton } }
void mouseRelease(JsonObject& params) {
  String button = params["button"];

  //  Serial.print("button: ");
  //  Serial.println(button);

  char mouseButton = convertMouseButton(button);

  Mouse.release(mouseButton);
}



/*
   KEYBOARD METHOD
*/

// enum KeyboardButton =
//  char | int | Hex | Oct |
//  "LEFT_CTRL" | "LEFT_SHIFT" | "LEFT_ALT" | "LEFT_GUI" |
//  "RIGHT_CTRL" | "RIGHT_SHIFT" | "RIGHT_ALT" | "RIGHT_GUI" |
//  "UP_ARROW" | "DOWN_ARROW" | "LEFT_ARROW" | "RIGHT_ARROW" |
//  "BACKSPACE" | "TAB" | "RETURN" | "ESC" | "INSERT" | "DELETE" |
//  "PAGE_UP" | "PAGE_DOWN" |
//  "HOME" | "END" |
//  "CAPS_LOCK |
//  "F1" | "F2" | "F3" | "F4" | "F5" | "F6" |
//  "F7" | "F8" | "F9" | "F10" | "F11" | "F12"
char convertKeyboardButton(String& button) {
  if (button == "LEFT_CTRL") return KEY_LEFT_CTRL;
  if (button == "LEFT_SHIFT") return KEY_LEFT_SHIFT;
  if (button == "LEFT_ALT") return KEY_LEFT_ALT;
  if (button == "LEFT_GUI") return KEY_LEFT_GUI;
  if (button == "RIGHT_CTRL") return KEY_RIGHT_CTRL;
  if (button == "RIGHT_SHIFT") return KEY_RIGHT_SHIFT;
  if (button == "RIGHT_ALT") return KEY_RIGHT_ALT;
  if (button == "RIGHT_GUI") return KEY_RIGHT_GUI;
  if (button == "UP_ARROW") return KEY_UP_ARROW;
  if (button == "DOWN_ARROW") return KEY_DOWN_ARROW;
  if (button == "LEFT_ARROW") return KEY_LEFT_ARROW;
  if (button == "RIGHT_ARROW") return KEY_RIGHT_ARROW;
  if (button == "BACKSPACE") return KEY_BACKSPACE;
  if (button == "TAB") return KEY_TAB;
  if (button == "RETURN") return KEY_RETURN;
  if (button == "ESC") return KEY_ESC;
  if (button == "INSERT") return KEY_INSERT;
  if (button == "DELETE") return KEY_DELETE;
  if (button == "PAGE_UP") return KEY_PAGE_UP;
  if (button == "PAGE_DOWN") return KEY_PAGE_DOWN;
  if (button == "HOME") return KEY_HOME;
  if (button == "END") return KEY_END;
  if (button == "CAPS_LOCK") return KEY_CAPS_LOCK;
  if (button == "F1") return KEY_F1;
  if (button == "F2") return KEY_F2;
  if (button == "F3") return KEY_F3;
  if (button == "F4") return KEY_F4;
  if (button == "F5") return KEY_F5;
  if (button == "F6") return KEY_F6;
  if (button == "F7") return KEY_F7;
  if (button == "F8") return KEY_F8;
  if (button == "F9") return KEY_F9;
  if (button == "F10") return KEY_F10;
  if (button == "F11") return KEY_F11;
  if (button == "F12") return KEY_F12;
}

int getKeyButton(String key) {
  int keyButton;

  if (key.length() == 1) {
    keyButton = key[0];
  } else {
    keyButton = convertKeyboardButton(key);

    if (!keyButton) {
      char *stopStrtol;
      keyButton = strtol(key.c_str(), &stopStrtol, 0);
    }
  }

  return keyButton;
}

// { "method": "keyboard.write", "params": {"key": KeyboardButton } }
void keyboardWrite(JsonObject& params) {
  String key = params["key"];

  //  Serial.print("key: ");
  //  Serial.println(key);

  int keyButton = getKeyButton(key);

  Keyboard.write(keyButton);
}

// { "method": "keyboard.press", "params": {"key": KeyboardButton } }
void keyboardPress(JsonObject& params) {
  String key = params["key"];

  //  Serial.print("key: ");
  //  Serial.println(key);

  int keyButton = getKeyButton(key);

  Keyboard.press(keyButton);
}

// { "method": "keyboard.release", "params": {"key": KeyboardButton } }
void keyboardRelease(JsonObject& params) {
  String key = params["key"];

  //  Serial.print("key: ");
  //  Serial.println(key);

  int keyButton = getKeyButton(key);

  Keyboard.release(keyButton);
}

// { "method": "keyboard.releaseAll", "params": {} }
void keyboardReleaseAll(JsonObject& params) {
  Keyboard.releaseAll();
}

// { "method": "keyboard.print", "params": {"string": KeyboardButton } }
void keyboardPrint(JsonObject& params) {
  String string = params["string"];

  //  Serial.print("string: ");
  //  Serial.println(string);

  Keyboard.print(string);
}

// { "method": "keyboard.println", "params": {"string": KeyboardButton } }
void keyboardPrintln(JsonObject& params) {
  String string = params["string"];

  //  Serial.print("string: ");
  //  Serial.println(string);

  Keyboard.println(string);
}
