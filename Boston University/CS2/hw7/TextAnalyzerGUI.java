package hw7;

/**
 * TextAnalyzerGUI.java
 * Boston University CAS CS 112 HW7
 * By Ian Denhardt and Leo Reyzin
 */

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.Scanner;
import javax.swing.*;

//Our main class extends JFrame, which is essentially a window.
public class TextAnalyzerGUI extends JFrame{

    private TextAnalyzer ta = null;

    public TextAnalyzerGUI() {

	// A JFrame has one top level container, which we can get at like so:
	Container contentPane = getContentPane();

	// We want to line up our top-level components inside the JFrame vertically.
	contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));

	// Create text areas in which to output errors and results.  
	// We need them now in order to create other components,
	// but will add them to the contentPane later
	JTextArea output = new JTextArea();
	JTextArea errorAndProgressMessage = new JTextArea();
			
	// JPanels allow us to group other components into one.
	// This panel contains a button that will open a file dialog when pressed,
	// and places to indicate the first and end word
	JPanel openFilePanel = new JPanel();
	// Lay it out horizontally
	openFilePanel.setLayout(new BoxLayout(openFilePanel, BoxLayout.X_AXIS));

	// create and place the button
	JButton openButton = new JButton("Click to select a file");
	openFilePanel.add(openButton);
	JLabel firstWordText = new JLabel("First word (blank for none):");
	openFilePanel.add(firstWordText);
	// The word PREFIX starts Jane Eyre  text,
	// after Project Gutenberg's initial text
	// It is important that the word PREFACE (all uppercase) doesn't appear in
	// Project Gutenberg's initial text
	JTextField firstWordInput = new JTextField("PREFACE");
	openFilePanel.add(firstWordInput);
	JLabel endWordText = new JLabel("End word (blank for none):");
	openFilePanel.add(endWordText);
	// The word END starts Project Gutenberg's end text
	// following Jane Eyre text
	// It is important that the word END (all uppercase) doesn't appear in
	// Jane Eyre text
	JTextField endWordInput = new JTextField("END");
	openFilePanel.add(endWordInput);
	openButton.addActionListener(new OpenListener(errorAndProgressMessage,
						      firstWordInput, endWordInput));
		
		
	JPanel listWordsPanel = new JPanel();
	listWordsPanel.setLayout(new BoxLayout(listWordsPanel, BoxLayout.X_AXIS));

	JLabel beforeLowText = new JLabel("List all words occuring between ");
	listWordsPanel.add(beforeLowText);
	JTextField lowInput = new JTextField();
	listWordsPanel.add(lowInput);
	JLabel betweenLowAndHighText = new JLabel(" and ");
	listWordsPanel.add(betweenLowAndHighText);
	JTextField highInput = new JTextField();
	listWordsPanel.add(highInput);
	JLabel afterHighText = new JLabel (" times ");
	listWordsPanel.add(afterHighText);
		
	JButton listWordsButton = new JButton("List");
	// We register an instance of the ListWordsListener, below, with the button.
	// when the button is pressed, the ListWordsListener's actionPerformed method will be called.
	listWordsButton.addActionListener(new ListWordsListener(lowInput, highInput, output));
	listWordsPanel.add(listWordsButton);	

	// Add everything to the main window.
	contentPane.add(openFilePanel);	
		
	errorAndProgressMessage.setEditable(false);
	// add scroll bar to the error window
	JScrollPane scroll1 = new JScrollPane(errorAndProgressMessage);
	scroll1.setPreferredSize(new Dimension(640, 160));
	contentPane.add(scroll1);
		
	contentPane.add(listWordsPanel);
		

	output.setEditable(false);
	// add scroll a bar to the output window
	JScrollPane scroll2 = new JScrollPane(output);
	scroll2.setPreferredSize(new Dimension(640, 480));
	contentPane.add(scroll2);
		


    }
	
    public static void main(String[] args) {
	TextAnalyzerGUI frame = new TextAnalyzerGUI();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setSize(800,600);
	frame.setVisible(true);
    }

    // This class is in charge of opening the file
    private class OpenListener implements ActionListener {
	private JTextArea out;
	private JTextField firstWord, endWord;

	// constructor: keeps track of where the information message (opened/failed) is to be displayed
	public OpenListener(JTextArea out, JTextField firstWord, JTextField endWord) {
	    this.out = out;
	    this.firstWord = firstWord;
	    this.endWord = endWord;
	}

	// is invoked when file is chosen; sends the file for processing or displays a failure message
	public void actionPerformed(ActionEvent e) {
	    JFileChooser chooser = new JFileChooser();
	    int option = chooser.showOpenDialog(null);

	    if(option == JFileChooser.APPROVE_OPTION) {
		try {
		    Scanner fileScanner = new Scanner(chooser.getSelectedFile());
		    out.setText("Opened file: " + chooser.getSelectedFile().getName()+"\n");
		    ta = new TextAnalyzer();
		    out.append(ta.readText(fileScanner, firstWord.getText(), endWord.getText()));
		} 
		catch (IOException exc) {
		    out.setText("Unable to open file because of the following error: \""
				+ exc.getMessage()+"\"");
		    ta = null;
		}
	    }
	}
    }

    // This class is in charge of processing requests to list words of a certain frequency 
    private class ListWordsListener implements ActionListener {
	private JTextField opA, opB;
	private JTextArea out;

	public ListWordsListener(JTextField opA, JTextField opB, JTextArea out) {
	    this.opA = opA;
	    this.opB = opB;
	    this.out = out;
	}

	public void actionPerformed(ActionEvent e) {
	    if (ta == null) {
		out.setText("Please select a file first!\n");
		return;
	    }
	    try {
		out.setText(ta.printWords(Integer.decode(opA.getText()),
					  Integer.decode(opB.getText())));
	    }
	    catch (NumberFormatException exc) {
		out.setText("Please enter two integers above!");
	    }
	}
    }
}




