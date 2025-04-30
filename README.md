# ChessEngine

A C++ chess engine project built from scratch with the goal of understanding and implementing the core components of chess programming — including board representation, move generation, search algorithms, and evaluation.  
This is an exploratory project inspired by the [VICE engine](https://github.com/bluefeversoft/vice).

---

## Features Implemented (So Far)

- **120-square board representation** for easy move legality checks.
- **Move generation** (pawns, knights, bishops, rooks, queens, king — with legality).
- **Perft testing** for verifying move generator accuracy.
- **Alpha-beta pruning** for efficient search.
- **Null move pruning** for forward pruning speedup.
- **Quiescence search** to stabilize evaluation in tactical positions.
- **PV (Principal Variation) storage** via a simple hash table.
- **Static evaluation** using piece-square tables and basic material count.
- **Simple text-based command loop**: you can enter moves, undo them, test positions, or run searches interactively.

---

## 📁 Project Structure

```plaintext
src/
├── ChessEngine.cpp           # Main entry point and REPL interface
├── Common/                   # Core engine types, board representation, macros
│   ├── Board.cpp/.h          # Board setup, piece list, state representation
│   ├── BitBoard.cpp/.h       # (Future support) Bitboard utility functions
│   └── Movements/            # Move making, legality, and PV table
│       ├── MakeMove.cpp/.h   # Movemaking and takeback logic
│       ├── PVTable.cpp/.h    # Principal variation logic
│       └── Attack.cpp/.h     # Square attack logic
├── Data/                     # Hashing, validation, FEN parsing
│   ├── Fen.cpp/.h            # FEN string parsing
│   ├── HashKeys.cpp/.h       # Zobrist key generation
│   └── BoardValidator.cpp    # Internal board state checker (assert-heavy)
├── Engine/                   # Core search, evaluation, perft
│   ├── Search.cpp/.h         # Alpha-beta, null move pruning, quiescence
│   ├── Evaluate.cpp/.h       # Piece-square evaluation
│   ├── MoveGenerator.cpp/.h  # Legal move generation
│   └── Perft.cpp/.h          # Perft (performance test) implementation
├── Interface/                # IO helpers
│   ├── InterfaceManager.cpp/.h
│   └── IO.cpp/.h             # Move input/output formatting
```

---

##  How to Use

This is a terminal-based REPL (read-eval-print loop) interface. After running, you can interact via the console:

### Commands:
- `e2e4`, `d2d4`, etc. — input standard algebraic moves to play.
- `t` — take back the last move.
- `p` — run a perft test to depth 5 from the current position.
- `r` — print the PV (principal variation) line.
- `s` — run search using alpha-beta with quiescence and null move pruning.
- `q` — quit the program.

All other inputs are attempted as moves.

---

## 📌 Known Limitations

- ❌ No GUI or UCI/XBoard protocol (currently console-only).
- ❌ Evaluation is very basic (only material and piece-square tables).
- ❌ No checkmate/stalemate detection or draw evaluation beyond repetition/fifty-move rule.
- ❌ No time management (search always runs full depth).
- ❌ No multi-threading or advanced pruning (like LMR, SEE, etc.).

---

## 📚 Future Plans

- Improve evaluation function (mobility, king safety, pawn structure, etc.).
- Add support for UCI protocol to interface with GUIs like Arena or CuteChess.
- Implement LMR (Late Move Reductions), futility pruning, and transposition tables.
- Add full game loop and endgame recognition.
- Expand PV storage and move ordering heuristics.
- Add multi-threading for parallel search (e.g., shared hash table + split points).
- Add opening book support (polyglot or hardcoded lines).
- Integrate tablebase support for perfect endgames (e.g., Syzygy or Gaviota).

---

## 📖 Additional Documentation for some complicated methods.

- [ClearPiece](ChessEngine/docs/ClearPiece.md)
- [CountBits-Bitboard](ChessEngine/docs/CountBits.md)
- [Move encoding](ChessEngine/docs/Move.md)
- [PopBit-Bitboard](ChessEngine/docs/PopBit.md)

---

## Author

Project developed by **Gonzalo Larghero**.

Inspired by [VICE](https://github.com/bluefeversoft/vice), and guided by principles from [ChessProgramming Wiki](https://www.chessprogramming.org/Main_Page).

---

## 🤝 Contributions

This project is currently focused on personal learning and experimentation, but suggestions and discussions are always welcome.
