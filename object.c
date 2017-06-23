//RISK: READING AND WRITING IN THE SAME REGISTER

#include "object.h"



int register_zero = 0;
int register_result = 1;
int register_operator_loader = 2;
int register_operator_left = 3;
int register_operator_right = 4;
int register_context_offset = 5;
int register_operator_offset = 6;
int register_return = 30;
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
	format_two(instructions_list, G_ADDI, register_source, temp, 0, "none");
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

void treat_jumps_n_branches(list_instructions *instructions_list, list_labels *labels_list, list_labels *calls_list){
	type_label *label = labels_list->start;
	type_label *call = calls_list->start;
	type_instruction *instruction;

	while (label!=NULL) {
		switch (label->type) {
			case LabAddr:
				instruction = instructions_list->start;
				while (instruction!=NULL) {
					if (label->index==instruction->target_label) {
						if (instruction->jump==label_kind) {
							if (!strcmp(instruction->label_name, "none")) {
							if (instruction->type==G_BOZ) {
								instruction->immediate = label->line-instruction->line;
							}else if(instruction->type==G_JMP){
								instruction->immediate = label->line;
								printf("LL: %d, LI: %d LK: %d LN: %s\n", label->line, label->index, label->type, instruction->label_name);
							}
							}
						}
					}
					instruction = instruction->next;
				}
				break;
				case String:
					instruction = instructions_list->start;
					while (instruction!=NULL) {
						if (instruction->type==G_JMP) {
							if(!strcmp(instruction->label_name, label->name)){
								if(instruction->jump==label_kind){
									instruction->immediate = label->line;
								}
							}
						}
						instruction = instruction->next;
					}
					break;
			default:
				printf("ERROR: unknown type label: %d\n", label->type);
			break;
		}
		label = label->next;
	}

	while (call!=NULL) {
		instruction = instructions_list->start;
		while (instruction!=NULL) {
			if (instruction->type==G_JMP){
						if(!strcmp(call->name, instruction->label_name)){
							if (instruction->jump==call_kind) {
							instruction->immediate = call->line;
						}
						}
					}
					instruction = instruction->next;
				}
		call = call->next;
	}
}


