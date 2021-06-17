#include <iostream>
#include<cassert>
using namespace std;

class Drob {
private:
	int* m_numerator;
	int* m_denominator;
public:
	Drob() :Drob(1, 1) {}
	Drob(int numerator, int denominator)
		:m_numerator{ new int( numerator ) }, m_denominator{ new int(denominator) }{}
	friend ostream& operator<<(ostream& out, const Drob& drob);
	Drob& setNumerator(int numerator) { *m_numerator = numerator; return *this; }
	Drob& setDenominator(int denominator);
	Drob& operator+(Drob& drob);
	Drob& operator-(Drob& drob);
	Drob& operator*(Drob& drob);
	Drob& operator/(Drob& drob);
	Drob& operator=(Drob& drob);
	~Drob() { delete m_numerator; delete m_denominator; }

};
Drob& Drob::setDenominator(int denominator) {
	*m_denominator = denominator;
	int nod, less;
	do {
		*m_numerator < *m_denominator ? less = *m_numerator : less = *m_denominator;

		for (nod = less; nod > 0; nod--) {
			if (!(*m_numerator % nod) && !(*m_denominator % nod)) {
				*m_numerator /= nod;
				*m_denominator /= nod;
				break;
			}
		}
	} while (nod != 1);
	return *this;
}
Drob& Drob::operator+(Drob& drob) {
	Drob* tmp = new Drob;
	if (*m_denominator == *drob.m_denominator) {
		*tmp->m_numerator = *m_numerator + *drob.m_numerator;
		*tmp->m_denominator = *m_denominator;
	}
	else {
		*tmp->m_numerator = *m_numerator * *drob.m_denominator + *m_denominator * *drob.m_numerator;
		*tmp->m_denominator = *m_denominator * *drob.m_denominator;
	}
	return *tmp;
}
Drob& Drob::operator-(Drob& drob) {
	Drob* tmp  = new Drob;
	if (*m_denominator == *drob.m_denominator) {
		*tmp->m_numerator = *m_numerator - *drob.m_numerator;
		*tmp->m_denominator = *m_denominator;
	}
	else {
		*tmp->m_numerator = *m_numerator * *drob.m_denominator - *m_denominator * *drob.m_numerator;
		*tmp->m_denominator = *m_denominator * *drob.m_denominator;
	}
	return *tmp;
}
Drob& Drob::operator*(Drob& drob) {
	Drob* tmp = new Drob;
	*tmp->m_numerator = *m_numerator * *drob.m_numerator;
	*tmp->m_denominator = *m_denominator * *drob.m_denominator;
	return *tmp;
}
Drob& Drob::operator/(Drob& drob) {
	Drob* tmp = new Drob;
	*tmp->m_numerator = *m_numerator * *drob.m_denominator;
	*tmp->m_denominator = *m_denominator * *drob.m_numerator;
	return *tmp;
}
ostream& operator<<(ostream& out, const Drob& drob) {
	if (*drob.m_denominator == 1) {
		out << *drob.m_numerator;
		return out;
	}
	else if (!(*drob.m_numerator % *drob.m_denominator)) cout << *drob.m_numerator / *drob.m_denominator;
	else {
		out << *drob.m_numerator << "/" << *drob.m_denominator;
		return out;
	}
}
Drob& Drob::operator=(Drob& drob) {
	*m_numerator = *drob.m_numerator;
	setDenominator(*drob.m_denominator);
	return *this;

}
int main()
{
	system("chcp 1251");
	system("cls");
	Drob drob, drob2, result;
	int numerator, denominator, numerator2, denominator2;
	char Operator;
	cout << "Введите числитель первой дроби: ";
	cin >> numerator;
	drob.setNumerator(numerator);
	cout << "Введите знаменатель первой дроби: ";
	cin >> denominator;
	if (denominator == 0) {
		cout << "На ноль делить нельзя!";
		return -1;
	}
	drob.setDenominator(denominator);
	cout << "Введите числитель второй дроби: ";
	cin >> numerator2;
	drob2.setNumerator(numerator2);
	cout << "Введите знаменатель второй дроби: ";
	cin >> denominator2;
	if (denominator2 == 0) {
		cout << "На ноль делить нельзя!";
		return -1;
	}
	drob2.setDenominator(denominator2);
	cout << "Введите действие(+,-,*,/): ";
	cin >> Operator;
	cout << "Результат: ";
	switch (Operator) {
		case '+': 	cout << (result = drob + drob2);
				break;
		case '-': 	cout << (result = drob - drob2);
				break;
		case '*': 	cout << (result = drob * drob2);
			break;
		case '/': 	cout << (result = drob / drob2);
			break;
		default: cout << "Не верное действие. ";
			break;
	}
}

