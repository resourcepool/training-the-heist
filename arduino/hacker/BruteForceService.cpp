#include "BruteForceService.h"
#include "xtensa/core-macros.h"

BruteForceService::BruteForceService() {}

void BruteForceService::startBruteForce() {
    Serial.println("start bruteforce");
    long timeStart = millis();
    setupPinForBruteforce();

for (int i =0; i<100; i++){
  
sendTouch(2);
delay(1000);
sendTouch(3);
delay(1000);
}

//    int i = 1000;
//    while (!digitalRead(SUCCESS_PIN) && i < 10000) {
////      if (i % 1000 == 0){
//        Serial.println(i);
////      } 
//        send4DigitCode(i);
//        sendTouch(10); //send * to validate password
//        i++;
//    }
//    if (digitalRead(SUCCESS_PIN)) {
//        Serial.println("unlocked");
//        Serial.println("time needed : ");
//        Serial.println(millis() - timeStart);
//    }
//    //mainly for speakers, so we can reset keypad without to disconnect hacker arduino
//    setupPinForNeutralAction();
}

void BruteForceService::setupPinForNeutralAction() {
    pinMode(LIN0, INPUT_PULLUP);
    pinMode(LIN1, INPUT_PULLUP);
    pinMode(LIN2, INPUT_PULLUP);
    pinMode(LIN3, INPUT_PULLUP);
    pinMode(COL0, INPUT_PULLUP);
    pinMode(COL1, INPUT_PULLUP);
    pinMode(COL2, INPUT_PULLUP);
}

void BruteForceService::setupPinForBruteforce() {

    pinMode(SUCCESS_PIN, INPUT_PULLUP);

    // INPUT_PULLUP instead of simple INPUT makes things a lot better! (no false number)
    pinMode(COL0, INPUT_PULLUP);
    pinMode(COL1, INPUT_PULLUP);
    pinMode(COL2, INPUT_PULLUP);

    pinMode(LIN0, OUTPUT);
    pinMode(LIN1, OUTPUT);
    pinMode(LIN2, OUTPUT);
    pinMode(LIN3, OUTPUT);
    digitalWrite(LIN0, HIGH);
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, HIGH);
    digitalWrite(LIN3, HIGH);

}


void BruteForceService::send4DigitCode(int code) {
    if (code >= 10)
        send4DigitCode(code / 10);

    int digit = code % 10;
    sendTouch(digit);
}

//void BruteForceService::simulateButtonPress(int col,int line){
//// version easy mais moins efficace
//  while (digitalRead(col)) {}
//  digitalWrite(line,LOW);
//  while (!digitalRead(col)) {}
//  digitalWrite(line,HIGH);
//}

void BruteForceService::simulateButtonPress(int col,int line){
  //le principe est de copier l'état de la colonne contenant la touche voulue sur la ligne de la touche.
  //tant que la colonne de la touche est à l'état haut, on attends
  while (GPIO.in>>col & 0x1){}
  Serial.println("col is low");
  
  //dès qu'elle passe à l'état bas, on fait passer la ligne de la touche à l'état bas
  GPIO.out_w1tc = ((uint32_t)1 << line);
  Serial.println("line is low");
  
  //tant que la colonne est toujours à l'état bas, on attends
  while(!(GPIO.in>>col & 0x1)){}
  
  Serial.println("col is high");
  
  //dès qu'elle repasse à l'état haut, on repasse la ligne à l'état haut
  GPIO.out_w1ts = ((uint32_t)1 << line);
  
  Serial.println("line is high");
}

void BruteForceService::sendTouch(byte touch) {
    setupPinForBruteforce();
//Serial.println("sending : ");
//Serial.println(touch);
    switch (touch) {
        //press button 0
        case 0: //button 0 col1 lin1
            Serial.println("simulate 0");
            simulateButtonPress(COL1,LIN3);
            break;
        case 1: //button 1
            Serial.println("simulate 1");
            simulateButtonPress(COL0,LIN0);
            break;
        case 2: //button 2
            Serial.println("simulate 2");
            simulateButtonPress(COL1,LIN0);
            break;
        case 3: //button 3
            Serial.println("simulate 3");
            simulateButtonPress(COL2,LIN0);
            break;
        case 4: //button 4
            Serial.println("simulate 4");
            simulateButtonPress(COL0,LIN1);
            break;
        case 5: //button 5
            Serial.println("simulate 5");
            simulateButtonPress(COL1,LIN1);
            break;
        case 6: //button 6
            Serial.println("simulate 6");
            simulateButtonPress(COL2,LIN1);
            break;
        case 7: //button 7
            Serial.println("simulate 7");
            simulateButtonPress(COL0,LIN2);
            break;
        case 8: //button 8
            Serial.println("simulate 8");
            simulateButtonPress(COL1,LIN2);
            break;
        case 9: //button 9
            Serial.println("simulate 9");
            simulateButtonPress(COL2,LIN2);
            break;
        case 10: //button *
            Serial.println("simulate *");
            simulateButtonPress(COL0,LIN3);
            break;
        case 11: //button #
            Serial.println("simulate #");
            simulateButtonPress(COL2,LIN3);
            break;
    }
    
    setupPinForNeutralAction();
 delayMicroseconds(500); 
}
