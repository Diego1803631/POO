#include <iostream>
#include <time.h>
#include <string>

using namespace std;

enum TypeDamage
{

};

enum Dice
{
	D2 = 2,
	D4 = 4,
	D6 = 6,
	D8 = 8,
	D10 = 10,
	D12 = 12,
	D20 = 20
};

struct Attack
{//Inicio Ataque
	//Atributos
	char m_name[50];
	Dice m_diceDamage;
	int m_energy;
	bool m_isCritic;

	//Constructores
	Attack()
	{
	}

	Attack(char name[50], Dice diceDamage, int energy)
	{
		strcpy_s(m_name, name);
		m_diceDamage = diceDamage;
		m_energy = energy;
	}
	//Metodos
	int CheckValue()
	{
		return m_diceDamage;
	}

	int ThrowDice()
	{
		srand(time(NULL));
		return (rand() % CheckValue()) + 1;
	}

	int ThrowDice(Dice dice)
	{
		srand(time(NULL));
		return (rand() % dice) + 1;
	}
	int VerifyDefense()
	{
		srand(time(NULL));
		return ThrowDice(D20);
	}
};//Fin de Ataque

struct Character
{
	char m_name[50];
	int m_hitPoints;//Vida
	int m_energy;
	int m_defense;

	Character()
	{
	}

	Character(char name[50], int hitPoins, int energy, int defensa)
	{
		strcpy_s(m_name, name);
		m_hitPoints = hitPoins;
		m_energy = energy;
		m_defense = defensa;
	}
};

struct Enemy
{
	char m_name[50];
	int m_hitPoints;//Vida
	int m_energy;
	int m_defense;

	Enemy()
	{}

	Enemy(char name[50], int hitPoins, int energy, int defensa)
	{
		strcpy_s(m_name, name);
		m_hitPoints = hitPoins;
		m_energy = energy;
		m_defense = defensa;
	}
	void TakeDamage(int damage)
	{
		m_hitPoints -= damage;
	}
	void PrintHealth()
	{
		cout << "Enemy HP= " << m_hitPoints << endl;
	}
};

void main()
{
	Attack* atk = new Attack((char*)"Star platinum", D4, 5);
	Character* mainCharacter = new Character((char*)"Jotaro Kujo", 100, 15, 10);
	Enemy* enemy01 = new Enemy((char*)"DIO", 100, 12, 9);
	cout << "Attack= " << atk->m_name << endl;
	cout << "Name= " << mainCharacter->m_name << endl;
	cout << "Enemy= " << enemy01->m_name << endl;
	enemy01->PrintHealth();
	cout << endl;
	int dmg = atk->ThrowDice();
	cout << "Attack= " << dmg << endl;
	cout << "ThrowDice= " << atk->ThrowDice(D2) << endl;
	cout << "Defense= " << atk->VerifyDefense() << endl;
	enemy01->TakeDamage(dmg);
	enemy01->PrintHealth();
	cout << endl;
	system("PAUSE");

	if (atk)
		delete atk;
	if (mainCharacter)
		delete mainCharacter;
	if (enemy01)
		delete enemy01;
}