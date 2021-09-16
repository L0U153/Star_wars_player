// ITP 365 Fall 2018 
// HW6 ¨C Doubly Linked List and Movie Player
// Name: Yuzhi Lu
// Email: yuzhilu@usc.edu 
// Platform: Windows

#pragma once

#include <string>
#include <sstream>
#include "vector.h"
#include "ginteractors.h"
#include "ITPDoubleList.hpp"

class MoviePlayer
{
public:
    // Function: Parameterized Constructor
    // Purpose: Sets member variables to input, clears list, and calls loader
    // Input: None
    // Returns: Nothing
	MoviePlayer(std::string);

    // Function: Destructor
    // Purpose: Empties the list
    // Input: None
    // Returns: Nothing
    ~MoviePlayer();
    
    // Function: goFwrd
    // Purpose: Moves the current "frame" forward by 1 frame
    // Also keeps track of how many frames have been viewed
    // Shouldn't go past the end of the movie
    // Input: None
    // Returns: Nothing
    void goFwrd();

    // Function: goBack
    // Purpose: Moves the current "frame" backward by 1 frame
    // Also keeps track of how many frames have been viewed
    // Shouldn't go past the end of the movie
    // Input: None
    // Returns: Nothing
    void goBack();
    
    // Function: rewind
    // Purpose: Moves the current "frame" to the movie's beginning again
    // Input: None
    // Returns: Nothing
    void rewind();
    
	// Function: getCurrFrame
	// Purpose: Gets the string that contains the current "frame" as stored
	// in the list "mFilm"
	// Input: None
	// Returns: String with the current "frame"
	std::string getCurrFrame();
	
	// Function: delCurrFrame
    // Purpose: Deletes the current frame, moves forward to the next one
    // Also keeps track of how many frames have been viewed
    // Input: None
    // Returns: Nothing
    void delCurrFrame();

    // Function: copyCurrFrame
    // Purpose: Copies current frame and places the copy BEFORE the current frame
    // Also keeps track of how many frames have been viewed
    // Input: None
    // Returns: Nothing
    void copyCurrFrame();
	
    // Function: getCurrFrameNum
    // Purpose: Gets the "index" that corresponds to the current frame
    // Input: None
    // Returns: Number of frames that have been viewed
    unsigned int getCurrFrameNum() const;
    
    // Function: getNumFrames
    // Purpose: Gets the total number of frames in the movie
    // Input: None
    // Returns: The overall number of frames in the movie
    unsigned int getNumFrames() const;
    
    // Function: getFrameSize
    // Purpose: Gives the number of lines in a frame
    // For how big the "screen" for the film should be
    // Input: None
    // Returns: The value stored in FRAMESIZE
    unsigned int getFrameSize() const;

    // Function: getCurrFrame
    // Purpose: Retrieves the current "frame" from the film list
    // Modifies the inputted vector of GLabels to contain the current frame
    // Input: A vector of "GLabels" that are the "screen" -- passed by reference
    // Returns: Nothing
    void getCurrFrame(Vector<GLabel*>&);

private:
    // Function: load_tape
    // Purpose: Uses mFilmName (set by constructor) to fill
    // mFilm with strings that make up the movie to display
    // Input: None
    // Returns: Nothing
    void loadTape();
    
    // Holds the current frame the film is on
    unsigned currFrameNum;
    
    // Stores the name of the input file
    // that has the ASCII film in it
    std::string mFilmName;
    
    // The film is made a series of strings
    // each string is 1 frame to be displayed
    // by the main function
    ITPDoubleList<std::string> mFilm;
    
    // Stores the current position of the reader
    ITPDoubleList<std::string>::Iterator pos;
    
    // DON'T CHANGE THIS!
    const unsigned FRAMESIZE = 13;
};

