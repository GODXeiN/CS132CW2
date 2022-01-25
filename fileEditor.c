#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

	// Log to record that program was opened

	FILE *log;
	log = fopen("log.txt", "a");
	fputs("Program initialised \n", log);
	fclose(log);

	printf("..######...........########.########..####.########..#######..########..\n");
	printf(".##....##..........##.......##.....##..##.....##....##.....##.##.....##.\n");
	printf(".##................##.......##.....##..##.....##....##.....##.##.....##.\n");
	printf(".##................######...##.....##..##.....##....##.....##.########..\n");
	printf(".##................##.......##.....##..##.....##....##.....##.##...##...\n");
	printf(".##....##..........##.......##.....##..##.....##....##.....##.##....##..\n");
	printf("..######...........########.########..####....##.....#######..##.....##.\n");
	printf("\n");
	printf("Welcome to the C editor. Type help to open the command menu\n");

	// Declaration of input of file and directory storage

	char directory[256];
	char file[128];
	char directoryAndFile[385];
	char lineCopy[512];

	// Declaration of true/false values that are used later in methods

	int editMode = 0;
	int fixed = 0;

	// Location combiner method for file name and directory, as these are taken separately

	void getLocation() {
		strcpy(directoryAndFile, directory);
		strcat(directoryAndFile, "/");
		strcat(directoryAndFile, file);
	}

	// Method used in commands that require a specific line selected. Writes it to log.txt.

	void selectedLineLog(unsigned int i) {
		char selectedLineNumber[10];
		FILE *log;
		log = fopen("log.txt", "a");
		sprintf(selectedLineNumber, "%u", i);
		fputs("Line ", log);
		fputs(selectedLineNumber, log);
		fputs(" was selected. \n", log);
		fclose(log);
	}

	// Standard log message that is used for all commands. Takes input a string which is specifically the command itself.

	void standardLogMessage(char o[]) {
		FILE *log;
		log = fopen("log.txt", "a");
		fputs("The operation ", log);
		fputs(o, log);
		fputs(" was commenced in the path ", log);
		fputs(directoryAndFile, log);
		fputs(". \n", log);
		fclose(log);
	}

	// Counts the amount of lines in the file before a command.

	void lineLogBefore() {
		unsigned int lineCounter = 0; 
		char c; 
		char lineNumber[10];
		FILE *fp; 
		FILE *log;
		log = fopen("log.txt", "a"); 
		fp = fopen(directoryAndFile, "r"); 
		while((c = fgetc(fp)) != EOF) {
			if (c == '\n') { /* check if character is a new line, and +1 counter if so */
				lineCounter++;	
			}
		}
		fclose(fp);
		sprintf(lineNumber, "%u", lineCounter);
		fputs("Before operation, there are ", log);
		fputs(lineNumber, log);
		fputs(" lines in the path ", log);
		fputs(directoryAndFile, log);
		fputs(". \n", log);
		fclose(log);
	}

	// Counts the amount of lines in the file after a command.

	void lineLogAfter() {
		unsigned int lineCounter = 0; 
		char c; 
		char lineNumber[10];
		FILE *fp; 
		FILE *log;
		log = fopen("log.txt", "a");
		fp = fopen(directoryAndFile, "r"); 
		while((c = fgetc(fp)) != EOF) {
			if (c == '\n') { /* check if character is a new line, and +1 counter if so */
				lineCounter++;
			}
		}
		fclose(fp);
		sprintf(lineNumber, "%u", lineCounter);
		fputs("After operation, there are ", log);
		fputs(lineNumber, log);
		fputs(" lines in the path ", log);
		fputs(directoryAndFile, log);
		fputs(". \n", log);
		fputs("================================================================================ \n", log); /* Line seperator to make log easier to read */
		fclose(log);
	}
	

	// Checks if the given location is valid.

	void validLocation() {
			DIR* tempDirectoryAndFile = opendir(directoryAndFile);
			DIR* tempDirectory = opendir(directory);
			if (tempDirectoryAndFile) {
				printf("The path %s has been selected successfully.\n", directoryAndFile); /* Check if path depending on current inputs WITHOUT file input exists */
				fixed = 0; /* Value used to repeat loop */
				closedir(tempDirectoryAndFile);
			} else if (ENOENT == errno) {
				printf("The path %s does not exist.\n", directoryAndFile); /* Check if error because it does not exist */
				fixed = 0; /* Value used to repeat loop */
			} else if (ENOTDIR == errno && tempDirectory) {
				printf("The path %s has been selected successfully. \n", directoryAndFile); /* Check if path depending on current inputs exists and would be a valid directory without the existence of file */
				fixed = 1; /* Value used to break loop */
			} else {
				printf("The path %s could not be opened.\n", directoryAndFile); /* Other errors */
				fixed = 0; /* Value used to repeat loop */
			}
	}

	// Method used that forces the user to fix location if a file input is required and is wrong

	void forceFixLocation() {
		while (fixed == 0) {
			printf("Bad file location detected. You will be be required to enter a valid location to proceed with the request.\n");
			printf("Please type the full name of file that you want to edit:\n");
			scanf("%127s", file);
			printf("Please type the parent directory that you want to open:\n");
			scanf("%255s", directory); /* Take file input information again */
			getLocation(); /* Combine it to get full location */
			validLocation(); /* Check if it is a valid location that breaks the loop*/
		}
	}	

	// Main loop. Loop that continuously takes instructions from the user

	while (1) {
		char command[20];	

		scanf("%19s", command); /* command input */

		// Check if the entered string is a command, if not let the user know it is wrong

		if (strcmp(command, "help") != 0 && strcmp(command, "dirf") != 0 && strcmp(command, "namef") != 0 && strcmp(command, "copyl") != 0 && strcmp(command, "pastel") != 0 && strcmp(command, "log") != 0 && strcmp(command, "exit") != 0 && strcmp(command, "deletef") != 0 && strcmp(command, "readf") != 0 && strcmp(command, "copyf") != 0 && strcmp(command, "createf") != 0 && strcmp(command, "linef") != 0 && strcmp(command, "deletel") != 0 && strcmp(command, "showl") != 0 && strcmp(command, "insertl") != 0 && strcmp(command, "appendl") != 0) {
			printf("Unknown command. Type <help> for a list of commands.\n");
		}

		// Help command that prints existing commands

		if (strcmp(command, "help") == 0) {
			printf("=============FILE SELECTION=============\n");
			printf("Change parent directory:\n");
			printf("dirf\n");
			printf("Change file:\n");
			printf("namef\n");
			printf("=============FILE MANAGEMENT=============\n");
			printf("Delete selected file:\n");
			printf("deletef\n");
			printf("Read selected file:\n");
			printf("readf\n");
			printf("Copy selected file:\n");
			printf("copyf\n");
			printf("Create file:\n");
			printf("createf\n");
			printf("=============LINE MANAGEMENT=============\n");
			printf("Number of lines in file:\n");
			printf("linef\n");
			printf("Append a line:\n");
			printf("appendl\n");
			printf("Insert a line:\n");
			printf("insertl\n");
			printf("Show a line:\n");
			printf("showl\n");
			printf("Delete a line:\n");
			printf("deletel\n");
			printf("=============OTHER=============\n");
			printf("Exit the program:\n");
			printf("exit\n");
			printf("View writing log:\n");
			printf("log\n");
			}


/* =============FILE SELECTION============= COMMAND DECLARATIONS */

		// File name input command

		if (strcmp(command, "namef") == 0) {
			printf("Please type the full name of file that you want to edit:\n");
		       	scanf("%127s", file);
			getLocation();
			validLocation();

		// Directory input command

		}
		if (strcmp(command, "dirf") == 0) {
			printf("Please type the parent directory that you want to open:\n");
			scanf("%255s", directory);
			getLocation();
			validLocation();
		}

/* =============FILE MANAGEMENT============= COMMAND DECLARATIONS */	

		// File delete command

		if (strcmp(command, "deletef") == 0) {
			forceFixLocation(); /* required correct file input */
			if (remove(directoryAndFile) == 0) {
				printf("File has been deleted successfully.\n");
			} else {
				printf("Error. File could not be deleted. \n");
			}
			standardLogMessage("deletef"); /* write it to log */
		}

		// File read command

		if (strcmp(command, "readf") == 0) {
			forceFixLocation(); /* required correct file input */
			FILE *fp; 
			char c; 
   			fp = fopen (directoryAndFile, "r");
			
			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			while((c = fgetc(fp)) != EOF) {
				printf("%c", c); /* print characters found in file until end of file */
			}
			printf("\n");
			fclose(fp);
		}

		// File copy command

		if (strcmp(command, "copyf") == 0) {
			forceFixLocation();
			int newLocation = 0;
			char c;
			char copyDirectory[256];
			char copyDirectoryAndFile[385];

			// Similar to validLocation and forceFixLocation, forced correct input is required for the target copy directory.

			while (newLocation == 0) {
				printf("Please enter the parent directory of the new file:\n");
				scanf("%127s", copyDirectory);

				// Combine input directory and file name for writing

				strcpy(copyDirectoryAndFile, copyDirectory);
				strcat(copyDirectoryAndFile, "/");
				strcat(copyDirectoryAndFile, file);

				// Check if the directory exists

				DIR* createTempDirectoryAndFile = opendir(copyDirectoryAndFile);
				DIR* createTempDirectory = opendir(copyDirectory);
			
				if (createTempDirectory) {
					printf("The path %s has been selected successfully.\n", copyDirectory);
					closedir(createTempDirectory);
					newLocation = 1;
				} else if (ENOENT == errno) {
					printf("The path %s does not exist.\n", copyDirectoryAndFile);
				} else {
					printf("The path %s could not be opened.\n", copyDirectory);
				}

				FILE *fp;
				FILE *copy;

				fp = fopen(directoryAndFile, "r");
				copy = fopen(copyDirectoryAndFile, "w");

				// Check if file opened correctly

				if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
				}
			
				while((c = fgetc(fp)) != EOF) {
					fputc(c, copy); /* write characters found in file until end of file */
				}
				fclose(fp);
				fclose(copy);
			}
		}

		// The file create command

		if (strcmp(command, "createf") == 0) {
			int newLocation = 0;
			char createDirectory[256];
			char createFile[128];
			char createDirectoryAndFile[385];

			// Similar to validLocation and forceFixLocation, designed for the new input within the method for the target location instead

			while (newLocation == 0) {
				printf("Please enter the name of the new file:\n");
				scanf("%255s", createFile);
				printf("Please enter the parent directory of the new file:\n");
				scanf("%127s", createDirectory);

				// Combine input directory and input file name for writing

				strcpy(createDirectoryAndFile, createDirectory);
				strcat(createDirectoryAndFile, "/");
				strcat(createDirectoryAndFile, createFile);

				// Check if the input directory exist
			
				DIR* createTempDirectoryAndFile = opendir(createDirectoryAndFile);
				DIR* createTempDirectory = opendir(createDirectory);
				if (createTempDirectory) {
					printf("The path %s has been selected successfully.\n", createDirectory);
					closedir(createTempDirectory);
					newLocation = 1;
				} else if (ENOENT == errno) {
					printf("The path %s does not exist.\n", createDirectoryAndFile);
				} else {
					printf("The path %s could not be opened.\n", createDirectory);
				}
			}

			// Log specialised for this particular operation

			FILE *log;
			log = fopen("log.txt", "a");
			fputs("The operation ", log);
			fputs("createf", log);
			fputs(" was commenced in the path ", log);
			fputs(createDirectoryAndFile, log);
			fputs(". \n", log);
			fputs("Time: \n", log);
			fclose(log);

			// File writer

			FILE *fp; 
			fp = fopen (createDirectoryAndFile, "w"); 
			fclose(fp);
			printf("%s has been written successfully.\n", createDirectoryAndFile);
		}


