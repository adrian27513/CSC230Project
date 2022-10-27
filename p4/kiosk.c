/**
  @file kiosk.c
  @author Adrian Chan (amchan)
  This program takes takes in user's commands and adds, removes, or list items.
*/
#include "menu.h"
#include "input.h"
#include <string.h>

/**
  OrderItemStruct to store OrderItem information
*/
struct OrderItemStruct {
  MenuItem *menuItem;
  int quantity;
};

/** Typedef for OrderItemStruct */
typedef struct OrderItemStruct OrderItem;

/** OrderStruct to store Order information and a list of OrderItems */
struct OrderStruct {
  OrderItem **list;
  int count;
  int capacity;
};

/** Typedef for OrderStruct */
typedef struct OrderStruct Order;

/**
  List items in user order
  @param order user order
  @param compare comparator to sort orderItem list
*/
void listOrderItems( Order *order, int (*compare)( void const *va, void const *vb ))
{
  qsort(order->list, order->count, sizeof(order->list[0]), compare);
  printf("%-4s %-20s %8s %-15s %-s\n", "ID", "Name", "Quantity", "Category", "Cost");
  int total = 0;
  for (int i = 0; i < order->count; i++) {
    printf("%-4s %-20s %8d %-15s $%3d.%02d\n", order->list[i]->menuItem->id, order->list[i]->menuItem->name, order->list[i]->quantity, order->list[i]->menuItem->category, ((order->list[i]->menuItem->cost * (order->list[i]->quantity)) / 100), ((order->list[i]->menuItem->cost * (order->list[i]->quantity)) % 100));
    total += order->list[i]->menuItem->cost * (order->list[i]->quantity);
  }
  printf("%-50s $%3d.%02d\n", "Total", total/100, total%100);
}

/**
  Private static comparator method to compare menu items
  @param va void pointer to a MenuItem
  @param vb void pointer to a MenuItem
  @return if -1 if va comes before vb, 1, if va comes after vb, 0 if they are both equal
*/
static int menuCompare (void const *va, void const *vb)
{
  MenuItem const *a = *(MenuItem**) va;
  MenuItem const *b = *(MenuItem**) vb;
  
  int cat = strcmp(a->category, b->category);
  int idA;
  int idB;
  sscanf(a->id, "%d", &idA);
  sscanf(b->id, "%d", &idB);
  
  if (cat < 0) {
    return -1;
  } else if (cat > 0) {
    return 1;
  }
  
  if (idA < idB) {
    return -1;
  } if (idA > idB) {
    return 1;
  }
  return 0;
}

/**
  Private static comparator method to order items
  @param va void pointer to a OrderItem
  @param vb void pointer to a OrderItem
  @return if -1 if va comes before vb, 1, if va comes after vb, 0 if they are both equal
*/
static int orderCompare( void const *va, void const *vb)
{
  OrderItem const *orderA = *(OrderItem**) va;
  OrderItem const *orderB = *(OrderItem**) vb;
  
  MenuItem *a = orderA->menuItem;
  MenuItem *b = orderB->menuItem;
  
  int costA = (orderA->quantity) * (a->cost);
  int costB = (orderB->quantity) * (b->cost);
  
  if (costA < costB) {
    return 1;
  } else if (costA > costB) {
    return -1;
  }
  
  int idA;
  int idB;
  sscanf(a->id, "%d", &idA);
  sscanf(b->id, "%d", &idB);
  
  if (idA < idB) {
    return -1;
  } if (idA > idB) {
    return 1;
  }
  return 0;
}

/**
  Private static filter test that always returns true
  @param item MenuItem to test
  @param str category string to test
  @return always true
*/
static bool all(MenuItem const *item, char const *str)
{
  return true;
}

/**
  Private static filter test for MenuItems
  @param item MenuItem to test
  @param catefory string to test
  @return if MenuItem category matches given category string
*/
static bool menuItemCompare(MenuItem const *item, char const *str)
{
  return strcmp(item->category, str) == 0;
}

/**
  Private static method that gets an MenuItem with a given id
  @param menu Menu to search
  @param id id to match
  @return found MenuItem or NULL if id does not match
*/
static MenuItem *getItem(Menu *menu, char *id)
{
  for (int i = 0; i < menu->count; i++) {
    if (strcmp(menu->list[i]->id, id) == 0) {
      return menu->list[i];
    }
  }
  
  return NULL;
}

