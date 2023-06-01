#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <thread>

using namespace std;

bool isRed(int number) {
	// Check if the number is red
	if (number == 1 || number == 3 || number == 5 || number == 7 || number == 9 || number == 12 || number == 14 || number == 16 || number == 18 || number == 19 || number == 21 || number == 23 || number == 25 || number == 27 || number == 30 || number == 32 || number == 34 || number == 36)
		return true;
	else
		return false;
}

void setConsoleFontSize(int size)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &fontInfo);
	fontInfo.dwFontSize.Y = size; // Set the font size
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &fontInfo);
}

void spinRoulette() {
	std::cout << "Spinning the roulette wheel..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        3" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        2" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        1" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        Spinning!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void spinSlots() {
	std::cout << "Spinning the slots..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        3" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        2" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        1" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        Spinning!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void flipCoin() {
	std::cout << "Flipping the coin..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        3" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        2" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        1" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "        Flipping!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void disableConsoleScrolling()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);
	bufferInfo.dwSize.Y = bufferInfo.srWindow.Bottom + 1;
	SetConsoleScreenBufferSize(consoleHandle, bufferInfo.dwSize);
}

void displayCard(int value)
{
	const string suits[] = { "S", "C", "H", "D" };  // Spades, Clubs, Hearts, Diamonds
	const string ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };  // Ace, 2-10, Jack, Queen, King

	int suit = (value - 1) / 13;
	int rank = (value - 1) % 13;

	cout << " ___ " << endl;
	cout << "|" << ranks[rank] << "  |" << endl;
	cout << "| " << suits[suit] << " |" << endl;
	cout << "|__" << ranks[rank] << "|" << endl;
}

int calculateTotalPoints(const vector<int>&hand) {
	// Calculate the total points in the hand
	int totalPoints = 0;
	bool hasAce = false;
	for (int card : hand) {
		int rank = (card - 1) % 13 + 1;
		if (rank > 10) {
			totalPoints += 10; // Face cards are worth 10 points
		}
		else if (rank == 1) {
			totalPoints += 11; // Ace is worth 11 points initially
			hasAce = true;
		}
		else {
			totalPoints += rank;
		}
	}

	// Adjust the value of Ace if necessary
	if (hasAce && totalPoints > 21) {
		totalPoints -= 10;
	}

	return totalPoints;
}

void clearScreen() {
	system("cls");
}

int main() {
	int balance = 1000;
	srand(static_cast<unsigned int>(time(0))); // Explicit cast to unsigned int
	disableConsoleScrolling();
	setConsoleFontSize(16);

	std::cout << "Welcome to the Casino!" << std::endl;
	std::cout << "Your current balance is $" << balance << std::endl;

	std::ifstream file("balance.txt"); // Open the file for reading

	if (file) {
		file >> balance; // Read the balance from the file
		file.close(); // Close the file
	}

	while (balance > 0) {
		clearScreen();
		std::cout << std::endl;
		std::cout << "----- MENU -----" << std::endl;
		std::cout << "Balance: $" << balance << std::endl; // Display the balance
		std::cout << "1. Play Blackjack" << std::endl;
		std::cout << "2. Coin Flip" << std::endl;
		std::cout << "3. Slots" << std::endl;
		std::cout << "4. roulette" << std::endl;
		std::cout << "5. Quit" << std::endl;
		std::cout << "" << std::endl;

		int choice;
		std::cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			clearScreen();
			std::cout << "----- BLACKJACK -----" << std::endl;
			std::cout << "Your current balance is $" << balance << std::endl; // Display the balance
			std::cout << "Enter your bet amount: ";
			int bet;
			cin >> bet;

			if (bet > balance) {
				std::cout << "Insufficient balance. Please place a smaller bet." << std::endl;
				break;
			}

			// Initialize the deck
			vector<int> deck;
			for (int i = 1; i <= 52; i++) {
				deck.push_back(i);
			}

			// Shuffle the deck
			random_shuffle(deck.begin(), deck.end());

			// Deal initial cards
			vector<int> playerHand;
			vector<int> dealerHand;

			playerHand.push_back(deck.back());
			deck.pop_back();
			dealerHand.push_back(deck.back());
			deck.pop_back();
			playerHand.push_back(deck.back());
			deck.pop_back();

			// Game loop
			bool playerTurn = true;
			bool gameOver = false;

			while (!gameOver) {
				clearScreen();
				cout << endl;
				cout << "----- BLACKJACK -----" << endl;
				cout << "Balance: $" << balance << endl; // Display the balance
				cout << endl;

				cout << "Dealer's Hand: " << endl;
				displayCard(dealerHand[0]); // Display only the first card of the dealer's hand
				cout << "Total Points: " << calculateTotalPoints(dealerHand) << endl;
				cout << endl;

				cout << "Your Hand: " << endl;
				for (int card : playerHand) {
					displayCard(card); // Display each card in the player's hand
				}
				cout << "Total Points: " << calculateTotalPoints(playerHand) << endl;
				cout << endl;

				if (playerTurn) {
					char action;
					cout << "Choose an action: (H)it or (S)tand: ";
					cin >> action;

					if (action == 'H' || action == 'h') {
						playerHand.push_back(deck.back());
						deck.pop_back();

						if (calculateTotalPoints(playerHand) > 21) {
							gameOver = true;
							playerTurn = false;
						}
					}
					else if (action == 'S' || action == 's') {
						playerTurn = false;
					}
				}
				else {
					if (calculateTotalPoints(dealerHand) < 17) {
						dealerHand.push_back(deck.back());
						deck.pop_back();

						if (calculateTotalPoints(dealerHand) > 21) {
							gameOver = true;
						}
					}
					else {
						gameOver = true;
					}
				}
			}

			clearScreen();
			cout << endl;
			cout << "----- BLACKJACK -----" << endl;
			cout << "Balance: $" << balance << endl; // Display the balance
			cout << endl;

			cout << "Dealer's Hand: " << endl;
			for (int card : dealerHand) {
				displayCard(card); // Display each card in the dealer's hand
			}
			cout << "Total Points: " << calculateTotalPoints(dealerHand) << endl;
			cout << endl;

			cout << "Your Hand: " << endl;
			for (int card : playerHand) {
				displayCard(card); // Display each card in the player's hand
			}
			cout << "Total Points: " << calculateTotalPoints(playerHand) << endl;
			cout << endl;

			int playerTotal = calculateTotalPoints(playerHand);
			int dealerTotal = calculateTotalPoints(dealerHand);

			// Determine the winner
			if (playerTotal > 21) {
				std::cout << "Player busts! You lose $" << bet << std::endl;
				balance -= bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (dealerTotal > 21) {
				std::cout << "Dealer busts! You win $" << bet << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (playerTotal == dealerTotal) {
				std::cout << "Push! It's a tie." << std::endl;
			}
			else if (playerTotal > dealerTotal) {
				std::cout << "Player wins! You win $" << bet << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else {
				std::cout << "Dealer wins! You lose $" << bet << std::endl;
				balance -= bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}

			std::cout << "Your new balance is $" << balance << std::endl;
			cin.ignore(); // Ignore any remaining characters in the input buffer
			std::cout << "Press Enter to continue...";
			cin.get(); // Wait for the user to press Enter
			break;
		}
		case 2: {
			clearScreen();
			std::cout << "----- COIN FLIP -----" << std::endl;
			std::cout << "Your current balance is $" << balance << std::endl; // Display the balance
			std::cout << "Enter your bet amount: ";
			int bet;
			cin >> bet;

			if (bet > balance) {
				std::cout << "Insufficient balance. Please place a smaller bet." << std::endl;
				break;
			}

			std::cout << "Choose heads (0) or tails (1): ";
			int choice;
			cin >> choice;

			flipCoin();

			int result = rand() % 2;  // Generate a random result (0 or 1)

			if (choice == result) {
				std::cout << "Congratulations! You won $" << bet << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else {
				std::cout << "Oops! You lost $" << bet << std::endl;
				balance -= bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}

			std::cout << "Your new balance is $" << balance << std::endl;
			cin.ignore(); // Ignore any remaining characters in the input buffer
			std::cout << "Press Enter to continue...";
			cin.get(); // Wait for the user to press Enter
			break;
		}
		case 3: {
			clearScreen();
			std::cout << "----- SLOTS -----" << std::endl;
			std::cout << "Your current balance is $" << balance << std::endl; // Display the balance
			std::cout << "Enter your bet amount: ";
			int bet;
			cin >> bet;

			if (bet > balance) {
				std::cout << "Insufficient balance. Please place a smaller bet." << std::endl;
				break;
			}

			// Spin the slots
			int slot1 = rand() % 10 + 1;
			int slot2 = rand() % 10 + 1;
			int slot3 = rand() % 10 + 1;

			spinSlots();

			std::cout << "===============" << std::endl;
			std::cout << "Slots: " << slot1 << "|" << slot2 << "|" << slot3 << std::endl;
			std::cout << "===============" << std::endl;

			if (slot1 == slot2 && slot1 == slot3) {
				int winnings = bet * 10;
				std::cout << "Jackpot! You won $" << winnings << std::endl;
				balance += winnings;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (slot1 == slot2 || slot1 == slot3 || slot2 == slot3) {
				int winnings = bet * 2;
				std::cout << "Congratulations! You won $" << winnings << std::endl;
				balance += winnings;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else {
				std::cout << "Sorry, you lost $" << bet << std::endl;
				balance -= bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}

			std::cout << "Your new balance is $" << balance << std::endl;
			cin.ignore(); // Ignore any remaining characters in the input buffer
			std::cout << "Press Enter to continue...";
			cin.get(); // Wait for the user to press Enter
			break;
		}
		case 4: {
			// Play Roulette
			clearScreen();
			std::cout << "----- ROULETTE -----" << std::endl;
			std::cout << "Your current balance is $" << balance << std::endl; // Display the balance
			std::cout << "Enter your bet amount: ";
			int bet;
			cin >> bet;

			if (bet > balance) {
				std::cout << "Insufficient balance. Please place a smaller bet." << std::endl;
				break;
			}

			std::cout << "1. Bet on Odds" << std::endl;
			std::cout << "2. Bet on Evens" << std::endl;
			std::cout << "3. Bet on Red" << std::endl;
			std::cout << "4. Bet on Black" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter your choice: ";
			std::cin >> choice;

			// Spin the roulette wheel
			spinRoulette();

			// Generate a random number between 0 and 36
			srand(static_cast<unsigned int>(time(0)));
			int result = rand() % 37;

			std::cout << "The roulette landed on " << result << "." << std::endl;

			if (choice == '1' && result % 2 != 0) {
				std::cout << "You win! The number is odd." << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (choice == '2' && result % 2 == 0) {
				std::cout << "You win! The number is even." << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (choice == '3' && isRed(result)) {
				std::cout << "You win! The number is red." << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else if (choice == '4' && !isRed(result)) {
				std::cout << "You win! The number is black." << std::endl;
				balance += bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}
			else {
				std::cout << "You lose!" << std::endl;
				balance -= bet;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file
			}

			std::cout << "Your new balance is $" << balance << std::endl;
			cin.ignore(); // Ignore any remaining characters in the input buffer
			std::cout << "Press Enter to continue...";
			cin.get(); // Wait for the user to press Enter
			break;
		}
		case 5: {
			std::cout << "Thank you for playing!" << std::endl;
			std::cin.ignore(); // Ignore the newline character in the input buffer

			std::ofstream outFile("balance.txt");
			outFile << balance;
			outFile.close();

			exit(0);
		}
		case 6: {
			clearScreen();
			std::cout << "----- MODIFY BALANCE -----" << std::endl;
			std::cout << "Your current balance is $" << balance << std::endl; // Display the balance
			std::cout << "What do you want to do with your balance?" << std::endl;
			std::cout << "1. Add" << std::endl;
			std::cout << "2. Remove" << std::endl;
			std::cout << "3. Set" << std::endl;
			std::cout << "4. Back to Menu" << std::endl;

			int modifyChoice;
			cin >> modifyChoice;

			switch (modifyChoice) {
			case 1: {
				std::cout << "Enter the amount you want to add to the balance: ";
				int addAmount;
				cin >> addAmount;
				balance += addAmount;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file

				std::cout << "Added $" << addAmount << " to the balance." << std::endl;

				std::cout << "Your new balance is $" << balance << std::endl;
				cin.ignore(); // Ignore any remaining characters in the input buffer
				std::cout << "Press Enter to continue...";
				cin.get(); // Wait for the user to press Enter
				break;
			}
			case 2: {
				std::cout << "Enter the amount you want to remove from the balance: ";
				int removeAmount;
				cin >> removeAmount;
				if (removeAmount > balance) {
					std::cout << "Invalid amount. Cannot remove more than the current balance." << std::endl;
				}
				else {
					balance -= removeAmount;

					std::ofstream outFile("balance.txt"); // Open the file for writing
					outFile << balance; // Write the updated balance to the file
					outFile.close(); // Close the file

					std::cout << "Removed $" << removeAmount << " from the balance." << std::endl;
				}
				std::cout << "Your new balance is $" << balance << std::endl;
				cin.ignore(); // Ignore any remaining characters in the input buffer
				std::cout << "Press Enter to continue...";
				cin.get(); // Wait for the user to press Enter
				break;
			}
			case 3: {
				std::cout << "Enter the new balance amount: ";
				cin >> balance;

				std::ofstream outFile("balance.txt"); // Open the file for writing
				outFile << balance; // Write the updated balance to the file
				outFile.close(); // Close the file

				std::cout << "Balance set to $" << balance << "." << std::endl;
				cin.ignore(); // Ignore any remaining characters in the input buffer
				std::cout << "Press Enter to continue...";
				cin.get(); // Wait for the user to press Enter
				break;
			}
			case 4: {
				break; // Go back to the main menu
			}
			default: {
				std::cout << "Invalid choice. Please try again." << std::endl;
				break;
			}
			}
			break;
		}
		default: {
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}
		}
	}

	std::ofstream outFile("balance.txt");
	outFile << balance;
	outFile.close();

	std::cout << "You have run out of balance. Goodbye!" << std::endl;
	std::cin.ignore(); // Ignore the newline character in the input buffer
	exit(0);
}