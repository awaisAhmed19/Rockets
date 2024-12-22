import processing.core.PApplet;

public class init extends PApplet {
  float angle = PI;   // Angle in radians
  float angleVelocity=0;
  float angleAcceleration=0;
  float amp = 200;    // Amplitude of the pendulum's swing
  float gravity = -9.81f; // Increment for the angle

  public static void main(String[] args) {
    PApplet.main("init");
  }

  public void settings() {
    size(800, 600); // Set canvas size
  }

  public void setup() {
    stroke(0);       // Set stroke color to black
    strokeWeight(2); // Set line thickness
  }

  public void draw() {
    background(200); // Clear the screen with a light gray background
    float Ox=width/2;
    float Oy=100;
    // Calculate pendulum's position
    float bx = Ox + amp * sin(angle);
    float by = Oy + amp * cos(angle);

    // Increment angle for motion
    //angle += speed;

    // Draw the pendulum
    line(Ox, Oy, bx, by); // Rod
    fill(0);
    ellipse(bx, by, 20, 20);    // Bob
    
    angleAcceleration=(1*gravity/amp)*sin(angle);
    angleVelocity+=angleAcceleration;
    angleVelocity*=0.99;
    angle+=angleVelocity;
  }
}
