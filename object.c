//RISK: READING AND WRITING IN THE SAME REGISTER

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

/* macro to control processor register file overflow */
#define MAXREGISTER 20
#define OFFSET 7


/* array to control available temporaries
 * at current intermediate code instruction
 */
static int temporaries[MAXREGISTER];

/* Function get_temporary returns
 * next available temporary,
 * terminating execution of the program
 * if there is no available temporary
*/
void map_temporary(int register_temporary){
	int i, temp = -1;
	for(i = 0; i < MAXREGISTER; ++i){
		if(temporaries[i] == 0){
			temporaries[i] = register_temporary;
			temp = i+OFFSET;
			break;
		}
	}
	if(temp < 0){
		printf("ERROR: register file overflow: no temporaries available at requested instruction\n");
		exit(0);
	}
}

/* Function releaseTemp releases
 * specified temporary
*/
void release_temporary(int temp){
  int t = temp-OFFSET;
	if(t >= 0 && t < MAXREGISTER)
		temporaries[t] = 0;
}

/*Function search_temporary searches
  a specific temporary*/
  int search_temporary(int index_temporary){
    int i;
    for (i = 0; i < MAXREGISTER; i++) {
      if (temporaries[i]==index_temporary) {
        return i+OFFSET;
      }
    }
  }


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

