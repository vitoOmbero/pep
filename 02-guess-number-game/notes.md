# what is going on

Segregation of duties:
* console app
* engine (as a ghost in sources)
* game assets & game logic
* messaging and layout separation

...plus minor fixes.

Your system may have not locale

```bash
locale -a

sudo locale-gen ru_RU
sudo locale-gen ru_RU.UTF-8

sudo update-locale 
```