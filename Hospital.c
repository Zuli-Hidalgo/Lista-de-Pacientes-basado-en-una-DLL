#include<stdio.h>
/*Para printf y scanf*/
#include<stdlib.h>
/*Para malloc y demás*/
#include<stdbool.h>
/*Para funciones booleanas*/
#include<assert.h>
/*Para funcion assert()*/
#include<string.h>
//para cadenas de caracteres


/*Se crea la estructura donde irá la información del paciente*/
typedef struct {
	char nombre[40];
	char paterno[20];
	char materno [20];
	int edad;
	char sexo[15];
}Paciente;

/*Creamos la estructura nodo donde se guardardará la información*/
typedef struct Node{
	Paciente* paciente;
	struct Node* next;
	struct Node* prev;
}Node;

/*Creamos la estructura de la DLL*/
typedef struct{
	struct Node* first;
	struct Node* last;
	struct Node* cursor;
	int cont;
}DLL;

/*Creación e inicialización del nodo*/
static Node* newNode(Paciente* x)
 {
 	Node* n = (Node*) malloc(sizeof(Node));
 	if (NULL==n)exit(1);
 	n->paciente=x;
 	n->next=NULL;
 	n->prev=NULL;
 
 	return n;
 }
 
 
/*_-_-_-_-_-_-__-_-_-_-_-_-_-_-_-_-_-_-_-_-_DECLARACION DE FUNCIONES DE LA DLL _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-__-_-_-_-_-_*/
	
/*Crear a la DLL*/  
DLL* DLL_New();										
/*Liberar la memoria de la DLL*/ 
void DLL_Delete( DLL* this );
/*Insertar un elemento en la DLL*/ 
bool DLL_Insert( DLL* this, Paciente* x );
/*Insertar un elemento de lado derecho de cursor*/ 
bool DLL_InsertNext( DLL* this, Paciente* );
/*Insertar un elemento de lado izquierdo de cursor*/ 
bool DLL_InsertPrev( DLL* this, Paciente* );
/*Quita el primer elemento de la lista*/ 
bool DLL_Remove( DLL* this/*, int* value*/ );
/*quita el elemento apuntado por cursor*/ 
bool DLL_RemoveAt( DLL* this/*, int* value*/ );
/*Muestra el contenido apuntado por cursor*/ 
Paciente* DLL_Get( DLL* this );
/*Manda a cursor al primero elemento*/ 
void DLL_CursorHome( DLL* this );
/*manda al cursor al último elemento*/ 
void DLL_CursorEnd( DLL* this );
/*mueve al cursor a la derecha un elemento*/ 
void DLL_CursorNext( DLL* this );
/*mueve al cursor a la izquierda un elemento*/ 
void DLL_CursorPrev( DLL* this );
//si encontró una coincidencia, entonces coloca al “cursor” en esa posición y devuelve true.
//false en cualquier otro caso.
bool DLL_Find(DLL* this, char* nombre, char* paterno, char* materno, int edad);
// devuelve true si encontró al menos una coincidencia. false en cualquier otro caso.
bool DLL_FindIf(DLL* this, char* nombre, char* paterno, char* materno, int edad);
//Saber si la lista está vacío
bool DLL_IsEmpty( DLL* this);
//Vacia la lista
void DLL_MakeEmpty( DLL* this);


/*_-_-_-_-_-_-__-_-_-_-_-_-_-_-_-_-_-_-_-_-_DECLARACION DE FUNCIONES DEL PACIENTE  _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-__-_-_-_-_-_*/
/*Aparte memoria para la información del paciente*/
Paciente* Paciente_New();
/*Elimina un paciente*/
void Paciente_Delete(Paciente* this);
/*Agrega el nombre del paciente*/
void Paciente_Nombre(Paciente* this, char* nombre);
/*Agrega el apellido paterno del paciente*/
void Paciente_Paterno(Paciente* this, char* paterno);
/*Agrega el apellido materno del paciente*/
void Paciente_Materno(Paciente* this, char* materno);
/*Agrega la edad del paciente*/
void Paciente_Edad(Paciente* this, int n);
/*Agrega el sexo del paciente*/
void Paciente_Sexo(Paciente* this, char* fom);

/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_FUNCION PARA IMPRESIÓN E INTERACCIÓN CON ESTRUCTURA PACIENTE-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

