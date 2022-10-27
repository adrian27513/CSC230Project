/**
  @file menu.h
  @author Adrian Chan (amchan)
  Header file and declares the public implementation of menu.c
*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

/**
  MenuItemStruct to store MenuItem information
*/
struct MenuItemStruct{
  char id[5];
  char category[16];
  char name[21];
  int cost;
};

/** Typedef for MenuItemStruct */
typedef struct MenuItemStruct MenuItem;

/**
  MenuStruct to store Menu information
*/
struct MenuStruct{
  MenuItem **list;
  int count;
  int capacity;
};

/** Typedef for MenuStruct */
typedef struct MenuStruct Menu;

/**
  Creates a menu and allocates spacec for an array of MenuItems
  @return menu created
*/
Menu *makeMenu();

/**
  Free all associated allocated heap memory for a give menu
  @param menu menu to free memory
*/
void freeMenu(Menu *menu);

/**
  Reads in MenuItems into a Menu from a file
  @param filename file to read in from
  @param menu Menu to add MenuItems to
*/
void readMenuItems(char const *filename, Menu *menu);

/**
  Lists and sorts MenuItems from a give Menu
  @param menu Menu to list MenuItems from
  @param compare comparator used to store MenuItems
  @param test test to filter MenuItems based on category
  @param str category string to filter by
*/
void listMenuItems( Menu *menu, int (*compare)( void const *va, void const *vb ), bool (*test)( MenuItem const *item, char const *str ), char const *str );
