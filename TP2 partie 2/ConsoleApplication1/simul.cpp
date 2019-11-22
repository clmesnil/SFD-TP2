   #include "stdafx.h"
#include <iostream>
#include <sstream>
#include"simul.h"
#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;


int tag = 1;

void gerer_entree(T_Entree& E, int date)
{
	E.contenu.entree_date = date;
	E.contenu.sortie_date = -1;
	E.contenu.identifiant = tag;
	tag = tag + 1;
	E.DPE = date + E.DIA;
}

void simuler(int duree_max, int duree_inter_arrivee, int DT1, int DT2, int DT3,
			System::Windows::Forms::RichTextBox^ affichage,
			System::Windows::Forms::DataVisualization::Charting::Chart^ chart1)
{
	int stop, delta;
	int nb_pieces;
	int nb_perdus = 0; //jamais incrémenté
	int temps = 0; // Date de simulation
	int id_piece = 1;
	int res = 0;
	int temps_sejour_total = 0;
	int moyenne_temps_sejour = 0;
	T_File file_1;
	T_File file_2;
	T_File file_3;
	T_Piece P;
	T_Machine Machine_1;
	T_Machine Machine_2;
	T_Machine Machine_3;
	T_Sortie S;
	T_Entree E;
	initialiser_machine(Machine_1, DT1);
	initialiser_machine(Machine_2, DT2);
	initialiser_machine(Machine_3, DT3);
	initialiser_file(file_1);
	initialiser_file(file_2);
	initialiser_file(file_3);
	S.nb = 0;
	E.DPE = 0;
	E.DIA = duree_inter_arrivee;
	
	while (temps < duree_max) {
		if (temps > 15) {
			int u = 0;
		}
		if ((Machine_1.DPE <= E.DPE) && (Machine_1.DPE < Machine_2.DPE))
			res = 2;
		else if ((Machine_2.DPE <= Machine_1.DPE) && (Machine_2.DPE <= E.DPE))
			res = 3;
		else
			res = 1;

		if (res == 1) {										// l'entrée avait la date la plus petite
			temps = E.DPE; //
			gerer_entree(E, temps);//
			P = E.contenu;//

			if (Machine_1.etat == 0) {
				deposer_piece_machine(Machine_1, P, temps);
			}
			else if (est_pleine(file_1))
			{
				nb_perdus++;
				E.etat = 2;
				E.DPE = 9999;
			}
			else // La file n'est pas pleine et M1 est occupée
			{
				P.entree_date = temps;
				deposer_piece_file(file_1, P);
			}
		}
		
		else if (res == 2) {								// Machine 1 avec DPE la plus faible
			temps = Machine_1.DPE;
			P = Machine_1.contenu;
			if (Machine_2.etat == 0) // Machine 2 libre
			{ 
				P.sortie_M1 = temps;
				vider_machine(Machine_1);
				deposer_piece_machine(Machine_2, P, temps);
				if (est_vide(file_1)) {
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else {
					stop = 0;
					while (stop == 0) {
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						if (delta < 30) {
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1)) {
							stop = 2;
						}
					}
					E.etat = 1;
					E.DPE = temps;
				}
			}
			else if (est_pleine(file_2) == 0) {				// File 2 n'est pas pleine
				P.sortie_M1 = temps;
				deposer_piece_file(file_2, P);
				if (est_vide(file_1)) {
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else {
					stop = 0;
					while (stop == 0) {
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						if (delta < 30) {
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1)) {
							stop = 2;
						}
					}
					E.etat = 1;
					E.DPE = temps;
				}	
			}
			else {											// File 2 pleine
				Machine_1.etat = 2; // Machine 1 bloquée
				Machine_1.DPE = 9999;
			}
		}

		else if (res == 3) { // la machine M2 avec la date la plus petite
			temps = Machine_2.DPE;
			P = Machine_2.contenu;
			deposer_piece_sortie(S, P, affichage, temps);
			if (est_vide(file_2))
			{
				vider_machine(Machine_2);
			}
			else
			{
				T_Piece Nouv_Piece;
				Nouv_Piece = retirer_piece(file_2);
				deposer_piece_machine(Machine_2, Nouv_Piece, temps);
				if (Machine_1.etat == 2) {
					Machine_1.etat = 1;
					Machine_1.DPE = temps;
				}
			}
			temps_sejour_total += P.sortie_date - P.entree_date;
			nb_pieces++;
		}
	}


	//affichage->Refresh();
	
	moyenne_temps_sejour = temps_sejour_total / nb_pieces;
	System::String^ moy = "Moyenne du temps de séjour: " + transformer_int_string(moyenne_temps_sejour);
	affichage->AppendText(moy);
	affichage->Refresh();

	/*
	int j = 2;
	int i = 1;
	System::String^ mm = transformer_int_string(i);
	System::String^ k = transformer_int_string(j);

	System::String^ l = k + " " + mm;
	affichage->Text = l;
	affichage->Refresh();*/

	//affichage->AppendText("Ca fonctionne un peu (pas trop)");

	//affichage du premier graphe

	int x = 0;
	while (x < nb_pieces)
	{
		float y = S.L[x].entree_date;
		chart1->Series[0]->Points->AddXY(y, x);
		x = x + 1;
	}

	int x2 = 0;
	while (x2 < nb_pieces)
	{
		float y2 = S.L[x2].sortie_date;
		chart1->Series[0]->Points->AddXY(y2,x2);
		x2 = x2 + 1;
	}

}


