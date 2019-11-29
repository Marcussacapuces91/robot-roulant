#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pipes import PipesModule
import logging
logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.WARNING)

def finir(obj):
    logging.debug("Arrêt commandé du Module deplacement.")
    exit(0)
    
def avancer(obj):
    logging.debug("Commande AVANCER.")

def init(obj):
    logging.debug("Commande d'initialisation du module.")
            
if __name__ == "__main__":
    logging.debug("Démarrage du module deplacement.")
    with PipesModule("deplacement") as pipes:
        pipes.record()
        while True:
            obj = pipes.readMessage()
            if obj:
                logging.debug("Message reçu : {}".format(obj))
                try:
                    switcher = {
                        'fin': finir,
                        'init': init,
                        'avancer': avancer
                    }[obj['verbe']](obj)
                except KeyError:
                    logging.warning("Commande inattendue, message ignoré ({}) !".format(obj))
                    continue
                