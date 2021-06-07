
import static org.junit.Assert.assertEquals;

import org.junit.Test;

import game.LifeGame;

public class AppTest2 {

  private final LifeGame jogo = new LifeGame();

  @Test
  public void t1(){    
	int response = jogo.getNextState(-1,3);
	assertEquals(-1, response);
  }

  @Test
  public void t2(){
    int response = jogo.getNextState(2,0);
    assertEquals(-1, response); 
  }

  @Test
  public void t3(){
    int response = jogo.getNextState(0,-1);
    assertEquals(-1, response);
  }

  @Test
  public void t4(){
    int response = jogo.getNextState(1,0);
    assertEquals(0, response);
  }

  @Test
  public void t5(){
    int response = jogo.getNextState(0,0);
    assertEquals(0, response);
  }

  @Test
  public void t6(){
    int response = jogo.getNextState(1,1);
    assertEquals(0, response);
  }

  @Test
  public void t7(){
    int response = jogo.getNextState(1,2);
    assertEquals(1, response);
  }

  @Test
  public void t8(){
    int response = jogo.getNextState(0,2);
    assertEquals(0, response);
  }

  @Test
  public void t9(){
    int response = jogo.getNextState(1,3);
    assertEquals(1, response);
  }

  @Test
  public void t10(){
    int response = jogo.getNextState(0,3);
    assertEquals(1, response);
  }

  @Test
  public void t11(){
    int response = jogo.getNextState(1,4);
    assertEquals(0, response);
  }

  @Test
  public void t12(){
    int response = jogo.getNextState(1,7);
    assertEquals(0, response);
  }

  @Test
  public void t13(){
    int response = jogo.getNextState(1,8);
    assertEquals(0, response);
  }

  @Test
  public void t14(){
    int response = jogo.getNextState(0,8);
    assertEquals(0, response);
  }

  @Test
  public void t15(){
    int response = jogo.getNextState(1,9);
    assertEquals(-1, response);
    
  }
  
}
