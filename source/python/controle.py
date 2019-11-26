#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pipes import PipesControl
#import subprocess

def stopAll(pipes, modules):
    for k, m in modules.items():
        print("Commande d'arrêt du module {}".format(m))
        pipes.writeMessage(m['path'], { 'source': 'controle', 'verbe': 'fin' })

def main():
    modules = dict()
    with PipesControl() as pipes:
        print("Enregistrement des modules...")
        while True:
            r = pipes.readMessage()
            if r:
                try:
                    if (r['verbe'] == "hello"):
                        modules[r['source']] = { 'path': r['path'] }
                        print("Enregistrement du module {} avec le tube nommé {}.".format(r['source'], r['path']))
                        break
                        
                except KeyError:
                    print("Message ignoré (", end='')
                    print(r, end='')
                    print(") !")
                    continue

        stopAll(pipes, modules)            

if __name__ == "__main__":
    
    print("Démarrage de Controle")
    main()
    print("Arrêt de Contrôle")