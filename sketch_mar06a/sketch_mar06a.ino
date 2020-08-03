#include <AccelStepper.h> //library motor stepper

#define HALFSTEP 8        // definisi jumlah step

// definisi pin Arduino pada driver motor

#define motorPin1 6 // IN1 pada ULN2003 driver 1

#define motorPin2 5 // IN2 pada ULN2003 driver 1

#define motorPin3 4 // IN3 pada ULN2003 driver 1

#define motorPin4 3 // IN4 pada ULN2003 driver 1

// inisiasi urutan pin IN1-IN3-IN2-IN4 untuk library AccelStepper dengan motor 28BYJ-48

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{

 stepper1.setMaxSpeed(10000.0);    //setting kecepatan maksimal motor

 stepper1.setAcceleration(100.0); //setting akselerasi

 stepper1.setSpeed(10000);            //setting kecepatan

 stepper1.moveTo(3000);        //setting untuk bergerak 3 putaran penuh

}

void loop()
{

 //bila sampai posisi(3000) rubah ke posisi kealikan(berbalik arah)

 if (stepper1.distanceToGo() == 0)
 {

  stepper1.moveTo(-stepper1.currentPosition());

  Serial.println(stepper1.currentPosition());

 }

 stepper1.run(); // perintah menjalankan motor stepper

}
