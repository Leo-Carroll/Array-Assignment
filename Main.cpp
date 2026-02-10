#include <iostream>
#include <print>
#include <random>
#include <conio.h>

#include "Sorting.h"

static void ClearScreen() {
	std::print("\033[2J\033[1;1H");
}

static void WaitForInput() {
	std::print("\nPress anything to continue...\n");
	char c = _getch();
}

static int GetInt(int min, int max) {
	while (true) {
		int userInput = 0;
		if (!(std::cin >> userInput)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::print("Invalid input. Please enter a valid integer value between {} and {}.\n", min, max);
		}
		else if (userInput < min || userInput > max) {
			std::print("Invalid input. Please enter a valid integer value between {} and {}.\n", min, max);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return userInput;
		}
	}
}

static int GetInt(int min) {
	while (true) {
		int userInput = 0;
		if (!(std::cin >> userInput)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::print("Invalid input. Please enter a valid integer value greater than {}.\n", min);
		}
		else if (userInput < min) {
			std::print("Invalid input. Please enter a valid integer value greater than {}.\n", min);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return userInput;
		}
	}
}

static int GetInt() {
	while (true) {
		int userInput = 0;
		if (!(std::cin >> userInput)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::print("Invalid input. Please enter a valid integer value.\n");
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return userInput;
		}
	}
}

std::random_device rd;
std::mt19937 rng(rd());

static int GetRandomInt(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

class Program {
private:
	void DisplayArray() const {
		ClearScreen();
		std::print("==========  Display Array  ==========\n");
		for (size_t i = 0; i < m_Values.Size(); ++i) {
			std::print("{}{}", m_Values[i], (i + 1 < m_Values.Size()) ? ", " : "");
			if (i != 0 && i % 10 == 0) {
				std::print("\n");
			}
		}
		WaitForInput();
	}

	void RandomizeArray(int minValue, int maxValue) {
		size_t prevSize = m_Values.Size();
		m_Values.Clear();
		for (size_t i = 0; i < prevSize; ++i) {
			m_Values.PushBack(GetRandomInt(minValue, maxValue));
		}
	}

	size_t GetSmallestValueIndex() const {
		size_t smallestValueIndex = 0;
		for (size_t i = 0; i < m_Values.Size(); ++i) {
			if (m_Values[i] < m_Values[smallestValueIndex]) {
				smallestValueIndex = i;
			}
		}
		return smallestValueIndex;
	}

	int GetSmallestValue() const {
		size_t smallestValueIndex = 0;
		for (size_t i = 0; i < m_Values.Size(); ++i) {
			if (m_Values[i] < m_Values[smallestValueIndex]) {
				smallestValueIndex = i;
			}
		}
		return m_Values[smallestValueIndex];
	}

	double GetAverageOfValues() const {
		int result = 0;
		for (size_t i = 0; i < m_Values.Size(); ++i) {
			result += m_Values[i];
		}
		return static_cast<double>(result) / static_cast<double>(m_Values.Size());
	}

	void HandleMainMenu(bool& running) {
		ClearScreen();
		std::print(
			"==========  Main Menu  ==========\n"
			"   1. Display Array\n"
			"   2. Randomize Array\n"
			"   3. Get Smallest Value Index\n"
			"   4. Get Smallest Value\n"
			"   5. Get Average of Values\n"
			"   6. Sort Values\n"
			"   7. Change Value at Index\n"
			"   8. Swap Values\n"
			"   9. Change Size\n"
			"   10. Quit Program\n"
		);

		int mainInput = GetInt(1, 10);

		switch (mainInput) {
			case 1:
				DisplayArray();
				break;
			case 2: {
				ClearScreen();
				std::print("==========  Randomize Array  ==========\nEnter Minimum Value: ");
				int minValue = GetInt();
				std::print("Enter Maximum Value: ");
				int maxValue = GetInt();
				RandomizeArray(minValue, maxValue);
				break;
			}
			case 3:
				std::print("\nThe Smallest Value is at Index {}.\n", GetSmallestValueIndex());
				WaitForInput();
				break;
			case 4:
				std::print("\nThe Smallest Value is {}.\n", GetSmallestValue());
				WaitForInput();
				break;
			case 5:
				std::print("\nThe Average of All Values is {:.2f}.\n", GetAverageOfValues());
				WaitForInput();
				break;
			case 6: {
				std::print("   1. Smallest to Largest\n   2. Largest to Smallest\n   3. Cancel Sort\n");
				int sortInput = GetInt(1, 3);
				if (sortInput == 1) {
					Introsort(m_Values, 0, static_cast<int>(m_Values.Size() - 1));
				}
				else if (sortInput == 2) {
					Introsort(m_Values, 0, static_cast<int>(m_Values.Size() - 1));
					ReverseVector(m_Values);
				}
				break;
			}
			case 7: {
				std::print("Enter Index (1-{}): ", m_Values.Size());
				int indexInput = GetInt(1, static_cast<int>(m_Values.Size()));
				std::print("Enter New Value: ");
				int valueInput = GetInt();
				int prevValue = m_Values[indexInput - 1];
				m_Values[indexInput - 1] = valueInput;
				std::print("The value at index {} had been changed from {} to {}.\n", indexInput, prevValue, valueInput);
				WaitForInput();
				break;
			}
			case 8: {
				std::print("Enter First Index (1-{}): ", m_Values.Size());
				int index1 = GetInt(1, static_cast<int>(m_Values.Size()));
				std::print("Enter Second Index: (1-{}): ", m_Values.Size());
				int index2 = GetInt(1, static_cast<int>(m_Values.Size()));
				int temp = m_Values[index1 - 1];
				m_Values[index1 - 1] = m_Values[index2 - 1];
				m_Values[index2 - 1] = temp;
				break;
			}
			case 9: {
				std::print("Enter New Size (must be > 0): ");
				int newSize = GetInt(1);
				Vector<int> copy = m_Values;
				m_Values = Vector<int>(newSize);
				for (size_t i = 0; i < m_Values.Capacity(); ++i) {
					if (i < copy.Size()) {
						m_Values.PushBack(copy[i]);
					}
					else {
						m_Values.PushBack(0);
					}
				}
				break;
			}
			case 10:
				running = false;
				break;
		}
	}
private:
	Vector<int> m_Values;

public:
	Program() {
		const size_t STARTING_SIZE = 10;
		for (size_t i = 0; i < STARTING_SIZE; ++i) {
			m_Values.PushBack(static_cast<int>(i));
		}
	}

	void Run() {
		bool programRunning = true;
		while (programRunning) {
			HandleMainMenu(programRunning);
		}
	}
};

int main() {
	Program program;
	program.Run();
}
