# ChessEngine

A C++ chess engine project built from scratch with the goal of understanding and implementing the core components of chess programming — including board representation, move generation, search algorithms, and evaluation.  

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
- **Xboard support** for interface integration.

---

## 📁 Project Structure

```plaintext
src/
├── ChessEngine.cpp           # Main entry point and REPL interface
├── Common/                   # Core engine types, board representation, macros
│   ├── Board.cpp/.h          # Board setup, piece list, state representation
│   ├── BitBoard.cpp/.h       # (Future support) Bitboard utility functions
|   ├── Validate.cpp/h        # Board validation to maintain integrity
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
│   ├── Console.cpp/.h        # Console input loop
│   ├── XBoard.cpp/.h         # XBoard protocol loop
│   ├── GameRules.cpp/.h      # End-game rules
│   └── IO.cpp/.h             # Move input/output formatting
```

---

##  How to Use in Console mode

This is a terminal-based REPL (read-eval-print loop) interface. After running, you can interact via the console after writing the command **console**:

### Commands:
| Command                  | Description |
|--------------------------|-------------|
| `help`                  | Show all available commands |
| `quit`                  | Exit the program |
| `print`                 | Display the current board |
| `move e2e4`             | Manually make a move (UCI-style coordinate input) |
| `new`                   | Start a new game from the initial position |
| `go`                    | Let the engine take over as the side to move |
| `force`                 | Stop engine from thinking (manual mode) |
| `depth x`               | Set search depth (e.g., `depth 5`) |
| `time x`                | Set move time in seconds (e.g., `time 3`) |
| `view`                  | Show current search settings (depth, time) |
| `post` / `nopost`       | Enable/disable engine's thinking output |
| `setboard <FEN>`        | Set up position via FEN string |

All other inputs are attempted as moves.

---

## ♟️ Using with WinBoard (XBoard Protocol)

The engine now supports the **XBoard/WinBoard protocol**, allowing it to interface with graphical user interfaces like [WinBoard](http://www.open-aurec.com/wbforum/WinBoard/WB.4.3.15.zip) or [Arena](https://playwitharena.de/).

To run the engine in **WinBoard**, use the `-fcp` (first chess program) option and point it to your compiled engine executable:

```powershell
Start-Process "C:\Path\To\WinBoard\winboard.exe" `
  -ArgumentList '-fcp', '"C:\Path\To\ChessEngine.exe"'
```
---

## 📌 Known Limitations

- ⚠️ XBoard protocol support is functional but not fully tested — may have quirks depending on the GUI used.
- ❌ Evaluation is very basic (only material and piece-square tables).
- ❌ No multi-threading or advanced pruning (like LMR, SEE, etc.).

---

## 📚 Future Plans

- Improve evaluation function (mobility, king safety, pawn structure, etc.).
- Implement LMR (Late Move Reductions), futility pruning, and transposition tables.
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
