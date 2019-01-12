package editor;

import java.io.File;
import java.util.ArrayList;
import java.io.IOException;

import javax.imageio.ImageIO;

import javafx.stage.FileChooser;
import javafx.application.Application;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.layout.VBox;
import javafx.scene.control.ToolBar;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import javafx.scene.paint.Color;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;


public class Canvas4New extends Application {
	
	public int width, height;
	
    public static void main(String[] args) {
        
    	launch(args);
    
    }
    
    public void setWidth(int w) {
    
    	width = w;
    
    }
    
    public void setHeight(int h) {
    
    	height = h;
    
    }
	
    public int getWidth() {
        
    	return width;
    
    }
    
    public int getHeight() {
    
    	return height;
    
    }
    
	public void start(Stage New_Stage) {	

        WritableImage NewCanvas= new WritableImage(width, height);
    	PixelWriter Pixel_Writer = NewCanvas.getPixelWriter();
    	FileChooser ToSave = new FileChooser(); 
    	
		Scene New_Scene = new Scene(new VBox());
    	ToolBar ToolsBar= new ToolBar();
    	Button Save = new Button("Save");
    	ColorPicker Color_Picker = new ColorPicker();
    	GridPane Grid_Pane = new GridPane();
    	VBox Box = (VBox) New_Scene.getRoot();
    	ArrayList<Button> Buttons = new ArrayList<Button>();
    	
    	Box.getChildren().add(ToolsBar);
    	ToolsBar.getItems().addAll(Color_Picker);
    	ToolsBar.getItems().addAll(Save);
    	
    	for (int x = 0; x < width; x++) 
    		
    		for (int y = 0; y < height; y++) {
    		
    			ButtonCoordinate Button_Coordinate = new ButtonCoordinate();
    			Button_Coordinate.setX(x);
    			Button_Coordinate.setY(y);
        		Button_Coordinate.getButton().setMinSize(25, 25);
        		Button_Coordinate.getButton().setStyle("-fx-border-radius: 0;"+
        												"-fx-background-radius: 0;"+
        												"-fx-border-color: white;"+
        												"-fx-background-color: white;");
        		Buttons.add(Button_Coordinate.getButton());
        		
        		Button_Coordinate.getButton().setOnAction(new EventHandler<ActionEvent>() {
                    
        			@Override
                    public void handle(ActionEvent event) {
                    
        				Color color = Color_Picker.getValue();
                    	Pixel_Writer.setColor(Button_Coordinate.getX(), Button_Coordinate.getY(), color);
                    	
                    	String RGB2Hex = String.format("#%02x%02x%02x", (int) (color.getRed() * 255), 
                    								(int) (color.getGreen() * 255), (int) (color.getBlue() * 255)); 
                    	
                    	Button_Coordinate.getButton().setStyle("-fx-background-color:"+ 
                    											RGB2Hex +";"+
                    											"-fx-border-radius: 0;"+
                    											"-fx-background-radius: 0;"+
                    											"-fx-border-color:"+ 
                    											RGB2Hex);
                
        			}
        			
        		});
        		
        		Grid_Pane.add(Buttons.get(height * x + y), x, y);
    		
    		}
    	
    	Box.getChildren().add(Grid_Pane);
        
        Save.setOnAction(new EventHandler<ActionEvent>() {       	
        
        	@Override
			public void handle(ActionEvent event) {
			
        		File filename = ToSave.showSaveDialog(New_Stage.getOwner());
			
        		if (filename != null) {
				
        			try {
						
							ImageIO.write(SwingFXUtils.fromFXImage(NewCanvas, null), "png", filename);
					
					} catch (IOException e) {
					
						e.printStackTrace();
				
					}
			
				}
		
			}
		
        });
    	
    	New_Stage.setScene(New_Scene);
    	New_Stage.show();     
    	
    }

}

