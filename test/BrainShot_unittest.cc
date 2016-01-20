#include "gtest/gtest.h"
#include "arduino-mock/Arduino.h"
#include "arduino-mock/Serial.h"

#include "../BrainShot.ino"
#include "../FSM.h"
#include "../Logger.h"

using ::testing::Return;
using ::testing::AtLeast;                     // #1

TEST(main, setup) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SerialMock* serialMock = serialMockInstance();
    EXPECT_CALL(*arduinoMock, pinMode(10, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(11, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(12, OUTPUT)).Times(1);
    setup();
    releaseSerialMock();
    releaseArduinoMock();
}

/*
TEST(loop, pushed) {
  ArduinoMock* arduinoMock = arduinoMockInstance();
  SerialMock* serialMock = serialMockInstance();
  EXPECT_CALL(*arduinoMock, digitalRead(2))
    .WillOnce(Return(1));
  EXPECT_CALL(*serialMock, println(1, 10));
  EXPECT_CALL(*arduinoMock, delay(1));
  loop();
  releaseSerialMock();
  releaseArduinoMock();
}
*/
TEST(logger, setup) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    EXPECT_CALL(*arduinoMock, pinMode(10, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(11, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(12, OUTPUT)).Times(1);
    Logger::setup();
    releaseArduinoMock();
}

TEST(logger, idle) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SerialMock* serialMock = serialMockInstance();
    EXPECT_CALL(*arduinoMock, digitalWrite(10, HIGH)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(11, LOW)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(12, LOW)).Times(1);
    Logger::idle();
    releaseSerialMock();
    releaseArduinoMock();
}

TEST(logger, read) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SerialMock* serialMock = serialMockInstance();
    EXPECT_CALL(*arduinoMock, digitalWrite(10, LOW)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(11, HIGH)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(12, LOW)).Times(1);
    Logger::read();
    releaseSerialMock();
    releaseArduinoMock();
}

TEST(fsm, construct) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SerialMock* serialMock = serialMockInstance();
    EXPECT_CALL(*arduinoMock, pinMode(10, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(11, OUTPUT)).Times(1);
    EXPECT_CALL(*arduinoMock, pinMode(12, OUTPUT)).Times(1);
    FSM *fsm = new FSM();
    releaseSerialMock();
    releaseArduinoMock();
}

TEST(fsm, init) {
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SerialMock* serialMock = serialMockInstance();
    FSM *fsm = new FSM();
    EXPECT_CALL(*arduinoMock, digitalWrite(10, HIGH)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(11, LOW)).Times(1);
    EXPECT_CALL(*arduinoMock, digitalWrite(12, LOW)).Times(1);
    fsm->init();
    releaseSerialMock();
    releaseArduinoMock();
}
