/**
  @file menu.c
  @author Adrian Chan (amchan)
  This program creates, free, and lists menus.
*/
#include "menu.h"

Menu *makeMenu()
{
  Menu *menu = malloc(sizeof(Menu));
  menu->list = malloc(5 * sizeof(MenuItem*));
  menu->capacity = 5;
  menu->count = 0;
  
  return menu;
}

void freeMenu(Menu *menu)
{
  for (int i = 0; i < menu->count; i++) {
    free(menu->list[i]);
  }
  free(menu->list);
  free(menu);
}

void readMenuItems(char const *filename, Menu *menu)
{
  FILE *input = fopen(filename, "r");
  if (!input) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(1);
  }
  int index = menu->count;
    
  int cost;
  MenuItem *item = malloc(sizeof(MenuItem));
  int found;
  while ((found = fscanf(input, "%4s%15s%d%*[ ]%20[^\n]", item->id, item->category, &cost, item->name)) == 4) {
    if (menu->count == menu->capacity) {
      menu->capacity = 2*(menu->count);
      menu->list = realloc(menu->list, (menu->capacity) * sizeof(MenuItem*));
    }
    if (cost < 0) {
      fprintf(stderr, "Invalid menu file: %s\n", filename);
      exit(1);
    }
    
    for (int i = 0; i < index; i++) {
      if (strcmp(menu->list[i]->id, item->id) == 0) {
        fprintf(stderr, "Invalid menu file: %s\n", filename);
        exit(1);
      }    
    }
    
    if (strlen(item->id) < 4) {
      fprintf(stderr, "Invalid menu file: %s\n", filename);
      exit(1);
    }
    item->cost = cost;
    
    (menu->list)[index++] = item;
    menu->count++;
    item = malloc(sizeof(MenuItem));
  }
  
  if (found != -1) {
    fprintf(stderr, "Invalid menu file: %s\n", filename);
    exit(1);
  }
  free(item);
  fclose(input);
}

void listMenuItems( Menu *menu, int (*compare)( void const *va, void const *vb ), bool (*test)( MenuItem const *item, char const *str ), char const *str )
{
  qsort(menu->list, menu->count, sizeof(menu->list[0]), compare);
  printf("%-4s %-20s %-15s %-s\n", "ID", "Name", "Category", "Cost");
  for (int i = 0; i < menu->count; i++) {
    if (test(menu->list[i], str)) {
      printf("%-4s %-20s %-15s $%3d.%02d\n", menu->list[i]->id, menu->list[i]->name, menu->list[i]->category, (menu->list[i]->cost / 100), (menu->list[i]->cost % 100));
    }
  }
}
