# what is going on

Segregation of duties:
* console app loads assets and provides runtime context.
* engine acts like static library and produces gameplay flow execution.
* game assets are predefined in source code.
* game logic is written in C++ and uses special API.

## relations

* Game core loop, gameplay terms and assets are created independently.
* Engine provides a kind of pipeline to game be played. 
* Application initializes the engine object. 
* Guess number game has statically declared assets in c++ header files, so the simple predefined assets loader may be used.
* Game object configures engine object at runtime, because engine is handled like a ahead of time compiled library.
* It is possible to compile engine and the game together notwithstanding, this approach helps to make preparations for script language embedding.

So being compiled to serve not yet created games, somehow engine have to accept game logic, which includes *what* should be *happened* at game flow defined *time*.
 
1. Reflection
The easiest way to use runtime defined variables is reflection. In case of C++17 it is not yet standardized and is too generic for current project purposes.

2. Mapping
The engine may be allowed to own all variables that the game needs. Simple service should give an ability to declare predefined supported variable types with predefined lifetime (game level or game object).
The trade-off in this solution is *parsing* and *layouts* with templated strings, as variable names may be passed as strings.
Of cause indices may be used instead, but in this case game logic coding will produce awful experience.

3. Templated trait-based interface (kind of nominative interface)
This solution is just a code size bomb. It is similar to creating an engine for each possible variables combination.

4. Skip a step and just embed a scripting language.
It is a wise solution for real-production software products. In some rare cases it is also wise to have an option not to use scripting language and write C++ code.

At this step solution #2 is used.

## where is a Game class?

There is no need in game class. A game is a name of process in which human is involved.
The game is a high level abstraction, the game exists when player uses application to play game.  


    