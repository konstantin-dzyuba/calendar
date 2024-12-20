#include <iostream>
#include <iomanip>
#include <array>
#include <string>

#define WIDTH 4

using namespace std;

const array<string, 12> months = { "ЯНВАРЬ", "ФЕВРАЛЬ", "МАРТ", "АПРЕЛЬ", "МАЙ", "ИЮНЬ", "ИЮЛЬ", "АВГУСТ", "СЕНТЯБРЬ", "ОКТЯБРЬ", "НОЯБРЬ", "ДЕКАБРЬ" };
const array<string, 7> days = { "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС" };
const array<int, 12> month_days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const string message_welcome = "Добро пожаловать";
const string message_format = "Введите дату в формате ММ ГГГГ";
const string message_year = "Год должен быть в диапазоне от 1919 до 2069";
const string message_month = "Месяц должен быть в диапазоне от 1 до 12";
const string message_exit = "Введите exit для выхода";
const string message_bye = "До свидания!";

bool leap_year(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

int first_day(int month, int year) {
	int days = 2;
	while (month-- > 0) {
		days += month_days.at(month);
		if (leap_year(year) && month == 1) {
			days++;
		}
	}

	while (year-- > 1919) {
		days += 365;

		if (leap_year(year)) {
			days++;
		}
	}

	return days % 7;
}

void calendar(int month, int year) {
	cout << months.at(month) << ' ' << year << endl;
	for (int i = 0; i < days.size(); i++) {
		cout << setw(WIDTH) << days.at(i);
	}
	cout << endl;

	int first = first_day(month, year);

	for (int i = 1; i <= month_days.at(month) + first + (month == 1 && leap_year(year) ? 1 : 0); i++) {
		cout << setw(WIDTH);

		if (i - first > 0) {
			cout << i - first;
		} else {
			cout << ' ';
		}

		if (i % 7 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

void test_first_day() {
	array<int, 12> test_set_1919 = { 2, 5, 5, 1, 3, 6, 1, 4, 0, 2, 5, 0 };
	array<int, 12> test_set_1920 = { 3, 6, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2 };
	array<int, 12> test_set_1921 = { 5, 1, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3 };
	array<array<int, 12>, 4> test_set = { test_set_1919, test_set_1920, test_set_1921 };
	for (int i = 0; i < test_set.size(); i++) {
		cout << i + 1919 << endl;
		for (int j = 0; j < 12; j++) {
			cout << (first_day(j, 1919 + i) == test_set.at(i).at(j)) << ' ' << months.at(j) << ' ' << first_day(j, 1919 + i) << ' ' << test_set.at(i).at(j) << endl;
		}
		cout << endl;
	}
}

int main() {
	setlocale(0, "");

	cout << message_welcome << endl << message_year << endl << message_month << endl << message_exit << endl << message_format << endl;

	while (true) {
		cout << endl;
		string input;
		getline(cin, input);

		if (input == "exit") {
			cout << message_bye << endl;
			return 0;
		}

		if (input.size() != 7) {
			cout << message_format << endl;
			continue;
		}
		int month = stoi(input.substr(0, 2));

		if (month < 1 || month > 12) {
			cout << message_month << endl;
			continue;
		}
		int year = stoi(input.substr(3));

		if (year < 1919 || year > 2069) {
			cout << message_year << endl;
			continue;
		}

		calendar(month - 1, year);
	}
}