/*Se agrega un nuevo paciente a la lista*/
void Agregar_Paciente(Paciente* this);
/*Se busca un paciente existente en la lista*/
void Buscar_Paciente(DLL* this);
/*Se imprimen los pacientes femeninos de la lista*/
void Imprimir_Femenino(DLL* this);
/*Se imprimen los pacientes masculinos de la lista*/
void Imprimir_Masculino(DLL* this);
/*Se imprimen los pacientes por una edad señalada por el usuario*/
void Imprimir_PorEdad(DLL* this, int n);
/*Se imprimen todos los pacientes*/
void Imprimir_Pacientes(DLL* this);
/*Se da de alta al paciente*/
void Paciente_Alta(DLL* this);

/*_-_-_-_-_-_-__-_-_-_-_-_-_-_-_-_-_-_-_-_-_FUNCIONES DEL PACIENTE  _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-__-_-_-_-_-_*/

/*Aparta memoria para la información del paciente*/
Paciente* Paciente_New(){

	Paciente* p = (Paciente*) malloc(sizeof(Paciente));
	if (p==NULL)exit(1);
	p->edad=0;
	strncpy(p->nombre,"  ", 40);
	strncpy(p->paterno,"  ", 20);
	strncpy(p->materno,"  ", 20);
	strncpy(p->sexo,"  ", 15);
	
	return p;
}
//Elimina la informacion del paciente y devuelve la memoria
void Paciente_Delete(Paciente* this)
{
	assert(this);
	free(this);
	this=NULL;
	
}
/*Agrega el nombre del paciente*/
void Paciente_Nombre(Paciente* this, char* nombre){
	assert(this);
	strncpy(this->nombre, nombre, 40);
}
/*Agrega el apellido paterno del paciente*/
void Paciente_Paterno(Paciente* this, char* paterno){
	assert(this);
	strncpy(this->paterno, paterno, 20);
}
/*Agrega el apellido materno del paciente*/
void Paciente_Materno(Paciente* this, char* materno){
	assert(this);
	strncpy(this->materno, materno, 20);
}
/*Agrega el sexo del paciente*/
void Paciente_Sexo(Paciente* this, char* sexo){
	assert(this);
	strncpy(this->sexo, sexo, 20);
}

/*Agrega la edad del paciente*/
void Paciente_Edad(Paciente* this, int n){
	assert(this);
	this->edad=n;
}



/*_-_-_-_-_-_-__-_-_-_-_-_-_-_-_-_-_-_-_-_-_FUNCIONES DE LA DLL _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-__-_-_-_-_-_*/

