package editor;

import javafx.scene.control.Button;

class ButtonCoordinate {
	
	public Button b = new Button("");
	public int x, y;
	
	public int getX() {
		
		return x;
	
	}
	
	public int getY() {
	
		return y;
	}
	
	public Button getButton() {
	
		return b;
	}
	
	public void setX(int x) {
	
		this.x = x;
	
	}
	
	public void setY(int y) {
	
		this.y = y;
	
	}
	
	public void setButton(Button br) {
	
		this.b = br;
	
	}

}