# Robot Roulant


Dans cette version (initiale), l'ensemble des modules sont développés sous la forme d'applications Python autonomes qui communiquent au travers de « Tubes Nommés », cette architecture n'interdit pas que les modules puissent utiliser d'autres languages ou technologies.

Un composant spécifique dit **Système de Contrôle** assure une fonction de cerveau et coordonne le fonctionnement des autres modules au-travers de messages échangés. Chaque module déploie un tube nommé portant son nom et y lit les messages émis par le **Système de Contrôle** indiquant des commandes qu'il doit exécuter. Les réponses sont transmises directement au **Système de Contrôle**.

## Système de Contrôle

## Module de Déplacement

## Module de Sythèse vocale

## Module de reconnaissance de forme

---

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
* installer Python 3 ;
* installer l'IDE Arduino 1.8 depuis le site Arduino ;

Note : à date, les modules Python ne fonctionnent pas sur environnements Windows car il ne supporte pas la fonction os.mkfifo.

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versionnage

Nous utilisons [SemVer](https://semver.org/lang/fr/) pour le versionnage. Vous trouverez chaque version disponible sous forme de [tags dans ce répertoire](https://github.com/Marcussacapuces91/robot-roulant/tags).

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
