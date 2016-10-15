import processing.serial.*;
Serial myPort;

import controlP5.*; //Libary mit diversen Knoepfen
ControlP5 controlP5;

import processing.video.*; //Videolibary
Movie theMov; 



void setup() {

  size(800, 500);
  // Visualisierung
  
  theMov = new Movie(this, "DogsEye.mp4"); // Videoeinstellungen
 


  for (int i=0; i< Serial.list ().length; i++) //Zeigt mir in Console meine Ports
    println("["+i+"]"+Serial.list()[i]);

  String portName = Serial.list()[5];
  myPort = new Serial(this, portName, 9600);

  controlP5 = new ControlP5(this); // Knoepfe definieren
  controlP5.addButton("Off", 1, width/2+300, height/2, 65, 20);

  controlP5.addButton("1M vor", 1, 565, 220, 65, 20);
  controlP5.addButton("1M zur", 1, 565, 190, 65, 20);
  controlP5.addButton("kipp vor", 1, 485, 190, 65, 20);
  controlP5.addButton("kipp zur", 1, 485, 220, 65, 20);
  
  controlP5.addButton("Oben", 1, 565, 280, 65, 20);
  controlP5.addButton("Unten", 1, 485, 280, 65, 20);
  
  controlP5.addButton("RD rota", 1, 565, 310, 65, 20);
  controlP5.addButton("LN rota", 1, 485, 310, 65, 20);
  
  controlP5.addButton("Rechts", 1, 565, 340, 65, 20);
  controlP5.addButton("Links", 1, 485, 340, 65, 20);
  
  //controlP5.addButton("Oben", 1, 565, 340, 65, 20);
  //controlP5.addButton("Unten", 1, 485, 340, 65, 20);

  controlP5.addButton("3M Rechts", 1, 565, 130, 65, 20);
  controlP5.addButton("3M Links", 1, 565, 100, 65, 20);
  
  controlP5.addButton("Choreo1", 1, width/2+300, height/2-30, 65, 20);
}

void movieEvent(Movie m) { //Videovoid
  m.read();
}

void draw() {
  background(0, 0, 0);
  image(theMov, 50, 50, width/2, height/2); //Videobildposition
  
  
  if (myPort.available() > 0)
    println("SERIAL INPUT: " +myPort.read());
}

void controlEvent(ControlEvent theEvent) {

  if (theEvent.isController()) { 

    print("control event from : "+theEvent.getController().getName());
    println(", value : "+theEvent.getController().getValue());

    if (theEvent.getController().getName()=="Off") //ButtonOff
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(0);
        println("0");
        theMov.stop();
      }
    }

    if (theEvent.getController().getName()=="1M vor") //Button1
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(1);
        println("1");
        theMov.play();  //plays the movie once
      }
    }

    if (theEvent.getController().getName()=="Oben") //Button2
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(2);
        println("2");
      }
    }

    if (theEvent.getController().getName()=="3M Rechts") //Button3
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(3);
        println("3");
      }
    }

    if (theEvent.getController().getName()=="3M Links") //Button4
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(4);
        println("4");
      }
    }

    if (theEvent.getController().getName()=="1M zur") //Button5
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(5);
        println("5");
      }
    }

    if (theEvent.getController().getName()=="Unten") //Button6
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(6);
        println("6");
      }
    }
    
       if (theEvent.getController().getName()=="RD rota") //Button7
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(7);
        println("7");
      }
    }
      if (theEvent.getController().getName()=="LN rota") //Button8
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(8);
        println("8");
      }
    }
     if (theEvent.getController().getName()=="Rechts") //Button9
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(9);
        println("9");
      }
    }
     if (theEvent.getController().getName()=="Links") //Button10
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(10);
        println("10");
      }
    }
      if (theEvent.getController().getName()=="Choreo1") //Button13
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(13);
        println("13");
      }
    }
       if (theEvent.getController().getName()=="kipp vor") //Button14
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(14);
        println("14");
      }
    }
     if (theEvent.getController().getName()=="kipp zur") //Button15
    {
      if (theEvent.getController().getValue()==1) // die eins ist fix von addButton-Funktion
      {
        myPort.write(15);
        println("15");
      }
    }
  }
}

