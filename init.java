import processing.core.PApplet;

public class init extends PApplet{
  public static void main(String args[]){
    PApplet.main("init");
  }

  public void settings(){
    size(800,600);
  }
  public void setup(){
    background(200);
  }
  public void draw(){
    ellipse(mouseX,mouseY,50,50);
  }
}
