#include "vex.h"
#include "autogrid.h"
#include "auto-selector.h"

int currentAlliance = -1;
int currentPosition = -1;
bool selectionMade = false;

const int BUTTON_WIDTH = 110;
const int BUTTON_HEIGHT = 70;
const int SPACING = 20;
const int SCREEN_WIDTH = 480;
const int START_X = (SCREEN_WIDTH - (3 * BUTTON_WIDTH + 2 * SPACING)) / 2;
const int RED_Y = 80;
const int BLUE_Y = RED_Y + BUTTON_HEIGHT + SPACING;

bool isInButton(int x, int y, int btnX, int btnY, int btnWidth, int btnHeight) {
  return (x >= btnX && x <= btnX + btnWidth && y >= btnY && y <= btnY + btnHeight);
}

void displayButtons() {
  Brain.Screen.clearScreen();
  
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(propXL);
  const char* title = "Select Auton Path";
  int titleWidth = title[0] == '\0' ? 0 : Brain.Screen.getStringWidth(title);
  Brain.Screen.printAt((SCREEN_WIDTH - titleWidth) / 2, 40, title);
  
  for (int i = 0; i < 3; i++) {
    int x = START_X + i * (BUTTON_WIDTH + SPACING);
    
    if (currentAlliance == 0 && currentPosition == i) {
      Brain.Screen.setFillColor(orange);
    } else {
      Brain.Screen.setFillColor(red);
    }
    
    Brain.Screen.drawRectangle(x, RED_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.setPenColor(white);
    
    char btnText[10];
    sprintf(btnText, "Red %d", i+1);
    int textWidth = btnText[0] == '\0' ? 0 : Brain.Screen.getStringWidth(btnText);
    int textX = x + (BUTTON_WIDTH - textWidth) / 2;
    int textY = RED_Y + BUTTON_HEIGHT/2 + 8;
    Brain.Screen.printAt(textX, textY, btnText);
  }
  
  for (int i = 0; i < 3; i++) {
    int x = START_X + i * (BUTTON_WIDTH + SPACING);
    
    if (currentAlliance == 1 && currentPosition == i) {
      Brain.Screen.setFillColor(purple);
    } else {
      Brain.Screen.setFillColor(blue);
    }
    
    Brain.Screen.drawRectangle(x, BLUE_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.setPenColor(white);
    
    char btnText[10];
    sprintf(btnText, "Blue %d", i+1);
    int textWidth = btnText[0] == '\0' ? 0 : Brain.Screen.getStringWidth(btnText);
    int textX = x + (BUTTON_WIDTH - textWidth) / 2;
    int textY = BLUE_Y + BUTTON_HEIGHT/2 + 8;
    Brain.Screen.printAt(textX, textY, btnText);
  }
  
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setFont(propM);
  
  if (currentAlliance == -1 || currentPosition == -1) {
    Brain.Screen.printAt((SCREEN_WIDTH - Brain.Screen.getStringWidth("No path selected")) / 2, 
                       BLUE_Y + BUTTON_HEIGHT + 40, "No path selected");
  } else {
    char selectionText[50];
    sprintf(selectionText, "Selected Path: %s %d", 
           (currentAlliance == 0 ? "RED" : "BLUE"), currentPosition + 1);
    int selTextWidth = selectionText[0] == '\0' ? 0 : Brain.Screen.getStringWidth(selectionText);
    Brain.Screen.printAt((SCREEN_WIDTH - selTextWidth) / 2, 
                       BLUE_Y + BUTTON_HEIGHT + 40, selectionText);
  }
}

int buzzControllerTask() {
  while (!selectionMade) {
    Controller1.rumble(".");
    wait(1000, msec);
  }
  return 0;
}

void onScreenTouch() {
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();
  
  for (int i = 0; i < 3; i++) {
    int btnX = START_X + i * (BUTTON_WIDTH + SPACING);
    if (isInButton(x, y, btnX, RED_Y, BUTTON_WIDTH, BUTTON_HEIGHT)) {
      currentAlliance = 0;
      currentPosition = i;
      selectionMade = true;
      displayButtons();
      return;
    }
  }
  
  for (int i = 0; i < 3; i++) {
    int btnX = START_X + i * (BUTTON_WIDTH + SPACING);
    if (isInButton(x, y, btnX, BLUE_Y, BUTTON_WIDTH, BUTTON_HEIGHT)) {
      currentAlliance = 1;
      currentPosition = i;
      selectionMade = true;
      displayButtons();
      return;
    }
  }
}

void initAutoSelector() {
  Brain.Screen.pressed(onScreenTouch);
  
  displayButtons();
  
  vex::task buzzTask(buzzControllerTask);
}

void runSelectedAutonomous() {
  if (currentAlliance == -1 || currentPosition == -1) {
    return;
  }
  
  if (currentAlliance == 0) {
    switch (currentPosition) {
      case 0:
        setStarting(0, 0);
        moveTo(0, 1);
        break;
        
      case 1:
        setStarting(0, 0);
        lookAt(2, 0);
        break;
        
      case 2:
        setStarting(0, 0);
        lookAt(1, -1);
        break;
    }
  } 

  else {
    switch (currentPosition) {
      case 0:
        setStarting(0, -1);
        lookAt(2, 4);
        break;
        
      case 1:
        setStarting(-1, -1);
        lookAt(4, 3);
        break;
        
      case 2:
        setStarting(-1, 0);
        lookAt(6, 4);
        break;
    }
  }
}