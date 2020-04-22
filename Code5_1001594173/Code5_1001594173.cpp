/* Tu Mai 
1001594173*/

#include <gtkmm.h>
#include <iostream>
//#include "MainWindow.h"

class MainWindow : public Gtk::Window
{
	public: 
		MainWindow();
		void OK_button_clicked(Gtk::Entry *AnsEntry);
		void Cancel_button_clicked();
};


//fuction to check answer and display the message dialog when then user click OK button
void MainWindow::OK_button_clicked(Gtk::Entry *AnsEntry)
{
	//create the message
	Gtk::MessageDialog *Correct = new Gtk::MessageDialog{"Congrats! You got the <span fgcolor='#0000ff'>CORRECT</span> answer!",true,Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK};
	Gtk::MessageDialog *Incorrect = new Gtk::MessageDialog{"Sorry! That's an <span fgcolor='#ff0000'>INCORRECT</span> answer.\nTry again", true, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK};
	
	//get in the answer and check
	std::string ans = AnsEntry->get_text();
	if (ans == "Larva" || ans == "larva" ||  ans == "LARVA")
	{
		Correct->run();
		Correct->close();
		hide();
	}
	else
	{
		Incorrect->run();
		Incorrect->close();
	}
}


//exit when user clicks cancel
void MainWindow::Cancel_button_clicked()
{
	hide();
}





MainWindow::MainWindow()
{
	//Set up Vertical Box, Set title, default size
	Gtk::Box *MainVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	add(*MainVBox);
	set_title("Welcome to MY GUESSING GAME");
	set_position(Gtk::WIN_POS_CENTER);
	//set_default_size(700,300);
	
	//Menu bar
	Gtk::MenuBar *MyMenuBar= Gtk::manage(new Gtk::MenuBar());
	MainVBox->pack_start(*MyMenuBar, Gtk::PACK_SHRINK, 0);
	//FamilyHints
	Gtk::MenuItem *Menu_Fam= Gtk::manage(new Gtk::MenuItem("_Family Hints", true));
	MyMenuBar->append(*Menu_Fam);
	//set
	Gtk::Menu *SubMenu_Fam= Gtk::manage(new Gtk::Menu());
	Menu_Fam->set_submenu(*SubMenu_Fam);
	//sub menu for family hints
	Gtk::MenuItem *SubFam_Item1 = Gtk::manage (new Gtk::MenuItem("_Mom",true));
	SubMenu_Fam->append(*SubFam_Item1);
	Gtk::MenuItem *SubFam_Item2 = Gtk::manage (new Gtk::MenuItem("_Dad",true));
	SubMenu_Fam->append(*SubFam_Item2);
	Gtk::MenuItem *SubFam_Item3 = Gtk::manage (new Gtk::MenuItem("_Vivi",true));
	SubMenu_Fam->append(*SubFam_Item3);
	
	//Friends Hints
	Gtk::MenuItem *Menu_Fr= Gtk::manage(new Gtk::MenuItem("_Friend Hints", true));
	MyMenuBar->append(*Menu_Fr);
	
	Gtk::Menu *SubMenu_Fr= Gtk::manage(new Gtk::Menu());
	Menu_Fr->set_submenu(*SubMenu_Fr);
	
	Gtk::MenuItem *SubFr_Item1 = Gtk::manage (new Gtk::MenuItem("_Tu",true));
	SubMenu_Fr->append(*SubFr_Item1);
	Gtk::MenuItem *SubFr_Item2 = Gtk::manage (new Gtk::MenuItem("_Bill",true));
	SubMenu_Fr->append(*SubFr_Item2);
	Gtk::MenuItem *SubFr_Item3 = Gtk::manage (new Gtk::MenuItem("_Jahue",true));
	SubMenu_Fr->append(*SubFr_Item3);
	
	//More Hints
	Gtk::MenuItem *Menu_M= Gtk::manage(new Gtk::MenuItem("_More Hints", true));
	MyMenuBar->append(*Menu_M);
	
	Gtk::Menu *SubMenu_M= Gtk::manage(new Gtk::Menu());
	Menu_M->set_submenu(*SubMenu_M);
	
	Gtk::MenuItem *SubM_Item1 = Gtk::manage (new Gtk::MenuItem("_First Letter",true));
	SubMenu_M->append(*SubM_Item1);
	Gtk::MenuItem *SubM_Item2 = Gtk::manage (new Gtk::MenuItem("_Last Letter",true));
	SubMenu_M->append(*SubM_Item2);
	Gtk::MenuItem *SubM_Item3 = Gtk::manage (new Gtk::MenuItem("_Word Number",true));
	SubMenu_M->append(*SubM_Item3);
	
	
	//add Message to the VBox
	Gtk::Label *Question = Gtk::manage(new Gtk::Label ("What is this TV show's name?"));
	MainVBox->add(*Question);
	//display all for Vertical box 1
	Gtk::Image *image = Gtk::manage(new Gtk::Image("larva.jpg"));
	MainVBox->add(*image);
	//image->set_size_request(300,100);
	//image.show();
	
	//add empty space below the image 
	Gtk::Label *emptySpace = Gtk::manage(new Gtk::Label{"\n"});
	MainVBox->add(*emptySpace);
	
	//hBox
	Gtk::Box *hBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	MainVBox->add(*hBox);
	
	//create 2 vBox inside the hbox
	Gtk::Box *vBox1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	hBox->pack_start(*vBox1);
	
	Gtk::Box *vBox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	hBox->pack_start(*vBox2);
	
	
	Gtk::Button* OKbutton = Gtk::manage(new Gtk::Button("OK", 1));
	OKbutton->set_size_request(350, 25);
	vBox1->add(*OKbutton);
	OKbutton->set_can_default(true);
	OKbutton->grab_default();
	OKbutton->set_border_width(2);
	Gtk::Button* Cancelbutton = Gtk::manage(new Gtk::Button("Cancel", 2));
	Cancelbutton->set_size_request(350, 25);
	vBox1->add(*Cancelbutton);
	Cancelbutton->set_border_width(2);
	
	// create entry box to vBox2
	Gtk::Entry *AnsEntry = Gtk::manage(new Gtk::Entry());
	AnsEntry->set_activates_default(true);
	AnsEntry->set_size_request(450, 25);
	AnsEntry->set_text("Enter your answer here..");
	vBox2->add(*AnsEntry);
	
	//make space below entry
	Gtk::Label *emptySpace2 = Gtk::manage(new Gtk::Label{"\n"});
	vBox2->add(*emptySpace2);	
	
	//connect functions with the OK and Cancel buttons
	OKbutton->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainWindow::OK_button_clicked), AnsEntry));
	Cancelbutton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::Cancel_button_clicked));
	
	//keyboard focus
	AnsEntry->set_can_focus(true);
	AnsEntry->grab_focus();
	
	MainVBox->show_all();
}
	
int main (int argc, char* argv[])
{
	auto app = Gtk::Application::create(argc,argv,"app.CA5.CSE1325");
	MainWindow MyWindow;
	
	return app->run(MyWindow);
}	