/**
  Private static method to make OrderStruct
  @return Created Order struct
*/
static Order *makeOrder()
{
  Order *order = malloc(sizeof(Order));
  order->list = malloc(5 * sizeof(OrderItem*));
  order->capacity = 5;
  order->count = 0;
  
  return order;
}

/**
  Private static method that gets a OrderItem with a MenuItem with a given id
  @param Order to search
  @param id to match
  @return found OrderItem or NULL if id does not match
*/
static OrderItem *findOrder(Order *order, char *id)
{
  for (int i = 0; i < order->count; i++) {
    if (strcmp(order->list[i]->menuItem->id, id) == 0) {
      return order->list[i];
    }
  }
  
  return NULL;
}

/**
  Prints Invalid Command
*/
static void invalidCommand()
{
  printf("Invalid command\n\n");
}

/**
  Frees all heap memory for a given Order struct
  @param order Order struct to free all associated heap memory
*/
static void freeOrder(Order *order)
{
  for (int i = 0; i < order->count; i++) {
    free(order->list[i]);
  }
  free(order->list);
  free(order);
}

/**
  Program starting point. Reads in user commands until end of file or "quit"
  @param argc number of command line arguements
  @param argv list of command line arguements
  @return exit status of program
*/
int main(int argc, char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "usage: kiosk <menu-file>*\n");
    exit(1);
  }
  int (*menuCmp) (void const *va, void const *vb);
  menuCmp = menuCompare;
  
  int (*orderCmp) (void const *va, void const *vb);
  orderCmp = orderCompare;
  
  bool (*menuItemCmp) (MenuItem const *item, char const *str);
  
  char *str = "";
  Menu *menu = makeMenu();
  Order *order = makeOrder();
  
  for (int i = 1; i < argc; i++) {
    
    readMenuItems(argv[i], menu);
  }
  
  char command[10];
  char parameter[10];
  char category[20];
  
  bool end = false;
  while (strncmp("quit", command, 4) && !end) {
    printf("cmd> ");
    str = readLine(stdin);
    if (!str[0]) {
      free(str);
      end = true;
      return EXIT_SUCCESS;
    }
    int matches = sscanf(str, "%9s%9s%19s", command, parameter, category);
    
    printf("%s\n", str);
    free(str);
    if (strcmp(command, "list") == 0) {
      if (strcmp(parameter, "menu") == 0) {
        if (matches > 2) {
          invalidCommand();
          continue;
        }
        menuItemCmp = all;
        listMenuItems(menu, menuCmp, menuItemCmp, NULL);
      } else if (strcmp(parameter, "category") == 0){
        menuItemCmp = menuItemCompare;
        listMenuItems(menu, menuCmp, menuItemCmp, category);
      } else if (strcmp(parameter, "order") == 0) {
        listOrderItems(order, orderCmp);
      }
    } else if (strcmp(command, "add") == 0) {
      MenuItem *item = getItem(menu, parameter);
      if (!item) {
        invalidCommand();
        continue;
      }
      int num;
      sscanf(category, "%d", &num);
      OrderItem *orderItemTemp = findOrder(order, item->id);
      if (orderItemTemp) {
        orderItemTemp->quantity += num;
      } else {
        OrderItem *orderItem = malloc(sizeof(OrderItem));
        orderItem->menuItem = item;
        orderItem->quantity = num;
        
        if (order->count == order->capacity) {
          order->capacity = 2*(order->count);
          order->list = realloc(order->list, (order->capacity) * sizeof(OrderItem*));
        }
        order->list[order->count++] = orderItem;
      }
    } else if (strcmp(command, "remove") == 0) {
      int num;
      sscanf(category, "%d", &num);
      bool found = false;
      for (int i = 0; i < order->count; i++) {
        if (strcmp(order->list[i]->menuItem->id, parameter) == 0) {
          found = true;
          if (order->list[i]->quantity - num == 0) {
            free(order->list[i]);
            for (int j = i; j < order->count - 1; j++) {
              order->list[i] = order->list[i + 1];
              order->count--;
            }
          } else if (order->list[i]->quantity - num > 0) {
            order->list[i]->quantity -= num;
          }
        }
      }
      if (!found) {
        invalidCommand();
        continue;
      }
    } else if (strcmp(command, "quit") != 0) {
      invalidCommand();
      continue;
    }
    if (strcmp(command, "quit") != 0) {
      printf("\n");
    } 
  }
  
  freeMenu(menu);
  freeOrder(order);
  
  return EXIT_SUCCESS;
}
