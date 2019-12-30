#include "stdafx.h"
#include "simul.h"

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


int generer_prochaine_etape(T_Piece& p, int etape_actuelle) //renvoie le numéro de l'étape suivante que doit traverser la pièce
{
	int proc_etape;
	if (etape_actuelle == 1)
	{
		proc_etape = 2;
	}
	else //on doit tester si la piece reste dans le système ou sort vers la sortie
	{
		if (bernoulli(proba_p))
		{
			proc_etape = 1;
		}
		else
		{
			proc_etape = 0;
		}
	}
	return proc_etape;
}


void choisir_machine_etape(T_Piece& p, int etape) //donne à la piece le numéro de la prochaine machine qu'elle doit traverser dans l'étape donnée
{
	if (etape == 2)  //dans l'étape 2 on choisit entre les 2 machines 2 et 3
	{
		if (bernoulli(proba_q))
		{
			p.liste_machines[p.nb_etapes+1] = 2;
		}
		else
		{
			p.liste_machines[p.nb_etapes+1] = 3;
		}
	}
	else if (etape == 1) //si on est dans l'étape 1 on n'a pas le choix
	{
		p.liste_machines[p.nb_etapes+1] = 1;
	}
}


int calcul_DPE(int Entree, int M1, int M2, int M3)//pire fonction ever seen by chabrol => instant reported by chabrol
{
	int min1 = 0, min2 = 0, min = 0;
	int retour = -1;
	min1 = min(Entree, M1);
	min2 = min(M2, M3);
	min = min(min1, min2);
	if (min == Entree)
	{
		retour = 1;
	}
	else if (min == M1)
	{
		retour = 2;
	}
	else if (min == M2)
	{
		retour = 3;
	}
	else if (min == M3)
	{
		retour = 4;
	}
	return retour;
}



