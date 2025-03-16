typedef struct SneklangVar {
  int value;
  int scope_level;
  char type;
  char is_constant;
  char *name;
} sneklang_var_t;