/*Crear a la DLL*/  
DLL* DLL_New()
{
	DLL* miLista = (DLL*) malloc(sizeof(DLL));
	if (NULL==miLista){
	return NULL;}
	miLista->first=NULL;
	miLista->last=NULL;
	miLista->cursor=NULL;
	miLista->cont=0;
	
	return miLista; 
}
/*Liberar la memoria de la DLL*/ 
void DLL_Delete( DLL* this )
{
		if(NULL==this)return;
	//Evitamos borrar la lista varias veces
	
	while (this->cont>0){
		Node* tmp = this->first->next;
		Paciente_Delete(this->first->paciente);
		free(this->first);
		this->first=tmp;
		--this->cont;
	}
	//Destruimos la lista
	free(this);
	this=NULL;
}
/*Insertar un elemento en la DLL*/ 
bool DLL_Insert( DLL* this, Paciente* x )
{

	assert(this);
	Node* n = newNode(x);
	if (NULL!=n)
	{
    	if(this->cont == 0)
		{
		this->first=n;
		this->last=n;
		this->cursor=n;
	    
		}
	else
	{
		this->last->next=n;
		n->prev=this->last;
		this->last=n;
	}
	++this->cont;
	return true; 
	}
	else return false;
}
/*Insertar un elemento de lado derecho de cursor*/ 
bool DLL_InsertNext( DLL* this, Paciente* x )
{
	assert(this);
	
	if (this->cont==0)
	{
		DLL_Insert(this, x);
	}
	else if (this->cursor==this->last)
	{
		DLL_Insert(this, x);
		}
	else
	{
		Node* n = newNode(x);
		if (NULL!=n){
		Node* tmp= this->cursor->next;
		this->cursor->next=n;
		n->next=tmp;
		n->prev=this->cursor;
		tmp->prev=n;
		this->cursor=n;
		++this->cont;
		}
		else return false;
	}
	return true;
}
/*Insertar un elemento de lado izquierdo de cursor*/
bool DLL_InsertPrev( DLL* this, Paciente* x )
{
	assert(this);
	 
	if (this->cont==0){
		DLL_Insert(this,x);
	}
	else if (this->cursor==this->first){
		Node* n = newNode(x);
		if (NULL!=n){
		n->next=this->cursor;
		n->prev=NULL;
		this->cursor->prev=n;
		this->first=n;
		this->cursor=n;
		++this->cont;
		}
		else return false;
	}
	else{
		Node* n= newNode(x);
		if (NULL!=n){
		Node* tmp = this->cursor->prev;
		tmp->next=n;
		n->prev=tmp;
		n->next=this->cursor;
		this->cursor->prev=n;
		this->cursor=n;
		++this->cont;
		}
		else return false;
	}
	
	return true;
}
/*Quita el primer elemento de la lista*/ 
bool DLL_Remove( DLL* this/*, int* value*/ )
{
	assert(this);
	
	if (this->cont==0){
/*here*/return false;
	}
	if (this->cont==1)
	{
		Paciente_Delete(this->first->paciente);
		free(this->first);
		this->first=NULL;
		this->last=NULL;
		this->cursor=NULL;
		--this->cont;
	}
	else
	{
		Node* tmp = this->first->next;
		Paciente_Delete(this->first->paciente);
		free(this->first);
		this->first=tmp;
		this->first->prev=NULL;
		--this->cont;
	} 
	return true;
}
/*quita el elemento apuntado por cursor*/ 
bool DLL_RemoveAt( DLL* this/*, int* value*/ )
{
	assert(this);
	
	if(this->cursor==this->first)
	{
	
		DLL_Remove(this);
		this->cursor=this->first;
	}
	else if (this->cursor==this->last)
	{
		Node* tmp = this->cursor->prev;
		Paciente_Delete(this->cursor->paciente);
		free(this->cursor);
		this->last=tmp;
		this->cursor=tmp;
		this->cursor->next=NULL;
		--this->cont;
	}
	else if (this->cont==1)
	{
		Paciente_Delete(this->cursor->paciente);
		free(this->cursor);
		this->first=NULL;
		this->last=NULL;
		this->cursor=NULL;
		--this->cont;
	}
	else
	{
		Node* tmpPrev = this->cursor->prev;
		Node* tmpNext = this->cursor->next;
		Paciente_Delete(this->cursor->paciente);
		free(this->cursor);
		tmpPrev->next=tmpNext;
		tmpNext->prev=tmpPrev;
		this->cursor=tmpNext;
		--this->cont;
	}
	
	return true;
	
}
/*Muestra el contenido apuntado por cursor*/ 
Paciente* DLL_Get( DLL* this )
{
	assert(this);
	
	if (this->cont==0)return 0;
	else{
	return this->cursor->paciente;
	}
}
int DLL_Element(DLL* this)
{
	assert(this);
	return this->cont;
}
/*Manda a cursor al primero elemento*/
void DLL_CursorHome( DLL* this )
{
	assert(this);
	if(this->cursor==this->first)return;
	this->cursor=this->first; 
}
/*manda al cursor al último elemento*/ 
void DLL_CursorEnd( DLL* this )
{	
	assert(this);
	if(this->cursor==this->last)return;
	this->cursor=this->last;
	 
}
/*mueve al cursor a la derecha un elemento*/ 
void DLL_CursorNext( DLL* this )
{
	assert(this); 
	if (this->cursor==this->last)return;
	this->cursor=this->cursor->next;
}
/*mueve al cursor a la izquierda un elemento*/ 
void DLL_CursorPrev( DLL* this )
{
	assert(this);
	if(this->cursor==this->first)return;
	this->cursor=this->cursor->prev; 
}
//Saber si la lista está vacía
bool DLL_IsEmpty( DLL* this )
{		
	assert(this);
	if (this->cont!=0)return false;
	else return true;
}
//Vacia la lista
void DLL_MakeEmpty( DLL* this )
{
	assert(this);
	if (DLL_IsEmpty (this)) return;
	
	while (this->first!=this->last)
	{
		Node* tmp = this->first->next;
		Paciente_Delete(this->first->paciente);
		free(this->first);
		this->first=tmp;
		--this->cont;
	}
	free(this->first);
	this->first=NULL;
	this->last=NULL,
	this->cursor=NULL;
	--this->cont;	 
}

