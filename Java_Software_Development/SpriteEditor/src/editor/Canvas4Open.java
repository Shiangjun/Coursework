package editor;

import javafx.application.*;
import javafx.embed.swing.SwingFXUtils;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.stage.*;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ToolBar;
import javafx.scene.image.Image;
import javafx.scene.image.PixelReader;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;

import javax.imageio.ImageIO;

public class Canvas4Open extends Application {

	public int width, height;
	URL File_Path;
	
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
	
	@Override
	public void start(Stage New_Stage) {
		
		Image ImportedImage = new Image(File_Path.toString());
		WritableImage Writable_Image = new WritableImage(width,height);
		PixelWriter Pixel_Writer = Writable_Image.getPixelWriter();
        PixelReader Pixel_Reader = ImportedImage.getPixelReader();    
        
		Scene New_Scene = new Scene(new VBox());
    	ToolBar ToolsBar = new ToolBar();
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
        												" -fx-background-radius: 0;"+
        												" -fx-border-color: white;"+
        												"-fx-background-color: white;");
        		Buttons.add(Button_Coordinate.getButton());
        		
        		Button_Coordinate.getButton().setOnAction(new EventHandler<ActionEvent>() {
        			
                    @Override
                    public void handle(ActionEvent event) {
                    	
                    	Color color = Color_Picker.getValue();
                    	Pixel_Writer.setColor(Button_Coordinate.getX(), Button_Coordinate.getY(), color);//
                    	
                    	String RGB2Hex = String.format("#%02x%02x%02x", (int) (color.getRed() * 255), 
                    								(int) (color.getGreen() * 255), (int) (color.getBlue() * 255));
                    	
                    	Button_Coordinate.getButton().setStyle("-fx-background-color:"+ 
                    											RGB2Hex);
                    	
                    }
                    
        		});
        		
        		Grid_Pane.add(Buttons.get(height * x + y), x, y);
        		
    		}
		            		               		
        for (int x = 0; x < ImportedImage.getWidth(); x++)
        	
        	for (int y = 0; y < ImportedImage.getHeight(); y++) {
        		
        		Color color = Pixel_Reader.getColor(y,x);
        		Pixel_Writer.setColor(y,x,color);
                        
                String RGB2Hex = String.format("#%02x%02x%02x", (int) (color.getRed() * 255), 
                  							(int) (color.getGreen() * 255), (int) (color.getBlue() * 255)); 
                
                Buttons.get(width*y+x).setStyle("-fx-background-color:"+ 
                  								RGB2Hex+ 
                  								"; -fx-border-radius: 0; -fx-background-radius: 0;"+
                  								"-fx-border-color:"+ 
                  								RGB2Hex);
               	
         	}    
		
    	 
		Box.getChildren().add(Grid_Pane);
		
		New_Stage.setScene(New_Scene);
    	New_Stage.show();
    	
    	FileChooser ToSave = new FileChooser(); 
    	
    	Save.setOnAction(new EventHandler<ActionEvent>() {       	
    		 
			@Override
			public void handle(ActionEvent event) {
				
				File filename = ToSave.showSaveDialog(New_Stage.getOwner());
				
				if (filename != null) {
					
					try {
						
							ImageIO.write(SwingFXUtils.fromFXImage(Writable_Image, null), "png", filename);
							
					} catch (IOException e) {
						
						e.printStackTrace();
						
					}
					
				}
				
			}
			
		});
		
	}

}