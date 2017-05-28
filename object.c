#include "object.h"

int register_zero = 0;
int register_result = 1;
int register_operator_loader = 2;
int register_operator_left = 3;
int register_operator_right = 4;
int register_context_offset = 5;
int register_operator_offset = 6;
int line_counter = 0;
int memory_index = 0;

//insertion function for variables
void insert_variable(list_variables *variables_list, int index, int index_array, kind_variable kind, char id[], char scope[]){
   type_variable *p = variables_list->start;
   type_variable *new_variable = malloc(sizeof(type_variable));

   new_variable->index = index;
   new_variable->index_array = index_array;
   new_variable->kind = kind;
   strcpy(new_variable->scope, scope);
   strcpy(new_variable->id, id);

   if(p==NULL){
     variables_list->start = new_variable;
     variables_list->start->next = NULL;
   }
   else{
     while(p->next!=NULL){
       p = p->next;
     }
      p->next = new_variable;
      p->next->next = NULL;
   }
}

//reserves spaces in memory for variables of a given function
void declaration_variables(list_variables *variables_list, TipoLista *table, char scope[]){
  int i;
  int array_memory_index;
  TipoID *table_item;
  for(i = 0;i<211;i++){
    if(&table[i]!=NULL){
      table_item = table[i].start;
      while (table_item!=NULL) {
        if (!strcmp(table_item->escopo, scope)) {
          if (!strcmp(table_item->tipoID, "var")) {
            insert_variable(variables_list, memory_index, 0, variable_kind, table_item->nomeID, scope);
            memory_index++;
          }
          else if(!strcmp(table_item->tipoID, "vet")){
            array_memory_index = memory_index;
            for (size_t j = 0; j <= table_item->array_size; j++) {
              insert_variable(variables_list, array_memory_index, j, array_kind, table_item->nomeID, scope);
              memory_index++;
            }
          }
        }
        table_item = table_item->prox;
      }
    }
  }

}
//numbers relate to amount of registers in the operation
void format_zero(galetype type, int immediate){
  if(type==G_HLT||type==G_NOP)
    printf("%4d: \ttype: %d\n", line_counter, type);
  else
    printf("%4d: \ttype: %d \timmediate: %d\n", line_counter, type, immediate);
  line_counter++;
}

void format_one(galetype type, int register_a, int immediate){
  printf("%4d: \ttype: %d \tregister: %d \timmediate: %d\n", line_counter, type, register_a, immediate);
  line_counter++;
}

void format_two(galetype type, int register_source, int register_target, int immediate){
  printf("%4d: \ttype: %d \tsource: %d \ttarget: %d \timmediate: %d\n",
  line_counter, type, register_source,register_target, immediate);
  line_counter++;
}

void format_three(galetype type, int register_source_a, int register_source_b, int register_target){
  printf("%4d: \ttype: %d \tsource_a: %d \tsource_b: %d \ttarget: %d\n",
  line_counter, type, register_source_a, register_source_b, register_target);
  line_counter++;
}

void generate_code(list_quadruple *quad_list, TipoLista *table){
    quadruple *p = quad_list->start;
    while (p!=NULL) {
      switch (p->op) {
        case AddK:
        // printf("galeto\n");
          // format_three(G_ADD, , register_result)
          break;
        case SubK:
          break;
        case TimK:
          break;
        case EqlK:
          break;
        case GeqK:
          break;
        case AsvK:
          break;
        case AsaK:
          break;
        case InnK:
          break;
        case OutK:
          break;
        case PrmK:
          break;
        case CalK:
          break;
        case RetK:
          break;
        case IffK:
          break;
        case GtoK:
          break;
        case HltK:
          break;
        case LblK:
          break;
        case CstK:
          break;
        case VstK:
          break;
        case AstK:
          break;
        default:
          break;
      }
      // printf("%d\n", p->op);
      p = p->next;
    }
  }


void generate_code_launcher(list_quadruple *quad_list, TipoLista *table){
  //stores all variables positions
  list_variables *variables_list;

  variables_list->start = NULL;

  file_target_code = fopen("target_code.gc", "w");

  declaration_variables(variables_list, table, "global");

// adding global variables to the beggining of execution
  // for(i = 0;i<211;i++){
  //   if(&table[i]!=NULL){
  //     table_item = table[i].start;
  //     while (table_item!=NULL) {
  //       if (!strcmp(table_item->escopo, "global")) {
  //         if (!strcmp(table_item->tipoID, "var")) {
  //           // insert_variable(variables_list, memory_index, 0, variable_kind, table_item->nomeID);
  //           // memory_index++;
  //         }
  //         else if(!strcmp(table_item->tipoID, "vet")){
  //         }
  //       }
  //       table_item = table_item->prox;
  //     }
  //   }
  // }
  //

  generate_code(quad_list, table);
  fclose( file_target_code );
}

// to do:
// - attribute index to quadruples
// - find functions declarations and specify them in symbols table
// - allocate global/main variables in memory (static)
