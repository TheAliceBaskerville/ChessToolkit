#include <stdexcept>
#include "MoveFactory.h"
#include "IGameData.h"
#include "ClassicGameData.h"
#include "ChessGame.h"
#include "ChessGameImpl.h"

Move MoveFactory::make(const Position& start, const Position& end, const IGameData& data,
                       const std::optional<Piece>& promotionChoice){
    std::optional<Piece> movedPiece{data.getBoard().getAt(start)};
    std::optional<Piece> capturedPiece{data.getBoard().getAt(end)};
    bool isPawnPromotion{false};
    // TODO: think on better condition for variants
    if (end.getRank() == data.getBoard().getHeight()){
        isPawnPromotion = true;
        if (!promotionChoice.has_value()){
            // TODO: better error message
            throw std::invalid_argument{"Move is promotion, but promotionChoice = std::nullopt is given."};
        }
    }
    else{
        // TODO: think on whether promotionChoice validation here is needed or I could just set it to std::nullopt
    }
    bool isEnPassant{false};
    const ClassicGameData* classicData = dynamic_cast<const ClassicGameData*>(&data);
    if (classicData->canEnPassant() && end == classicData->getEnPassant().value()){
        isEnPassant = true;
    }
    bool isCastling{false};
    std::unordered_set<std::size_t> castlingRemovals{};
    if (movedPiece.value().getType() == PieceType::KING){
        std::function<void(std::size_t, Color)> checkCastling = [&](std::size_t rank, Color side){
            // Queenside
            if (end == Position{3, rank} && classicData->getCastlingRights().at(side, 1)){
                bool flag{true};
                for (std::size_t i{2}; i <= 4; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    isCastling = true;
                }
            }
            // Kingside
            else if (end == Position{7, rank} && classicData->getCastlingRights().at(side, 8)){
                bool flag{true};
                for (std::size_t i{6}; i <= 7; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    isCastling = true;
                }
            }
        };
        if (movedPiece.value().getColor() == Color::WHITE){
            checkCastling(1, Color::WHITE);
        }
        else{
            checkCastling(data.getBoard().getHeight(), Color::BLACK);
        }
        for (std::size_t file : classicData->getCastlingRights().get(movedPiece.value().getColor())){
            castlingRemovals.insert(file);
        }
    }
    else if (movedPiece.value().getType() == PieceType::ROOK &&
             classicData->getCastlingRights().at(movedPiece.value().getColor(), start.getFile())){
        castlingRemovals.insert(start.getFile());
    }
    return Move{start, end, isEnPassant, isPawnPromotion, isCastling, 
                promotionChoice, movedPiece, capturedPiece, castlingRemovals};
}


Move MoveFactory::make(const Position& start, const Position& end, const ChessGame& game,
                       const std::optional<Piece>& promotionChoice){
    return make(start, end, *(game.pImpl->data), promotionChoice);
}