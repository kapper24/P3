// Rehabilitation_Robot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED

#include "CrustCrawlerDynamics.h"
#include "CrustCrawlerKinematics.h"
#include "RehabilitationGame.h"
#include "MyoController.h"
#include "Rehabilitation_GUI.h"

#include <myo/myo.hpp>


int main()
{	
		// First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
		// publishing your application. The Hub provides access to one or more Myos.
		myo::Hub hub("com.example.hello-myo");
		std::cout << "Attempting to find a Msyo..." << std::endl;
		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* themyo = hub.waitForMyo(10000);
		// If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!themyo) {
			throw std::runtime_error("Unable to find a Myo!");
		}
		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;
		themyo->unlock(myo::Myo::unlockHold);
		// Next we enable EMG streaming on the found Myo.
		themyo->setStreamEmg(myo::Myo::streamEmgEnabled);

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		MyoController collector;
		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(&collector);

		

		 SDL_SetMainReady();

		Rehabilitation_GUI GUI;
		GUI.Update(hub, collector);
    return 0;
}