/* =============LINE MANAGEMENT============= COMMAND DECLARATIONS */

		// File line counting comamnd

		if (strcmp(command, "linef") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineCounter = 0; 
			char c; 
			FILE *fp; 
			fp = fopen(directoryAndFile, "r"); 

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			while((c = fgetc(fp)) != EOF) {
				if (c == '\n') { /* check if character is a new line, and +1 counter if so */
					lineCounter++;
				}
			}
			printf("There are %u lines in the path %s. \n", lineCounter, directoryAndFile);
		}

		// File line appending command
		
		if (strcmp(command, "appendl") == 0) {
			forceFixLocation(); /* required correct file input */
			lineLogBefore();
			char insertLine[512];
			FILE *fp;
			fp = fopen(directoryAndFile, "a"); 

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			printf("Please type the line text that you wish to insert:\n");
			scanf(" %519[^\n]s", insertLine);
			printf("The line %s was appended successfully in the path %s.", insertLine, directoryAndFile);

			standardLogMessage("appendl"); /* write it to log */

			strcat(insertLine, "\n");
			fputs(insertLine, fp);
			fclose(fp);

			lineLogAfter();
		}

		// File line inserting command

		if (strcmp(command, "insertl") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineNumber;
			unsigned int lineCounter = 1;
			char tempDirectoryAndFile[262];
			char insertLine[512];
			char c;
			lineLogBefore();

			printf("Please enter the line number that you wish to insert to:\n");
			scanf("%u", &lineNumber);
			selectedLineLog(lineNumber);
			printf("Please the line text that you wish to insert: \n");
			scanf(" %519[^\n]s", insertLine);
			printf("The line %s was inserted successfully in the path %s.", insertLine, directoryAndFile);

			standardLogMessage("insertl"); /* write it to log */

			// Combine inpput directory and input file for writing

			strcpy(tempDirectoryAndFile, directory);
			strcat(tempDirectoryAndFile, "/");
			strcat(tempDirectoryAndFile, ".temp");

			strcat(insertLine, "\n");

			FILE *fp;
			FILE *temp;
			fp = fopen(directoryAndFile, "r");

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			temp = fopen(".temp", "w");
			temp = fopen(tempDirectoryAndFile, "w");
			
			while((c = fgetc(fp)) != EOF) {
				if (c == '\n') {
					lineCounter++;
				}
				if (lineCounter != lineNumber) {
					fputc(c, temp);
				}
				else {
					fputs("\n", temp);
					fputs(insertLine, temp);
					lineCounter++;
				}
			}

			fclose(fp);
			remove(directoryAndFile);
			fclose(temp);
			rename(tempDirectoryAndFile, directoryAndFile);

			lineLogAfter();
		}

		// File line showing command

		if (strcmp(command, "showl") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineNumber;
			unsigned int lineCounter = 1;
			char c;
			FILE *fp;
			fp = fopen(directoryAndFile, "r");

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			printf("Please enter the line number that you wish to view:\n");
			scanf("%u", &lineNumber);

			while((c = fgetc(fp)) != EOF) {
				if (c == '\n') {
					lineCounter++;
				}

				if (lineCounter == lineNumber) {
					printf("%c", c); /* print that character until end of file */
				}
			}
			printf("\n");
		}

		// File line deleting command

		if (strcmp(command, "deletel") == 0) {
			forceFixLocation(); /* required correct file input */

			lineLogBefore();

			standardLogMessage("deletel"); /* write it to log */
			unsigned int lineNumber;
			unsigned int lineCounter = 1;
			char tempDirectoryAndFile[262];
			char c;

			printf("Please enter the line number that you wish to delete:\n");
			scanf("%u", &lineNumber);
			selectedLineLog(lineNumber);

			// Combine inpput directory and input file for writing

			strcpy(tempDirectoryAndFile, directory);
			strcat(tempDirectoryAndFile, "/");
			strcat(tempDirectoryAndFile, ".temp");

			FILE *fp;
			FILE *temp;
			fp = fopen(directoryAndFile, "r");

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}
			
			temp = fopen(tempDirectoryAndFile, "w");

			while((c = fgetc(fp)) != EOF) {
				if (c == '\n') {
					lineCounter++;
				}
				if (lineCounter != lineNumber) {
					fputc(c, temp);
				}
			}
			printf("The line %u was deleted successfully in the path %s.", lineNumber, directoryAndFile);
			fclose(fp);
			remove(directoryAndFile);
			fclose(temp);
			rename(tempDirectoryAndFile, directoryAndFile);

			lineLogAfter();
		}

		if (strcmp(command, "copyl") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineCounter = 0;
			unsigned int lineNumber;

			printf("Please enter the line number that you wish to copy:\n");
			scanf("%u", &lineNumber);

			FILE *fp;
			fp = fopen(directoryAndFile, "r");

			while(fgets(lineCopy, 511, fp) != NULL) {
				if (lineCounter == lineNumber) {
					fclose(fp);
					break;
				} else {
					lineCounter++;
				}

			}
			printf("The line %s was copied successfully in the path %s", lineCopy, directoryAndFile);
			fclose(fp);
		}

		if (strcmp(command, "pastel") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineNumber;
			unsigned int lineCounter = 1;
			char tempDirectoryAndFile[262];
			char c;

			printf("Please enter the line number that you wish to pasted:\n");
			scanf("%u", &lineNumber);

			selectedLineLog(lineNumber);
			lineLogBefore();

			FILE *fp;
			FILE *temp;
			fp = fopen(directoryAndFile, "r");

			// Combine inpput directory and input file for writing

			strcpy(tempDirectoryAndFile, directory);
			strcat(tempDirectoryAndFile, "/");
			strcat(tempDirectoryAndFile, ".temp");

			// Check if file opened correctly

			if (fp == NULL) {
    			perror("Failed to open file: ");
    			return 1;
			}

			temp = fopen(".temp", "w");
			temp = fopen(tempDirectoryAndFile, "w");
			
			while((c = fgetc(fp)) != EOF) {
				if (c == '\n') {
					lineCounter++;
				}
				if (lineCounter != lineNumber) {
					fputc(c, temp);
				}
				else {
					fputs("\n", temp);
					fputs(lineCopy, temp);
					lineCounter++;
				}
			}
			printf("The line %s was pasted successfully in the path %s.", lineCopy, directoryAndFile);

			standardLogMessage("pastel");

			fclose(fp);
			remove(directoryAndFile);
			fclose(temp);
			rename(tempDirectoryAndFile, directoryAndFile);

			lineLogAfter();
		}

/* =============OTHER============= COMMAND DECLARATIONS */

		// The exit command

		if (strcmp(command, "exit") == 0) {
			exit(0);
			FILE *log;
		log = fopen("log.txt", "a");
		fputs("Program closed using exit \n", log);
		fclose(log);
		}

		// Read log command

		if (strcmp(command, "log") == 0) {
			FILE *fp; 
			char c;
   			fp = fopen ("log.txt", "r");
			while((c = fgetc(fp)) != EOF) {
				printf("%c", c); 
			}
			printf("\n");
			fclose(fp);
		}
	}
}