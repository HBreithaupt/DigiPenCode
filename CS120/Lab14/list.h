struct Node
{
  int number;        /* data portion    */
  struct Node *next; /* pointer portion */
};

void add_front(struct Node **list, int value);
void add_back(struct Node **list, int value);
void free_list(struct Node *list);
void print_list(const struct Node *list);
void remove_item(struct Node **list, int value);
int size_list(const struct Node *list);
int sum_list(const struct Node *list);