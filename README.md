# Robot Roulant

Projet de développement d'un système autonome sous la forme d'une plateforme roulante qui pourra être équipée d'autres modules.

Dans cette version (initiale), l'ensemble des modules sont développés sous la forme d'applications Python autonomes qui communiquent au travers de « Tubes Nommés », cette architecture n'interdit pas que les modules puissent utiliser d'autres languages ou technologies.

Un composant spécifique dit **Système de Contrôle** assure une fonction de cerveau et coordonne le fonctionnement des autres modules au-travers de messages échangés. Chaque module déploie un tube nommé portant son nom et y lit les messages émis par le **Système de Contrôle** indiquant des commandes qu'il doit exécuter. Les réponses sont transmises directement au **Système de Contrôle**.

## Système de Contrôle

## Module de Déplacement

## Module de Sythèse vocale

## Module de reconnaissance de forme
