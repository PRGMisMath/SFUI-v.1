//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<complex>
#include "GUI.hpp"
#include "GButton.hpp"
#include "GCursor.hpp"
#include "GEntry.hpp"
#include "GScrollPane.hpp"
#include "System.hpp"

#define NB_MENUS 2
#define PI 3.141592

// Fonctions
void make_drawing(sf::VertexArray& drw, std::vector<std::complex<float>> coef);
void update_drw();
void params();
void upd_Langle();

int PRECISION = 1000;
int NB_PARAMS = 3;

const const char* Nmenus[NB_MENUS] = { "Calculer", "Paramètres" };
void (* const Fmenus[NB_MENUS])() = { update_drw, params };

sf::VertexArray Drawing{ sf::LineStrip, (size_t)PRECISION + 1 };
std::vector<std::complex<float>> Coef_list{};
sf::VertexArray Vectors{ sf::LineStrip };

struct ParamsFourrier {
	Component box{ };
	Cursor angle{ 360 };
	Entry norme{ "0" };
	Entry Langle{ "0°" };
};
std::vector<ParamsFourrier> pFour{};

void make_drawing(sf::VertexArray& drw, std::vector<std::complex<float>> coef) {
	const int n = std::size(coef) / 2;
	for (int t = 0; t < PRECISION + 1; ++t) {
		std::complex<float> res = 0;
		for (int i = -n; i < n + 1; ++i)
			res += coef[i + n] * std::exp(std::complex<float>(0, 2 * PI / PRECISION * i * t));
		drw[t] = sf::Vertex({ 10 * res.real(), 10 * res.imag() }, sf::Color::Red);
	}
}

void update_coef() {
	for (int i = 0; i < NB_PARAMS; ++i) {
		try {
			Coef_list[i] = (float)std::stod(pFour[i].norme.getText()) * std::exp(std::complex<float>(0,pFour[i].angle.get() / 180.f * PI));
		}
		catch (const std::exception& e) {
			Coef_list.resize(3,0);
			std::cerr << "Invalid entry n°" << i+1 << std::endl;
			// Error
			return;
		}
	}
}

bool need_adding = false;
Container Fours{};
void addParams() {
	for (int k = -(NB_PARAMS/2); k < NB_PARAMS/2+1; k += NB_PARAMS-1) {
		int i = (k>0) * (NB_PARAMS+1);
		if (k < 0)
			pFour.insert(std::begin(pFour), ParamsFourrier());
		else
			pFour.push_back(ParamsFourrier());
		pFour[i].angle.setPosition({ 0, 80.f + 80 * k });
		pFour[i].angle.on_update(new FoncAction(upd_Langle));
		pFour[i].angle.on_update(new FoncAction(update_drw));
		pFour[i].norme.setPosition({ 0, 100.f + 80 * k });
		pFour[i].norme.setSize({ 485,30 });
		pFour[i].norme.canFocus(true);
		pFour[i].norme.on_entry(new FoncAction(update_drw));
		pFour[i].box.setPosition({ -7.5f, 72.5f + 80 * k });
		pFour[i].box.setBoxAppear({ NULL,{0,0,0,0},sf::Color::Transparent,sf::Color::Black,1 });
		pFour[i].box.setSize({ 500,65 });
		pFour[i].Langle.setPosition({ 380, 70.f + 80 * k });
		pFour[i].Langle.canFocus(false);
		pFour[i].Langle.setSize({ 50,10 });
		pFour[i].Langle.setBoxAppear({ NULL,{0,0,0,0},sf::Color::Transparent,sf::Color::Black,1 });
		Fours.addComponent(&pFour[i].box);
		Fours.addComponent(&pFour[i].angle);
		Fours.addComponent(&pFour[i].norme);
		Fours.addComponent(&pFour[i].Langle);
	}
	NB_PARAMS += 2;
}

void newParam() { 
	need_adding = true;
}
void update_drw() { update_coef(); make_drawing(Drawing, Coef_list); }
void params() { /* Déclencher une fenêtre de dialogue */ }
void upd_Langle() { for (int i = 0; i < 3; ++i) pFour[i].Langle.setText(std::to_string(pFour[i].angle.get()) + '°'); }


