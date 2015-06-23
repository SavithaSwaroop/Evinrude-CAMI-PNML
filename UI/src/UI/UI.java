package UI;

import java.awt.FlowLayout;
import javax.swing.ImageIcon;
import java.io.*;
import javax.swing.JOptionPane;
import java.awt.EventQueue;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JPanel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Font;
import com.jgoodies.forms.factories.DefaultComponentFactory;


public class UI {
	
	private JFrame frame;
	private JTextField txtSelectFolder;
	private JTextField txtSelectOutputFolder;
	private JTextField txtSelectCamiFile;
	private JTextField txtOutputFileName;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UI window = new UI();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public UI() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame(" ");
		frame.getContentPane().setBackground(new Color(224, 255, 255));
		frame.setBounds(100, 100, 869, 536);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
				
		// create the status bar panel and shove it down the bottom of the frame
		JPanel statusPanel = new JPanel();
		JLabel statusLabel = new JLabel("status");
		statusPanel.add(statusLabel);
		
		txtSelectFolder = new JTextField();
		txtSelectFolder.setFont(new Font("Times New Roman", Font.PLAIN, 16));
		txtSelectFolder.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				txtSelectFolder.setText("");
			}
		});
		txtSelectFolder.setText("Select Folder");
		txtSelectFolder.setBounds(167, 196, 514, 30);
		frame.getContentPane().add(txtSelectFolder);
		txtSelectFolder.setColumns(10);
		JButton open = new JButton("Open");
		open.setFont(new Font("Times New Roman", Font.BOLD, 16));
		open.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println("Clicked Open");
				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setCurrentDirectory(new File("C:\\CFG_ALL"));
				fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				int result = fileChooser.showOpenDialog(frame);
				fileChooser.setAcceptAllFileFilterUsed(false);
				if (result == JFileChooser.APPROVE_OPTION) {
					System.out.println("getCurrentDirectory(): " + fileChooser.getCurrentDirectory());
					txtSelectFolder.setText(fileChooser.getSelectedFile().getAbsolutePath());
				     System.out.println("getSelectedFile() : " + fileChooser.getSelectedFile());
				    }
			}
		});
		open.setBounds(691, 195, 135, 30);
		frame.getContentPane().add(open);
		
		JLabel lblSource = new JLabel("Source Directory");
		lblSource.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblSource.setBounds(9, 195, 171, 31);
		frame.getContentPane().add(lblSource);
		
		JLabel lblTarget = new JLabel("Target Folder");
		lblTarget.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblTarget.setBounds(9, 237, 148, 30);
		frame.getContentPane().add(lblTarget);
		
		txtSelectOutputFolder = new JTextField();
		txtSelectOutputFolder.setFont(new Font("Times New Roman", Font.PLAIN, 16));
		txtSelectOutputFolder.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				txtSelectOutputFolder.setText("");
			}
		});
		txtSelectOutputFolder.setText("Output Folder Name");
		txtSelectOutputFolder.setColumns(10);
		txtSelectOutputFolder.setBounds(167, 238, 659, 30);
		frame.getContentPane().add(txtSelectOutputFolder);
		
		txtSelectCamiFile = new JTextField();
		txtSelectCamiFile.setFont(new Font("Times New Roman", Font.PLAIN, 16));
		txtSelectCamiFile.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				txtSelectCamiFile.setText("");
			}
		});
		txtSelectCamiFile.setText("Select Cami File");
		txtSelectCamiFile.setBounds(167, 358, 515, 30);
		frame.getContentPane().add(txtSelectCamiFile);
		txtSelectCamiFile.setColumns(10);
		
		JLabel lblSource_1 = new JLabel("Source");
		lblSource_1.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblSource_1.setBounds(9, 361, 61, 23);
		frame.getContentPane().add(lblSource_1);
		
		JLabel lblTarget_1 = new JLabel("Target Name");
		lblTarget_1.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblTarget_1.setBounds(9, 399, 110, 30);
		frame.getContentPane().add(lblTarget_1);
		
		txtOutputFileName = new JTextField();
		txtOutputFileName.setFont(new Font("Times New Roman", Font.PLAIN, 16));
		txtOutputFileName.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				txtOutputFileName.setText("");
			}
		});
		txtOutputFileName.setText("Output File Name");
		txtOutputFileName.setColumns(10);
		txtOutputFileName.setBounds(167, 400, 659, 30);
		frame.getContentPane().add(txtOutputFileName);
		
		JButton button = new JButton("Choose");
		button.setFont(new Font("Times New Roman", Font.BOLD, 16));
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.out.println("Clicked choose");
				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setCurrentDirectory(new File("C:\\Evinrude\\"));
				int result = fileChooser.showOpenDialog(frame);
				if (result == JFileChooser.APPROVE_OPTION) {
				    File selectedFile = fileChooser.getSelectedFile();
				    txtSelectCamiFile.setText(selectedFile.getAbsolutePath());
					     System.out.println("Selected file: " + selectedFile.getAbsolutePath());
				}
			}
		});
		button.setBounds(692, 357, 134, 30);
		frame.getContentPane().add(button);
		
		JButton btnCreate = new JButton("Create ");
		btnCreate.setFont(new Font("Times New Roman", Font.BOLD, 16));
		btnCreate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				 try {  // Execute command
					  String command = "cmd /c start /wait C:/savitha/evinrude/fromneethi5/Full/Converter.bat "+txtSelectCamiFile.getText()+" "+txtOutputFileName.getText();
					 // String command = "cmd /c start C:/Users/sneeth/Desktop/New.bat "; 
					 Process child = Runtime.getRuntime().exec(command);
					 child.waitFor();
				      OutputStream out = child.getOutputStream();
					  out.flush();
					  out.close();
					  System.out.println("completed");
					  JOptionPane.showMessageDialog(frame, "Completed");
					} catch (Exception ex) {
						System.out.println("execution failed");
					}
				}
		});
	
		btnCreate.setBounds(167, 459, 134, 27);
		frame.getContentPane().add(btnCreate);
		
		JButton Run_Evinrude = new JButton(" Run Evinrude");
		Run_Evinrude.setFont(new Font("Times New Roman", Font.BOLD, 16));
		Run_Evinrude.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				 try {  // Execute command
					  String command = "cmd /c start C:/savitha/evinrude/fromneethi5/Full/Evinrude.bat "+txtSelectFolder.getText()+" "+txtSelectOutputFolder.getText();
				      Process child = Runtime.getRuntime().exec(command);
					   // Get output stream to write from it
					  OutputStream out = child.getOutputStream();
					  out.flush();
					  out.close();
					  } catch (Exception ex) {}
			}
		});
		Run_Evinrude.setBounds(167, 290, 134, 30);
		frame.getContentPane().add(Run_Evinrude);
		
		JButton btnNewButton_3 = new JButton("Clear");
		btnNewButton_3.setFont(new Font("Times New Roman", Font.BOLD, 16));
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				txtSelectOutputFolder.setText("");
			}
		});
		btnNewButton_3.setBounds(311, 290, 134, 30);
		frame.getContentPane().add(btnNewButton_3);
		
		JButton btnNewButton_5 = new JButton("Cancel");
		btnNewButton_5.setFont(new Font("Times New Roman", Font.BOLD, 16));
		btnNewButton_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.exit(0);
			}
		});
		//btnNewButton_5.setBounds(454, 457, 134, 30);
		btnNewButton_5.setBounds(311, 458, 133, 29);
		frame.getContentPane().add(btnNewButton_5);
		   
		JLabel Background = new JLabel(new ImageIcon("C:\\savitha\\evinrude\\fromneethi5\\Full\\UI\\Src2Pnet1.png"));
		Background.setBounds(0, 0, 853, 176);
		frame.getContentPane().add(Background);
		Background.setLayout(new FlowLayout());
		
		
	   	}
}
