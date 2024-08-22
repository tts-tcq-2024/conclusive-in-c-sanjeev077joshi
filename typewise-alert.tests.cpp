#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(InferBreachTest, TemperatureTooLow) {
  EXPECT_EQ(inferBreach(-1, 0, 35), TOO_LOW);
  EXPECT_EQ(inferBreach(5, 10, 35), TOO_LOW);
}

TEST(InferBreachTest, TemperatureTooHigh) {
  EXPECT_EQ(inferBreach(36, 0, 35), TOO_HIGH);
  EXPECT_EQ(inferBreach(46, 0, 45), TOO_HIGH);
}

TEST(InferBreachTest, TemperatureNormal) {
  EXPECT_EQ(inferBreach(25, 0, 35), NORMAL);
  EXPECT_EQ(inferBreach(30, 0, 45), NORMAL);
  EXPECT_EQ(inferBreach(40, 0, 40), NORMAL);
}

TEST(ClassifyTemperatureBreachTest, PassiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 0), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 35), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
}

TEST(ClassifyTemperatureBreachTest, HighActiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
}

TEST(ClassifyTemperatureBreachTest, MedActiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
}

TEST(CheckAndAlertTest, SendToController) {
  BatteryCharacter batteryChar = {PASSIVE_COOLING};
  checkAndAlert(TO_CONTROLLER, batteryChar, -1);
  checkAndAlert(TO_CONTROLLER, batteryChar, 36);
  checkAndAlert(TO_CONTROLLER, batteryChar, 25);
}

TEST(CheckAndAlertTest, SendToEmail) {
  BatteryCharacter batteryChar = {PASSIVE_COOLING};
  checkAndAlert(TO_EMAIL, batteryChar, -1);
  checkAndAlert(TO_EMAIL, batteryChar, 36);
  checkAndAlert(TO_EMAIL, batteryChar, 25);
}