void initialiser_machine(T_Machine& Machine, int DT) {
	Machine.etat = 0;
	Machine.DPE = 99999;
	Machine.duree_traitement = DT;
}


System::String^ transformer_int_string(int var) {

	std::stringstream chaine_res;
	chaine_res << var;
	std::string chaine_res_string = chaine_res.str();

	System::String^ s_nb_res = marshal_as<String^>(chaine_res_string);
	return s_nb_res;
}


int est_vide(T_File file) // 1 si vide
{
	return(file.debut==file.fin);
}


int est_pleine(T_File file) // 1 si pleine
{
	return (file.debut==(file.fin)%10 +1);
}


void deposer_piece_file(T_File &file, T_Piece P)
{
	if (!est_pleine(file))
	{
		file.L[file.fin] = P;
		file.fin = (file.fin) % 10 + 1;
	}
}

void deposer_piece_machine(T_Machine & M, T_Piece P, int date_simulation)
{
	M.contenu = P;
	M.DPE = date_simulation + M.duree_traitement;
	M.etat = 1;
}

void deposer_piece_sortie(T_Sortie & S, T_Piece & P, System::Windows::Forms::RichTextBox^ affichage, int date_simulation)
{
	P.sortie_date = date_simulation;
	S.nb++;
	S.L[S.nb] = P;
	System::String^ a = transformer_int_string(P.identifiant);
	System::String^ b = transformer_int_string(P.entree_date);
	System::String^ c = transformer_int_string(P.sortie_date);
	System::String^ e = transformer_int_string(P.sortie_M1);
	System::String^ d = a + " \t " + b + " \t " + e + " \t " + c + "\n";

	affichage->AppendText(d);

}


T_Piece retirer_piece(T_File & file)
{
	T_Piece retour;
	if (!est_vide(file))
	{
		retour = file.L[file.debut];
		file.debut = (file.debut) % 10 + 1;
		return (retour);
	}
}


void initialiser_file(T_File & file)
{
	file.debut = 4;
	file.fin = 4;
}


void vider_machine(T_Machine & M)
{
	M.etat = 0;
	M.DPE = 99999;
}

int generer_prochaine_etape(T_Piece & p,int etape_actuelle) { //renvoie le numéro de l'étape suivante que doit traverser la pièce
	int proc_etape;
	if (etape_actuelle == 1) {
		proc_etape = 2;
	}
	else { //on doit tester si la piece reste dans le système ou sort vers la sortie
		
	}
	return proc_etape;
}

void choisir_machine_etape(T_Piece& p, int etape) { //donne à la piece le numéro de la prochaine machine qu'elle doit traverser dans l'étape donnée
	int temp;
	if (etape == 2) {
	}
}


int bernoulli(float p)
{
	srand(time(NULL));
	int retour = 0, max_nb = 100000;
	float nb = (rand() % max_nb) / max_nb;
	if (nb < p)
	{
		retour = 1;
	}
	return retour;
}