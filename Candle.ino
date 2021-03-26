/**
  ******************************************************************************
  * @file    pumpkin.ino
  * @author  Ryan DeWitt
  * @version V2
  * @date    21-Oct-2018
  * @brief   Realisticly simulates a candle flame using four LEDs
  ******************************************************************************
  Copyright (c) 2018 Ryan DeWitt (Pie Thrower)  All rights reserved.

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
  ******************************************************************************
  */

#include <stdint.h>

// First red LED
int ledR1 = D0;
// First yellow LED
int ledY1 = D1;
// Second red LED
int ledR2 = D2;
// Second yellow LED
int ledY2 = D3;


// Current LED Strength
int curStrength = 120;

// Maximum amplitude of flickering
int maxAmp = 100;

// Milliseconds per frame
int frameLength = 10;


void setup() {
    // Pin configuration
    pinMode(ledR1, OUTPUT);
    pinMode(ledY1, OUTPUT);
    pinMode(ledR2, OUTPUT);
    pinMode(ledY2, OUTPUT);
}


void loop() {
    // Keep the lights flickering
    flicker();
}

void flicker() {
    // Amplitude of flickering
    int amp = random(maxAmp)+1;
    
    // Length of flickering in milliseconds
    int length = random(10000/amp)+1000;
    
    // Strength to go toward
    int endStrength = random(255-(amp/4))+(amp/4);
    
    // Flicker function
    flickerSection(length, amp, endStrength);
}

void flickerSection(int length, int amp, int endStrength) {
    // Initilize variables
    int i, max, min;
    double oldStrengthRatio, endStrengthRatio;
    
    // Number of frames to loop through
    int frameNum = length/frameLength;
    
    // Use variable to hold the old LED strength
    int oldStrength = curStrength;
    
    
    // Loop <frameNum> times 
    for(i = 0; i <= frameNum; i += 1){
        // The ratio of the old/end strengths should be proprtional to the ratio of total frames/current frames
        // Use type casting to allow decimals
        oldStrengthRatio = (1-(double)i/(double)frameNum);
        endStrengthRatio = ((double)i/(double)frameNum);
        
        // Fade current LED strength from the old value to the end value
        curStrength = (oldStrength*oldStrengthRatio) + (endStrength*endStrengthRatio);
        
        // LED brightnesses must be in between max and min values
        // Both values are half an amplitude's distance from the average
        max = curStrength+(amp/2);
        min = curStrength-(amp/2);
        
        // Light LEDs to random brightnesses
        setRandom(ledR1, max, min);
        setRandom(ledY1, max, min);
        setRandom(ledR2, max, min);
        setRandom(ledY2, max, min);
        
        // Wait until next frame
        delay(frameLength);
    }
}

void setRandom(int led, int max, int min) {
    // Set chosen LED to a random brightness between the maximum and minimum values
    analogWrite(led, random(max - min) + min);
}

