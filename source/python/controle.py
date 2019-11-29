#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pipes import PipesControl
#import subprocess
import logging
logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.WARNING)

class Control:
    def __init__(self, labels):
        logging.debug("Démarrage de Controle")
        self._pipes = PipesControl()
        self._recordAllModules(labels)
    
    def __del__(self):
        self._stopAllModules()
        logging.debug("Arrêt de Contrôle")
        
    def _recordAllModules(self, labels):
        self._pipes.__enter__()
        self._modules = dict()
        logging.debug("Enregistrement des modules...")
        l = list(labels)
        while l:
            r = self._pipes.readMessage()
            if r:
                try:
                    if (r['verbe'] == "hello"):
                        self._modules[r['source']] = { 'path': r['path'] }
                        logging.debug("Enregistrement du module {} avec le tube nommé {}.".format(r['source'], r['path']))
                        l.remove(r['source'])
                        break
                        
                except KeyError:
                    logging.warning("Message ignoré ({}).".format(r))
                    continue
                except ValueError:
                    logging.error("Nom de module inattendu ({}) !".format(r['source']))
                    raise
                

    def _stopAllModules(self):
        for m in self._modules:
            logging.debug("Commande d'arrêt du module {}".format(m))
            self._pipes.writeMessage(self._modules[m]['path'], { 'source': 'controle', 'verbe': 'fin' })
        self._pipes.__exit__(None, None, None)
    
    def initAll(self):
        for m in self._modules:
            logging.debug("Commande d'initialisation du module {}".format(m))
            self._pipes.writeMessage(self._modules[m]['path'], { 'source': 'controle', 'verbe': 'init' })

if __name__ == "__main__":
    control = Control([ 'deplacement' ])
    control.initAll()

    control = None
