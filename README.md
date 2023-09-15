> **Note**: This plugin started as a Puzzle System but since I realized it can be used for much more, the plan is to update it to make it a more generic Rule Executor (a bit following the idea by Elan Ruskin as he explained in [this GDC Talk](https://www.youtube.com/watch?v=tAbBID3N64A)).

# The Puzzle System

The system is designed to be game-independent and as flexible as possible for designers. It revolves around the `APuzzleManager` which is responsible for managing and checking the state of puzzles in the game. 

## How to Use

### 1. Creating a new PuzzleManager

The PuzzleManager is an Actor, so you can place it directly into your level from the Editor. The system supports more than one Puzzle Manager per level, so it's really up to your needs. You might want to consider splitting your managers when they grow beyond a certain amount of Definitions.

### 2. Setting up Puzzle Definitions

The PuzzleManager needs to know about the puzzles in your game. This is done through Puzzle Definitions. Each puzzle should have its own Puzzle Definition, which contains conditions and actions. You can define these in the Editor, in the PuzzleManager's properties.

A Puzzle Definition is a structured object that contains:

- A list of Puzzle Conditions: These are checks that the PuzzleManager will run to see if a puzzle is solved. Each condition can refer to a specific Actor.
  
- A list of Puzzle Actions: These are the actions that will be executed when a puzzle is solved.

### 3. Triggering Puzzle Checks

In order for a puzzle check to be triggered, an Actor with a `PuzzlePieceComponent` needs to call the `CheckPuzzle` function. This could be done, for example, when a player interacts with the Actor in some way. The PuzzleManager will then check the state of the puzzle associated with that Actor.

### 4. What happens during a Puzzle Check

When a Puzzle Check is triggered, the PuzzleManager goes through the Puzzle Conditions of the Puzzle Definition associated with the Actor. If all conditions are met, it will then execute the actions defined in the Puzzle Actions of that Puzzle Definition.

> **Note**: The PuzzleManager does not tick, which means it won't automatically check puzzles over time. You need to trigger a puzzle check when you think a puzzle might have been solved.

## Additional Components

### Puzzle Piece Component

Each Actor that's part of a puzzle should have a `PuzzlePieceComponent` attached to it. This component is responsible for triggering the puzzle check when necessary (e.g., when the player interacts with the Actor). You need to manually define when the trigger should occur based on other systems in the game. In Atmos each Interaction tries to trigger a check (if the Actor which is targeted by the interaction has a `PuzzlePieceComponent` on itself).

### Puzzle Conditions

`UPuzzleCondition` is a class that defines a specific condition for a puzzle. To create new conditions:

1. Create a Blueprint subclass of `UPuzzleCondition`.
2. Override the `IsConditionMet` function to implement your condition check.

The condition is now ready to be used in a Puzzle Manager. When the `IsConditionMet` function is called, it should return `true` if the condition is met and `false` otherwise.

### Puzzle Actions

`UPuzzleAction` is a class that defines a specific action that should be executed when a puzzle is solved. To create a new action:

1. Create a Blueprint subclass of `UPuzzleAction`.
2. Override the `Execute` function to implement your action.

When the `Execute` function is called, it should perform whatever action you've defined (e.g., opening a door, playing a sound, spawning an item, etc.).

