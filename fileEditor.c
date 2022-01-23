#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
	printf("..######........########.##.....##.########.......########.########..####.########..#######..########.\n");
	printf(".##....##..........##.....##...##.....##..........##.......##.....##..##.....##....##.....##.##.....##\n");
	printf(".##................##......##.##......##..........##.......##.....##..##.....##....##.....##.##.....##\n");
	printf(".##................##.......###.......##..........######...##.....##..##.....##....##.....##.########.\n");
	printf(".##................##......##.##......##..........##.......##.....##..##.....##....##.....##.##...##..\n");
	printf(".##....##..........##.....##...##.....##..........##.......##.....##..##.....##....##.....##.##....##.\n");
	printf("..######...........##....##.....##....##..........########.########..####....##.....#######..##.....##\n");
	printf("Welcome to the C editor. Type help to open the command menu\n");

	// Declaration of input of file and directory storage

	char directory[256];
	char file[128];
	char directoryAndFile[385];

	// Declaration of true/false values that are used later in methods

	int editMode = 0;
	int fixed = 0;

	// Location combiner method for file name and directory, as these are taken separately

	void getLocation() {
		strcpy(directoryAndFile, directory);
		strcat(directoryAndFile, "/");
		strcat(directoryAndFile, file);
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
		       	scanf("%s", file);
			printf("Please type the full directory that you want to open:\n");
			scanf("%s", directory); /* Take file input information again */
			getLocation(); /* Combine it to get full location */
			validLocation(); /* Check if it is a valid location that breaks the loop*/
		}
	}	

	// Main loop. Loop that continuously takes instructions from the user

	while (1) {
		char command[20];	

		scanf("%s", command); /* command input */

		// Check if the entered string is a command, if not let the user know it is wrong

		if (strcmp(command, "help") != 0 && strcmp(command, "dir") != 0 && strcmp(command, "file") != 0 && strcmp(command, "exit") != 0 && strcmp(command, "delete") != 0 && strcmp(command, "read") != 0 && strcmp(command, "write") != 0 && strcmp(command, "copy") != 0 && strcmp(command, "create") != 0 && strcmp(command, "line") != 0) {
			printf("Unknown command. Type <help> for commands.\n");
		}

		// Help command that prints existing commands

		if (strcmp(command, "help") == 0) {
			printf("=============FILE SELECTION=============\n");
			printf("Change directory:\n");
			printf("dir\n");
			printf("Change file:\n");
			printf("file <file name>\n");
			printf("=============FILE EDITING=============\n");
			printf("Delete selected file:\n");
			printf("delete\n");
			printf("Read selected file:\n");
			printf("read\n");
			printf("Enable write mode:\n");
			printf("write\n");
			printf("Copy selected file:\n");
			
printf("copy\n");
			printf("Create file:\n");
			printf("create\n");
			printf("Number of lines in file:\n");
			printf("line\n");
			}

		// The exit command

		if (strcmp(command, "exit") == 0) {
			exit(0);
		}

		// The file create command

		if (strcmp(command, "create") == 0) {
			int newLocation = 0;
			char createDirectory[256];
			char createFile[128];
			char createDirectoryAndFile[385];

			// Similar to validLocation and forceFixLocation, designed for the new input within the method for the target location instead

			while (newLocation == 0) {
				printf("Please enter the name of the new file:\n");
				scanf("%s", createFile);
				printf("Please enter the directory of the new file:\n");
				scanf("%s", createDirectory);
				strcpy(createDirectoryAndFile, createDirectory);
				strcat(createDirectoryAndFile, "/");
				strcat(createDirectoryAndFile, createFile);
			
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

			// File writer

			FILE *fp; /* file pointer declaration */
			fp = fopen (createDirectoryAndFile, "w"); /* writing file depending on input */
			fclose(fp);
			printf("%s has been written successfully.\n", createDirectoryAndFile);
		}

		// File read method

		if (strcmp(command, "read") == 0) {
			forceFixLocation(); /* required correct file input */
			FILE *fp; /* file pointer declaration */
			char c; /* character declaration to read from file */
   			fp = fopen (directoryAndFile, "r");
			while(!feof(fp)) {
				c = fgetc(fp); /* get character from file */
				printf("%c", c); /* print that character until end of file */
			}
			fclose(fp);
		}

		// File line counting method

		if (strcmp(command, "line") == 0) {
			forceFixLocation(); /* required correct file input */
			unsigned int lineCounter = 0; /* line counter variable declaration */
			char c; /* character declaration to read from file */
			FILE *fp; /* file pointer declaration */
			fp = fopen(directoryAndFile, "r"); 
			while(!feof(fp)) {
				c = fgetc(fp); /* get character from file */
				if (c == '\n') { /* check if character is a new line, and +1 counter if so */
					lineCounter++;
				}
			}
			printf("There are %u lines in the path %s. \n", lineCounter, directoryAndFile);
		}
		
		// File name input command

		if (strcmp(command, "file") == 0) {
			printf("Please type the full name of file that you want to edit:\n");
		       	scanf("%s", file);
			getLocation();
			validLocation();

		// Directory input command

		}
		if (strcmp(command, "dir") == 0) {
			printf("Please type the full directory that you want to open:\n");
			scanf("%s", directory);
			getLocation();
			validLocation();
		}
		if (strcmp(command, "edit") == 0) {
		editMode = 1;
		}

		// File delete command

		if (strcmp(command, "delete") == 0) {
			forceFixLocation(); /* required correct file input */
			if (remove(directoryAndFile) == 0) {
				printf("File has been deleted successfully.\n");
			} else {
				printf("Error. File could not be deleted. \n");
			}
		}


	}
}

