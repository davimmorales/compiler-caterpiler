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
void map_temporary(list_instructions *instructions_list, int register_temporary, int register_source){
	int i, temp = -1;
	for(i = 0; i < MAXREGISTER; ++i){
		if(temporaries[i] == 0){
			temporaries[i] = register_temporary;
			temp = i+OFFSET;
			break;
		}
	}
	if(temp < OFFSET){
		printf("ERROR: register file overflow: no temporaries available at requested instruction\n");
		exit(0);
	}
	format_two(instructions_list, G_ADDI, register_source, temp, 0);
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

void print_variables(list_variables *variables_list) {
	type_variable *p = variables_list->start;
	while (p!=NULL) {
		printf("index: %d \t array: %d \t id: %s \t scope: %s\n", p->index, p->index_array, p->id, p->scope);
		p = p->next;
	}
}

void print_instructions(list_instructions *instructions_list){
	type_instruction *p = instructions_list->start;
	while (p!=NULL) {
		printf("%4d: \ttype: %d \tsource_a: %d \tsource_b: %d\n \ttarget: %d \timmediate: %d\n",
		p->line, p->type, p->register_a, p->register_b, p->register_c,p->immediate);
		p = p->next;
	}
}

//searches the position in memory of a variable given its name, scope and array index
int search_variable(list_variables *variables_list, char name[], int array_position, char scope[]){
	type_variable *p = variables_list->start;
	char local_scope[50];
	strcpy(local_scope, scope);

	while (p!=NULL) {
		// printf("index: %d \t array: %d \t id: %s \t scope: %s\n", p->index, p->index_array, p->id, p->scope);
		if(!strcmp(p->scope, "global")){
			if(!strcmp(name, p->id)){
				strcpy(local_scope, "global");
				break;
			}
		}
		p = p->next;
	}

	p = variables_list->start;
	while (p!=NULL) {
		if(!strcmp(p->scope, local_scope)){
			if(!strcmp(p->id, name)){
				// printf("SEARCH VARIABLE\n");
				if(p->kind==variable_kind){
					// printf("VARIABLE INDEX: %d\n", p->index);
					// printf("%s %d %s\n", name, array_position, scope);

					return p->index;

				}
				else{  return p->index+array_position; }
			}
		}
		p = p->next;
	}

	printf("ERROR: variable not found!\n");
	printf("%s %d %s\n", name, array_position, local_scope);
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
void format_zero(list_instructions *instructions_list,  galetype type, int immediate, AddrKind kind, char label_string[], kind_jump jump){
	// if(type==G_HLT||type==G_NOP)
	// printf("%4d: \ttype: %d\n", line_counter, type);
	// else
	// printf("%4d: \ttype: %d \timmediate: %d\n", line_counter, type, immediate);

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = 0;
	new_instruction->register_b = 0;
	new_instruction->register_c = 0;
	new_instruction->immediate = immediate;
	new_instruction->type = type;
	if(type==G_BOZ||type==G_JMP){
		if(kind==String){
			strcpy(new_instruction->label_name, label_string);
			new_instruction->jump = jump;
		}else{
			new_instruction->target_label = immediate;
			new_instruction->jump = jump;
		}
	} else
	new_instruction->target_label = 0;


	if (p==NULL) {
		instructions_list->start = new_instruction;
		instructions_list->start->next = NULL;
	}
	else{
		while (p->next!=NULL) {
			p = p->next;
		}
		p->next = new_instruction;
		p->next->next = NULL;
	}
	line_counter++;
}

void format_one(list_instructions *instructions_list, galetype type, int register_a, int immediate){
	// printf("%4d: \ttype: %d \tregister: %d \timmediate: %d\n", line_counter, type, register_a, immediate);

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = register_a;
	new_instruction->register_b = 0;
	new_instruction->register_c = 0;
	new_instruction->immediate = immediate;
	new_instruction->type = type;
	new_instruction->target_label = 0;



	if (p==NULL) {
		instructions_list->start = new_instruction;
		instructions_list->start->next = NULL;
	}
	else{
		while (p->next!=NULL) {
			p = p->next;
		}
		p->next = new_instruction;
		p->next->next = NULL;
	}
	line_counter++;
}

void format_two(list_instructions *instructions_list, galetype type, int register_source, int register_target, int immediate){
	// printf("%4d: \ttype: %d \tsource: %d \ttarget: %d \timmediate: %d\n",
	// line_counter, type, register_source,register_target, immediate);

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = register_source;
	new_instruction->register_b = 0;
	new_instruction->register_c = register_target;
	new_instruction->immediate = immediate;
	new_instruction->type = type;
	new_instruction->target_label = 0;



	if (p==NULL) {
		instructions_list->start = new_instruction;
		instructions_list->start->next = NULL;
	}
	else{
		while (p->next!=NULL) {
			p = p->next;
		}
		p->next = new_instruction;
		p->next->next = NULL;
	}
	line_counter++;
}



void format_three(list_instructions *instructions_list, galetype type, int register_source_a, int register_source_b, int register_target){
	// printf("%4d: \ttype: %d \tsource_a: %d \tsource_b: %d \ttarget: %d\n",
	// line_counter, type, register_source_a, register_source_b, register_target);

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = register_source_a;
	new_instruction->register_b = register_source_b;
	new_instruction->register_c = register_target;
	new_instruction->immediate = 0;
	new_instruction->type = type;
	new_instruction->target_label = 0;



	if (p==NULL) {
		instructions_list->start = new_instruction;
		instructions_list->start->next = NULL;
	}
	else{
		while (p->next!=NULL) {
			p = p->next;
		}
		p->next = new_instruction;
		p->next->next = NULL;
	}
	line_counter++;
}

void generate_code(list_instructions *instructions_list, list_quadruple *quad_list, TipoLista *table, list_variables *variables_list){
	quadruple *p = quad_list->start;
	TipoID *table_item;
	type_instruction *instruction;
	type_variable *v = variables_list->start;

	char current_scope[50];
	int i;
	int flag_immediate_left = 0;
	int flag_immediate_right = 0;
	int flag_temp;
	int immediate_left = 0;
	int immediate_right = 0;
	int register_temporary_left;
	int register_temporary_right;
	int register_temporary;
	int memory_position;
	int memory_offset;

	while (p!=NULL) {

		//the following procedures retrieve the scope of the possible variable/array
		for(i = 0;i<211;i++){
			if(&table[i]!=NULL){
				table_item = table[i].start;
				while (table_item!=NULL) {
					if(!strcmp(table_item->tipoID, "func")){
						if (p->index>table_item->intermediate_start
							&&p->index<table_item->intermediate_finish) {
								strcpy(current_scope, table_item->nomeID);
								break;
							}
						}
						table_item = table_item->prox;
					}
				}
			}


			switch (p->op) {
				case AddK:
				case SubK:
				//left operand
				if (p->address_1.kind==Temp) {
					register_temporary_left = search_temporary(p->address_1.value);
					format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_left, 0);
				}else if(p->address_1.kind==String){
					int memory_position_left = 0;
					memory_position_left = search_variable(variables_list, p->address_1.name, 0, current_scope);

					format_one(instructions_list, G_LD, register_operator_left, memory_position_left);
				}else if(p->address_1.kind==IntConst){
					if(p->address_1.value<65000){
						flag_immediate_left = 1;
						immediate_left = p->address_1.value;
					}
					else{
						format_one(instructions_list, G_LDI, register_operator_left, p->address_1.value);
					}
				}else{
					printf("ERROR: intermediate variable kind unknown: %d!\n", p->address_1.kind);
				}

				//right operand
				if (p->address_2.kind==Temp) {
					register_temporary_right = search_temporary(p->address_2.value);
					format_two(instructions_list, G_ADDI, register_temporary_right, register_operator_right, 0);
				}else if(p->address_2.kind==String){
					int memory_position_right = 0;
					memory_position_right = search_variable(variables_list, p->address_2.name, 0, current_scope);


					format_one(instructions_list, G_LD, register_operator_right, memory_position_right);
				}else if(p->address_2.kind==IntConst){
					if(p->address_2.value<65000){
						flag_immediate_right = 1;
						immediate_right = p->address_2.value;
					}
					else{
						format_one(instructions_list, G_LDI, register_operator_right, p->address_2.value);
					}
				}else{
					printf("ERROR: intermediate variable kind unknown: %d!\n", p->address_2.kind);
				}

				switch (p->op) {
					case AddK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left+immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else if (flag_immediate_left) {
						format_two(instructions_list, G_ADDI, register_operator_right, register_result, immediate_left);
						flag_immediate_left = 0;
					}else if (flag_immediate_right) {
						format_two(instructions_list, G_ADDI, register_operator_left, register_result, immediate_right);
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_ADD, register_operator_left, register_operator_right, register_result);
					}
					break;
					case SubK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left-immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else if (flag_immediate_left) {
						format_two(instructions_list, G_SUBI, register_operator_right, register_result, immediate_left);
						flag_immediate_left = 0;
					}else if (flag_immediate_right) {
						format_two(instructions_list, G_SUBI, register_operator_left, register_result, immediate_right);
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SUB, register_operator_left, register_operator_right, register_result);
					}
				}

				map_temporary(instructions_list, p->address_3.value, register_result);
				release_temporary(register_temporary_left);
				release_temporary(register_temporary_right);

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
					format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_left, 0);
				}else if(p->address_1.kind==String){
					int memory_position_left = 0;
					memory_position_left = search_variable(variables_list, p->address_1.name, 0, current_scope);


					format_one(instructions_list, G_LD, register_operator_left, memory_position_left);
				}else if(p->address_1.kind==IntConst){
					if(p->address_1.value<65000){
						flag_immediate_left = 1;
						immediate_left = p->address_1.value;
					}
					format_one(instructions_list, G_LDI, register_operator_left, p->address_1.value);
				}else{
					printf("ERROR: intermediate variable kind unknown!\n");
				}

				//right operand
				if (p->address_2.kind==Temp) {
					register_temporary_right = search_temporary(p->address_2.value);
					format_two(instructions_list, G_ADDI, register_temporary_right, register_operator_right, 0);
				}else if(p->address_2.kind==String){
					int memory_position_right = 0;
					memory_position_right = search_variable(variables_list, p->address_2.name, 0, current_scope);


					format_one(instructions_list, G_LD, register_operator_right, memory_position_right);
				}else if(p->address_2.kind==IntConst){
					if(p->address_2.value<65000){
						flag_immediate_right = 1;
						immediate_right = p->address_2.value;
					}
					format_one(instructions_list, G_LDI, register_operator_right, p->address_2.value);
				}else{
					printf("ERROR: intermediate variable kind unknown!\n");
				}

				switch (p->op) {
					case TimK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left*immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_MUL, register_operator_left, register_operator_right, register_result);
					}
					break;
					case OvrK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left/immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_DIV, register_operator_left, register_operator_right, register_result);
					}
					break;
					case EqlK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left==immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_left, register_operator_right, register_result);
						format_three(instructions_list, G_SLT, register_operator_right, register_operator_left, register_operator_left);
						format_three(instructions_list, G_OR, register_result, register_operator_left, register_result);
						format_two(instructions_list, G_NOT, register_result, register_result, 0);
					}
					break;
					case NeqK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left!=immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_left, register_operator_right, register_result);
						format_three(instructions_list, G_SLT, register_operator_right, register_operator_left, register_operator_left);
						format_three(instructions_list, G_OR, register_result, register_operator_left, register_result);
					}
					break;
					case GtrK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left!=immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_right, register_operator_left, register_operator_left);
					}
					break;
					case GeqK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left!=immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_left, register_operator_right, register_result);
						format_two(instructions_list, G_NOT, register_result, register_result, 0);
					}
					break;
					case LsrK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left!=immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_left, register_operator_right, register_result);
					}
					break;
					case LeqK:
					if(flag_immediate_left&&flag_immediate_right){
						format_one(instructions_list, G_LDI, register_result, immediate_left!=immediate_right);
						flag_immediate_left = 0;
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SLT, register_operator_right, register_operator_left, register_operator_left);
						format_two(instructions_list, G_NOT, register_result, register_result, 0);
					}
					break;
				}

				map_temporary(instructions_list, p->address_3.value, register_result);
				release_temporary(register_temporary_left);
				release_temporary(register_temporary_right);
				break;
				case AsvK:

				register_temporary = search_temporary(p->address_1.value);
				memory_position = search_variable(variables_list, p->address_3.name, 0, current_scope);



				format_one(instructions_list, G_ST, register_temporary, memory_position);

				release_temporary(register_temporary);

				break;
				case AsaK:
				flag_temp = 0;
				register_temporary = search_temporary(p->address_1.value);
				switch (p->address_2.kind) {
					case IntConst:
					memory_offset = p->address_2.value;
					// printf("OFFSET %d\n", memory_offset); THIS ONE IS WORKING
					break;
					case String:
					memory_offset = search_variable(variables_list, p->address_2.name, 0, current_scope);


					// printf("STRING OFFSET %d %s\n", memory_offset, p->address_2.name);
					break;
					case Temp:
					memory_offset = search_temporary(p->address_2.value);
					flag_temp = 1;
					// printf("TEMP OFFSET %d, %d\n", memory_offset, p->address_2.value);// NOT SURE IF IT'S WORKING
					break;
					default:
					break;
				}

				memory_position = search_variable(variables_list, p->address_3.name, memory_offset, current_scope);

				format_one(instructions_list, G_ST, register_temporary, memory_position);

				// release_temporary(register_temporary);
				// if(flag_temp)
				// 	release_temporary(memory_offset);

				break;
				case PrmK:
				break;
				case CalK:
				// remember in and out
				format_zero(instructions_list, G_JMP, 0, String, p->address_3.name, label_kind);

				instruction = instructions_list->start;
				while (instruction!=NULL) {
					if (p->address_3.kind==String&&(
							instruction->type==G_JMP)){
								if(!strcmp(p->address_3.name, instruction->label_name)&&instruction->jump==call_kind){
									instruction->immediate = line_counter-instruction->line+1;

									instruction->target_label = p->address_2.value;
									printf("TARGET LABEL: %d\n", instruction->target_label);

									// printf("Target: %s %s\n", p->address_3.name, instruction->label_name);
								}
							}
							instruction = instruction->next;
						}

					break;
				case RetK:

				if (p->address_3.kind==Temp) {
					register_temporary = search_temporary(p->address_3.value);
					format_two(instructions_list, G_ADDI, register_temporary, register_result, 0);
				}else if(p->address_3.kind==String){
					int memory_position = 0;
					memory_position = search_variable(variables_list, p->address_3.name, 0, current_scope);
					format_one(instructions_list, G_LD, register_result, memory_position);
				}else if(p->address_3.kind==IntConst){
					if(p->address_3.value<65000){
						immediate_left = p->address_3.value;
					}
					else{
						format_one(instructions_list, G_LDI, register_result, p->address_3.value);
					}
				}else{
					printf("ERROR: intermediate variable kind unknown: %d!\n", p->address_1.kind);
				}


				instruction = instructions_list->start;
				int flag_gotit=0;
				while (instruction!=NULL) {
					if (instruction->type==G_JMP){
								if(!strcmp(current_scope, instruction->label_name)&&instruction->jump==call_kind){
									// map_temporary(instructions_list, instruction->target_label, );
									flag_gotit = 1;
									break;
								}
							}
							instruction = instruction->next;
						}

				if(!flag_gotit)
					format_zero(instructions_list, G_JMP, 0, String, current_scope, call_kind);

				break;
				case IffK:
				register_temporary_left = search_temporary(p->address_1.value);
				// format_one(instructions_list, G_PBC, register_operator_left, 0);
				format_one(instructions_list, G_PBC, register_temporary_left, 0);

				format_zero(instructions_list, G_BOZ, p->address_3.value, IntConst, "none", label_kind);

				release_temporary(register_temporary_left);
				break;
				case GtoK:
				if (p->address_3.kind==LabAddr) {
					format_zero(instructions_list, G_JMP, p->address_3.value, IntConst, "none", label_kind);
				}else if(p->address_3.kind==String){
					format_zero(instructions_list, G_JMP, p->address_3.value, String, p->address_3.name, label_kind);
				}else{
					printf("EXCEPTION\n");
				}
				break;
				case HltK:
				break;
				case LblK:
				instruction = instructions_list->start;
				while (instruction!=NULL) {
					if (p->address_3.kind==LabAddr&&(
						instruction->type==G_BOZ||instruction->type==G_JMP)) {
							if(p->address_3.value==instruction->target_label&&instruction->jump==label_kind){
								instruction->immediate = line_counter-instruction->line;
								// printf("Target: %d %d\n", p->address_3.value, instruction->immediate);
							}
						}else if (p->address_3.kind==String&&(
							instruction->type==G_JMP)){
								if(!strcmp(p->address_3.name, instruction->label_name)&&instruction->jump==label_kind){
									instruction->immediate = line_counter-instruction->line;
									// printf("Target: %s %s\n", p->address_3.name, instruction->label_name);
								}
							}
							instruction = instruction->next;
						}

						break;
						case CstK:
						if(p->address_1.value<65000){
							immediate_left = p->address_1.value;
							flag_immediate_left = 1;
						}else{
							format_one(instructions_list, G_LDI, register_operator_left, p->address_1.value);
						}

						if (flag_immediate_left) {
							format_one(instructions_list, G_LDI, register_result, immediate_left);
							flag_immediate_left = 0;
						}
						map_temporary(instructions_list, p->address_3.value, register_result);

							break;
						case VstK:
							memory_position = search_variable(variables_list, p->address_1.name, 0, current_scope);
							format_one(instructions_list, G_LD, register_operator_left, memory_position);
							map_temporary(instructions_list, p->address_3.value, register_operator_left);
							break;
						case AstK:
							memory_position = search_variable(variables_list, p->address_1.name, p->address_2.value, current_scope);
							format_one(instructions_list, G_LD, register_operator_left, memory_position);
							map_temporary(instructions_list, p->address_3.value, register_operator_left);
							break;
						default:
						break;
					}
					// printf("%d\n", p->op);
					// printf("SCOPE: %s\n", p->scope);
					p = p->next;
				}
			}


			void generate_code_launcher(list_quadruple *quad_list, TipoLista *table){
				int i;
				//stores all variables positions
				list_variables *variables_list;
				list_instructions *instructions_list;

				variables_list = (list_variables*) malloc(sizeof(list_variables));
				instructions_list = (list_instructions*) malloc(sizeof(list_instructions));

				variables_list->start = NULL;
				instructions_list->start = NULL;

				file_target_code = fopen("target_code.gc", "w");

				//global and main variables' memory allocation
				TipoID *table_item;
				for(i = 0;i<211;i++){
					if(&table[i]!=NULL){
						table_item = table[i].start;
						while (table_item!=NULL) {
							if (!strcmp(table_item->tipoID, "func")) {
								declaration_variables(variables_list, table, table_item->nomeID);
								memory_index++;
							}
							table_item = table_item->prox;
						}
					}
				}
				declaration_variables(variables_list, table, "global");
				// declaration_variables(variables_list, table, "main");

				printf("\n");
				generate_code(instructions_list, quad_list, table, variables_list);
				fclose( file_target_code );

				print_variables(variables_list);
				print_instructions(instructions_list);
			}
