#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "variants/Classic/ClassicChessGame.h"
#include "FileConverter.h"

void printGame(const ClassicChessGame& game) {
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "board = [";

    const Board& board = game.getBoard();
    for (int i = 8; i >= 1; --i){
        if (i != 8){
            std::cout << "         [";
        }
        else{
            std::cout << "[";
        }
        for (int j = 1; j <= 8; ++j){
            Position pos{j, i};
            if (board.isExist(pos)){
                if (board.isEmpty(pos)){
                    std::cout << "--";
                }
                else{
                    Piece piece = board.getAt(pos).value();
                    char color;
                    if (piece.getColor() == Color::BLACK){
                        color = 'b';
                    }
                    else{
                        color = 'w';
                    }
                    char type;
                    switch (piece.getType()){
                        case PieceType::PAWN:   type = 'p'; break;
                        case PieceType::KNIGHT: type = 'N'; break;
                        case PieceType::BISHOP: type = 'B'; break;
                        case PieceType::ROOK:   type = 'R'; break;
                        case PieceType::QUEEN:  type = 'Q'; break;
                        case PieceType::KING:   type = 'K'; break;
                        default: throw std::out_of_range{"Unexpected PieceType given."};
                    }
                    std::cout << color << type;
                }
            }
            else{
                std::cout << "xx";
            }
            if (j < 8){
                std::cout << " ";
            }
        }
        if (i > 1){
            std::cout << "]\n";
        }
    }
    std::cout << "]]\n";
    std::cout << "history size = " << game.getHistory().size() << "\n";
    std::cout << "Current turn = " << EnumConverter::toString(game.getCurrentTurn()) << "\n";
    std::cout << "--------------------------------------------------------------------\n";
}

int main(){
    try{
        ClassicChessGame game{};
        std::string input;
        printGame(game);
        while (true){
            std::cout << "Enter command (e.g., 'make e2 e4' or 'undo 1'), or 'q' to quit: ";
            std::getline(std::cin, input);
            if (input == "q"){
                break;
            }
            std::stringstream ss{input};
            std::string command;
            ss >> command;

            if (command == "make") {
                std::string startPosition, endPosition;
                ss >> startPosition >> endPosition;

                if (ss.fail() || startPosition.length() != 2 || endPosition.length() != 2) {
                    std::cout << "Invalid input for 'make' command. Please try again.\n";
                    continue;
                }

                try {
                    int startFile = fileToIndex(startPosition[0]);
                    int startRank = static_cast<int>(startPosition[1] - '0');
                    int endFile = fileToIndex(endPosition[0]);
                    int endRank = static_cast<int>(endPosition[1] - '0');

                    Position start{startFile, startRank};
                    Position end{endFile, endRank};
                    
                    game.makeMove(ClassicMoveConstruct{start, end});
                    printGame(game);
                } catch (const std::exception& error) {
                    std::cout << "Error making move: " << error.what() << '\n';
                }
            } 
            else if (command == "undo") {
                int steps;
                ss >> steps;

                if (ss.fail()) {
                    std::cout << "Invalid input for 'undo' command. Please try again.\n";
                    continue;
                }

                try {
                    game.undoMove(steps);
                    printGame(game);
                } catch (const std::exception& error) {
                    std::cout << "Error undoing move: " << error.what() << '\n';
                }
            } 
            else {
                std::cout << "Unknown command. Use 'make', 'undo', or 'q'.\n";
            }
        }
    }
    catch(const std::exception& error){
        std::cerr << "Unhandled exception in main(): " << error.what() << '\n';
    }
    catch(const std::string& error){
        std::cerr << "Caught std::string exception in main(): " << error << '\n';
    }
    catch (const char* error){
        std::cerr << "Caught string literal exception in main(): " << error << '\n';
    }
    catch(int error){
        std::cerr << "Caught an integer exception in main(): " << error << '\n';
    }
    catch(...){
        std::cerr << "Unknown exception is caught in main()\n";
    }
    
    return 0;
}