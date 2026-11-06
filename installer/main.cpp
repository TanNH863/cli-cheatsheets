#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

// ANSI Escape Codes for Styling
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

struct Option {
    std::string name;
    std::string description;
    bool selected;
    std::string command;
};

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    // Define installable components
    std::vector<Option> options = {
        {"Git Configuration", "Set default branch to main and global configs", true, "git config --global init.defaultBranch main"},
        {"Common CLI Utils", "Install curl, htop, jq, tree via package manager", true, "sudo apt-get install -y curl htop jq tree || brew install curl htop jq tree"},
        {"Docker Check", "Verify Docker and Docker Compose installation", false, "docker --version && docker compose version"},
        {"Zsh & Setup", "Setup shell configurations", false, "echo 'Configuring Zsh... (placeholder)'"}
    };

    int choice = 0;
    while (true) {
        clearScreen();
        std::cout << BOLD << CYAN << "==========================================" << RESET << "\n";
        std::cout << BOLD << CYAN << "   🚀 C++ Interactive CLI Setup Wizard    " << RESET << "\n";
        std::cout << BOLD << CYAN << "==========================================" << RESET << "\n\n";
        
        std::cout << "Use " << YELLOW << "[W/S]" << RESET << " or " << YELLOW << "[Up/Down]" << RESET << " to navigate, " 
                  << YELLOW << "[Space]" << RESET << " to toggle, " << YELLOW << "[Enter]" << RESET << " to run.\n\n";

        for (size_t i = 0; i < options.size(); ++i) {
            if ((int)i == choice) {
                std::cout << CYAN << " > " << RESET;
            } else {
                std::cout << "   ";
            }

            // Checkbox indicator
			if (options[i].selected) {
				std::cout << "[" << GREEN << "x" << RESET << "] ";
			}
			else {
				std::cout << "[" << " " << "] ";
			}
            std::cout << BOLD << options[i].name << RESET << " - " << options[i].description << "\n";
        }

        std::cout << "\n(Press 'r' to Run Selected, 'q' to Quit)\n";

        // Read single character input
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            // Enter key pressed without text -> toggle current item or move? 
            // For simplicity in a basic standard loop, let's look at simple input commands:
        }

        if (input == "q" || input == "Q") {
            std::cout << "Exiting installer.\n";
            break;
        } else if (input == "r" || input == "R") {
            // Run installation
            clearScreen();
            std::cout << BOLD << GREEN << "\n📦 Starting Installation...\n" << RESET;
            std::cout << "------------------------------------------\n";

            for (const auto& opt : options) {
                if (opt.selected) {
                    std::cout << "\n--> Running: " << opt.name << "\n";
                    int result = std::system(opt.command.c_str());
                    if (result == 0) {
                        std::cout << GREEN << "    [SUCCESS]" << RESET << "\n";
                    } else {
                        std::cout << RED << "    [FAILED OR SKIPPED]" << RESET << "\n";
                    }
                }
            }

            std::cout << "\n" << BOLD << GREEN << "✨ All selected tasks completed!" << RESET << "\n";
            break;
        } else if (input == " ") {
            // Toggle selection on current row
            options[choice].selected = !options[choice].selected;
        } else if (input == "w" || input == "W") {
            if (choice > 0) choice--;
        } else if (input == "s" || input == "S") {
            if (choice < (int)options.size() - 1) choice++;
        }
    }

    return 0;
}