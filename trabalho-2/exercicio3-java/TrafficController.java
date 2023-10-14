import java.util.concurrent.Semaphore;

public class TrafficController {
  private Semaphore sem;

  public TrafficController(Semaphore s) {
    this.sem = s;
  }
  
  public void enterLeft(){
    try {
    sem.acquire();
    } catch (InterruptedException e) {
    }
  }

  public void enterRight(){
    try {
      sem.acquire();
    } catch (InterruptedException e) {
    }
  }

  public void leaveLeft() {
    sem.release();
  }

  public void leaveRight() {
    //vai usar o release()
    sem.release();
  }

}