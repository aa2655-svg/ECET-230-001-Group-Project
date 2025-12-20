#include <Servo.h>
#include "SR04.h"

// --- PIN ASSIGNMENTS ---
#define TRIG_PIN 12
#define ECHO_PIN 11   
#define BUZZER_PIN 8

// Second Sensor (Out Sensor)
#define HOLE_TRIG 7
#define HOLE_ECHO 4  

SR04 mainSensor = SR04(ECHO_PIN, TRIG_PIN);
SR04 holeSensor = SR04(HOLE_ECHO, HOLE_TRIG);

Servo base, shoulder, elbow, wrist, gripper;

// --- Positions ---
const int base_pos = 70;
const int shoulder_pos = 50;
const int elbow_pos = 100;
const int wrist_pos = 5;
const int gripper_pos = 135;

const int base_target = 0;
const int shoulder_target = 133+1;
const int elbow_target = 61+0;
const int wrist_target = 5;
const int gripper_target = 90;

const int base_target2 = 0;
const int shoulder_target2 = 100;
const int elbow_target2 = 140;
const int wrist_target2 = 5;
const int gripper_target2 = 95;

int s_time = 10; 

// --- Frequencies ---
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_DS4 311  
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_G5  784

enum SongType { MISSION, PINK, CHRISTMAS };
SongType currentSong = MISSION;

int missionMelody[] = { NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_FS4, NOTE_AS4, NOTE_G4, NOTE_D5, NOTE_AS4, NOTE_G4, NOTE_CS5, NOTE_AS4, NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_FS4 };
int missionDur[] = { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800 };

int pinkMelody[] = { NOTE_DS4, NOTE_E4, 0, NOTE_FS4, NOTE_G4, 0, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4 };
int pinkDur[] = { 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 400 };

int xmasMelody[] = { NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4 };
int xmasDur[] = { 200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 800, 200, 200, 200, 200, 200, 200, 200, 100, 100, 200, 200, 200, 200, 400 };

int musicIdx = 0;
unsigned long nextNoteTime = 0;
bool isMoving = false;

void setup() {
  Serial.begin(9600);
  delay(500);

  base.attach(3);
  shoulder.attach(5);
  elbow.attach(6);
  wrist.attach(9); 
  gripper.attach(10);

  base.write(base_pos);
  shoulder.write(shoulder_pos - 3);
  elbow.write(elbow_pos - 50);
  wrist.write(wrist_pos);
  gripper.write(gripper_pos);

  Serial.println("System Ready - Constant Sensing Active.");
}

void loop() {
  checkSensors();
  playMusic();
  delay(10); 
}

void checkSensors() {
  long mainDist = mainSensor.Distance();
  // Small delay to prevent cross-talk between sensors
  delay(10); 
  long holeDist = holeSensor.Distance();

  // PRIORITY 1: Robot Movement (Main Sensor)
  // Only trigger if not already in the middle of a movement sequence
  if (mainDist > 0 && mainDist < 3 && !isMoving) {
    Serial.println("Main Sensor Triggered!");
    isMoving = true;
    currentSong = PINK;
    musicIdx = 0;
    
    waitWithSensing(1000); // 1s wait with music before moving
    runSequence();
    
    // Play remaining song after sequence finishes
    while (musicIdx != 0) {
      playMusic();
      delay(10);
    }
    
    currentSong = MISSION;
    musicIdx = 0;
    isMoving = false;
  } 
  
  // PRIORITY 2: Christmas Song (Hole Sensor)
  // Only trigger if not currently moving
  else if (holeDist > 0 && holeDist < 2 && !isMoving && currentSong != CHRISTMAS) {
    Serial.println("Hole Sensor Triggered!");
    currentSong = CHRISTMAS;
    musicIdx = 0;
    
    // Play full song but keep checking main sensor in case we need to interrupt for movement
    while (currentSong == CHRISTMAS && musicIdx != 0 || (currentSong == CHRISTMAS && musicIdx == 0)) {
        playMusic();
        
        // Re-check main sensor to see if we should interrupt for movement
        long interruptDist = mainSensor.Distance();
        if (interruptDist > 0 && interruptDist < 5) {
            Serial.println("Interrupting Christmas for Robot Movement!");
            return; // Exit loop to handle mainDist in the next global loop iteration
        }
        
        if (musicIdx == 0 && currentSong == CHRISTMAS) break; 
        delay(10);
    }
    
    currentSong = MISSION;
    musicIdx = 0;
  }
}

void playMusic() {
  int* mel; int* dur; int len;
  if (currentSong == MISSION) { mel = missionMelody; dur = missionDur; len = 27; }
  else if (currentSong == PINK) { mel = pinkMelody; dur = pinkDur; len = 21; }
  else if (currentSong == CHRISTMAS) { mel = xmasMelody; dur = xmasDur; len = 25; }
  else return;

  unsigned long currentTime = millis();
  if (currentTime >= nextNoteTime) {
    if (musicIdx < len) {
      if (mel[musicIdx] > 0) tone(BUZZER_PIN, mel[musicIdx], dur[musicIdx]);
      else noTone(BUZZER_PIN);
      nextNoteTime = currentTime + dur[musicIdx] * 1.25;
      musicIdx++;
    } else {
      musicIdx = 0; 
    }
  }
}

// Custom wait that keeps the music playing
void waitWithSensing(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    playMusic();
    delay(5);
  }
}

void smoothMove(Servo &sv, int target) {
  int currentPos = sv.read();
  if (currentPos < target) {
    for (int i = currentPos; i <= target; i++) {
      sv.write(i);
      playMusic(); 
      delay(s_time);
    }
  } else if (currentPos > target) {
    for (int i = currentPos; i >= target; i--) {
      sv.write(i);
      playMusic(); 
      delay(s_time);
    }
  }
}

void runSequence() {
    smoothMove(elbow, elbow_target);
    smoothMove(shoulder, shoulder_target);
    smoothMove(wrist, wrist_target);
    waitWithSensing(800);
    smoothMove(gripper, gripper_target);
    smoothMove(elbow, elbow_pos - 50);
    waitWithSensing(800);
    smoothMove(base, base_pos);
    smoothMove(shoulder, shoulder_pos);
    smoothMove(elbow, elbow_pos);
    smoothMove(wrist, wrist_pos);
    smoothMove(base, base_target);
    smoothMove(elbow, elbow_target2);
    smoothMove(shoulder, shoulder_target2);
    smoothMove(wrist, wrist_target2);
    smoothMove(gripper, gripper_pos);
    waitWithSensing(800);
    smoothMove(base, base_pos);
    smoothMove(shoulder, shoulder_pos - 5);
    smoothMove(elbow, elbow_pos - 50);
    smoothMove(wrist, wrist_pos);
}
