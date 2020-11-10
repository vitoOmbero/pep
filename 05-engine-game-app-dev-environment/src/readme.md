# what is going on

## branches as subdirectories

this approach is more documentative and code base is easy to be used as notes and to view differencies from other pseudo-branches.
This repo targets prototyping but not product developmnet.

## build targets

Global build targets: 
* *engine* - shared library and tests
* *game* - shared library and tests
* *app* - executable and tests

Engine library: 
* self versioning;
* produces *services* which are C++ wrappers of different libs or built-in features;
* produces *main loop*;
* produces interfaces for *game library* development;
* may produce interfaces for common asset managing polytics realisations (packing & unpacking);
* default assets are built in sources, as there is no game developmant toolchain yet;

Game library:
* self versioning;
* declare asset managing polytics: optional, core, etc;
* declare game features and objects using engine interfaces;
* handles game logic in case using C++ (with or without embedded scripting);
* produce handles to be used in runtime by *app* (extern C);

App executable:
* provides execution runtime context: test app, release client, debuggable client, game development toolchain app, etc;
* realise the asset managing polytics;
* contains the code which is specific for target platform;
* in theory may be written in any language, not C++;


## build pipeline

* the first artifact to be built is *engine library*;
* the second is variant of: engine test app, game lib, both;
* the third is variant of: game test app, target app, both;

    