//searches the position in memory of a variable given its name, scope and array index
int search_variable(list_variables *variables_list, char name[], int array_position, char scope[]){
  type_variable *p = variables_list->start;
  while (p!=NULL) {
    if(!strcmp(p->scope, scope)||!strcmp(p->scope,"global")){
      if(!strcmp(p->id, name)){
        if(p->kind==variable_kind)
          return p->index;
        else return p->index+array_position;
      }
    }
    p = p->next;
  }
  printf("ERROR: variable not found!\n");
  return 0;
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

void generate_code(list_quadruple *quad_list, TipoLista *table, list_variables *variables_list){
    quadruple *p = quad_list->start;
    char current_scope[50];
    int flag_immediate_left = 0;
    int flag_immediate_right = 0;
    int immediate_left = 0;
    int immediate_right = 0;
    int register_temporary_left;
    int register_temporary_right;

    while (p!=NULL) {
      switch (p->op) {
				case AddK:
				case SubK:
//left operand
          if (p->address_1.kind==Temp) {
            register_temporary_left = search_temporary(p->address_1.value);
            format_two(G_ADDI, register_temporary_left, register_operator_left, 0);
          }else if(p->address_1.kind==String){
            int memory_position_left = 0;
            memory_position_left = search_variable(variables_list, p->address_1.name, 0, current_scope);
            format_one(G_LD, register_operator_left, memory_position_left);
          }else if(p->address_1.kind==IntConst){
            if(p->address_1.value<65000){
              flag_immediate_left = 1;
              immediate_left = p->address_1.value;
            }
            else{
              format_one(G_LDI, register_operator_left, p->address_1.value);
            }
          }else{
            printf("ERROR: intermediate variable kind unknown!\n");
          }

//right operand
          if (p->address_2.kind==Temp) {
            register_temporary_right = search_temporary(p->address_2.value);
            format_two(G_ADDI, register_temporary_right, register_operator_right, 0);
          }else if(p->address_2.kind==String){
            int memory_position_right = 0;
            memory_position_right = search_variable(variables_list, p->address_2.name, 0, current_scope);
            format_one(G_LD, register_operator_right, memory_position_right);
          }else if(p->address_2.kind==IntConst){
            if(p->address_2.value<65000){
              flag_immediate_right = 1;
              immediate_right = p->address_2.value;
            }
            else{
              format_one(G_LDI, register_operator_right, p->address_2.value);
            }
          }else{
            printf("ERROR: intermediate variable kind unknown!\n");
          }

					switch (p->op) {
						case AddK:
						if(flag_immediate_left&&flag_immediate_right){
							format_one(G_LDI, register_result, immediate_left+immediate_right);
							flag_immediate_left = 0;
							flag_immediate_right = 0;
						}else if (flag_immediate_left) {
							format_two(G_ADDI, register_operator_right, register_result, immediate_left);
							flag_immediate_left = 0;
						}else if (flag_immediate_right) {
							format_two(G_ADDI, register_operator_left, register_result, immediate_right);
							flag_immediate_right = 0;
						}else{
							format_three(G_ADD, register_operator_left, register_operator_right, register_result);
						}
						break;
						case SubK:
						if(flag_immediate_left&&flag_immediate_right){
							format_one(G_LDI, register_result, immediate_left-immediate_right);
							flag_immediate_left = 0;
							flag_immediate_right = 0;
						}else if (flag_immediate_left) {
							format_two(G_SUBI, register_operator_right, register_result, immediate_left);
							flag_immediate_left = 0;
						}else if (flag_immediate_right) {
							format_two(G_SUBI, register_operator_left, register_result, immediate_right);
							flag_immediate_right = 0;
						}else{
							format_three(G_SUB, register_operator_left, register_operator_right, register_result);
						}
					}


          map_temporary(p->address_3.value);
          release_temporary(register_operator_left);
          release_temporary(register_operator_right);

          break;
        case TimK:
				case OvrK:
				case EqlK:
				case NeqK:
				case GtrK:
				case GeqK:
				case LsrK:
				case LeqK:
				//left operand
				          if (p->address_1.kind==Temp) {
				            register_temporary_left = search_temporary(p->address_1.value);
				            format_two(G_ADDI, register_temporary_left, register_operator_left, 0);
				          }else if(p->address_1.kind==String){
				            int memory_position_left = 0;
				            memory_position_left = search_variable(variables_list, p->address_1.name, 0, current_scope);
				            format_one(G_LD, register_operator_left, memory_position_left);
				          }else if(p->address_1.kind==IntConst){
				            if(p->address_1.value<65000){
				              flag_immediate_left = 1;
				              immediate_left = p->address_1.value;
				            }
			              format_one(G_LDI, register_operator_left, p->address_1.value);
				          }else{
				            printf("ERROR: intermediate variable kind unknown!\n");
				          }

				//right operand
				          if (p->address_2.kind==Temp) {
				            register_temporary_right = search_temporary(p->address_2.value);
				            format_two(G_ADDI, register_temporary_right, register_operator_right, 0);
				          }else if(p->address_2.kind==String){
				            int memory_position_right = 0;
				            memory_position_right = search_variable(variables_list, p->address_2.name, 0, current_scope);
				            format_one(G_LD, register_operator_right, memory_position_right);
				          }else if(p->address_2.kind==IntConst){
				            if(p->address_2.value<65000){
				              flag_immediate_right = 1;
				              immediate_right = p->address_2.value;
				            }
				              format_one(G_LDI, register_operator_right, p->address_2.value);
				          }else{
				            printf("ERROR: intermediate variable kind unknown!\n");
				          }

								switch (p->op) {
									case TimK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left*immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_MUL, register_operator_left, register_operator_right, register_result);
									}
									break;
									case OvrK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left/immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_DIV, register_operator_left, register_operator_right, register_result);
									}
									break;
									case EqlK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left==immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_left, register_operator_right, register_result);
										format_three(G_SLT, register_operator_right, register_operator_left, register_operator_left);
										format_three(G_OR, register_result, register_operator_left, register_result);
										format_two(G_NOT, register_result, register_result, 0);
									}
									break;
									case NeqK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left!=immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_left, register_operator_right, register_result);
										format_three(G_SLT, register_operator_right, register_operator_left, register_operator_left);
										format_three(G_OR, register_result, register_operator_left, register_result);
									}
									break;
									case GtrK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left!=immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_right, register_operator_left, register_operator_left);
									}
									break;
									case GeqK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left!=immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_left, register_operator_right, register_result);
										format_two(G_NOT, register_result, register_result, 0);
									}
									break;
									case LsrK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left!=immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_left, register_operator_right, register_result);
									}
									break;
									case LeqK:
									if(flag_immediate_left&&flag_immediate_right){
										format_one(G_LDI, register_result, immediate_left!=immediate_right);
										flag_immediate_left = 0;
										flag_immediate_right = 0;
									}else{
										format_three(G_SLT, register_operator_right, register_operator_left, register_operator_left);
										format_two(G_NOT, register_result, register_result, 0);
									}
									break;
								}

									map_temporary(p->address_3.value);
				          release_temporary(register_operator_left);
				          release_temporary(register_operator_right);
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

//global variables' memory allocation
  declaration_variables(variables_list, table, "global");

  generate_code(quad_list, table, variables_list);

  fclose( file_target_code );
}

// to do:
// - attribute index to quadruples
// - find functions declarations and specify them in symbols table
// - allocate global/main variables in memory (static)
