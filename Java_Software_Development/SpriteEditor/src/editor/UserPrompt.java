package editor;

import java.io.File;
import java.io.IOException;

import javafx.application.*;
import javafx.stage.*;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;

public class UserPrompt extends Application {

	public static void main(String[] args) {
		
		launch(args);
	
	}
 
	@Override
	public void start(Stage Current_Stage) throws Exception {
		
		GridPane Grid_Pane = new GridPane();
		Scene New_Scene = new Scene(Grid_Pane, 400, 275);
		Text PromptInfo = new Text("What size of the canvas do u want?");
		Label LabelHeight = new Label("Height:");
		Label LabelWidth = new Label("Width:");
		TextField Width_Input = new TextField();
		TextField Height_Input = new TextField();	
		Button New = new Button("New");
		Button Open = new Button("Open");
		
		Grid_Pane.setAlignment(Pos.CENTER);
		Grid_Pane.setHgap(10);
		Grid_Pane.setVgap(10);
		Grid_Pane.setPadding(new Insets(25, 25, 25, 25));		
 		PromptInfo.setFont(Font.font("Times New Roman", FontWeight.NORMAL, 23));
		Grid_Pane.add(PromptInfo, 0, 0, 2, 1);
		LabelWidth.setFont(Font.font("Times New Roman", FontWeight.NORMAL, 17));
		Grid_Pane.add(LabelWidth, 0, 1);
		Grid_Pane.add(Width_Input, 1, 1);		
		LabelHeight.setFont(Font.font("Times New Roman", FontWeight.NORMAL, 17));
		Grid_Pane.add(LabelHeight, 0, 2);
		Grid_Pane.add(Height_Input, 1, 2);		
		New.setMinSize(100, 40);
		Open.setMinSize(100, 40);		
		New.setStyle(" -fx-background-color: \r\n" + 
				"        #090a0c,\r\n" + 
				"        linear-gradient(#38424b 0%, #1f2429 20%, #191d22 100%),\r\n" + 
				"        linear-gradient(#20262b, #191d22),\r\n" + 
				"        radial-gradient(center 50% 0%, radius 100%, rgba(114,131,148,0.9), rgba(255,255,255,0));\r\n" + 
				"    -fx-background-radius: 5,4,3,5;\r\n" + 
				"    -fx-background-insets: 0,1,2,0;\r\n" + 
				"    -fx-text-fill: white;\r\n" + 
				"    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 5, 0.0 , 0 , 1 );\r\n" + 
				"    -fx-font-family: \"Arial\";\r\n" + 
				"    -fx-text-fill: linear-gradient(white, #d0d0d0);\r\n" + 
				"    -fx-font-size: 16px;\r\n" + 
				"    -fx-padding: 10 20 10 20;" +
				"    -fx-font-weight: bold;");		
		Open.setStyle(" -fx-background-color: \r\n" + 
				"        #090a0c,\r\n" + 
				"        linear-gradient(#38424b 0%, #1f2429 20%, #191d22 100%),\r\n" + 
				"        linear-gradient(#20262b, #191d22),\r\n" + 
				"        radial-gradient(center 50% 0%, radius 100%, rgba(114,131,148,0.9), rgba(255,255,255,0));\r\n" + 
				"    -fx-background-radius: 5,4,3,5;\r\n" + 
				"    -fx-background-insets: 0,1,2,0;\r\n" + 
				"    -fx-text-fill: white;\r\n" + 
				"    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 5, 0.0 , 0 , 1 );\r\n" + 
				"    -fx-font-family: \"Arial\";\r\n" + 
				"    -fx-text-fill: linear-gradient(white, #d0d0d0);\r\n" + 
				"    -fx-font-size: 16px;\r\n" + 
				"    -fx-padding: 10 20 10 20;" +
				"    -fx-font-weight: bold;");	
		HBox CenteralPosition = new HBox(10);
		CenteralPosition.setAlignment(Pos.BOTTOM_CENTER);
		CenteralPosition.getChildren().add(New);
		CenteralPosition.getChildren().add(Open);
		Grid_Pane.add(CenteralPosition, 1, 4);
		
		
		New.setOnAction(e->{
			
			Canvas4New Canvas = new Canvas4New();
			
			try {
				
				String wstr = Width_Input.getText();
				String hstr = Height_Input.getText();
				
				int w = Integer.parseInt(wstr);
				int h = Integer.parseInt(hstr);
				
				Canvas.width = w; 
				Canvas.height = h;

				Canvas.start(new Stage());
				Current_Stage.hide(); 
				
			} catch (Exception e1) {
				
				System.out.println("Input Invalid (Should greater than zero)");
				e1.printStackTrace();
				
			}
			
		});
		
		
		FileChooser File_Path = new FileChooser();
		
		Open.setOnAction(e->{
		
			Canvas4Open Canvas = new Canvas4Open();
			
			try {
				
				String wstr = Width_Input.getText();
				String hstr = Height_Input.getText();
				
				int w = Integer.parseInt(wstr);
				int h = Integer.parseInt(hstr);
				
				Canvas.width = w; 
				Canvas.height = h;
				
				File filename = File_Path.showOpenDialog(Current_Stage);
				
                if (filename != null) {
                
                	try {
                		
                		Canvas.File_Path = filename.toURI().toURL();     		
                    
                	} catch(IOException IOe) {
                		
                	}
				
                	Canvas.start(new Stage());
                
                	Current_Stage.hide(); 
                
                }

			} catch (Exception ex) {
				
				ex.printStackTrace();
			
			}
		
		});
		
		Current_Stage.setScene(New_Scene);
		Current_Stage.show();
	
	}

}