#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<cctype>

using namespace std;

struct member
{
	string id;
	string pseudonym;
	string name;
	string lastName;
	string age; 
	string missions;
};

void setRegister(vector<member> &);
void showList(vector<member> &);
void showMember(member &);
void addMember(vector<member> &);
void editMember(vector<member> &);
void deleteMember(vector<member> &);
void sendToFiles(vector<member> &, ofstream &, ofstream &);
bool isDigit(string);

int main()
{
	vector<member> members;
	
	int option;
	while(true)
	{
		setRegister(members);
		system("CLS");
		cout<<"******************************"<<endl
			<<"Wiaj w systemie tajnego klubu"<<endl
			<<"******************************"<<endl
			<<"Opcje:"<<endl
			<<"1. Pokaz liste czlonkow"<<endl
			<<"2. Dodaj czlonka"<<endl
			<<"3. Edytuj czlonka"<<endl
			<<"4. Usun czlonka"<<endl
			<<"0. Zakoncz"<<endl
			<<"-> "; cin>>option;
		switch(option)
		{
			case 0:
				return 0;
			case 1:
				showList(members);
				break;
			case 2:
				addMember(members);
				break;
			case 3:
				editMember(members);
				break;
			case 4:
				deleteMember(members);
				break;
			default:
				cout<<endl<<"\aNie ma takiej opcji!"<<endl<<endl;
				system("pause");
				continue;
		}
	}
	return 0;
}

