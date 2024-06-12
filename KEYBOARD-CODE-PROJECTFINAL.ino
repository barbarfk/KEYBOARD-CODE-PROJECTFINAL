#include <Keyboard.h>
#include "Keyboard.h"
#include <Encoder.h>
#include <Keypad.h>
#include <Mouse.h>


#define ENCODER1_PIN_A A2 
#define ENCODER1_PIN_B A1 
#define ENCODER1_BUTTON_PIN A0 
#define ENCODER2_PIN_A 15
#define ENCODER2_PIN_B 14
#define ENCODER2_BUTTON_PIN 16
int lastEncoded1 = 0;
long encoderValue1 = 0;
bool rightTurn1 = false;
bool leftTurn1 = false;
bool enterPressed1 = false;
int lastEncoded2 = 0;
long encoderValue2 = 0;
bool upTurn2 = false;
bool downTurn2 = false;
bool undoPressed2 = false;
#define ROWS 3
#define COLS 4
char klavye[ROWS][COLS] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'}
};
byte rowPins[ROWS] = {7, 8, 9};
byte colPins[COLS] = {3, 4, 5, 6};
void setup() {
 
 pinMode(ENCODER1_PIN_A, INPUT_PULLUP);
 pinMode(ENCODER1_PIN_B, INPUT_PULLUP);
 pinMode(ENCODER1_BUTTON_PIN, INPUT_PULLUP);
 pinMode(ENCODER2_PIN_A, INPUT_PULLUP);
 pinMode(ENCODER2_PIN_B, INPUT_PULLUP);
 pinMode(ENCODER2_BUTTON_PIN, INPUT_PULLUP);
 for (int i = 0; i < ROWS; i++) {
 pinMode(rowPins[i], OUTPUT);
 }
 for (int i = 0; i < COLS; i++) {
 pinMode(colPins[i], INPUT_PULLUP);
 }
 Keyboard.begin();
 Serial.begin(9600);
}
void loop() {
 int MSB1 = digitalRead(ENCODER1_PIN_A);
 int LSB1 = digitalRead(ENCODER1_PIN_B);
 int encoded1 = (MSB1 << 1) | LSB1;
 int sum1 = (lastEncoded1 << 2) | encoded1;
 if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011) {
 encoderValue1++;
 rightTurn1 = true;
 }
 if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000) {
 encoderValue1--;
 leftTurn1 = true;
 }
 lastEncoded1 = encoded1;
 if (digitalRead(ENCODER1_BUTTON_PIN) == LOW) {
 enterPressed1 = true;
 }
 if (rightTurn1) {
 Keyboard.press(KEY_RIGHT_ARROW);
 delay(0); 
 Keyboard.release(KEY_RIGHT_ARROW);
 rightTurn1 = false;
 }
 if (leftTurn1) {
 Keyboard.press(KEY_LEFT_ARROW);
 delay(0);
 Keyboard.release(KEY_LEFT_ARROW);
 leftTurn1 = false;
 }
 if (enterPressed1) {
 Mouse.click(MOUSE_LEFT); // Left click
 delay(1000); // Hold for 1 second
 Mouse.release(MOUSE_LEFT); // Release left button
 enterPressed1 = false;
 }
 int MSB2 = digitalRead(ENCODER2_PIN_A);
 int LSB2 = digitalRead(ENCODER2_PIN_B);
 int encoded2 = (MSB2 << 1) | LSB2;
 int sum2 = (lastEncoded2 << 2) | encoded2;
 if (sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) {
 encoderValue2++;
 upTurn2 = true;
 }
 if (sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) {
 encoderValue2--;
 downTurn2 = true;
 }
 lastEncoded2 = encoded2;
 if (digitalRead(ENCODER2_BUTTON_PIN) == LOW) {
 undoPressed2 = true;
 }
 if (upTurn2) {
 Keyboard.press(KEY_UP_ARROW);
 delay(0); 
 Keyboard.release(KEY_UP_ARROW);
 upTurn2 = false;
 }
 if (downTurn2) {
 Keyboard.press(KEY_DOWN_ARROW);
 delay(0);
 Keyboard.release(KEY_DOWN_ARROW);
 downTurn2 = false;
 }
 if (undoPressed2) {
 Mouse.click(MOUSE_RIGHT); // Right click
 delay(1000); // Hold for 1 second
 Mouse.release(MOUSE_RIGHT); // Release Right button
 undoPressed2 =  false;
 }
 char pressedKey = scanKeypad();
 if (pressedKey) {
 Serial.println(pressedKey);
 sendKeyCommand(pressedKey);
 }
 delay(10);
}
char scanKeypad() {
 for (int i = 0; i < ROWS; i++) {
 digitalWrite(rowPins[i], LOW);
 for (int j = 0; j < COLS; j++) {
 if (!digitalRead(colPins[j])) { 
 digitalWrite(rowPins[i], HIGH); 
 while (!digitalRead(colPins[j])); 
 delay(500); 
 return klavye[i][j]; 
 }
 }
 digitalWrite(rowPins[i], HIGH); 
 }
 return 0; 
}
void sendKeyCommand(char key) {
 if (key) {
 Serial.println(key);
 switch (key) {
 case '1':
 Keyboard.println("if() {");
 Keyboard.println("}");
 Keyboard.write(KEY_UP_ARROW);
 Keyboard.write(KEY_UP_ARROW);
 Keyboard.write(KEY_RIGHT_ARROW);
 Keyboard.write(KEY_RIGHT_ARROW);
 Keyboard.write(KEY_RIGHT_ARROW); 
 break;
 case '2':
 Keyboard.println("BUTTON CONTROL 2");
 break;
 case '3':
 Keyboard.println("BUTTON CONTROL 3");
 break;
 case 'A':
 Keyboard.println("BUTTON CONTROL A");
 break;
 case '4':
 Keyboard.println("BUTTON CONTROL 4");
 break;
 case '5':
 Keyboard.println("BUTTON CONTROL 5");
 break;
 case '6':
 Keyboard.println("BUTTON CONTROL 6");
 break;
 case 'B':
 Keyboard.println("BUTTON CONTROL B");
 break;
 case '7':
 Keyboard.println("BUTTON CONTROL 7");
 break;
 case '8':
 Keyboard.println("BUTTON CONTROL 8");
 break;
 case '9':
 Keyboard.println("BUTTON CONTROL 9");
 break;
 case 'C':
 Keyboard.println("BUTTON CONTROL C");
 break;
 
 
 }
 delay(200);
 
}
}
