# Robot roulant

Projet de développement d'un système autonome sous la forme d'une plateforme roulante qui pourra être équipée d'autres modules.
Tous les modules collaboreront autour d'un module de contrôle central.

## Pour démarrer

Cloner l'ensemble du projet dans un répertoire local, vous trouverez l'ensemble des sources du projet dans 3 répertoires :
- /documents : toute la documentation ;
- /sources : tous les codes source, par langage ou destination ;
- /impression 3D : les éléments pour réaliser les impressions (.stl) utilisées dans le prototype.

Voir aussi le paragraphe "Déploiement" où est expliqué comment déployer le projet sur un robot réel.

### Prérequis

Pour fonctionner, il vous faudra :
* une carte Raspberry Pi 3 (mais ça peut fonctionner sur une autre version) ;
* un Arduino Nano (le code peut être adapté à une autre carte).
* installer Python 3, s'il n'y est pas déjà ;
* installer Mosquitto (https://mosquitto.org/download/), ou avoir accès à une instance distante, comme http://www.hivemq.com/demos/websocket-client/ ;
* installer l'IDE Arduino 1.8 depuis le site Arduino ;

### Installing

Détail pas à pas de l'installation du projet pour assurer son développement.

@TODO À faire !

## Lancer les tests

Pour le moment aucun système de test n'a été mis en place.

## Déploiment

Pour déployer ce projet sur une Raspberry PI toute fraiche, il vous faudra :

1. Une Raspbian neuve complète : Raspbian Buster with desktop and recommended software (version Sept. 2019)
   https://www.raspberrypi.org/downloads/raspbian/
2. Se connecter avec le compte Pi et se placer dans le "home" : `cd ~`
3. Cloner le répertoire présent : `git clone https://github/Marcussacapuces91/robot-roulant`
4. Configurer la destination du serveur MQTT (Mosquitto) dans le fichier https://github.com/Marcussacapuces91/robot-roulant/blob/Bascule-vers-MQTT/source/python/mqtt.py#L26
4. Au besoin, flasher le code dans l'Arduino Nano après avoir installé l'IDE Arduino.
5. Installer espeak-ng :
   * `sudo apt-get install -y espeak-ng`
6. Installer des compléments Python avec pip :
   * `pip3 install py-espeak-ng`
   * `pip3 install pyserial`
7. Lancer successivement les modules avec la commande unique : `./start.sh`

C'est tout !

## Construit avec

Pas de dépendance à un autre framework.

## Contribuer

Merci de lire le manifeste [CONTRIBUTING.md](CONTRIBUTING.md) [en] pour avoir les détails de notre code de conduite, et le processus pour nous soumettre des demandes de modifications (*pull requests*).

## Versionnage

Nous utilisons [SemVer](https://semver.org/lang/fr/) pour le versionnage. Vous trouverez chaque version disponible sous forme de [tags dans ce répertoire](https://github.com/Marcussacapuces91/robot-roulant/tags).

## Authors

* **Marc Sibert** - *travail initial* - [Marcussacapuces91](https://github.com/Marcussacapuces91) - Fablab [Lab'Allen](https://lab-allen.fr)

Voir la liste des contributeurs [contributors](https://github.com/Marcussacapuces91/robot-roulant/contributors) ayant participé à ce projet.

## Licence

Ce projet est placé sous licence Apache V2 - Voir le fichier [LICENSE](LICENSE) pour les détails.

## Remerciements

* L'équipe de la Médiathèque de Saint-Michel-sur-Orge qui a soutenu ce projet et Malek en particulier 
* Tous les participants aux ateliers qui ont développés 
* Différentes sources d'inspiration, comme :
  * Gaël LANGEVIN – French InMoov designer - [InMoov.fr](https://inmoov.fr)
  * Omron et son robot mobile : https://industrial.omron.fr/fr/products/mobile-robot
  * Knapp : https://www.knapp.com/fr/solutions/technologies/robotique-et-manutention/

---
Ce document est tiré de https://gist.github.com/PurpleBooth/109311bb0361f32d87a2
