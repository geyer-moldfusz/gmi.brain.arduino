BOARD_TAG              = uno
ARDUINO_LIBS           = SoftwareSerial Adafruit_Thermal
USER_LIB_PATH          := $(realpath ./lib)

include /usr/share/arduino/Arduino.mk