void consume_parameters(TipoLista *table, list_instructions *instructions_list, list_parameters *parameters_list,list_variables *variables_list, char function[]){
		type_variable *variable = variables_list->start;
		type_instruction *instruction = instructions_list->start;
		type_parameter *parameter = parameters_list->start;
		TipoID *table_item;

		int memory_from;
		int memory_to;
		int temp_from;
		int parameter_index = 1;
		int i;
		int array_index;

		while(parameter!=NULL){
			//loading parameter to register result
			switch (parameter->kind){
				case String:
					//search for parameter in memory
					memory_from = search_variable(variables_list, parameter->name, 0, parameter->scope);
					//load from memory to register result
					format_one(instructions_list, G_LD, register_result, memory_from);
					break;
				case IntConst:
				  //load parameter as immediate to register result
					format_one(instructions_list, G_LDI, register_result, parameter->value);
					break;
				case Temp:
					//search for register that stores parameter
					temp_from = search_temporary(parameter->value);
					//load parameter from temporary to register result
					format_two(instructions_list, G_ADDI, temp_from, register_result, 0, "none");
					break;
			}
			//storing parameter in memory
			for ( i = 0; i < 211; i++) {
				if(&table[i]!=NULL){
					table_item = table[i].start;
					while (table_item!=NULL) {
						if (!strcmp(table_item->escopo, function)) {
							if (table_item->indice_parametro==parameter_index) {
								if (!strcmp(table_item->tipoID,"var")) {
									//search for position in memory to store parameter
									memory_to = search_variable(variables_list, table_item->nomeID, 0, table_item->escopo);
									//store value from register result into memory
									format_one(instructions_list, G_ST, register_result, memory_to);
								}else{
									//goes through 'from' array and stores values into 'to' array
									for (array_index = 0; array_index <= table_item->array_size; array_index++) {
										//search for parameter in memory
										memory_from = search_variable(variables_list, parameter->name, array_index, parameter->scope);
										//load from memory to register result
										format_one(instructions_list, G_LD, register_result, memory_from);
										//search for position in memory to store parameter
										memory_to = search_variable(variables_list, table_item->nomeID, array_index, table_item->escopo);
										//store value from register result into memory
										format_one(instructions_list, G_ST, register_result, memory_to);
									}
								}
							}
						}
						table_item = table_item->prox;
					}
				}
			}

			parameter_index++;
			parameter = parameter->next;
		}
		parameters_list->start = NULL;
		release_temporary(temp_from);
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

void insert_label(list_labels *labels_list, AddrKind type, char name[], int index, int line){
				type_label *l = labels_list->start;
				type_label *new_label = malloc(sizeof(type_label));

				if (type==LabAddr) {
					new_label->index = index;
					strcpy(new_label->name, "none");
				}else{
					new_label->index = 0;
					strcpy(new_label->name, name);
				}
				new_label->type = type;
				new_label->line = line;

				if(l==NULL){
					labels_list->start = new_label;
					labels_list->start->next = NULL;
				}
				else{
					while(l->next!=NULL){
						l = l->next;
					}
					l->next = new_label;
					l->next->next = NULL;
				}
			}

void print_parameters(list_parameters *parameters_list) {
	type_parameter *p = parameters_list->start;
	while (p!=NULL) {
		printf("kind: %d \t value: %d \t name: %s scope: %s\n", p->kind, p->value, p->name, p->scope);
		p = p->next;
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

void print_labels(list_labels *labels_list) {
	type_label *p = labels_list->start;
	while (p!=NULL) {
		printf("NAME:%s INDEX:%d LINE:%d TYPE:%d \n", p->name, p->index, p->line, p->type);
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

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = 0;
	new_instruction->register_b = 0;
	new_instruction->register_c = 0;
	new_instruction->immediate = immediate;
	new_instruction->type = type;
	if(type==G_BOZ||type==G_JMP){
		// if(kind==String){
			strcpy(new_instruction->label_name, label_string);
			// new_instruction->jump = jump;
		// }else if(kind==LabAddr){
			new_instruction->target_label = immediate;
			new_instruction->jump = jump;
		// }
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

void format_two(list_instructions *instructions_list, galetype type, int register_source, int register_target, int immediate, char label_string[]){
	// printf("%4d: \ttype: %d \tsource: %d \ttarget: %d \timmediate: %d\n",
	// line_counter, type, register_source,register_target, immediate);

	type_instruction *p =instructions_list->start;
	type_instruction *new_instruction = malloc(sizeof(type_instruction));

	new_instruction->line = line_counter;
	new_instruction->register_a = register_source;
	new_instruction->register_b = 0;
	new_instruction->register_c = register_target;
	new_instruction->immediate = immediate;
	strcpy(new_instruction->label_name, label_string);
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

void generate_code(list_instructions *instructions_list, list_quadruple *quad_list, TipoLista *table, list_variables *variables_list, list_parameters *parameters_list, list_labels *labels_list, list_labels *calls_list){
	quadruple *p = quad_list->start;
	TipoID *table_item;
	type_instruction *instruction;
	type_variable *v = variables_list->start;
	type_parameter *par;


	char current_scope[50];
	int i;
	int flag_immediate_left = 0;
	int flag_immediate_right = 0;
	int flag_temp_left = 0;
	int flag_temp_right = 0;
	int immediate_left = 0;
	int immediate_right = 0;
	int register_temporary_left;
	int register_temporary_right;
	int register_temporary;
	int memory_position;
	int memory_offset;
	int counter;

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
					format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_left, 0, "none");
					flag_temp_left = 1;
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
					format_two(instructions_list, G_ADDI, register_temporary_right, register_operator_right, 0, "none");
					flag_temp_right = 1;
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
						format_two(instructions_list, G_ADDI, register_operator_right, register_result, immediate_left, "none");
						flag_immediate_left = 0;
					}else if (flag_immediate_right) {
						format_two(instructions_list, G_ADDI, register_operator_left, register_result, immediate_right, "none");
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
						format_two(instructions_list, G_SUBI, register_operator_right, register_result, immediate_left, "none");
						flag_immediate_left = 0;
					}else if (flag_immediate_right) {
						format_two(instructions_list, G_SUBI, register_operator_left, register_result, immediate_right, "none");
						flag_immediate_right = 0;
					}else{
						format_three(instructions_list, G_SUB, register_operator_left, register_operator_right, register_result);
					}
				}

				if (flag_temp_left) {
					release_temporary(register_temporary_left);
					flag_temp_left = 0;
				}
				if (flag_temp_right) {
					release_temporary(register_temporary_right);
					flag_temp_right;
				}
				map_temporary(instructions_list, p->address_3.value, register_result);


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
					format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_left, 0, "none");
					flag_temp_left = 1;

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
					format_two(instructions_list, G_ADDI, register_temporary_right, register_operator_right, 0, "none");
					flag_temp_right = 1;

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
						format_two(instructions_list, G_NOT, register_result, register_result, 0, "none");
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
						format_two(instructions_list, G_NOT, register_result, register_result, 0, "none");
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
						format_two(instructions_list, G_NOT, register_result, register_result, 0, "none");
					}
					break;
				}

				if (flag_temp_left) {
					release_temporary(register_temporary_left);
					flag_temp_left = 0;
				}
				if (flag_temp_right) {
					release_temporary(register_temporary_right);
					flag_temp_right;
				}
				map_temporary(instructions_list, p->address_3.value, register_result);
				break;
				case AsvK:

				register_temporary = search_temporary(p->address_1.value);
				memory_position = search_variable(variables_list, p->address_3.name, 0, current_scope);
				format_one(instructions_list, G_ST, register_temporary, memory_position);

				release_temporary(register_temporary);

				break;
				case AsaK:
				register_temporary = search_temporary(p->address_1.value);
				switch (p->address_2.kind) {
					case IntConst:
					memory_offset = p->address_2.value;
					memory_position = search_variable(variables_list, p->address_3.name, memory_offset, current_scope);
					format_one(instructions_list, G_ST, register_temporary, memory_position);
					break;
					case String:

					memory_position = search_variable(variables_list, p->address_2.name, 0, current_scope);
					memory_offset = search_variable(variables_list, p->address_3.name, 0, current_scope);
					format_one(instructions_list, G_LD, register_operator_left, memory_position);
					format_two(instructions_list, G_ADDI, register_operator_left, register_operator_right, memory_offset, "none");
					format_two(instructions_list, G_STR, register_operator_right, register_temporary, 0, "none");

					break;
					case Temp:

					memory_offset = search_variable(variables_list, p->address_3.name, 0, current_scope);
					register_temporary_left = search_temporary(p->address_2.value);
					format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_right, memory_offset, "none");
					format_two(instructions_list, G_STR, register_operator_right, register_temporary, 0, "none");
					release_temporary(register_temporary_left);

					break;
					default:
					break;
				}

				release_temporary(register_temporary);

				break;
				case PrmK:
					par = parameters_list->start;
					type_parameter *new_parameter = malloc(sizeof(type_parameter));
					new_parameter->kind = p->address_3.kind;
					strcpy(new_parameter->scope, current_scope);
					switch (p->address_3.kind) {
						case IntConst:
						case Temp:
							new_parameter->value = p->address_3.value;
							break;
						case String:
							strcpy(new_parameter->name, p->address_3.name);
							break;
						default:
							printf("Unknown parameter kind!\n");
							break;
					}
					if(par==NULL){
						parameters_list->start = new_parameter;
						parameters_list->start->next = NULL;
					}
					else{
						while (par->next!=NULL) {
							par = par->next;
						}
						par->next = new_parameter;
						par->next->next = NULL;
					}
					break;
				case CalK:
						//consume parameters
						consume_parameters(table, instructions_list, parameters_list, variables_list, p->address_3.name);
						// remember in and out
						format_zero(instructions_list, G_JMP, 0, String, p->address_3.name, label_kind);


						//counter is intended to work with various calls for a same function
						counter = 0;
						insert_label(calls_list, String, p->address_3.name, counter, line_counter);

						//map temporary from return
						if (p->address_2.kind==Temp) {
							map_temporary(instructions_list, p->address_2.value, register_return);
						}


					break;

				case EofK:
					break;
				case RetK:

				if(p->address_3.kind!=Empty){
					if (p->address_3.kind==Temp) {
						register_temporary = search_temporary(p->address_3.value);
						format_two(instructions_list, G_ADDI, register_temporary, register_result, 0, "none");
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
					format_two(instructions_list, G_ADDI, register_result, register_return, 0, current_scope);
				}

					format_zero(instructions_list, G_JMP, 0, String, current_scope, call_kind);

				break;
				case IffK:
				register_temporary_left = search_temporary(p->address_1.value);
				// format_one(instructions_list, G_PBC, register_operator_left, 0);
				format_one(instructions_list, G_PBC, register_temporary_left, 0);

				format_zero(instructions_list, G_BOZ, p->address_3.value, LabAddr, "none", label_kind);

				release_temporary(register_temporary_left);
				break;
				case GtoK:
				if (p->address_3.kind==LabAddr) {
					format_zero(instructions_list, G_JMP, p->address_3.value, LabAddr, "none", label_kind);
				}else if(p->address_3.kind==String){
					format_zero(instructions_list, G_JMP, p->address_3.value, String, p->address_3.name, label_kind);
				}else{
					printf("EXCEPTION\n");
				}
				break;
				case HltK:
				break;
				case LblK:

					insert_label(labels_list, p->address_3.kind, p->address_3.name, p->address_3.value, line_counter);

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
							switch (p->address_2.kind) {
								case IntConst:
									memory_position = search_variable(variables_list, p->address_1.name, p->address_2.value, current_scope);
									format_one(instructions_list, G_LD, register_result, memory_position);
									break;
								case String:
								  memory_position = search_variable(variables_list, p->address_1.name, 0, current_scope);
									memory_offset = search_variable(variables_list, p->address_2.name, 0, current_scope);
									format_one(instructions_list, G_LD, register_operator_left, memory_offset);
									format_two(instructions_list, G_ADDI, register_operator_left, register_operator_right, memory_position, "none");
									format_two(instructions_list, G_LDR, register_operator_right, register_result, 0, "none");
									break;
								case Temp:
									memory_position = search_variable(variables_list, p->address_1.name, 0, current_scope);
									register_temporary_left = search_temporary(p->address_2.value);
									format_two(instructions_list, G_ADDI, register_temporary_left, register_operator_left, 0, "none");
									format_two(instructions_list, G_ADDI, register_operator_left, register_operator_right, memory_position, "none");
									format_two(instructions_list, G_LDR, register_operator_right, register_result, 0, "none");
									release_temporary(register_temporary_left);
									break;
								default:
									printf("ASTK Type Problem: %d\n", p->address_2.kind);
									break;
							}

							map_temporary(instructions_list, p->address_3.value, register_result);
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
				list_parameters *parameters_list;
			  list_labels *labels_list;
				list_labels *calls_list;

				variables_list = (list_variables*) malloc(sizeof(list_variables));
				instructions_list = (list_instructions*) malloc(sizeof(list_instructions));
				parameters_list = (list_parameters*) malloc(sizeof(list_parameters));
				labels_list = (list_labels*) malloc(sizeof(list_labels));
				calls_list = (list_labels*) malloc(sizeof(list_labels));

				variables_list->start = NULL;
				instructions_list->start = NULL;
				parameters_list->start = NULL;
				labels_list->start = NULL;
				calls_list->start = NULL;

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
				generate_code(instructions_list, quad_list, table, variables_list, parameters_list, labels_list, calls_list);
				treat_jumps_n_branches(instructions_list, labels_list, calls_list);

				fclose( file_target_code );

				print_variables(variables_list);
				print_instructions(instructions_list);
				print_labels(labels_list);
				// print_parameters(parameters_list);
			}