void setRegister(vector<member> &members)
{
	members.clear();
	ifstream dataFile;
	dataFile.open("dane-czlonkow.txt");
	if(!dataFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	string line;
	while(!dataFile.eof())
	{
		getline(dataFile, line);
		if(line == "{")
		{
			member uploadingMember;
			
			getline(dataFile, line);
			uploadingMember.id = line;
			getline(dataFile, line);
			uploadingMember.pseudonym = line;
			getline(dataFile, line);
			uploadingMember.name = line;
			getline(dataFile, line);
			uploadingMember.lastName = line;
			getline(dataFile, line);
			uploadingMember.age = line;
			getline(dataFile, line);
			uploadingMember.missions = line;
			
			members.push_back(uploadingMember);
		}
	}
	dataFile.close();
}

void showList(vector<member> &members)
{
	ifstream dataFile, registerFile;
	dataFile.open("dane-czlonkow.txt");
	if(!dataFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFile.open("rejestr-czlonkow.txt");
	if(!registerFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	system("CLS");
	cout<<"******************************"<<endl
		<<"Wyswietlam dane czlonkow"<<endl
		<<"******************************"<<endl;
	if(members.size() > 0)
	{
		for(int i = 0; i < members.size(); i++)
		{
			showMember(members[i]);
		}
	}
	else
		cout<<"\nBrak czlonkow w rejestrze!\n\n";
	system("pause");
}

void showMember(member & currentMember)
{
	cout<<"ID: "<<currentMember.id<<endl
		<<"{"<<endl
		<<"\tPseudonim: "<<currentMember.pseudonym<<endl
		<<"\tImie: "<<currentMember.name<<endl
		<<"\tNazwisko: "<<currentMember.lastName<<endl
		<<"\tWiek: "<<currentMember.age<<endl
		<<"\tLiczba wykonanych misji: "<<currentMember.missions<<endl
		<<"}"<<endl<<endl;
}

void addMember(vector<member> &members)
{
	ofstream dataFile, registerFile;
	
	dataFile.open("dane-czlonkow.txt");
	if(!dataFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFile.open("rejestr-czlonkow.txt");
	if(!registerFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	member newMember;
	string age;
	string missions;
	
	system("CLS");
	cout<<"******************************"<<endl
		<<"Dodawanie nowego czlonka"<<endl
		<<"******************************"<<endl;
	cout<<"Podaj pseudonim: "; cin>>newMember.pseudonym;
	cout<<"Podaj imie: "; cin>>newMember.name;
	cout<<"Podaj nazwisko: "; cin>>newMember.lastName;
	cout<<"Podaj wiek: ";
	cin>>age;
	while(!isDigit(age))
	{
		cout<<"Podaj wiek: ";
		cin>>age;
	}
	newMember.age = age;
	cout<<"Podaj liczbe wykonanych misji: ";
	cin>>missions;
	while(!isDigit(missions))
	{
		cout<<"Podaj liczbe wykonanych misji: ";
		cin>>missions;
	}
	newMember.missions = missions;
		
	members.push_back(newMember);
	
	sendToFiles(members, dataFile, registerFile);
	
	dataFile.close();
	registerFile.close();
	
	cout<<"\nPomyslnie dodano nowego czlonka!\n\n";
	system("pause");
}

void editMember(vector<member> &members)
{
	ifstream dataFile, registerFile;
	
	dataFile.open("dane-czlonkow.txt");
	if(!dataFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFile.open("rejestr-czlonkow.txt");
	if(!registerFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	string line;
	string id;
	
	system("CLS");
	cout<<"******************************"<<endl
		<<"Edytowanie danych czlonka"<<endl
		<<"******************************"<<endl;
	if(!(members.size() > 0))
	{
		cout<<endl<<"Brak czlonkow do edytowania!"<<endl<<endl;
		system("pause");
		dataFile.close();
		registerFile.close();
		return;
	}
	
	while(!registerFile.eof())
	{
		getline(registerFile, line);
		cout<<line<<endl;
	}
	cout<<endl<<"Wybierz ID czlonka do edytowania: "; cin>>id;
	
	
	int index = 0;
	
	while(members[index].id != id)
	{
		while(!isDigit(id))
		{
			cout<<"Wybierz ID czlonka do edytowania: "; 
			cin>>id;
		}
		if(index == members.size())
		{
			cout<<"\aNiepoprawne ID czlonka!"<<endl<<endl;
			index = 0;
			cout<<"Wybierz ID czlonka do edytowania: "; cin>>id;
			continue;
		}
		index++;
	}
	
	member editingMember = members[index];
	
	cout<<endl<<"Aktualne dane czlonka: "<<endl;
	showMember(editingMember);
	
	char chosenOption;
	
	while(chosenOption != 'K' &&  chosenOption != 'k')
	{
		cout<<"Opcje: "<<endl
			<<"p - edytuj pseudonim"<<endl
			<<"i - edytuj imie"<<endl
			<<"n - edytuj nazwisko"<<endl
			<<"w - edytuj wiek"<<endl
			<<"m - edytuj liczbe wykonanych misji"<<endl
			<<"k - zakoncz edytowanie"<<endl
			<<"-> "; cin>>chosenOption;
			cout<<endl;
		switch(chosenOption)
		{
			case 'P':
			case 'p':
				cout<<"Podaj nowy pseudonim: ";
				cin>>editingMember.pseudonym;
				break;
			case 'I':
			case 'i':
				cout<<"Podaj nowe imie: ";
				cin>>editingMember.name;
				break;
			case 'N':
			case 'n':
				cout<<"Podaj nowe nazwisko: ";
				cin>>editingMember.lastName;
				break;
			case 'W':
			case 'w':
				{
					cout<<"Podaj nowy wiek: ";
					string age;
					cin>>age;
					while(!isDigit(age))
					{
						cout<<"Podaj nowy wiek: ";
						cin>>age;
					}
					editingMember.age = age;
					break;
				}
			case 'M':
			case 'm':
				{
					cout<<"Podaj nowa liczbe wykonanych misji: ";
					string missions;
					cin>>missions;
					while(!isDigit(missions))
					{
						cout<<"Podaj nowa liczbe wykonanych misji: ";
						cin>>missions;
					}
					editingMember.missions = missions;
					break;
				}
			case 'K':
			case 'k':
				break;
			default:
				cout<<"\aNie ma takiej opcji!"<<endl<<endl;
				continue;
		}
	}
	
	members[index] = editingMember;
	
	ofstream dataFileOut, registerFileOut;
	
	dataFileOut.open("dane-czlonkow.txt");
	if(!dataFileOut.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFileOut.open("rejestr-czlonkow.txt");
	if(!registerFileOut.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	sendToFiles(members, dataFileOut, registerFileOut);
	
	cout<<"Pomyslnie edytowano czlonka"<<endl<<endl;
	cout<<"Nowe dane czlonka:"<<endl;
	showMember(members[index]);
	
	dataFile.close();
	registerFile.close();
	dataFileOut.close();
	registerFileOut.close();	
	
	system("pause");
}

void deleteMember(vector<member> &members)
{	
	ifstream dataFile, registerFile;
	
	dataFile.open("dane-czlonkow.txt");
	if(!dataFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFile.open("rejestr-czlonkow.txt");
	if(!registerFile.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	string line;
	string id;
	
	system("CLS");
	cout<<"******************************"<<endl
		<<"Usuwanie czlonka"<<endl
		<<"******************************"<<endl;
	if(!(members.size() > 0))
	{
		cout<<endl<<"Brak czlonkow do edytowania!"<<endl<<endl;
		system("pause");
		dataFile.close();
		registerFile.close();
		return;
	}
	
	while(!registerFile.eof())
	{
		getline(registerFile, line);
		cout<<line<<endl;
	}
	cout<<endl<<"Wybierz ID czlonka do usuniecia: "; cin>>id;
	
	
	int index = 0;
	
	while(members[index].id != id)
	{
		while(!isDigit(id))
		{
			cout<<"Wybierz ID czlonka do usuniecia: "; 
			cin>>id;
		}
		if(index == members.size())
		{
			cout<<"\aNiepoprawne ID czlonka!"<<endl<<endl;
			index = 0;
			cout<<"Wybierz ID czlonka do usuniecia: "; cin>>id;
			continue;
		}
		index++;
	}
	
	char confirmation;
	
	cout<<"Czy jestes pewny, ze chcesz usunac czlonka o ID: "<<id<<" z tajnego klubu?"<<endl
		<<"Wpisz t, aby kontynuowac"<<endl
		<<"Wpisz n, aby anulowac"<<endl
		<<"-> ";
	while(confirmation != 'T' && confirmation != 't')
	{
		cin>>confirmation;
		switch(confirmation)
		{
			case 'T':
			case 't':
				break;
			case 'N':
			case 'n':
				cout<<endl<<"Pomyslnie anulowano usuwanie czlonka!"<<endl<<endl;
				system("pause");
				dataFile.close();
				registerFile.close();
				return;
			default:
				cout<<"\aNie ma takiej opcji!"<<endl<<endl
					<<"Wpisz t, aby kontynuowac"<<endl
					<<"Wpisz n, aby anulowac"<<endl
					<<"-> ";
				continue;
		}
	}
	
	vector<member> tempMembers;
	for(int j = 0; j < members.size(); j++)
	{
		if(j != index)
			tempMembers.push_back(members[j]);
	}
	members.clear();
	for(int j = 0; j < tempMembers.size(); j++)
	{
		members.push_back(tempMembers[j]);
	}
	
	ofstream dataFileOut, registerFileOut;
	
	dataFileOut.open("dane-czlonkow.txt");
	if(!dataFileOut.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	registerFileOut.open("rejestr-czlonkow.txt");
	if(!registerFileOut.good())
	{
		cout<<"Blad pliku!\a"<<endl<<endl;
		system("pause");
		return;
	}
	
	sendToFiles(members, dataFileOut, registerFileOut);
	
	dataFile.close();
	registerFile.close();
	dataFileOut.close();
	registerFileOut.close();
	
	cout<<endl<<"Czlonek o ID: "<<id<<" zostal pomyslnie usuniety!"<<endl<<endl;
	system("pause");
}

void sendToFiles(vector<member> & members, ofstream & dataFile, ofstream & registerFile)
{
	for(int i = 0; i < members.size(); i++)
	{
		members[i].id = to_string(i+1);
		dataFile<<"{"<<endl
			<<members[i].id<<endl
			<<members[i].pseudonym<<endl
			<<members[i].name<<endl
			<<members[i].lastName<<endl
			<<members[i].age<<endl
			<<members[i].missions<<endl
			<<"}"<<endl;
		
		registerFile<<"ID: "<<members[i].id<<", "<<"pseudonim: "<<members[i].pseudonym<<endl;
	}
}

bool isDigit(string value)
{
	for(int i = 0; i < value.length(); i++)
	{
		if(!isdigit(value[i]))
		{
			cout<<endl<<"\aBlad! Formula nie moze zawierac liter!"<<endl<<endl;
			return false;
		}
	}
	return true;
}