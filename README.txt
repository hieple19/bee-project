* which user types is your UI focused on
General users, kids, and hobbyists. BusyBee can be used for educational purposes. And can be used for research if provided with more accurate behavior description and models.

* what use cases does it support
	-BusyBee allows users to generate multiple experiments.
	-BusyBee is flexible and intuitive to use.
	-BusyBee provides modular UI which lets user switch between model generation and visualization.
	-BusyBee orginizes and plots bee count variation in a modern and easy-to-interpret graphs.
	-BusyBee allows the visualization of multiples hives within the same simulation.


INSTRUCTIONS:
	- Run BusyBee.pro to open Qt
	- Build BusyBee project
	- Move images folder in GUI/BusyBeeGui to the build folder inside the same location
	- Make sure to set Qt Run Folder to: 
		BUILD_FOLDER\GUI\BusyBeeGUI
		
		Path to build folder depends on the machine
	- Run BusyBeeGui subproject to run program
	
- For Linux/Mac Users, include 

		LIBS += -l sqlite3
		LIBS += -pthread
		LIBS += -ldl

		QMAKE_CXXFLAGS += -std=gnu++0x -pthread
		QMAKE_CFLAGS += -std=gnu++0x -pthread

	and comment out the following files
		sqlite3.c
		sqlite3.h
		sqlite3ext.h
		
		in DBee.pro &  BusyBeeEngine.pro & BusyBeeGui.pro

- Integration:
		1 - Run BusyBeeGui subproject.
		2 - Enter Parameters and Generate Model
		3 - Click on Visualize Model tab to see simulated data in graphs
		4 - If software is closed and restarted, previous runs and data will be
			visible in Visualize Tab
		5 - Past runs data is stored in DBee folder in Build
		6 - Engine subproject handles reading and writing data

