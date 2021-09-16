// ITP 365 Fall 2018 
// HW6 ¨C Doubly Linked List and Movie Player
// Name: Yuzhi Lu
// Email: yuzhilu@usc.edu 
// Platform: Windows

#include "MoviePlayer.h"

// Function: Parameterized Constructor
// Purpose: Sets member variables to input, clears list, and calls loader
// Input: None
// Returns: Nothing
MoviePlayer::MoviePlayer(std::string filmName)
{
	mFilmName = filmName;
	mFilm.clear();
	loadTape();
	rewind();
}

// Function: Destructor
// Purpose: Empties the list
// Input: None
// Returns: Nothing7
MoviePlayer::~MoviePlayer()
{
	mFilm.clear();
}

// Function: goFwrd
// Purpose: Moves the current "frame" forward by 1 frame
// Also keeps track of how many frames have been viewed
// Shouldn't go past the end of the movie
// Input: None
// Returns: Nothing
void MoviePlayer::goFwrd()
{
	//if the pos is not at the end
	if (pos->mNext != nullptr)
	{
		pos++;
		currFrameNum++;
	}
}

// Function: goBack
// Purpose: Moves the current "frame" backward by 1 frame
// Also keeps track of how many frames have been viewed
// Shouldn't go past the end of the movie
// Input: None
// Returns: Nothing
void MoviePlayer::goBack()
{
	//if the pos is not at the first
	if (pos->mPrev != nullptr)
	{
		pos--;
		currFrameNum--;
	}
}

// Function: rewind
// Purpose: Moves the current "frame" to the movie's beginning again
// Input: None
// Returns: Nothing
void MoviePlayer::rewind()
{
	pos = mFilm.begin();
	currFrameNum = 1;
}

// Function: getCurrFrame
// Purpose: Gets the string that contains the current "frame" as stored
// in the list "mFilm"
// Input: None
// Returns: String with the current "frame"
std::string MoviePlayer::getCurrFrame()
{
	std::string retVal = pos->mData;
	return retVal;
}

// Function: delCurrFrame
// Purpose: Deletes the current frame, moves forward to the next one
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::delCurrFrame()
{
	//if there are more than 1 frame in the movie
	if (getNumFrames() > 1)
	{
		//deleting the last frame
		if (getNumFrames() == currFrameNum)
		{
			pos--;
			mFilm.pop_back();
			currFrameNum--;
		}
		//not deleting the last frame
		else
		{
			pos = mFilm.erase(pos);
		}
	}
	//if delete the only frame left in the movie
	else if (getNumFrames() == 1)
	{
		return;
	}
}

// Function: copyCurrFrame
// Purpose: Copies current frame and places the copy BEFORE the current frame
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::copyCurrFrame()
{
	std::string copiedFrame = getCurrFrame();
	pos = mFilm.insert(pos, copiedFrame);
}

// Function: getCurrFrameNum
// Purpose: Gets the "index" that corresponds to the current frame
// Input: None
// Returns: Number of frames that have been viewed
unsigned MoviePlayer::getCurrFrameNum() const
{
	return currFrameNum;
}

// Function: getNumFrames
// Purpose: Gets the total number of frames in the movie
// Input: None
// Returns: The overall number of frames in the movie
unsigned int MoviePlayer::getNumFrames() const
{
	return mFilm.size();
}

// Function: getFrameSize
// Purpose: Gives the number of lines in a frame
// For how big the "screen" for the film should be
// Input: None
// Returns: The value stored in FRAMESIZE
unsigned int MoviePlayer::getFrameSize() const
{
	return FRAMESIZE;
}

// Function: getCurrFrame
// Purpose: Retrieves the current "frame" from the film list
// Modifies the inputted vector of GLabels to contain the current frame
// Input: A vector of "GLabels" that are the "screen" -- passed by reference
// Returns: Nothing
void MoviePlayer::getCurrFrame(Vector<GLabel*>& screen)
{
	std::string line;
	std::string fullLine = pos->mData;

	for (int i = 0; i < screen.size(); i++)
	{
		//separate each line from the frame
		unsigned index = fullLine.find("\n");

		//if is a line
		if (index != std::string::npos)
		{
			//substr line from the frame
			line = fullLine.substr(0, index);
			if (i < screen.size() - 1)
			{
				fullLine = fullLine.substr(index + 1);
			}
			//push the line into the GLabel vector
			screen[i]->setLabel(line);
		}
	}
}

// Function: loadTape
// Purpose: Uses mFilmName (set by constructor) to fill
// mFilm with strings that make up the movie to display
// Input: None
// Returns: Nothing
void MoviePlayer::loadTape()
{
	//input file
	std::ifstream input(mFilmName);
	std::string fNum;
	//if the file exist
	if (input.is_open())
	{
		//if the file doesn't end
		while (!input.eof())
		{
			//get the number of display times from the first line
			std::getline(input, fNum);
			fNum = trim(fNum);
			//if the first line is a number
			if (stringIsInteger(fNum))
			{
				//get content of frame into a string 
				std::ostringstream value;
				for (int i = 0; i < FRAMESIZE; i++)
				{
					std::string fileLine;
					std::getline(input, fileLine);
					value << fileLine << " \n";
				}
				std::string fLine = value.str();

				//push the line into the mFilm List
				for (int j = 0; j < stringToInteger(fNum); j++)
				{
					mFilm.push_back(fLine);
				}
			}
			//if the first line is not a number
			else
			{
				break;
			}
		}
	}
	//if the file doesn't exist
	else
	{
		error("Cannot find the file!");
	}
}