void simuler(int duree_max, int duree_inter_arrivee, int DT1, int DT2, int DT3,
			System::Windows::Forms::RichTextBox^ affichage,
			System::Windows::Forms::DataVisualization::Charting::Chart^ chart1,
			System::Windows::Forms::DataVisualization::Charting::Chart^ chart2)
{

	int stop, delta;
	int nb_pieces;
	int nb_perdus = 0; //jamais incrémenté
	int temps = 0; // Date de simulation
	int id_piece = 1;
	int res = 0;
	int temps_sejour_total = 0;
	int moyenne_temps_sejour = 0;
	int etape = 0;

	T_File file_1;
	T_File file_2;
	T_File file_3;

	T_Machine Machine_1;
	T_Machine Machine_2;
	T_Machine Machine_3;

	T_Sortie S;
	T_Entree E;
	T_Piece P;

	initialiser_machine(Machine_1, DT1);
	initialiser_machine(Machine_2, DT2);
	initialiser_machine(Machine_3, DT3);

	initialiser_file(file_1);
	initialiser_file(file_2);
	initialiser_file(file_3);

	S.nb = 0;
	E.DPE = 0;
	E.DIA = duree_inter_arrivee;

	while (temps < duree_max) 
	{

		std::cout << std::endl << std::endl << "temps = " << temps<<std::endl;
		res = calcul_DPE(E.DPE, Machine_1.DPE, Machine_2.DPE, Machine_3.DPE);
		std::cout << "E.DPE = " << E.DPE << " / M1.DPE = " << Machine_1.DPE << " / M2.DPE = " << Machine_2.DPE << " / M3.DPE = " << Machine_3.DPE << std::endl;
		std::cout << "res = " << res << std::endl;
		
		if (res == 1)
		{										// l'entrée avait la date la plus petite
			temps = E.DPE; //
			gerer_entree(E, temps);//
			P = E.contenu;//

			if (Machine_1.etat == 0) 
			{
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
		
		else if (res == 2)						// Machine 1 avec DPE la plus faible
		{					
			etape = 1;
			temps = Machine_1.DPE;
			P = Machine_1.contenu;

			std::cout << "res 2 ==== etape : " << etape << std::endl;
			etape = generer_prochaine_etape(P, etape);
			//choisir machine suivante
			if (etape == 2) 
			{
				choisir_machine_etape(P, etape);
				P.nb_etapes++;
			}
			

			if (P.liste_machines[P.nb_etapes] == 2 && Machine_2.etat == 0)// Machine 2 libre
			{ 
				P.sortie_M1 = temps;
				vider_machine(Machine_1);
				deposer_piece_machine(Machine_2, P, temps);
				if (est_vide(file_1)) 
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else 
				{
					stop = 0;
					while (stop == 0) 
					{
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						if (true) 
						{
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1)) 
						{
							stop = 2;
						}
					}
					E.etat = 1;
					E.DPE = temps;
				}
			}
			else if (est_pleine(file_2) == 0)  // File 2 n'est pas pleine
			{				
				P.sortie_M1 = temps;
				deposer_piece_file(file_2, P);
				if (est_vide(file_1)) 
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else {
					stop = 0;
					while (stop == 0)
					{
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						
						if (true) 
						{
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1))
						{
							stop = 2;
						}
					}
					E.etat = 1;
					E.DPE = temps;
				}	
			}
			else 
			{											// File 2 pleine
				Machine_1.etat = 2; // Machine 1 bloquée
				Machine_1.DPE = 9999;
			}

			if (P.liste_machines[P.nb_etapes] == 3 && Machine_3.etat == 0) // Machine 3 libre
			{
				P.sortie_M1 = temps;
				vider_machine(Machine_1);
				deposer_piece_machine(Machine_3, P, temps);
				if (est_vide(file_1))
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else
				{
					stop = 0;
					while (stop == 0)
					{
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						if (true)
						{
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1))
						{
							stop = 2;
						}
					}
					//E.etat = 1;
					//E.DPE = temps;
				}
			}
			else if (est_pleine(file_3) == 0)
			{				// File 3 n'est pas pleine
				P.sortie_M1 = temps;
				deposer_piece_file(file_3, P);
				if (est_vide(file_1))
				{
					Machine_1.etat = 0;
					Machine_1.DPE = 9999;
				}
				else {
					stop = 0;
					while (stop == 0)
					{
						P = retirer_piece(file_1);
						delta = temps - P.entree_date;
						if (true) {
							stop = 1;
							deposer_piece_machine(Machine_1, P, temps);
						}
						if (est_vide(file_1))
						{
							stop = 2;
						}
					}
					//E.etat = 1;
					//E.DPE = temps;
				}
			}
			else                           // File 2 pleine
			{											
				Machine_1.etat = 2; // Machine 1 bloquée
				Machine_1.DPE = 9999;
			}

		}

		else if (res == 3)						// la machine M2 avec la dpe la plus petite
		{ 
			temps = Machine_2.DPE;
			P = Machine_2.contenu;

			std::cout << "res 3 ==== etape : " << etape << std::endl;
			etape = generer_prochaine_etape(P, etape);
			std::cout << "res 3 ==== etape : " << etape << std::endl;
			P.nb_etapes++;
			if (etape == 0)
			{
				//on se casse tardplus
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
			else
			{
				//on revient au début

				//temps = Machine_1.DPE;
				//P = Machine_1.contenu;
				//choisir machine suivante
				choisir_machine_etape(P, etape);
				

				if (P.liste_machines[P.nb_etapes] == 1 && Machine_1.etat == 0)// Machine 1 libre
				{
					P.sortie_M1 = temps;
					vider_machine(Machine_2);
					deposer_piece_machine(Machine_1, P, temps);
					if (est_vide(file_2))
					{
						Machine_2.etat = 0;
						Machine_2.DPE = 9999;
					}
					else
					{
						stop = 0;
						while (stop == 0)
						{
							P = retirer_piece(file_2);
							delta = temps - P.entree_date;
							if (true)
							{
								stop = 1;
								deposer_piece_machine(Machine_2, P, temps);
							}
							if (est_vide(file_2))
							{
								stop = 2;
							}
						}
						//E.etat = 1;
						//E.DPE = temps;
					}
				}

				else if (est_pleine(file_1) == 0)  // File 2 n'est pas pleine
				{				
					P.sortie_M1 = temps;
					deposer_piece_file(file_1, P);
					if (est_vide(file_2))
					{
						Machine_2.etat = 0;
						Machine_2.DPE = 9999;
					}
					else {
						stop = 0;
						while (stop == 0)
						{
							P = retirer_piece(file_2);
							delta = temps - P.entree_date;
							if (true) {
								stop = 1;
								deposer_piece_machine(Machine_2, P, temps);
							}
							if (est_vide(file_2))
							{
								stop = 2;
							}
						}
						//E.etat = 1;
						//E.DPE = temps;
					}
				}
				else
				{											// File 2 pleine
					Machine_2.etat = 2; // Machine 1 bloquée
					Machine_2.DPE = 9999;
				}

			}
						
		}

		//here

		else if (res == 4)						// la machine M3 avec la date la plus petite
		{
			temps = Machine_3.DPE;
			P = Machine_3.contenu;

			std::cout << "res 4 ==== etape : " << etape << std::endl;
			etape = generer_prochaine_etape(P, etape);
			std::cout <<"res 4 ==== etape : "<< etape << std::endl;
			P.nb_etapes++;
			if (etape == 0)
			{
				std::cout << "etape 0" << std::endl;
				//on se casse tardplus
				deposer_piece_sortie(S, P, affichage, temps);
				if (est_vide(file_3))
				{
					vider_machine(Machine_3);
				}
				else
				{
					T_Piece Nouv_Piece;
					Nouv_Piece = retirer_piece(file_3);
					deposer_piece_machine(Machine_3, Nouv_Piece, temps);
					if (Machine_1.etat == 2) {
						Machine_1.etat = 1;
						Machine_1.DPE = temps;
					}
				}
				temps_sejour_total += P.sortie_date - P.entree_date;
				nb_pieces++;
			}
			else
			{
				//on revient au début
				//temps = Machine_1.DPE;
				//P = Machine_1.contenu;

				//choisir machine suivante
				choisir_machine_etape(P, etape);


				if (P.liste_machines[P.nb_etapes] == 1 && Machine_1.etat == 0)// Machine 1 libre
				{
					P.sortie_M1 = temps;
					vider_machine(Machine_3);
					deposer_piece_machine(Machine_1, P, temps);
					if (est_vide(file_3))
					{
						Machine_3.etat = 0;
						Machine_3.DPE = 9999;
					}
					else
					{
						stop = 0;
						while (stop == 0)
						{
							P = retirer_piece(file_3);
							delta = temps - P.entree_date;
							if (true)
							{
								stop = 1;
								deposer_piece_machine(Machine_3, P, temps);
							}
							if (est_vide(file_3))
							{
								stop = 2;
							}
						}
						//E.etat = 1;
						//E.DPE = temps;
					}
				}

				else if (est_pleine(file_1) == 0)  // File 1 n'est pas pleine
				{
					P.sortie_M1 = temps;
					deposer_piece_file(file_1, P);
					if (est_vide(file_3))
					{
						Machine_3.etat = 0;
						Machine_3.DPE = 9999;
					}
					else {
						stop = 0;
						while (stop == 0)
						{
							P = retirer_piece(file_3);
							delta = temps - P.entree_date;
							if (true) {
								stop = 1;
								deposer_piece_machine(Machine_3, P, temps);
							}
							if (est_vide(file_3))
							{
								stop = 2;
							}
						}
						//E.etat = 1;
						//E.DPE = temps;
					}
				}
				else
				{											// File 2 pleine
					Machine_3.etat = 2; // Machine 1 bloquée
					Machine_3.DPE = 9999;
				}

			}

		}
	
		//std::cout << temps << std::endl;

	}

	std::cout << " C FINI " << std::endl;

	affichage->Refresh();
	
	//moyenne_temps_sejour = temps_sejour_total / nb_pieces +1;
	//System::String^ moy = "Moyenne du temps de séjour: " + transformer_int_string(moyenne_temps_sejour);
	//affichage->AppendText(moy);
	//affichage->Refresh();

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
		chart1->Series[0]->Points->AddXY(x, y);
		x = x + 1;
	}

	int x2 = 0;
	while (x2 < nb_pieces)
	{
		float y2 = S.L[x2].sortie_date;
		chart2->Series[0]->Points->AddXY(x2, y2);
		x2 = x2 + 1;
	}

}


void initialiser_machine(T_Machine& Machine, int DT) 
{
	Machine.etat = 0;
	Machine.DPE = 99999;
	Machine.duree_traitement = DT;
}


System::String^ transformer_int_string(int var)
{

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

void deposer_piece_sortie(T_Sortie & S, T_Piece & P, System::Windows::Forms::RichTextBox^ affichage,
																				int date_simulation)
{
	P.sortie_date = date_simulation;
	S.nb++;
	S.L[S.nb] = P;
	System::String^ a = transformer_int_string(P.identifiant);
	System::String^ b = transformer_int_string(P.entree_date);
	System::String^ c = transformer_int_string(P.sortie_date);
	//System::String^ e = transformer_int_string(P.sortie_M1);
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



