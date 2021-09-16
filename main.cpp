#include "gwindow.h"
#include "ginteractors.h"
#include "gevents.h"
#include "gtimer.h"
#include "vector.h"
#include <string>
#include <sstream>
#include "Tests.hpp"
#include "MoviePlayer.h"

// Plays the movie
void playMovie()
{
	// Graphic elements for display
	GLabel *southMenuLabel;
	GLabel *northMenuLabel;
	Vector<GLabel*> screen;

	unsigned msDelay = 60;
	std::string aniFile;
	std::cout << "Input file: ";
	std::cin >> aniFile;
	std::cout << "MS delay between frames: ";
	std::cin >> msDelay;

	GWindow win(800, 600);
	win.setExitOnClose(true);
	win.requestFocus(); // Give window focus so it gets key events without needing to click on it for focus
	GTimer timer(msDelay);

	// Setup the bottom menu
	southMenuLabel = new GLabel("f->forward  b->backward  p->pause  d->delete  c->copy  x->exit");
	southMenuLabel->setFont("CourierNew-12");
	win.addToRegion(southMenuLabel, "SOUTH");

	// Setup the top status
	northMenuLabel = new GLabel("Loading tape...");
    northMenuLabel->setFont("CourierNew-12");
    win.add(northMenuLabel, 250, 10);
	
	// Load the movie
	MoviePlayer player(aniFile);
	player.rewind();

	// Create the "screen" to display the movie on
	for (unsigned int i = 0; i < player.getFrameSize(); i++)
	{
		screen.push_back(new GLabel(""));
		screen[i]->setFont("CourierNew-18");
		win.add(screen[i], 25, 150 + (i * 18));
	}
    
    char state = 'p'; // The movie player's state
	timer.start();
	while (1)
	{
		GEvent e = waitForEvent();
		// Check for key event
		if (e.getEventType() == KEY_PRESSED)
		{
			GKeyEvent ke(e);
			// Get key code
			if (ke.getKeyCode() == ESCAPE_KEY || ke.getKeyChar() == 'x')
			{
				break;
			}
			if (ke.getKeyChar() == 'f')
			{
				// Move forward
				state = 'f';
			}
            if (ke.getKeyChar() == 'b')
            {
				// Move backward
                state = 'b';
            }
            if (ke.getKeyChar() == 'd')
            {
				// Delete current frame
                state = 'd';
            }
            if (ke.getKeyChar() == 'c')
            {
				// Copy current frame
                state = 'c';
            }
            if (ke.getKeyChar() == 'p')
            {
				// Pause film
                state = 'p';
            }
		}
		else if (e.getEventType() == TIMER_TICKED)
		{
			// Timer fired...
			std::stringstream ss;
			// Displaying the current frame on the screen...
			player.getCurrFrame(screen);
            switch (state) {
                case 'f':
                    player.goFwrd();
					ss << "Playing forward, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
					northMenuLabel->setLabel(ss.str());
                    break;
                case 'b':
                    player.goBack();
					ss << "Playing backward, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
					northMenuLabel->setLabel(ss.str());
                    break;
                case 'c':
                    player.copyCurrFrame();
                    state = 'p';
                    northMenuLabel->setLabel("Copied current frame...");
                    break;
                case 'd':
                    player.delCurrFrame();
                    state = 'p';
                    northMenuLabel->setLabel("Deleted current frame...");
                    break;
                case 'p':
					ss << "Paused, frame # " << player.getCurrFrameNum() << " of " << player.getNumFrames();
                    northMenuLabel->setLabel(ss.str());
                    break;
                default:
                    northMenuLabel->setLabel("Unknown command, pausing...");
                    state = 'p';
                    break;
            }
		}
	}
	// Cleanup
	win.close();
}

// Runs the test cases
void runTests()
{
	TestFixtureFactory::theInstance().runTests();
	std::cout.flush();
}

// Creates the main menu
int main(int argc, char** argv) 
{
	std::cout << "Select an option..." << std::endl;
	std::cout << "1. Test ITPDoubleList" << std::endl;
	std::cout << "2. Play MOVIE" << std::endl;
	std::cout << ">";

	char choice;
	std::cin >> choice;
	if (choice == '1')
	{
		runTests();
	}
	else
	{
		playMovie();
	}


	return 0;
}
