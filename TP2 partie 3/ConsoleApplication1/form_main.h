#pragma once

#include <msclr\marshal_cppstd.h>
#include <sstream>
#include "simul.h"

namespace ConsoleApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace msclr::interop;

	/// <summary>
	/// Description r�sum�e de form_main
	/// </summary>
	public ref class form_main : public System::Windows::Forms::Form
	{
	public:
		form_main(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilis�es.
		/// </summary>
		~form_main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox6;




	private:
		/// <summary>
		/// Variable n�cessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�thode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette m�thode avec l'�diteur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(595, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(111, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Duree de la simulation";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(595, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Duree interarrivee 1";
			this->label2->Click += gcnew System::EventHandler(this, &form_main::label2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(715, 17);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"1000";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &form_main::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(715, 43);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = L"1";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &form_main::textBox2_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(595, 98);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(115, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Duree_de_traitement 1";
			this->label3->Click += gcnew System::EventHandler(this, &form_main::label3_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(715, 95);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->Text = L"5";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(598, 238);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(217, 21);
			this->button1->TabIndex = 6;
			this->button1->Text = L"SIMULER";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form_main::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(842, 25);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(326, 234);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"";
			// 
			// chart1
			// 
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			this->chart1->Cursor = System::Windows::Forms::Cursors::Cross;
			legend3->Name = L"Legend1";
			this->chart1->Legends->Add(legend3);
			this->chart1->Location = System::Drawing::Point(31, 276);
			this->chart1->Name = L"chart1";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series3->Legend = L"Legend1";
			series3->Name = L"Series1";
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(561, 362);
			this->chart1->TabIndex = 9;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &form_main::chart1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(56, 657);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(506, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &form_main::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(638, 657);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(506, 23);
			this->button3->TabIndex = 12;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &form_main::button3_Click);
			// 
			// chart2
			// 
			chartArea4->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea4);
			this->chart2->Cursor = System::Windows::Forms::Cursors::Cross;
			legend4->Name = L"Legend1";
			this->chart2->Legends->Add(legend4);
			this->chart2->Location = System::Drawing::Point(607, 276);
			this->chart2->Name = L"chart2";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series4->Legend = L"Legend1";
			series4->Name = L"Series1";
			this->chart2->Series->Add(series4);
			this->chart2->Size = System::Drawing::Size(561, 362);
			this->chart2->TabIndex = 13;
			this->chart2->Text = L"chart2";
			this->chart2->Click += gcnew System::EventHandler(this, &form_main::chart2_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(715, 121);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 14;
			this->textBox4->Text = L"1";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(595, 124);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(115, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"Duree_de_traitement 2";
			this->label4->Click += gcnew System::EventHandler(this, &form_main::label4_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(715, 69);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 17;
			this->textBox5->Text = L"10";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(595, 72);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(100, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Duree interarrivee 2";
			this->label5->Click += gcnew System::EventHandler(this, &form_main::label5_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(595, 153);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(98, 13);
			this->label6->TabIndex = 19;
			this->label6->Text = L"Duree_assemblage";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(715, 150);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 18;
			this->textBox6->Text = L"10";
			// 
			// form_main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1208, 701);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"form_main";
			this->Text = L"form_main";
			this->Load += gcnew System::EventHandler(this, &form_main::form_main_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {




		System::String^ s_nb_1 = textBox1->Text;
		System::String^ s_nb_2 = textBox2->Text;
		System::String^ s_nb_3 = textBox3->Text;
		System::String^ s_nb_4 = textBox4->Text;
		System::String^ s_nb_5 = textBox5->Text;
		System::String^ s_nb_6 = textBox6->Text;

		msclr::interop::marshal_context context;
		std::string chaine1 = context.marshal_as<std::string>(s_nb_1);
		std::string chaine2 = context.marshal_as<std::string>(s_nb_2);
		std::string chaine3 = context.marshal_as<std::string>(s_nb_3);
		std::string chaine4 = context.marshal_as<std::string>(s_nb_4);
		std::string chaine5 = context.marshal_as<std::string>(s_nb_5);
		std::string chaine6 = context.marshal_as<std::string>(s_nb_6);

		// autre sol
		int duree_simulation = -1;
		int duree_assemblage = -1;
		int duree_inter_arrivee1 = -1;
		int duree_inter_arrivee2 = -1;
		int duree_traitement_1 = -1;
		int duree_traitement_2 = -1;
		std::istringstream(chaine1) >> duree_simulation;
		std::istringstream(chaine2) >> duree_inter_arrivee1;
		std::istringstream(chaine5) >> duree_inter_arrivee2;
		std::istringstream(chaine3) >> duree_traitement_1;
		std::istringstream(chaine4) >> duree_traitement_2;
		std::istringstream(chaine6) >> duree_assemblage;

		simuler(duree_simulation, duree_inter_arrivee1, duree_inter_arrivee2, duree_traitement_1, duree_traitement_2, duree_assemblage, richTextBox1, chart1);

		




	}
private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {


}
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void chart2_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	float x = -10;
	while (x < 10)
	{
		float y = exp(x) - x*x;
		chart2->Series[0]->Points->AddXY(x, y);
		x = x + 1;
	}
}

private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void form_main_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
};

}
