#include <iostream>
#include <iomanip>
#include <array>
#include <string>

#define WIDTH 4

using namespace std;

const array<string, 12> months = { "ßÍÂÀĞÜ", "ÔÅÂĞÀËÜ", "ÌÀĞÒ", "ÀÏĞÅËÜ", "ÌÀÉ", "ÈŞÍÜ", "ÈŞËÜ", "ÀÂÃÓÑÒ", "ÑÅÍÒßÁĞÜ", "ÎÊÒßÁĞÜ", "ÍÎßÁĞÜ", "ÄÅÊÀÁĞÜ" };
const array<string, 7> days = { "ÏÍ", "ÂÒ", "ÑĞ", "×Ò", "ÏÒ", "ÑÁ", "ÂÑ" };
const array<int, 12> month_days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const string message_welcome = "Äîáğî ïîæàëîâàòü";
const string message_format = "Ââåäèòå äàòó â ôîğìàòå ÌÌ ÃÃÃÃ";
const string message_year = "Ãîä äîëæåí áûòü â äèàïàçîíå îò 1919 äî 2069";
const string message_month = "Ìåñÿö äîëæåí áûòü â äèàïàçîíå îò 1 äî 12";
const string message_exit = "Ââåäèòå exit äëÿ âûõîäà";
const string message_bye = "Äî ñâèäàíèÿ!";

bool leap_year(int year) {
	if (year % 400 == 0) {
		return true;
	} else {
		if (year % 100 == 0) {
			return false;
		} else {
			if (year % 4 == 0) {
				return true;
			}
		}
	}

	return false;
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
	array<int, 12> test_set_1922 = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

	array<array<int, 12>, 4> test_set = { test_set_1919, test_set_1920, test_set_1921, test_set_1922 };

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

	cout << message_welcome << endl;
	cout << message_year << endl;
	cout << message_month << endl;
	cout << message_exit << endl;
	cout << message_format << endl;

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
