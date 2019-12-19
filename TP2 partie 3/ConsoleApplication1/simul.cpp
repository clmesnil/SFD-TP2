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

int calcul_DPE(int Entree1, int Entree2, int M1, int M2, int Assemblage)//pire fonction ever seen by chabrol => instant reported by chabrol
{

	std::cout << "Entree1 = " << Entree1 << "\tEntree2 = " << Entree2 << "\tM1 = " << M1 << "\tM2 = " << M2 << "\tAssemblage = " << Assemblage << std::endl;

	int min1 = 0, min2 = 0, min3 = 0, minimum = 0;
	int retour = -1;
	min1 = min(Entree1, Entree2);
	min2 = min(min1, M1);
	min3 = min(min2, M2);
	minimum = min(Assemblage, min3);
	if (minimum == Entree1)
	{
		retour = 1;
	}
	else if (minimum == Entree2)
	{
		retour = 2;
	}
	else if (minimum == M1)
	{
		retour = 3;
	}
	else if (minimum == M2)
	{
		retour = 4;
	}
	else if (minimum == Assemblage)
	{
		retour = 5;
	}
	
	return retour;
}

void simuler(int duree_max, int duree_inter_arrivee1, int duree_inter_arrivee2, int DT1, int DT2, int DTA,
			System::Windows::Forms::RichTextBox^ affichage,
			System::Windows::Forms::DataVisualization::Charting::Chart^ chart1)
{
	int stop, delta;
	int nb_pieces;
	int nb_perdus = 0;
	int temps = 0; // Date de simulation
	int id_piece = 1;
	int res = 0;
	int temps_sejour_total = 0;
	int moyenne_temps_sejour = 0;

	T_File file_1;
	T_File file_2;
	T_Piece P;

	T_Machine Machine_1;
	T_Machine Machine_2;
	T_Machine Assemblage;

	T_Sortie S;
	T_Entree E1;
	T_Entree E2;

	initialiser_machine(Machine_1, DT1);
	initialiser_machine(Machine_2, DT2);
	initialiser_machine(Assemblage, DTA);

	initialiser_file(file_1);
	initialiser_file(file_2);

	S.nb = 0;
	E1.DPE = 0;
	E2.DPE = 0;
	E1.DIA = duree_inter_arrivee1;
	E2.DIA = duree_inter_arrivee2;
	std::cout << "DIA1 = " << duree_inter_arrivee1 << "\tDIA2 = " << duree_inter_arrivee2 << "\tDT1 = " << DT1 << "\tDT2 = " << DT2 << "\tDA = " << DTA << std::endl<<std::endl;
	while (temps < duree_max) {
		
					   
		
		res = calcul_DPE(E1.DPE, E2.DPE, Machine_1.DPE, Machine_2.DPE, Assemblage.DPE);




		if (res == 1)						// l'entrée 1 avait la date la plus petite
		{										
			std::cout << "res = 1" << std::endl;
			temps = E1.DPE; //
			std::cout << "temps = " << temps << std::endl << std::endl << std::endl;
			gerer_entree(E1, temps);//
			P = E1.contenu;//

			if (Machine_1.etat == 0) {
				deposer_piece_machine(Machine_1, P, temps);
			}
			else if (est_pleine(file_1))
			{
				nb_perdus++;
				E1.etat = 2;
				E1.DPE = 9999;
			}
			else // La file n'est pas pleine et M1 est occupée
			{
				P.entree_date = temps;
				deposer_piece_file(file_1, P);
			}
		}



		else if (res == 2)					// l'entrée 2 avait la date la plus petite
		{									
			std::cout << "res = 2" << std::endl;
			temps = E2.DPE; //
			std::cout << "temps = " << temps << std::endl << std::endl << std::endl;
			gerer_entree(E2, temps);//
			P = E2.contenu;//

			if (Machine_2.etat == 0) {
				deposer_piece_machine(Machine_2, P, temps);
			}
			else if (est_pleine(file_2))
			{
				nb_perdus++;
				E2.etat = 2;
				E2.DPE = 9999;
			}
			else // La file n'est pas pleine et M1 est occupée
			{
				P.entree_date = temps;
				deposer_piece_file(file_2, P);
			}
		}



		else if (res == 3) {								// Machine 1 avec DPE la plus faible
			std::cout << "res = 3" << std::endl;
			temps = Machine_1.DPE;
			std::cout << "temps = " << temps << std::endl << std::endl << std::endl;
			P = Machine_1.contenu;
			if ((Machine_2.etat == 2) && (Assemblage.etat == 0)) //Assemblage libre et autre pièce rdy
			{ 
				P.sortie_M1 = temps;
				vider_machine(Machine_1);
				vider_machine(Machine_2);
				deposer_piece_machine(Assemblage, P, temps);


				if (est_vide(file_1))  //on redémarre la file 1 (ne pas oublier de redémarrer la file 2 !!
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else 
				{
					if (est_pleine(file_1)) 
					{
						E1.etat = 1;
						E1.DPE = temps;
					}
					P = retirer_piece(file_1);
					deposer_piece_machine(Machine_1, P, temps);
				}


				if (est_vide(file_2)) // on redémarre la file 2
				{
					Machine_2.etat = 0;
					Machine_2.DPE = 9999;
				}
				else
				{
					if (est_pleine(file_2))
					{
						E2.etat = 1;
						E2.DPE = temps;
					}
					P = retirer_piece(file_2);
					deposer_piece_machine(Machine_2, P, temps);
				}
			}

			else 
			{
				Machine_1.etat = 2; // Machine 1 bloquée
				Machine_1.DPE = 9999;
			}
		}





		else if (res == 4) {								// Machine 2 avec DPE la plus faible
			std::cout << "res = 4" << std::endl;
			temps = Machine_2.DPE;
			std::cout << "temps = " << temps << std::endl << std::endl << std::endl;
			P = Machine_2.contenu;
			if ((Machine_1.etat == 2) && (Assemblage.etat == 0)) //Assemblage libre et autre pièce rdy
			{
				P.sortie_M1 = temps;
				vider_machine(Machine_2);
				vider_machine(Machine_1); 
				deposer_piece_machine(Assemblage, P, temps);


				if (est_vide(file_2)) // on redémarre la file 2 
				{
					Machine_2.etat = 0;
					Machine_2.DPE = 9999;
				}
				else 
				{
					if (est_pleine(file_2)) 
					{
						E2.etat = 1;
						E2.DPE = temps;
					}
					P = retirer_piece(file_2);
					deposer_piece_machine(Machine_2, P, temps);
				}


				if (est_vide(file_1))  //on redémarre la file 1 
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else
				{
					if (est_pleine(file_1))
					{
						E1.etat = 1;
						E1.DPE = temps;
					}
					P = retirer_piece(file_1);
					deposer_piece_machine(Machine_1, P, temps);
				}
			}

			else {
				Machine_2.etat = 2; // Machine 2 bloquée
				Machine_2.DPE = 9999;
			}
		}


		else if (res == 5) {					// la machine Assemblage avec la date la plus petite
		std::cout << "res = 5" << std::endl;
			temps = Assemblage.DPE;
			std::cout << "temps = " << temps << std::endl << std::endl << std::endl;
			P = Assemblage.contenu;
			deposer_piece_sortie(S, P, affichage, temps);

			vider_machine(Assemblage);

			temps_sejour_total += P.sortie_date - P.entree_date;
			nb_pieces++;

			//remettre en service les machines qui attendaient:
			
			std::cout << "machine1.etat : " << Machine_1.etat << "machine2.etat : " << Machine_2.etat << std::endl;

			if (Machine_1.etat == 2) //si la machine est bloquée on la déploque
			{
				Machine_1.etat = 1;
				Machine_1.DPE = temps;
			}

			if (Machine_2.etat == 2) //si la machine est bloquée on la déploque
			{
				Machine_2.etat = 1;
				Machine_2.DPE = temps;
			}
		}
	}
	std::cout << "C FINI" << std::endl;


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

void initialiser_assembleur(T_Assembleur& Assembleur, int DT) {
	Assembleur.etat = 0;
	Assembleur.DPE = 99999;
	Assembleur.duree_traitement = DT;
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

void deposer_piece_machine(T_Machine& M, T_Piece P, int date_simulation)
{
	M.contenu = P;
	M.DPE = date_simulation + M.duree_traitement;
	M.etat = 1;
}

void deposer_piece_assembleur(T_Assembleur A, T_Piece P1, T_Piece P2, int date_simulation)
{
	A.contenu1 = P1;
	A.contenu2 = P2;
	A.DPE = date_simulation + A.duree_traitement;
	A.etat = 1;
}

void deposer_piece_sortie(T_Sortie& S, T_Piece& P, System::Windows::Forms::RichTextBox^ affichage, int date_simulation)
{
	P.sortie_date = date_simulation;
	S.nb++;
	S.L[S.nb] = P;
	System::String^ a = transformer_int_string(P.identifiant);
	System::String^ b = transformer_int_string(P.entree_date);
	System::String^ c = transformer_int_string(P.sortie_date);
	System::String^ d = a + " \t " + b + " \t " + c + "\n";

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

void vider_assembleur(T_Assembleur & A)
{
	A.etat = 0;
	A.DPE = 99999;
}