int main() {
	Coef_list.resize(NB_PARAMS,0);

	sf::RenderWindow fntr{ sf::VideoMode(1400,700),"Fourrier" };
	GUI handler{};
	sf::View Fourrier{ {0, 0}, {500, 500} };
	Fourrier.setViewport({ .1,.2,.35,.7 });

	Button menus[NB_MENUS];
	for (int i = 0; i < NB_MENUS; ++i) {
		menus[i] = Button(Nmenus[i]);
		menus[i].setPosition({ 15.f + 180 * i,15.f });
		menus[i].on_click(new FoncAction(Fmenus[i]));
		menus[i].setSize({ 150, 30 });
		handler.addComponent(&menus[i]);
	}
	sf::RectangleShape menubar{ { fntr.getDefaultView().getSize().x, 60.f } };
	menubar.setFillColor(sf::Color(100, 100, 100));
	sf::RectangleShape sidebar{ { .4f * fntr.getDefaultView().getSize().x, fntr.getDefaultView().getSize().y } };
	sidebar.setFillColor(sf::Color(200, 100, 50));
	sidebar.setOutlineColor(sf::Color(50, 100, 200));
	sidebar.setPosition({ .6f * fntr.getDefaultView().getSize().x, 0 });

	Button addParam{ "+ Nouveau" };
	addParam.setPosition({ .61f * fntr.getDefaultView().getSize().x, 80 });
	addParam.setSize({ 200,30 });
	addParam.on_click(new FoncAction(newParam));
	handler.addComponent(&addParam);
	pFour.resize(3);
	for (int i = 0; i < 3; ++i) {
		pFour[i].angle.setPosition({ 0, 80.f + 80 * (i-1) });
		pFour[i].angle.on_update(new FoncAction(upd_Langle));
		pFour[i].angle.on_update(new FoncAction(update_drw));
		pFour[i].norme.setPosition({ 0, 100.f + 80 * (i-1) });
		pFour[i].norme.setSize({ 485,30 });
		pFour[i].norme.canFocus(true);
		pFour[i].norme.on_entry(new FoncAction(update_drw));
		pFour[i].box.setPosition({ -7.5f, 72.5f + 80 * (i-1) });
		pFour[i].box.setBoxAppear({ NULL,{0,0,0,0},sf::Color::Transparent,sf::Color::Black,1 });
		pFour[i].box.setSize({ 500,65 });
		pFour[i].Langle.setPosition({ 380, 70.f + 80 * (i-1) });
		pFour[i].Langle.canFocus(false);
		pFour[i].Langle.setSize({ 50,10 });
		pFour[i].Langle.setBoxAppear({ NULL,{0,0,0,0},sf::Color::Transparent,sf::Color::Transparent,0 });
		Fours.addComponent(&pFour[i].box);
		Fours.addComponent(&pFour[i].angle);
		Fours.addComponent(&pFour[i].norme);
		Fours.addComponent(&pFour[i].Langle);
	}
	ScrollPane scroller{ &Fours, 10 };
	scroller.setPosition({ .61f * fntr.getDefaultView().getSize().x, 120.f });
	scroller.setSize({ .38f * fntr.getDefaultView().getSize().x, .6f * fntr.getDefaultView().getSize().y });
	handler.addComponent(&scroller);

	while (fntr.isOpen()) {
		sf::Event event;
		while (fntr.pollEvent(event)) {
			handler.listen(event);
			switch (event.type) {
			case sf::Event::Closed:
				fntr.close();
				break;
			}
		}
		sf::RectangleShape rs{ Fourrier.getSize() };
		rs.setFillColor(sf::Color::White);
		rs.setPosition({ Fourrier.getCenter().x - Fourrier.getSize().x / 2,Fourrier.getCenter().y - Fourrier.getSize().y / 2 });
		handler.update();
		if (need_adding) {
			addParams();
			scroller.actualise();
			need_adding = false;
		}
		fntr.clear();
		fntr.draw(sidebar);
		fntr.draw(menubar);
		fntr.draw(handler);
		fntr.setView(Fourrier);
		fntr.draw(rs);
		fntr.draw(Drawing);
		fntr.setView(fntr.getDefaultView());
		fntr.display();
	}

	return 0;
}
