# what is going on

## base

05-engine-game-app-dev-environment

## what's new

Engine library:

* input modes and keymaps

Game library:

* ???

App executable:

* ???

## execution logic

0. Doctest integration with dynamic library testing scenario 
1. test dynamic linkage at entrypoint  
2. run "uniform" application logic (currently targeting Linux only)

## application logic

0. assets (check & load to memory)
1. engine (init | Configure)
2. go into engine execution flow & provide exit callback

## engine logic

0. be inited and configured
1. Configure services
2. run main loop

## main loop sequence

0. event service
1. delta
2. update service
3. window processing
    0. content rendering
    1. imgui rendering
    2. swap buffers
4. terminal service

Current game level is a context for the main loop.

Previous text-only engine version had no loop as text based games have it's own story graph.
The simplest solution is to define a game level as a term for any possible asset driven engine usage.
So, the "menu" concept will be realised as a game level.
Menu can be realised as interactive 2d/3d world visualization (like regular game room) or just using gui service (imgui).
Game room can be realised as closed-space or open world - engine will care of it.  

## how to run

```bash
cd /scripts
./run_build_d_vvv.sh
```

* copy assets directory from 00-common into directory where app.out is located;

* Run app.out from terminal in Debug or Test folder in install directory.

TODO: fix assets directory mounting
