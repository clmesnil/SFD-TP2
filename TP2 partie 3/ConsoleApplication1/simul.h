#pragma once
#ifndef SIMUL_H
#define SIMUL_H

#include <msclr\marshal_cppstd.h>
#include <sstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace msclr::interop;


// Définitions des structures

typedef struct T_Piece {
	int entree_date;
	int sortie_date;
	int identifiant;
	int sortie_M1 = -1;
	bool complete = false;
}T_Piece;

typedef struct T_File {
	T_Piece L[11];
	int debut;
	int fin;
}T_File;

typedef struct T_Machine {
	int etat; // 0 = machine vide , 1 = occupée, 2 = bloquée/en attente
	int duree_traitement;
	T_Piece contenu;
	int DPE; // Date prochain événement
}T_Machine;

typedef struct T_Assembleur {
	int etat; // 0 = machine vide , 1 = machine non vide, 2 = bloquée
	int duree_traitement;
	T_Piece contenu1;
	T_Piece contenu2;
	int DPE; // Date prochain événement
}T_Assembleur;

typedef struct T_Entree {
	int DIA; // Date inter-arrivée
	int DPE; // Date prochain événement
	int numero_P_courante;
	T_Piece contenu;
	int etat;
}T_Entree;

typedef struct T_Sortie {
	T_Piece L[10000];
	int nb;
}T_Sortie;

// Prototypes des fonctions


T_Piece retirer_piece(T_File& file);
System::String^ transformer_int_string(int);
void deposer_piece_file(T_File &file,T_Piece);
void deposer_piece_machine(T_Machine &M, T_Piece P, int date_simulation);
void deposer_piece_sortie(T_Sortie& S, T_Piece& P, System::Windows::Forms::RichTextBox^ affichage, int date_simulation);
void initialiser_file(T_File &file);
void vider_machine(T_Machine & M);

void simuler(int duree_max, int duree_inter_arrivee1, int duree_inter_arrivee2, int DT1, int DT2, int DTA,
	System::Windows::Forms::RichTextBox^ affichage,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1);

int est_vide(T_File file);
int est_pleine(T_File file);
void initialiser_machine(T_Machine& Machine, int DT);
int calcul_DPE(int Entree1, int Entree2, int M1, int M2, int Assemblage);
#endif