//si encontró una coincidencia, entonces coloca al “cursor” en esa posición y devuelve true.
//false en cualquier otro caso.
bool DLL_Find(DLL* this, char* nombre, char* paterno, char* materno, int edad)
{
assert (this);

Node* it = this->first;
// NO PODEMOS PERDER A FIRST !!!
while (it != NULL)
{
	//Se hace la comparación de la información con la ingresada para hacer la búsqueda
if (strcmp(it->paciente->nombre, nombre)==0) 
			{
				if (strcmp(it->paciente->paterno, paterno)==0)
				{
					if (strcmp(it->paciente->materno, materno)==0)
					{	
						if (it->paciente->edad == edad)
						{			
							this->cursor=it;
							return true;
						}
						else return false;
					}
				else return false;
				}
			else return false;
			}
else {
		it = it->next;
	 }
}
return false;
}
// devuelve true si encontró al menos una coincidencia. false en cualquier otro caso.
bool DLL_FindIf (DLL* this, char* nombre, char* paterno, char* materno, int edad)
{
	
assert (this);

Node* it = this->first;
// NO PODEMOS PERDER A FIRST !!!
while (it != NULL)
{
if (strcmp(it->paciente->nombre, nombre)==0) 
			{
				if (strcmp(it->paciente->paterno, paterno)==0)
				{
					if (strcmp(it->paciente->materno, materno)==0)
					{	
						if (it->paciente->edad == edad)
						{			
							return true;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
else {
		it = it->next;
	 }
}
return false;
}

/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_FUNCION PARA IMPRESIÓN E INTERACCIÓN CON ESTRUCTURA PACIENTE-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

//Esta función agregará un nuevo paciente
void Agregar_Paciente(Paciente* this)
{
	
	assert (this);
	char nombre[40], paterno[20], materno[40], sexo[15];
	int edad;
	printf("Indique el apellido paterno\n");
	scanf("%s", paterno);
	printf("Indique el apellido materno\n");
	scanf("%s", materno);
	printf("Indique el nombre (en caso de tener dos nombre separar por medio de un guión)\n");
	scanf("%s", nombre);
	printf("Indique el sexo [Femenino/Masculino]\n");
	scanf("%s", sexo);
	printf("Indique la edad (únicamente escribir dígitos)\n");
	scanf("%d", &edad);
	//En las siguientes funciones se agrga la información a la estructura Paciente
	Paciente_Nombre(this, nombre);
	Paciente_Paterno(this, paterno);
	Paciente_Materno(this, materno);
	Paciente_Sexo(this, sexo);
	Paciente_Edad(this, edad);
 	
} 
//Esta función buscará un paciente indicado por el usuario e imprimirá sus datos 
void Buscar_Paciente(DLL* this)
{
	assert (this);
	if (this->cont==0)return;
	char nombre[40], paterno[20], materno[40];
	int edad;
	printf("Indique el apellido paterno\n");
	scanf("%s", paterno);
	printf("Indique el apellido materno\n");
	scanf("%s", materno);
	printf("Indique el nombre (en caso de tener dos nombre separar por medio de un guión)\n");
	scanf("%s", nombre);
	printf("Indique la edad (únicamente escribir dígitos)\n");
	scanf("%d", &edad);
	//Busca la información para comparar información
	if(DLL_Find(this, nombre, paterno, materno, edad)==true)
	{
		printf("Se encontró al paciente:\nNombre: %s %s %s\nSexo: %s\nEdad: %d años\n", this->cursor->paciente->paterno, this->cursor->paciente->materno, this->cursor->paciente->nombre,this->cursor->paciente->sexo,  this->cursor->paciente->edad );
	}
	else
	{
		printf("No se encontró\n");
	}
	
}
/*Se imprimen los pacientes femeninos de la lista*/
void Imprimir_Femenino(DLL* this)
{
	assert(this);
	Node* it = this->first;
	while(it != NULL)
	{
		if(strcmp(it->paciente->sexo, "Femenino")==0||strcmp(it->paciente->sexo, "femenino")==0||strcmp(it->paciente->sexo, "mujer")==0||strcmp(it->paciente->sexo, "Mujer")==0)
		{
			printf("Nombre: %s %s %s\nSexo: %s\nEdad: %d años\n", it->paciente->paterno, it->paciente->materno, it->paciente->nombre,it->paciente->sexo,  it->paciente->edad ); 	
		}
	it = it->next;	
	}
	return;
}
/*Se imprimen los pacientes masculinos de la lista*/
void Imprimir_Masculino(DLL* this)
{
	assert(this);
	Node* it = this->first;
	while(it != NULL)
	{
		if(strcmp(it->paciente->sexo, "Masculino")==0||strcmp(it->paciente->sexo, "masculino")==0||strcmp(it->paciente->sexo, "hombre")==0||strcmp(it->paciente->sexo, "Hombre")==0)
		{
			printf("Nombre: %s %s %s\nSexo: %s\nEdad: %d años\n", it->paciente->paterno, it->paciente->materno, it->paciente->nombre,it->paciente->sexo,  it->paciente->edad ); 	
		}
	it = it->next;	
	}
	return;
}
/*Se imprimen los pacientes por una edad señalada por el usuario*/
void Imprimir_PorEdad(DLL* this, int n)
{
	assert(this);
	Node* it = this->first;
	while(it != NULL)
	{
		if(it->paciente->edad==n)
		{
			printf("Nombre: %s %s %s\nSexo: %s\nEdad: %d años\n", it->paciente->paterno, it->paciente->materno, it->paciente->nombre,it->paciente->sexo,  it->paciente->edad ); 	
		}
	it = it->next;	
	}
	return;
}
/*Se imprimen todos los pacientes*/
void Imprimir_Pacientes(DLL* this)
{
	assert(this);
	Node* it = this->first;
	while(it != NULL)
	{
		printf("Nombre: %s %s %s\nSexo: %s\nEdad: %d años\n", it->paciente->paterno, it->paciente->materno, it->paciente->nombre,it->paciente->sexo,  it->paciente->edad ); 	
	
	it = it->next;	
	}
	return;
}
/*Se da de alta al paciente, se libera su memoria*/
void Paciente_Alta(DLL* this)
{
	assert(this);
	char nombre[40], paterno[20], materno[40]; int edad;
	printf("Escribir la información del paciente a dar de alta\n");
	printf("Indique el apellido paterno\n");
	scanf("%s", paterno);
	printf("Indique el apellido materno\n");
	scanf("%s", materno);
	printf("Indique el nombre (en caso de tener dos nombre separar por medio de un guión)\n");
	scanf("%s", nombre);
	printf("Indique la edad (únicamente escribir dígitos) \n");
	scanf("%d", &edad);
	
	if (DLL_Find(this, nombre, paterno, materno, edad)==true)
	{
		DLL_RemoveAt(this);
		printf("Se eliminó el registro del paciente\n");
	}
	else printf("Falló la alta del paciente\n");
	
}
//Eliminar la información y regresar la memoria
void Eliminar_Lista(DLL* this)
{
	
	assert(this);
	if(this->cont!=0)
	{
	//Si la lista tiene elementos primero libera su memoria
	DLL_MakeEmpty(this); 	
	}
	DLL_Delete(this);

}
 

int Menu()
{	
	printf("¿Qué desea hacer?\n");
	printf("0) Eliminar y liberar memoria de la lista\n");
	printf("1) Agregar un nuevo paciente\n");
	printf("2) Buscar paciente por datos e imprimir nombre y edad\n");
	printf("3) Imprimir pacientes por sexo \n");
	printf("4) Imprimir pacientes por edad\n");
	printf("5) Número total de pacientes \n");
	printf("6) Imprimir todos los pacientes\n");
	printf("7) Dar de alta a un paciente \n");
	
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_DRIVER PROGRAM-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/


int main()
{
	//SE CREA LA LISTA
	DLL* Lista = DLL_New();
	//Funcion para la interacción con los pacientes
	printf("Para ingresar a las funciones usted deberá escribir el número del inciso que desea realizar\n\n");	
	while(1)
	{
	int opcion = Menu();
		
	switch(opcion)
	{
		case 0:
				Eliminar_Lista(Lista);
				printf("Se eliminaron todos los registros\n");
				exit(1);	
		break;	
		
		case 1: {
				Paciente* paciente=Paciente_New();
				Agregar_Paciente(paciente);
				if(DLL_Insert(Lista, paciente)==true)printf("Se agregó al paciente\n");
				else printf("Falló el registro, intente nuevamente");
				}

		break;	
	
		case 2:
				Buscar_Paciente(Lista);
		break;
		
		case 3:
		{	   int res;
		       printf("Presione '1' para mostrar pacientes femeninos o '2' para pacientes masculinos\n");
		       scanf("%d", &res);
		       if (res==1)
			   {
			   Imprimir_Femenino(Lista);  		
		       }
		       if(res==2)
			   {
			   Imprimir_Masculino(Lista);
		       }
		}
		break;
		case 4:
		{
				int n;
				printf("Ingrese la edad a buscar\n");
				scanf("%d", &n);
				Imprimir_PorEdad(Lista, n);
					
		}
		break;
		
		case 5: printf("Existen %d pacientes en el hospital\n", DLL_Element(Lista));
				
		break;
		
		case 6: Imprimir_Pacientes(Lista);
			    
		break;
		
		case 7: 
				Paciente_Alta(Lista);
		break;		  			
	}
}
	}

