/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

// Function that sorts an array by finding the lowest value & moving it to the bottom.
// It then increments so that it won't ever check the bottom value. It takes n^2 cycles to complete.
// Repeats the operations done to the melody on the note duration, so that the
// notes have the same length post-sorting as the did pre-sort.
void selectSort(int arrayIn[], int arrayIn2[], int n) 
{ 
    int i, j, min_i; 
 
    for (i = 0; i < n-1; i++)
    { 
        min_i = i; 
        for (j = i+1; j < n; j++) 
          if (arrayIn[j] < arrayIn[min_i]) 
            min_i = j; 
  
        swap(&arrayIn[min_i], &arrayIn[i]);
        swap(&arrayIn2[min_i], &arrayIn2[i]);
        
    } 
} 

// Generic swap function.
void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
}

void setup() {
  // Declare the variables.
  int limit = random(5, 10);
  int melody[limit];
  int noteDurations[limit];

  // Generate the random notes using the formula for the frequency of notes (2^((n-49)/12)*440).
  for (int i = 0; i < limit; i++) {
    int randnum = random(20, 70);
    float exponent = (randnum-49)/12;
    float freq = pow(2, exponent) * 440;
    melody[i] = round(freq);
  }
  
  // Generate random note durations. 
  // 1 = 1000ms/2 = 500ms, 2 = 1000ms/4 = 250ms, 3 = 1000ms/8 = 125ms.
  for (int i = 0; i < limit; i++) {
    int randnum = random(1,3);
    if(randnum == 1 || randnum == 2) {
      noteDurations[i] = randnum * 2;
    }
    else {
      noteDurations[i] = 8;
    }
  }

  //Plays the song.
  for (int thisNote = 0; thisNote < limit; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }

  // Sorts the song.
  selectSort(melody, noteDurations, limit);

  // Generate a pause between the 1st & 2nd playthrough.
  delay(1500);

  // Plays the song again.
  for (int thisNote = 0; thisNote < limit; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
